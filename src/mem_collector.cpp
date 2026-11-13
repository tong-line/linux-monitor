#include "mem_collector.hpp"

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <string>
#include <iomanip>

void collect_mem() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        std::cerr << "Fail to open meminfo" << '\n';
        return;
    }
    std::string line;
    std::string key;
    double value;
    double mem_usage = 0;
    double mem_total = 0;
    double mem_available = 0;
    std::string unit;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> key >> value >> unit;
        if (key == "MemTotal:") {
            mem_total = value;
        }
        if (key == "MemAvailable:") {
            mem_available = value;
        }
    }
    if (mem_total <= 0) {
        std::cout << "memtotal is zero" << '\n';
    } else {
        mem_usage = (mem_total - mem_available) / mem_total;
        mem_usage = mem_usage * 100;
        std::cout << std::fixed << std::setprecision(2) << mem_usage << '%' << '\n';
    }
}
