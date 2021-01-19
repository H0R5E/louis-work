#pragma once

#include <SFML/Graphics.hpp>

#include "state.h"

class StartState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Component& scene,
                             Service& service) override;
    State* HandleTextEntered (const sf::Event& event,
                              Component& scene,
                              Service& service) override;
    State* Update (Component& scene, Service& service) override;
    std::unique_ptr<Component> Enter (Service& service) override;
};
