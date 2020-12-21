#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Game;

class State {
public:
    bool isKeyReleased {false};
    virtual ~State () {};
    virtual State* HandleTextEntered (const sf::Event& event,
                                      Game& game) = 0;
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      Game& game) = 0;
    virtual State* Update (Game& game) = 0;
    virtual void Enter (Game& game) = 0;
};
