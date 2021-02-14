
#include "waitstate.h"

#include "scene.h"
#include "service.h"
#include "stateholder.h"
#include "window.h"

#include <iostream>

State* WaitState::HandleKeyPressed (const sf::Event& event,
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

State* WaitState::Update (polyComponentVector& scenes, Service& service) {
    
    std::cout << "WaitState::Update" << std::endl;
    
    auto& scene = *(scenes[0]);
    
    if (scene.isCompleted()) {
        
        if (service.triggerSpecial()) {
            return &StateHolder::special;
        } else {
            return &StateHolder::play;
        }
        
    } else if (scene.update()) {
        
        scene(service);
        service.getWindow().display();
    
    }
    
    return nullptr;
    
}
