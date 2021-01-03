
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "service.h"
#include "sound.h"

class DrawComponent {
public:
    virtual ~DrawComponent () = default;
    virtual void start (const sf::Event& event,
                        Service& service) = 0;
    virtual void update (Service& service) {};
    virtual bool isCompleted () = 0;
protected:
    sf::Clock clock;
};

class SoundComponent {
public:
    virtual ~SoundComponent () = default;
    virtual void start (const sf::Event& event,
                        Service& service) = 0;
    virtual void update (Service& service) {}
    virtual bool stop () = 0;
    Sound* getSoundPtr () {
        return sound.get();
    }
protected:
    sf::Clock clock;
    std::unique_ptr<Sound> sound;
};
