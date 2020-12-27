#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "sound.h"

// Forward declare
class Game;

class Command {
public:
    Command (std::unique_ptr<Sound>&& sound) :
        sound(std::move(sound)) {};
    virtual ~Command () {};
    virtual void Execute(const sf::Event& event, 
                         Game& game) = 0;
    virtual void Stop () = 0;
    virtual bool IsCompleted () = 0;
protected:
    sf::Clock clock;
    std::unique_ptr<Sound> sound;
};
