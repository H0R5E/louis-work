#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class PlayState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Game& game) override;
    State* HandleTextEntered (const sf::Event& event,
                              Game& game) override;
    void Enter (Game& game) override;
};
