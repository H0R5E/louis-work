
#include <memory>
#include <iostream>
#include <argparse/argparse.hpp>

#include "game.h"
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
    
    bool test_assets {false};
    
    if (program["-x"] == true) {
        std::cout << "Using source tree assets" << std::endl;
        test_assets = true;
    }
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  make_polymorphic_value<SoundMakerBase, SoundMaker<>>(),
                  test_assets};
    my_game.EventLoop();
    
    return 0;
    
}
