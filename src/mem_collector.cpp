#include "mem_collector.hpp"

#include <fstream>
#include <iostream>
#include <pthread.h>
#include <sstream>
#include <string>
#include <iomanip>

MemoryMetrics collect_mem() {
    MemoryMetrics mm_unit;
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        std::cerr << "Fail to open meminfo" << '\n';
        return {};
    }
    std::string line;
    std::string key;
    double value;
    std::string unit;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> key >> value >> unit;
        if (key == "MemTotal:") {
            mm_unit.total_kb = value;
        }
        if (key == "MemAvailable:") {
            mm_unit.avaliable_kb = value;
        }
    }
    if (mm_unit.total_kb <= 0) {
        std::cout << "memtotal is zero" << '\n';
    } else {
        mm_unit.usage_percent = static_cast<double>((mm_unit.total_kb - mm_unit.avaliable_kb)) / mm_unit.total_kb * 100;
        std::cout << std::fixed << std::setprecision(2) << mm_unit.usage_percent << '%' << '\n';
    }
    return mm_unit;
}
