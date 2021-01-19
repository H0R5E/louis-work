
#include "waitstate.h"

#include "scene.h"
#include "service.h"
#include "stateholder.h"

#include <iostream>

State* WaitState::HandleKeyPressed (const sf::Event& event,
                                    Component& scene,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* WaitState::Update (Component& scene, Service& service) {
    
    std::cout << "WaitState::Update" << std::endl;
    
    if (scene.isCompleted()) {
        return &StateHolder::play;
    } else {
        scene(service);
    }
    
    return nullptr;
    
}
