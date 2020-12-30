#pragma once

#include <SFML/Graphics.hpp>

#include "state.h"

class StartState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Service& service) override;
    State* HandleTextEntered (const sf::Event& event,
                              Service& service) override;
    State* Update (Service& service) override;
    void Enter (Service& service) override;
};
