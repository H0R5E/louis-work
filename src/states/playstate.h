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
                              polyComponentVector& scenes,
                              Service& service) override;
    void Enter (polyComponentVector& scenes, Service& service) override;
};
