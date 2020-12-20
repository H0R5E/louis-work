#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "gamestate.h"

class StartState : public GameState {
private:
    sf::Font titleFont;
    sf::Font msgFont;
public:
    StartState ();
    GameState* HandleTextEntered (const sf::Event& event,
                                  Game& game) override;
    GameState* HandleKeyReleased (const sf::Event& event,
                                  Game& game) override;
    GameState* Update (Game& game) override;
    void Enter (Game& game) override;
};
