#pragma once
#include <cstdint>

struct MemoryMetrics {
  std::uint64_t total_kb;
  std::uint64_t avaliable_kb;
  double usage_percent;
};

MemoryMetrics collect_mem();
