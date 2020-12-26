#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Game;

class State {
public:
    bool skipEvents {false};
    virtual ~State () {};
    virtual State* HandleKeyPressed (const sf::Event& event,
                                     Game& game) {return nullptr;};
    virtual State* HandleTextEntered (const sf::Event& event,
                                      Game& game) {return nullptr;};
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      Game& game) {return nullptr;};
    virtual State* Update (Game& game) {return nullptr;};
    virtual void Enter (Game& game) {};
};
