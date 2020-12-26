#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "state.h"

class StartState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Game& game) override;
    State* HandleTextEntered (const sf::Event& event,
                              Game& game) override;
    State* Update (Game& game) override;
    void Enter (Game& game) override;
};
