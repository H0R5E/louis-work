#pragma once

#include <SFML/Graphics.hpp>
#include "command.h"

class SingleLetterCommand : public Command {
public:
    SingleLetterCommand (std::unique_ptr<Sound>&& sound) :
        Command(std::move(sound)) {};
    void Execute(const sf::Event& event,
                 Game& game) override;
    void Stop () override;
    bool IsCompleted () override;
};
