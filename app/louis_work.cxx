
#include <memory>

#include "sound.h"
#include "window.h"
#include "game.h"
#include "sirensound.h"

int main() {
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  std::make_unique<SoundMaker<>>(),
                  componentMaker<SirenSound>()};
    
    try {
       my_game.EventLoop();
    } catch (...) {
       return 1;
    }
    
    return 0;
    
}
