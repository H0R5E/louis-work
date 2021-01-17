#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class DrawState : public State {
public:
    bool skipEvents {true};
    State* HandleKeyPressed (const sf::Event& event,
                             Service& service) override;
    State* HandleKeyReleased (const sf::Event& event,
                              Service& service) override;
    State* Update (Service& service) override;
};
