#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "component.h"

// Forward declare
class Service;

class State {
public:
    bool skipEvents {false};
    virtual ~State () {};
    virtual State* HandleKeyPressed (const sf::Event& event,
                                     Component& scene,
                                     Service& service) {return nullptr;}
    virtual State* HandleTextEntered (const sf::Event& event,
                                      Component& scene,
                                      Service& service) {return nullptr;}
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      Component& scene,
                                      Service& service) {return nullptr;}
    virtual State* Update (Component& scene,
                           Service& service) {return nullptr;}
    virtual std::unique_ptr<Component> Enter (Service& service) {
        return nullptr;
    }
};
