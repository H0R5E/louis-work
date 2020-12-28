
#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Command;
class Game;

class DrawComponent {
public:
    virtual ~DrawComponent () = default;
    virtual void start (const sf::Event& event,
                        Command& command,
                        Game& game) = 0;
    virtual bool update (Command& command, Game& game) = 0;
protected:
    sf::Clock clock;
};

class SoundComponent {
public:
    virtual ~SoundComponent () = default;
    virtual void start (const sf::Event& event,
                        Command& command,
                        Game& game) = 0;
    virtual void update (Command& command, Game& game) {};
    virtual void stop (Command& command) = 0;
protected:
    sf::Clock clock;
};
