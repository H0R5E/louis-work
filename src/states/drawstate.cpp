
#include "drawstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"
#include "window.h"

#include <iostream>

State* DrawState::HandleKeyPressed (const sf::Event& event,
                                    polyComponentVector& scenes,
                                    Service& service) {
    
    auto& scene = *(scenes[0]);
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        scene.abort();
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
        
        if (service.triggerSpecial()) {
            return &StateHolder::special;
        } else {
            return &StateHolder::play;
        }
        
    } else {
        return &StateHolder::wait;
    }
    
}

State* DrawState::Update (polyComponentVector& scenes, Service& service) {
    
    std::cout << "DrawState::Update" << std::endl;
    
    auto& scene = *(scenes[0]);
    
    if (scene.update()) {
        scene(service);
        service.getWindow().display();
    }
    
    return nullptr;
}
