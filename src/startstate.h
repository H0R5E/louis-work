#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "windowstate.h"

class StartState : public WindowState {
private:
    sf::Text text;
    sf::Font font;
public:
    StartState ();
    std::unique_ptr<WindowState> handleKeyPressed (
                                        const sf::Event& event,
                                        sf::RenderWindow& window) override;
    void update (sf::RenderWindow& window) override;
};
