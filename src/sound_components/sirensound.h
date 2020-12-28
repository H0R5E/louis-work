
#pragma once

#include "component.h"

class SirenSound: public SoundComponent {
public:
    void start (const sf::Event& event,
                Command& command,
                Game& game) override;
    void stop (Command& command) override;
};
