
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

#include "game.h"
#include "logging.h"
#include "polymorphic_value.h"
#include "sound.h"
#include "window.h"

#include <argparse/argparse.hpp>
#include <boost/stacktrace.hpp>
#include <spdlog/spdlog.h>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <memory>
#include <sstream>

#include <signal.h>

using namespace isocpp_p0201;

void my_signal_handler(int signum) {
    ::signal(signum, SIG_DFL);
    boost::stacktrace::safe_dump_to("./backtrace.dump");
    ::raise(SIGABRT);
}

int main(int argc, char* argv[]) {
    ::signal(SIGSEGV, &my_signal_handler);
    ::signal(SIGABRT, &my_signal_handler);

    argparse::ArgumentParser program("louis");

    program.add_argument("-x")
        .help("run using source tree assets")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-v")
        .help("show logging in console")
        .default_value(false)
        .implicit_value(true);

    program.add_argument("-V")
        .help("show debug logging in console")
        .default_value(false)
        .implicit_value(true);

    try {
        program.parse_args(argc, argv);
    } catch (std::runtime_error const& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }

    bool test_paths{false};
    bool console_log{false};
    bool console_debug{false};

    if (program["-x"] == true) {
        std::cout << "Using local paths" << std::endl;
        test_paths = true;
    }

    if (program["-v"] == true) {
        console_log = true;
    }

    if (program["-V"] == true) {
        console_log = true;
        console_debug = true;
    }

    // Bring up the logger
    setupDefaultLogger(test_paths, console_log, console_debug);

    if (std::filesystem::exists("./backtrace.dump")) {
        std::ifstream ifs("./backtrace.dump");
        std::stringstream ss;

        boost::stacktrace::stacktrace st =
            boost::stacktrace::stacktrace::from_dump(ifs);
        ss << "Previous run crashed:\n" << st << std::endl;
        spdlog::error(ss.str());

        ifs.close();
        std::filesystem::remove("./backtrace.dump");
    }

    spdlog::info("Starting Louis' Work");

    Game my_game{std::make_unique<WindowAdapter>(),
                 make_polymorphic_value<SoundMakerBase, SoundMaker<>>(),
                 test_paths};
    my_game.EventLoop();

    return 0;
}

int WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, char*, int nShowCmd) {
    return main(__argc, __argv);
}
