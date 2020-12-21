
#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
#include "command.h"
#include "state.h"
#include "startstate.h"
#include "playstate.h"
#include "drawstate.h"
#include "waitstate.h"

class Game {
public:
    static StartState start;
    static PlayState play;
    static DrawState draw;
    static WaitState wait;
    sf::RenderWindow window;
    State* current_state;
    std::unique_ptr<Command> command;
    std::unique_ptr<Command> sound_command;
    Game ();
    void EventLoop ();
};
