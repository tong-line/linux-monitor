#pragma once
#include <cstdint>

struct CpuTimes {
    std::uint64_t user{};
    std::uint64_t nice{};
    std::uint64_t system{};
    std::uint64_t idle{};
    std::uint64_t iowait{};
    std::uint64_t irq{};
    std::uint64_t softirq{};
    std::uint64_t steal{};
    std::uint64_t guest{};
    std::uint64_t guest_nice{};
};

CpuTimes collect_cpu();
double calculate_cpu_usage();
