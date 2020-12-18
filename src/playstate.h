#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "gamestate.h"

class PlayState : public GameState {
public:
    PlayState () {};
    GameState* handleTextEntered (const sf::Event& event,
                                  Game& game) override;
    void enter (Game& game) override;
};
