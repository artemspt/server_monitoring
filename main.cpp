#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

struct CpuStats {
    long user;
    long nice;
    long system;
    long idle;
    long iowait;
    long irq;
    long softirq;
    long steal;
};

CpuStats readCpuStats() {
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

long totalCpuTime(const CpuStats& stats) {
    return stats.user + stats.nice + stats.system +
           stats.idle + stats.iowait + stats.irq +
           stats.softirq + stats.steal;
}

long idleTime(const CpuStats& stats) {
    return stats.idle + stats.iowait;
}

double find_cpu_stats() {
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

int main() {
    while (true) {
        double cpu_stats = find_cpu_stats();
        std::cout << cpu_stats << std::endl;
    }

    return 0;
}