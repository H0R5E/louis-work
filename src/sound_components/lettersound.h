
#pragma once

#include <memory>

#include "component.h"

class LetterSound: public SoundComponent {
public:
    void set_active_event (const sf::Event& event,
                           Service& service) override;
    void set_active_event (Service& service) override;
    void play (Service& service) override;
    bool replay () override;
    bool isCompleted () override;
private:
    sf::SoundBuffer buffer;
    bool should_replay {true};
};
