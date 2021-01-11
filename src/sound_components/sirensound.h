
#pragma once

#include "component.h"

class SirenSound: public SoundComponent {
public:
    SirenSound (Service& service);
    void set_active_event (const sf::Event& event,
                           Service& service) override {}
    void set_active_event (Service& service) override {}
    void play (Service& service) override;
    bool replay () override;
    bool isCompleted () override;
private:
    bool should_replay {true};
};
