#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include <vector>

#include "gamestate.h"

class StartState : public GameState {
private:
    sf::Font titleFont;
    sf::Font msgFont;
    std::vector<sf::Text> phrases;
public:
    StartState ();
    GameState* handleKeyPressed (const sf::Event& event,
                                 Game& game) override;
    void update (Game& game) override;
};
