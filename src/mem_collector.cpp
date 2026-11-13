#include "mem_collector.hpp"

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

MemoryMetrics collect_mem() {
    bool found_total = false;
    bool found_available = false;
    MemoryMetrics mm_unit;
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        std::cerr << "Fail to open meminfo" << '\n';
        return {};
    }
    std::string line;
    std::string key;
    std::uint64_t value{};
    std::string unit;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        if (!(iss>>key>>value)) {
            continue;
        }
        if (key == "MemTotal:") {
            found_total = true;
            mm_unit.total_kb = value;
        }
        if (key == "MemAvailable:") {
            found_available = true;
            mm_unit.available_kb = value;
        }
    }
    if (!found_total || !found_available) {
        std::cout << "memtotal is zero" << '\n';
        return {};
    } else {
        mm_unit.usage_percent = static_cast<double>((mm_unit.total_kb - mm_unit.available_kb)) / mm_unit.total_kb * 100;
    }
    return mm_unit;
}
