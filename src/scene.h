#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "service.h"
#include "component.h"

class Scene {
public:
    Scene () = default;
    Scene (std::unique_ptr<DrawComponent>&& draw_component,
           std::unique_ptr<SoundComponent>&& sound_component);
    void Initialize(Service& service);
    void Modify(const sf::Event& event, 
                Service& service);
    void Modify(Service& service);
    bool Ready();
    void Update (Service& service);
    SoundComponent* getSoundComponentPtr () {
        return sound_component.get();
    }
private:
    std::unique_ptr<DrawComponent> draw_component;
    std::unique_ptr<SoundComponent> sound_component;
};
