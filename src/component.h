
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "service.h"
#include "sound.h"

class DrawComponent {
public:
    virtual ~DrawComponent () = default;
    virtual void set_active_event (const sf::Event& event,
                                   Service& service) = 0;
    virtual void set_active_event (Service& service) = 0;
    virtual void draw (Service& service) = 0;
    virtual bool redraw () = 0;
    virtual bool isCompleted () = 0;
protected:
    sf::Clock clock;
};

class SoundComponent {
public:
    virtual ~SoundComponent () = default;
    virtual void set_active_event (const sf::Event& event,
                                   Service& service) = 0;
    virtual void set_active_event (Service& service) = 0;
    virtual void play (Service& service) = 0;
    virtual bool replay () = 0;
    virtual bool isCompleted () = 0;
    Sound* getSoundPtr () {
        return sound.get();
    }
protected:
    sf::Clock clock;
    std::unique_ptr<Sound> sound;
};
