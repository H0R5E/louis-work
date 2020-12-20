#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "gamestate.h"

class PlayState : public GameState {
public:
    GameState* HandleTextEntered (const sf::Event& event,
                                  Game& game) override;
    GameState* HandleKeyReleased (const sf::Event& event,
                                  Game& game) override;
    GameState* Update (Game& game) override;
    void Enter (Game& game) override;
};
