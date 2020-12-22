#pragma once

#include <SFML/Graphics.hpp>
#include "command.h"

class SingleLetterCommand : public Command {
public:
    void Execute(const sf::Event& event,
                 Game& game) override;
    void Stop () override {};
    bool IsCompleted () override;
};
