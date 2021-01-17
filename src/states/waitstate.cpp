
#include "waitstate.h"

#include "scene.h"
#include "service.h"
#include "stateholder.h"

#include <iostream>

State* WaitState::HandleKeyPressed (const sf::Event& event,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* WaitState::Update (Service& service) {
    
    std::cout << "WaitState::Update" << std::endl;
    
    auto& scene = service.getScene();
    
    if (scene.Ready()) {
        return &StateHolder::play;
    } else {
        scene.Update(service);
    }
    
    return nullptr;
    
}
