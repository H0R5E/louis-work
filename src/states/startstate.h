#pragma once

#include <SFML/Graphics.hpp>

#include "state.h"

class StartState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Component& scene,
                             Service& service) override;
    State* HandleTextEntered (const sf::Event& event,
                              polyComponentVector& scenes,
                              Service& service) override;
    State* Update (polyComponentVector& scenes, Service& service) override;
    void Enter (polyComponentVector& scenes, Service& service) override;
};
