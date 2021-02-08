#pragma once

#include <memory>
#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "component.h"
#include "polymorphic_value.h"

using namespace isocpp_p0201;

using polyComponentVector = std::vector<polymorphic_value<Component>>;

// Forward declare
class Service;

class State {
public:
    virtual ~State () {};
    virtual State* HandleKeyPressed (const sf::Event& event,
                                     Component& scene,
                                     Service& service) {return nullptr;}
    virtual State* HandleTextEntered (const sf::Event& event,
                                      polyComponentVector& scenes,
                                      Service& service) {return nullptr;}
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      Component& scene,
                                      Service& service) {return nullptr;}
    virtual State* Update (polyComponentVector& scenes,
                           Service& service) {return nullptr;}
    virtual void Enter (polyComponentVector& scenes,
                        Service& service) {return;}
    bool skipEvents {false};
};
