#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class SpecialState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Component& scene,
                             Service& service) override;
    State* Update (uniqueComponentVector& scenes, Service& service) override;
    void Enter (uniqueComponentVector& scenes, Service& service) override;
};
