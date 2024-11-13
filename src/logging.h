
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include "helpers.h"
#include "pathconfig.h"

#include <sago/platform_folders.h>
#include <spdlog/sinks/basic_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>

#include <iostream>
#include <sstream>
#include <stdexcept>
#include <string_view>

void setupDefaultLogger(bool const& test = false, bool const& console = false,
                        bool const& console_debug = false) {
    std::string_view log_dir;
    if (test) {
        log_dir = LOGS_DIR_TEST;
    } else {
        log_dir = LOGS_DIR_RELEASE;
    }

    auto abs_log_dir =
        joinPaths(sago::getDataHome(), log_dir).lexically_normal();

    if (!std::filesystem::is_directory(abs_log_dir) ||
        !std::filesystem::exists(abs_log_dir)) {
        std::filesystem::create_directories(abs_log_dir);
    }

    auto log_path = joinPaths(abs_log_dir, "log.txt");
    auto file_sink = std::make_shared<spdlog::sinks::basic_file_sink_mt>(
        log_path.generic_string(), true);
    file_sink->set_pattern("[%H:%M:%S.%f] [%l] %v");
    file_sink->set_level(spdlog::level::debug);

    std::vector<spdlog::sink_ptr> sinks;
    sinks.push_back(file_sink);

    if (console) {
        auto console_sink =
            std::make_shared<spdlog::sinks::stdout_color_sink_mt>();
        console_sink->set_pattern("[%H:%M:%S.%f] [%l] %v");

        if (console_debug) {
            console_sink->set_level(spdlog::level::debug);
        } else {
            console_sink->set_level(spdlog::level::info);
        }

        sinks.push_back(console_sink);
    }

    auto combined_logger = std::make_shared<spdlog::logger>(
        "main_logger", begin(sinks), end(sinks));
    combined_logger->set_level(spdlog::level::debug);
    spdlog::set_default_logger(combined_logger);

    std::stringstream log_msg;
    log_msg << "Logging to file at: " << log_path.generic_string();
    spdlog::debug(log_msg.str());
}
