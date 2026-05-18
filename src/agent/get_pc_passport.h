//
// Created by artem on 24.04.2026.
//

#ifndef SERVER_MONITORING_GET_PC_PASSPORT_H
#define SERVER_MONITORING_GET_PC_PASSPORT_H


struct passport {
    std::string cpu;
    std::string gpu;
    std::string ssd;
    std::string motherboard;
};

class get_pc_passport {
public:
    std::string get_cpu_passport();
    std::string get_gpu_passport();
    std::string get_ssd_passport();
    std::string get_motherboard_passport();
    void get_all_info();
};



#endif //SERVER_MONITORING_GET_PC_PASSPORT_H
