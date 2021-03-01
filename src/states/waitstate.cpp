
#include <spdlog/spdlog.h>

#include "waitstate.h"

#include "scene.h"
#include "service.h"
#include "stateholder.h"
#include "window.h"

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
    
    spdlog::get("main_logger")->debug("WaitState::Update");
    
    auto& scene = *(scenes[0]);
    
    if (scene.isCompleted()) {
        
        if (service.triggerSpecial()) {
            return &StateHolder::special;
        } else if (scene.restartService(service)) {
            auto new_scene = service.makeScenePValue();
            scenes.push_back(std::move(new_scene));
            service.clearLetters();
            return &StateHolder::play;
        } else {
            return &StateHolder::play;
        }
        
    } else if (scene.update()) {
        
        scene(service);
        service.getWindow().display();
    
    }
    
    return nullptr;
    
}

void WaitState::Enter (polyComponentVector& scenes,
                       Service& service) {
    
    spdlog::get("main_logger")->info("Entering WaitState");
    
    return;
    
}
