
#include <SFML/Graphics.hpp>
#include <memory>
#include <iostream>

#include "game.h"
#include "gamestate.h"

int main() {
    
    Game my_game {};
    
    try {
        my_game.EventLoop();
    } catch (...) {
        return 1;
    }
    
    return 0;
    
}
