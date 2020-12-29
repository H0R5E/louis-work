#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "sound.h"
#include "component.h"

// Forward declare
class Game;

class Command {
public:
    Command (std::unique_ptr<Sound>&& sound,
             std::unique_ptr<DrawComponent>&& draw_component,
             std::unique_ptr<SoundComponent>&& sound_component) :
        sound(std::move(sound)),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {};
    void Execute(const sf::Event& event, 
                 Game& game);
    void Update (Game& game);
    bool Stop ();
    std::unique_ptr<Sound> sound;
private:
    std::unique_ptr<DrawComponent> draw_component;
    std::unique_ptr<SoundComponent> sound_component;
};
