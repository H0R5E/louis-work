
#include "SFML/Graphics.hpp"

#include "helpers.h"

bool CtrlC() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::C) &&
           (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::RControl));
}
