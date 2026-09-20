#!/bin/bash

# System monitoring script with colors
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
NC='\033[0m' # No Color

check_system() {
    echo "=== System Health Check ==="
    
    # CPU usage
    cpu_usage=$(top -bn1 | grep "Cpu(s)" | awk '{print $2}' | cut -d'%' -f1)
    if (( $(echo "$cpu_usage > 80" | bc -l) )); then
        echo -e "${RED}CPU: ${cpu_usage}% - CRITICAL${NC}"
    else
        echo -e "${GREEN}CPU: ${cpu_usage}% - OK${NC}"
    fi
    
    # Memory usage (تم تحسينه لعرض رقمين عشريين فقط)
    mem_used=$(free | grep Mem | awk '{printf "%.2f", ($3/$2) * 100.0}')
    if (( $(echo "$mem_used > 90" | bc -l) )); then
        echo -e "${RED}Memory: ${mem_used}% - CRITICAL${NC}"
    elif (( $(echo "$mem_used > 75" | bc -l) )); then
        echo -e "${YELLOW}Memory: ${mem_used}% - WARNING${NC}"
    else
        echo -e "${GREEN}Memory: ${mem_used}% - OK${NC}"
    fi
    
    # Disk usage
    disk_used=$(df -h / | awk 'NR==2 {print $5}' | sed 's/%//')
    if [ $disk_used -gt 90 ]; then
        echo -e "${RED}Disk: ${disk_used}% - CRITICAL${NC}"
    elif [ $disk_used -gt 75 ]; then
        echo -e "${YELLOW}Disk: ${disk_used}% - WARNING${NC}"
    else
        echo -e "${GREEN}Disk: ${disk_used}% - OK${NC}"
    fi
}

# Monitor continuously
while true; do
    clear
    check_system
    sleep 2
done
