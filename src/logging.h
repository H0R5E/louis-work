
#pragma once

#include <iostream>
#include <stdexcept>
#include <string_view>
#include <spdlog/sinks/basic_file_sink.h>

#include "helpers.h"
#include "pathconfig.h"

void startLogging (const bool& test=false) {
    
    std::string_view log_dir; 
    std::string_view release_dir {LOGS_DIR_RELEASE};
    
    if (test) {
        log_dir = LOGS_DIR_TEST;
    } else if (release_dir == "[APPDATA]") {
        throw std::runtime_error("Not implemented yet");
    } else {
        log_dir = release_dir;
    }
    
    auto log_path = joinPaths(log_dir, "log.txt");
    auto logger = spdlog::basic_logger_mt("file_logger", log_path, true);
    
}
