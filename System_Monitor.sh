#!/bin/bash

RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
CYAN='\033[0;36m'
BOLD='\033[1m'
NC='\033[0m' # No Color

tput civis
trap "tput cnorm; clear; exit 0" INT TERM EXIT

draw_bar() {
    local val=$1
    local color=$2
    local width=22
    local filled=$(awk -v v="$val" -v w="$width" 'BEGIN {printf "%d", (v / 100) * w}')
    local empty=$((width - filled))

    printf "${color}["
    for ((i=0; i<filled; i++)); do printf "■"; done
    printf "${NC}"
    for ((i=0; i<empty; i++)); do printf " "; done
    printf "${color}]${NC}"
}

check_system() {
    # 1. CPU usage
    cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)
    if (( $(echo "$cpu_usage > 80" | bc -l) )); then
        cpu_color=$RED
        cpu_status="CRITICAL"
    else
        cpu_color=$GREEN
        cpu_status="OK   "
    fi

    # 2. Memory usage
    mem_used=$(free | grep Mem | awk '{printf "%.2f", ($3/$2) * 100.0}')
    if (( $(echo "$mem_used > 90" | bc -l) )); then
        mem_color=$RED
        mem_status="CRITICAL"
    elif (( $(echo "$mem_used > 75" | bc -l) )); then
        mem_color=$YELLOW
        mem_status="WARNING "
    else
        mem_color=$GREEN
        mem_status="OK   "
    fi

    # 3. Disk usage
    disk_used=$(df -h / | awk 'NR==2 {print $5}' | sed 's/%//')
    if [ "$disk_used" -gt 90 ]; then
        disk_color=$RED
        disk_status="CRITICAL"
    elif [ "$disk_used" -gt 75 ]; then
        disk_color=$YELLOW
        disk_status="WARNING "
    else
        disk_color=$GREEN
        disk_status="OK   "
    fi

    echo -e "${CYAN}┌────────────────────────────────────────────────────────┐${NC}"
    echo -e "${CYAN}│${BOLD}                 SYSTEM HEALTH CHECK                    ${NC}${CYAN}│${NC}"
    echo -e "${CYAN}├──────────┬──────────────────────────┬──────────┬───────┤${NC}"
    echo -e "${CYAN}│${NC} RESOURCE │ VISUAL USAGE             │ VALUE    │ STATE ${CYAN}│${NC}"
    echo -e "${CYAN}├──────────┼──────────────────────────┼──────────┼───────┤${NC}"

    printf "${CYAN}│${NC} CPU      │ "
    draw_bar "$cpu_usage" "$cpu_color"
    printf " │ %6.2f%%  │ ${cpu_color}${cpu_status}${NC} ${CYAN}│\n${NC}" "$cpu_usage"

    printf "${CYAN}│${NC} Memory   │ "
    draw_bar "$mem_used" "$mem_color"
    printf " │ %6.2f%%  │ ${mem_color}${mem_status}${NC} ${CYAN}│\n${NC}" "$mem_used"

    printf "${CYAN}│${NC} Disk (/) │ "
    draw_bar "$disk_used" "$disk_color"
    printf " │ %6.2f%%  │ ${disk_color}${disk_status}${NC} ${CYAN}│\n${NC}" "$disk_used"

    echo -e "${CYAN}└──────────┴──────────────────────────┴──────────┴───────┘${NC}"
    echo -e "Press ${BOLD}[Ctrl+C]${NC} to exit | Refresh rate: 2s"
}

while true; do
    clear
    check_system
    sleep 2
done
