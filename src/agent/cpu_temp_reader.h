//
// Created by artem on 24.04.2026.
//

#include <string>

#ifndef SERVER_MONITORING_CPU_TEMP_READER_H
#define SERVER_MONITORING_CPU_TEMP_READER_H



class cpu_temp_reader {
public:
    std::string cpu_temp_path;
    std::string find_cpu_temp_path();
    int get_cpu_temp();
};



#endif //SERVER_MONITORING_CPU_TEMP_READER_H
