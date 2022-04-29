#include "util.h"
#include <fstream>
#include <sstream>
#include <iostream>

auto read_whole_file(const char* fname) -> std::string {
    try {
        auto f = std::fstream(fname);
        if(!f)
            throw std::runtime_error("file not found");
        auto iss = std::stringstream{};
        iss << f.rdbuf();
        return iss.str();
    } catch(const std::exception& e) {
        std::cerr << "Error opening file " << fname << ": " << e.what() << std::endl;
        exit(1);
    }
}
