
#include "drawstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"

#include <iostream>

State* DrawState::HandleKeyPressed (const sf::Event& event,
                                    Component& scene,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* DrawState::HandleKeyReleased (const sf::Event& event,
                                     Component& scene,
                                     Service& service ) {
    
    std::cout << "DrawState::HandleKeyReleased" << std::endl;
    
    scene.setActiveEvent(service);
    
    if (scene.isCompleted()) {
        return &StateHolder::play;
    } else {
        return &StateHolder::wait;
    }
    
}

State* DrawState::Update (Component& scene, Service& service) {
    std::cout << "DrawState::Update" << std::endl;
    scene(service);
    return nullptr;
}
