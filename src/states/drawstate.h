#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "state.h"

class DrawState : public State {
public:
    bool skipEvents {true};
    State* HandleKeyPressed (const sf::Event& event,
                             Component& scene,
                             Service& service) override;
    State* HandleKeyReleased (const sf::Event& event,
                              Component& scene,
                              Service& service) override;
    State* Update (Component& scene, Service& service) override;
};
