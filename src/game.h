
#pragma once

#include <SFML/Graphics.hpp>

#include "gamestate.h"
#include "startstate.h"
#include "playstate.h"

class Game {
public:
    static StartState start;
    static PlayState play;
    sf::RenderWindow window;
    GameState* current_state;
    Game ();
    void EventLoop ();
};
