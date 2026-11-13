#include <iostream>

#include "cpu_collector.hpp"
#include "mem_collector.hpp"

int main() {
    std::cout << "Linux System Monitor" << '\n';
    collect_mem();
    collect_cpu();
    return 0;
}
