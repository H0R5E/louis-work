#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Game;

class Command {
public:
    virtual ~Command () {};
    virtual void execute(const sf::Event& event, Game& game) = 0;
};

