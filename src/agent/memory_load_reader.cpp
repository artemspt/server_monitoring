//
// Created by artem on 23.04.2026.
//

#include <fstream>
#include <sstream>
#include <vector>
#include <cstddef>
#include <charconv>
#include <cmath>

#include "memory_load_reader.h"

namespace {

bool tryParseULL(const std::string& str, uint64_t& out) {
    auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), out);
    return ec == std::errc{};
}

uint64_t extractNumber(const std::string& line) {
    const size_t colonPos = line.find(':');
    if (colonPos == std::string::npos) return 0;

    const size_t start = line.find_first_of("0123456789", colonPos);
    if (start == std::string::npos) return 0;

    const size_t end = line.find(' ', start);
    const std::string valueStr = line.substr(start, end - start);

    uint64_t value = 0;
    if (!tryParseULL(valueStr, value)) {
        return 0;
    }
    return value;
}

std::string readLine(std::ifstream& file) {
    std::string line;
    if (std::getline(file, line)) {
        return line;
    }
    return {};
}

}  // namespace

MemoryStats memory_load_reader::read_memory_stats() {
    std::ifstream file("/proc/meminfo");
    if (!file.is_open()) {
        return {0, 0};
    }

    MemoryStats stats = {0, 0};

    const std::string lineTotal = readLine(file);
    if (!lineTotal.empty()) {
        stats.totalKB = extractNumber(lineTotal);
    }

    readLine(file);

    const std::string lineAvail = readLine(file);
    if (!lineAvail.empty()) {
        stats.availableKB = extractNumber(lineAvail);
    }

    return stats;
}

uint64_t memory_load_reader::find_memory_stats() {
    MemoryStats stats = read_memory_stats();
    uint64_t available_memory = stats.availableKB / 1000.0;
    return available_memory;
}
