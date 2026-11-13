#include <iostream>
#include <fstream>

#include "cpu_collector.hpp"
#include "mem_collector.hpp"

int main() {
    std::cout << "Linux System Monitor" << '\n';
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        std::cerr << "Failed to open /proc/meminfo\n";
        return 1;
    }
    std::string line;
    while (std::getline(file, line)) {
        collect_mem(line);
    }
    collect_cpu();
    return 0;
}
