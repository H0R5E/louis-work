#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

class WindowState {
public:
    virtual ~WindowState () {};
    virtual std::unique_ptr<WindowState> handleKeyPressed (
                                                const sf::Event& event,
                                                sf::RenderWindow& window) = 0;
    virtual void update (sf::RenderWindow& window) = 0;
};
