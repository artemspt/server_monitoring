//
// Created by artem on 23.04.2026.
//

#ifndef SERVER_MONITORING_CPU_READER_H
#define SERVER_MONITORING_CPU_READER_H

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

class cpu_load_reader {
public:
    CpuStats readCpuStats();
    long totalCpuTime(const CpuStats&);
    long idleTime(const CpuStats&);
    double find_cpu_stats();
};



#endif //SERVER_MONITORING_CPU_READER_H
