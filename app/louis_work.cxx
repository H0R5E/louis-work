
#include "window.h"
#include "game.h"

int main() {
    
    Game my_game {std::make_unique<WindowAdapter>()};
    
    try {
       my_game.EventLoop();
    } catch (...) {
       return 1;
    }
    
    return 0;
    
}
