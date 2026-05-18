//
// Created by artem on 24.04.2026.
//

#include <fstream>
#include <string>
#include <filesystem>
#include <array>
#include <memory>
#include <algorithm>

#include "get_pc_passport.h"

std::string trim(const std::string& s) {
    auto start = s.find_first_not_of(" \t\r\n");
    auto end = s.find_last_not_of(" \t\r\n");
    return (start == std::string::npos) ? "" : s.substr(start, end - start + 1);
}

// cpu (/proc/cpuinfo)
std::string get_pc_passport::get_cpu_passport() {
    std::ifstream file("/proc/cpuinfo");
    std::string line;
    while (std::getline(file, line)) {
        if (line.find("model name") == 0) {
            size_t pos = line.find(':');
            if (pos != std::string::npos)
                return trim(line.substr(pos + 1));
        }
    }
    return "Unknown Processor";
}

// 2. gpu (on lspci)
std::string get_pc_passport::get_gpu_passport() {
    std::array<char, 128> buffer;
    std::string result;
    // serach VGA or 3D
    std::unique_ptr<FILE, decltype(&pclose)> pipe(popen("lspci | grep -E 'VGA|3D'", "r"), pclose);
    if (!pipe) return "GPU Detection Failed";

    if (fgets(buffer.data(), buffer.size(), pipe.get()) != nullptr) {
        result = buffer.data();
        size_t pos = result.find(": ");
        if (pos != std::string::npos) return trim(result.substr(pos + 2));
    }
    return "GPU Not Found";
}


// 4. SSD/HDD (model sys disk)
std::string get_pc_passport::get_ssd_passport() {
    for (const auto& entry : std::filesystem::directory_iterator("/sys/block/")) {
        std::string name = entry.path().filename().string();
        // Игнорируем петлевые устройства (loop)
        if (name.find("loop") == std::string::npos) {
            std::ifstream model_file(entry.path().string() + "/device/model");
            std::string model;
            if (std::getline(model_file, model)) return trim(model);
        }
    }
    return "Storage Not Found";
}

//motherboard (DMI)
std::string get_pc_passport::get_motherboard_passport() {
    std::ifstream vendor_f("/sys/class/dmi/id/board_vendor");
    std::ifstream name_f("/sys/class/dmi/id/board_name");
    std::string vendor, name;
    std::getline(vendor_f, vendor);
    std::getline(name_f, name);

    if (vendor.empty() && name.empty()) return "Motherboard Unknown";
    return trim(vendor) + " " + trim(name);
}

void get_pc_passport::get_all_info() {
    passport object = {"", "", "", ""};
    object.cpu = get_cpu_passport();
    object.gpu = get_gpu_passport();
    object.ssd = get_ssd_passport();
    object.motherboard = get_motherboard_passport();
}
