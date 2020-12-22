#pragma once

#include <SFML/Audio.hpp>
#include "command.h"

class SoundCommand : public Command {
private:
    sf::Sound sound;
public:
    void Execute(const sf::Event& event,
                 Game& game) override;
    void Stop () override;
    bool IsCompleted () override;
};
