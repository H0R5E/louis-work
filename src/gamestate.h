#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Game;

class GameState {
public:
    virtual ~GameState () {};
    virtual GameState* handleTextEntered (const sf::Event& event,
                                          Game& game) = 0;
    virtual void enter (Game& game) = 0;
};
