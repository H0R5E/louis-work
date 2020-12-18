#pragma once

#include <SFML/Graphics.hpp>
#include "command.h"

class SingleLetterCommand : public Command {
private:
    sf::Font font;
public:
    SingleLetterCommand ();
    void execute(const sf::Event& event, Game& game) override;
};
