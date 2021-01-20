#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class PlayState : public State {
public:
    State* HandleKeyPressed (const sf::Event& event,
                             Component& scene,
                             Service& service) override;
    State* HandleTextEntered (const sf::Event& event,
                              Component& scene,
                              Service& service) override;
    std::unique_ptr<Component> Enter (Component* scene, 
                                      Service& service) override;
};
