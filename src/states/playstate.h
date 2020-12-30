#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class PlayState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Service& service) override;
    State* HandleTextEntered (const sf::Event& event,
                              Service& service) override;
    void Enter (Service& service) override;
};
