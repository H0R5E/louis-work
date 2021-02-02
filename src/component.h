
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
    Component (const Component& copy) {
        *this = copy;
    }
    Component (Component&& temp) = default; 	
    virtual void setActiveEvent (const sf::Event& event,
                                 Service& service) = 0;
    virtual void setActiveEvent (Service& service) = 0;
    virtual bool update () = 0;
    virtual bool isCompleted () = 0;
    virtual void abort () {}
    virtual void operator() (Service& service) = 0;
    Component& operator= (const Component& copy) {
        if (copy.background) {
            background = std::make_unique<sf::Color>(*copy.background);
        }
        return *this;
    }
    Component& operator= (Component&& temp) = default;
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
    DrawComponent (const DrawComponent& copy) :
            Component(copy) {}
    DrawComponent (DrawComponent&& temp) = default;
    DrawComponent& operator= (const DrawComponent& copy) = default;
    DrawComponent& operator= (DrawComponent&& temp) = default;
};

class SoundComponent : public Component {
public:
    SoundComponent (Service& service) :
        Component (service) {}
    SoundComponent (Service& service,
                    std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)) {};
    SoundComponent (const SoundComponent& copy) :
            Component(copy) {
        if (copy.sound) {
            sound = copy.sound->clone();
        };
    }
    SoundComponent (SoundComponent&& temp) = default;
    Sound* getSoundPtr () {
        return sound.get();
    }
    SoundComponent& operator= (const SoundComponent& copy) {
        Component::operator= (copy);
        if (copy.sound) {
            sound = copy.sound->clone();
        }
        return *this;
    }
    SoundComponent& operator= (SoundComponent&& temp) = default;
protected:
    std::unique_ptr<Sound> sound {nullptr};
};
