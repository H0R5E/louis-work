
#include "game.h"

int main() {
    
    Game my_game {};
    
    try {
        my_game.EventLoop();
    } catch (...) {
        return 1;
    }
    
    return 0;
    
}
