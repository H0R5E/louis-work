
#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "sound.h"

// Forward declare
class Service;

class Component {
public:
    Component () = delete;
    Component (Service& service) {};
    Component (Service& service,
               std::unique_ptr<sf::Color>&& background) :
        background(std::move(background)) {};
    virtual void setActiveEvent (const sf::Event& event,
                                 Service& service) = 0;
    virtual void setActiveEvent (Service& service) = 0;
    virtual bool update () = 0;
    virtual bool isCompleted () = 0;
    virtual void abort () {}
    virtual void operator () (Service& service) = 0;
    virtual ~Component () = default;
protected:
    std::unique_ptr<sf::Color> background {nullptr};
    sf::Clock clock;
};

class DrawComponent : public Component {
public:
    DrawComponent (Service& service) :
        Component (service) {}
    DrawComponent (Service& service,
                   std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)) {}
};

class SoundComponent : public Component {
public:
    SoundComponent (Service& service) :
        Component (service) {}
    SoundComponent (Service& service,
                    std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)) {};
    Sound* getSoundPtr () {
        return sound.get();
    }
protected:
    std::unique_ptr<Sound> sound {nullptr};
};
