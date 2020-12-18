#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "gamestate.h"
#include "command.h"

class PlayState : public GameState {
private:
    std::unique_ptr<Command> command;
public:
    PlayState ();
    GameState* handleTextEntered (const sf::Event& event,
                                  Game& game) override;
    void enter (Game& game) override;
};
