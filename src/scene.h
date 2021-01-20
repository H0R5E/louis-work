#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "component.h"
#include "service.h"

class Scene : public Component {
public:
    Scene (Service& service,
           std::unique_ptr<DrawComponent>&& draw_component,
           std::unique_ptr<SoundComponent>&& sound_component) :
        Component(service),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    Scene (Service& service,
           std::unique_ptr<DrawComponent>&& draw_component,
           std::unique_ptr<SoundComponent>&& sound_component,
           std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void operator () (Service& service) override;
    SoundComponent* getSoundComponentPtr () {
        return sound_component.get();
    }
private:
    std::unique_ptr<DrawComponent> draw_component;
    std::unique_ptr<SoundComponent> sound_component;
    bool replay {true};
};
