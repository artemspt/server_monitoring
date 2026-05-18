#include <iostream>
#include <fstream>
#include <string>
#include <cmath>
#include <thread>
#include <chrono>

#include "agent/cpu_load_reader.h"
#include "agent/memory_load_reader.h"


int main() {
    cpu_load_reader cpu_reader;
    memory_load_reader memory_render;
    double cpu_stat = cpu_reader.find_cpu_stats();
    uint64_t memory_stat = memory_render.find_memory_stats();

    //ВЫВОДЫ
    std::cout <<  "CPU >> " << cpu_stat << std::endl;
    std::cout <<  "MEMORY >> " << memory_stat << std::endl;

    return 0;
}