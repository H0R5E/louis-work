#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class GameState;
class Game;

class Command {
public:
    sf::Clock clock;
    virtual ~Command () {};
    virtual void Execute(const sf::Event& event, 
                         Game& game) = 0;
    virtual bool IsCompleted () = 0;
};

