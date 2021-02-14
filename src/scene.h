#pragma once

#include <memory>
#include <SFML/Graphics.hpp>

#include "component.h"
#include "polymorphic_value.h"
#include "service.h"

using namespace isocpp_p0201;

class Scene : public Component {
public:
    Scene (Service& service,
           polymorphic_value<DrawComponent>&& draw_component,
           polymorphic_value<SoundComponent>&& sound_component) :
        Component(service),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    Scene (Service& service,
           polymorphic_value<DrawComponent>&& draw_component,
           polymorphic_value<SoundComponent>&& sound_component,
           std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)),
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override;
    void setActiveEvent (Service& service) override;
    bool update () override;
    bool isCompleted () override;
    void abort () override;
    bool restartKey (const sf::Event::KeyEvent& event) override;
    SoundComponent* getSoundComponentPtr () {
        return sound_component.operator->();
    }
    void operator () (Service& service) override;
private:
    polymorphic_value<DrawComponent> draw_component;
    polymorphic_value<SoundComponent> sound_component;
    bool replay {true};
};
