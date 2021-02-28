
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

    try {
        program.parse_args(argc, argv);
    } catch (const std::runtime_error& err) {
        std::cout << err.what() << std::endl;
        std::cout << program;
        exit(0);
    }
    
    bool test_paths {false};
    
    if (program["-x"] == true) {
        std::cout << "Using local paths" << std::endl;
        test_paths = true;
    }
    
    // Bring up the logger
    startLogging(test_paths);
    spdlog::get("file_logger")->info("Starting Louis' Work");
    spdlog::set_level(spdlog::level::debug);
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  make_polymorphic_value<SoundMakerBase, SoundMaker<>>(),
                  test_paths};
    my_game.EventLoop();
    
    return 0;
    
}
