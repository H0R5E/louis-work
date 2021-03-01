
#include <memory>
#include <iostream>
#include <argparse/argparse.hpp>
#include <spdlog/spdlog.h>

#include "game.h"
#include "logging.h"
#include "sound.h"
#include "window.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

int main(int argc, char *argv[]) {
    
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
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }
    
    bool test_paths {false};
    bool console_log {false};
    bool console_debug {false};
    
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
    startLogging(test_paths, console_log, console_debug);
    spdlog::get("main_logger")->info("Starting Louis' Work");
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  make_polymorphic_value<SoundMakerBase, SoundMaker<>>(),
                  test_paths};
    my_game.EventLoop();
    
    return 0;
    
}
