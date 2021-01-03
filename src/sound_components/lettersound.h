
#pragma once

#include "component.h"

class LetterSound: public SoundComponent {
public:
    void start (const sf::Event& event,
                Service& service) override;
    bool stop () override;
private:
    sf::SoundBuffer buffer;
};
