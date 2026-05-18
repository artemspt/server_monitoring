#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

#include "cpu_load_reader.h"

CpuStats cpu_load_reader::readCpuStats() {
    std::ifstream file("/proc/stat");
    std::string line;
    CpuStats stats = {0, 0, 0, 0, 0, 0, 0, 0};

    if (std::getline(file, line)) {
        std::sscanf(line.c_str(), "cpu %ld %ld %ld %ld %ld %ld %ld %ld",
                   &stats.user, &stats.nice, &stats.system,
                   &stats.idle, &stats.iowait, &stats.irq,
                   &stats.softirq, &stats.steal);
    }
    return stats;
}

long cpu_load_reader::totalCpuTime(const CpuStats& stats) {
    return stats.user + stats.nice + stats.system +
           stats.idle + stats.iowait + stats.irq +
           stats.softirq + stats.steal;
}

long cpu_load_reader::idleTime(const CpuStats& stats) {
    return stats.idle + stats.iowait;
}

double cpu_load_reader::find_cpu_stats() {
    CpuStats prev = readCpuStats();
    std::this_thread::sleep_for(std::chrono::seconds(1));
    CpuStats curr = readCpuStats();
    long totalDiff = totalCpuTime(curr) - totalCpuTime(prev);
    long idleDiff = idleTime(curr) - idleTime(prev);

    if (totalDiff > 0) {
        double cpuUsage = 100.0 * (1.0 - (double)idleDiff / totalDiff);
        cpuUsage = std::trunc(cpuUsage * 100.0) / 100.0;
        return cpuUsage;
    }
    return 0;
}