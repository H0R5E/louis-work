
#pragma once

#include <iostream>
#include <stdexcept>
#include <string_view>
#include <spdlog/sinks/basic_file_sink.h>
#include "spdlog/sinks/stdout_color_sinks.h"

#include "helpers.h"
#include "pathconfig.h"

void startLogging (const bool& test=false,
                   const bool& console=false,
                   const bool& console_debug=false) {
    
    std::string_view log_dir; 
    std::string_view release_dir {LOGS_DIR_RELEASE};
    
    if (test) {
        log_dir = LOGS_DIR_TEST;
    } else if (release_dir == "[APPDATA]") {
        throw std::runtime_error("Not implemented yet");
    } else {
        log_dir = release_dir;
    }
    
    std::vector<spdlog::sink_ptr> sinks;
    
    auto log_path = joinPaths(log_dir, "log.txt");
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
                                                            log_path, true);
    file_sink->set_pattern("[%H:%M:%S.%f] [%l] %v");
    file_sink->set_level(spdlog::level::debug);
    
    sinks.push_back(file_sink);
    
    if (console) {
        
        auto console_sink = std::make_shared<
                                    spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%H:%M:%S.%f] [%l] %v");
        
        if (console_debug) {
            console_sink->set_level(spdlog::level::debug);
        } else {
            console_sink->set_level(spdlog::level::info);
        }
        
        sinks.push_back(console_sink);
        
    }
        
    auto combined_logger = std::make_shared<spdlog::logger>("main_logger",
                                                            begin(sinks),
                                                            end(sinks));
    combined_logger->set_level(spdlog::level::debug);
    spdlog::register_logger(combined_logger);
    
}
