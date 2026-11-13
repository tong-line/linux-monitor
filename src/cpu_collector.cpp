#include <cstdint>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

#include "cpu_collector.hpp"

std::uint64_t get_total_time(const CpuTimes& t) {
    return t.idle + t.iowait + t.irq + t.nice + t.softirq + t.steal + t.system + t.user;
}

std::uint64_t get_idle_time(const CpuTimes& times) {
    return times.idle + times.iowait;
}

double calculate_cpu_usage() {
    static CpuTimes previous{};
    static bool initialized = false;
    CpuTimes current = collect_cpu();
    if (!initialized) {
        previous = current;
        initialized = true;
        return -1.0;
    }
    std::uint64_t current_total = get_total_time(current);
        std::uint64_t previous_total = get_total_time(previous);

        std::uint64_t current_idle = get_idle_time(current);
        std::uint64_t previous_idle = get_idle_time(previous);

        if (current_total < previous_total ||
            current_idle < previous_idle) {
            previous = current;
            return -1.0;
        }

        std::uint64_t delta_total = current_total - previous_total;
        std::uint64_t delta_idle = current_idle - previous_idle;

        previous = current;

        if (delta_total == 0 || delta_idle > delta_total) {
            return -1.0;
        }

        return static_cast<double>(delta_total - delta_idle)
               / delta_total * 100.0;
}
CpuTimes collect_cpu() {
    std::ifstream file("/proc/stat");
    CpuTimes times{};
    if (!file.is_open()) {
        std::cerr << "Fail to open /proc/stat" << '\n';
        return {};
    }
    std::string line;
    std::string label;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        iss >> label;
        if (label == "cpu") {
            iss >> times.user >> times.nice >> times.system >> times.idle
                >> times.iowait >> times.irq >> times.softirq
                >> times.steal >> times.guest >> times.guest_nice;
            break;
        }
    }
    return times;
}
