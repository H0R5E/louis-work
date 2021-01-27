
#include <memory>

#include "sound.h"
#include "window.h"
#include "game.h"
#include "louissound.h"

int main() {
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  std::make_unique<SoundMaker<>>()};
    my_game.EventLoop();
    
    return 0;
    
}
