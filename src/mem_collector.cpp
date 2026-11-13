#include "mem_collector.hpp"

#include <iostream>
#include <sstream>
#include <string>

void collect_mem(const std::string& line) {
    std::istringstream iss(line);
    std::string key;
    long value;
    std::string unit;
    iss >> key >> value >> unit;
    if (key == "MemTotal:") {
        std::cout << "MemTotal: " << value << " " << unit << '\n';
    }
}
