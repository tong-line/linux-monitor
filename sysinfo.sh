#!/bin/bash

username=$(whoami)
hostname=$(hostname)
kernel=$(uname -r)
today=$(date +%F)
current_dir=$(pwd)

echo "User: $username"
echo "Hostname: $hostname"
echo "kernel: $kernel"
echo "Date: $today"
echo "Working Directory: $current_dir"
