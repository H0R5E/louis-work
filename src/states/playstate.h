#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class PlayState : public State {
public:
    State* HandleTextEntered (const sf::Event& event,
                              Game& game) override;
    State* HandleKeyReleased (const sf::Event& event,
                              Game& game) override;
    State* Update (Game& game) override;
    void Enter (Game& game) override;
};
