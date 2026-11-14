#!/bin/bash
mount_point=${1:-/}
threshold=${2:-80}

if [ ! -d "$mount_point" ]; then
    echo "ERROR: Directory does not exist: $mount_point"
    exit 1
fi

if ! [[ "$threshold" =~ ^[0-9]+$ ]]; then
    echo "ERROR: Threshold must be an integer"
    exit 1
fi

if [ "$threshold" -lt 0 ] || [ "$threshold" -gt 100 ]; then
    echo "ERROE: Threshold must be between 0 and 100"
    exit 1
fi


usage=$(df -P "$mount_point" | awk 'NR==2 {gsub(/%/,"", $5); print $5}')
echo "Filesystem: $mount_point"
echo "Disk Usage: ${usage}%"
if [ "$usage" -gt "$threshold" ]; then
    echo "WARNING: Disk uasge is too high"
else
    echo "OK: Disk usage is normal"
fi
