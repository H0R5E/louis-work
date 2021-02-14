#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class WaitState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             polyComponentVector& scenes,
                             Service& service) override;
    State* Update (polyComponentVector& scenes, Service& service) override;
};
