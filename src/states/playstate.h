#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class PlayState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Component& scene,
                             Service& service) override;
    State* HandleTextEntered (const sf::Event& event,
                              uniqueComponentVector& scenes,
                              Service& service) override;
    void Enter (uniqueComponentVector& scenes, Service& service) override;
};
