
#pragma once

#include <SFML/Graphics.hpp>

#include "gamestate.h"
#include "startstate.h"
#include "playstate.h"
#include "drawstate.h"
#include "waitstate.h"
#include "command.h"

class Game {
public:
    static StartState start;
    static PlayState play;
    static DrawState draw;
    static WaitState wait;
    sf::RenderWindow window;
    GameState* current_state;
    std::unique_ptr<Command> command;
    Game ();
    void EventLoop ();
};
