//
// Created by artem on 23.04.2026.
//

#ifndef SERVER_MONITORING_MEMORY_LOAD_READER_H
#define SERVER_MONITORING_MEMORY_LOAD_READER_H

#include <cstdint>

struct MemoryStats {
    uint64_t totalKB;
    uint64_t availableKB;
};

class memory_load_reader {
public:
    MemoryStats read_memory_stats();
    uint64_t find_memory_stats();
};



#endif //SERVER_MONITORING_MEMORY_LOAD_READER_H
