#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "service.h"
#include "component.h"

class Command {
public:
    Command (std::unique_ptr<DrawComponent>&& draw_component,
             std::unique_ptr<SoundComponent>&& sound_component) :
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    void Execute(const sf::Event& event, 
                 Service& service);
    void Update (Service& service);
    bool Stop ();
    SoundComponent* getSoundComponentPtr () {
        return sound_component.get();
    }
private:
    std::unique_ptr<DrawComponent> draw_component;
    std::unique_ptr<SoundComponent> sound_component;
};
