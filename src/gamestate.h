#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Game;

class GameState {
public:
    bool isKeyReleased {false};
    virtual ~GameState () {};
    virtual GameState* HandleTextEntered (const sf::Event& event,
                                          Game& game) = 0;
    virtual GameState* HandleKeyReleased (const sf::Event& event,
                                          Game& game) = 0;
    virtual GameState* Update (Game& game) = 0;
    virtual void Enter (Game& game) = 0;
};
