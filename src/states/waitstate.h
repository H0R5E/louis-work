#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class WaitState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Service& service) override;
    State* Update (Service& service) override;
};
