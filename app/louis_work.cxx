
#include <memory>
#include <iostream>

#include "game.h"
#include "sound.h"
#include "window.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

int main() {
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  make_polymorphic_value<SoundMakerBase, SoundMaker<>>()};
    my_game.EventLoop();
    
    return 0;
    
}
