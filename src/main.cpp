#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <thread>

#include "cpu_collector.hpp"
#include "mem_collector.hpp"

int main() {
    std::cout << "Linux System Monitor" << '\n';
    auto next_time = std::chrono::steady_clock::now();

    while (true) {
        //采集CPU，采集内存，分别输出，然后进行下一轮
        double cpu_usage = calculate_cpu_usage();
        MemoryMetrics metrics = collect_mem();
        std::cout << std::fixed << std::setprecision(2) << "CPU usage percent: " << cpu_usage << "%\n";
        std::cout << std::fixed << std::setprecision(2) << "Memory usage percent: " << metrics.usage_percent << "%\n";
        next_time += std::chrono::seconds(1);
        std::this_thread::sleep_until(next_time);
    }
    return 0;
}
