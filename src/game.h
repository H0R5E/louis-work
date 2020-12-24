
#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

// Forward declare
#include "command.h"
#include "resourceholder.h"
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
    ResourceHolder<sf::Font> font_holder {};
    ResourceHolder<sf::SoundBuffer> buffer_holder {};
    State* current_state;
    std::unique_ptr<Command> command;
    std::unique_ptr<Command> sound_command;
    Game ();
    void EventLoop ();
};
