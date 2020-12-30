#pragma once

#include <SFML/Graphics.hpp>

// Forward declare
class Service;

class State {
public:
    bool skipEvents {false};
    virtual ~State () {};
    virtual State* HandleKeyPressed (const sf::Event& event,
                                     Service& service) {return nullptr;};
    virtual State* HandleTextEntered (const sf::Event& event,
                                      Service& service) {return nullptr;};
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      Service& service) {return nullptr;};
    virtual State* Update (Service& service) {return nullptr;};
    virtual void Enter (Service& service) {};
};
