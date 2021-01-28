#pragma once

#include <memory>
#include <unordered_set>
#include <SFML/Graphics.hpp>

#include "component.h"

using uniqueComponentVector = std::vector<std::unique_ptr<Component>>;

// Forward declare
class Service;

class State {
public:
    virtual ~State () {};
    virtual State* HandleKeyPressed (const sf::Event& event,
                                     Component& scene,
                                     Service& service) {return nullptr;}
    virtual State* HandleTextEntered (const sf::Event& event,
                                      uniqueComponentVector& scenes,
                                      Service& service) {return nullptr;}
    virtual State* HandleKeyReleased (const sf::Event& event,
                                      Component& scene,
                                      Service& service) {return nullptr;}
    virtual State* Update (uniqueComponentVector& scenes,
                           Service& service) {return nullptr;}
    virtual void Enter (uniqueComponentVector& scenes,
                        Service& service) {return;}
    bool skipEvents {false};
    std::unordered_set<std::string> special_words {"louis", 
                                                   "mummy",
                                                   "daddy"};
};
