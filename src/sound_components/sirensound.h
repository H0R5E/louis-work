
#pragma once

#include "component.h"

class SirenSound: public SoundComponent {
public:
    void start (const sf::Event& event,
                Service& service) override;
    bool stop () override;
};
