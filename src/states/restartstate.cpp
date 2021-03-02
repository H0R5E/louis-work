
#include <spdlog/spdlog.h>

#include "restartstate.h"

#include "scene.h"
#include "service.h"
#include "stateholder.h"
#include "window.h"

State* RestartState::HandleKeyPressed (const sf::Event& event,
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

State* RestartState::Update (polyComponentVector& scenes, Service& service) {
    
    spdlog::get("main_logger")->debug("RestartState::Update");
    
    auto& scene = *(scenes[0]);
    
    if (scene.isCompleted()) {
        return &StateHolder::special;
    } else if (scene.update()) {
        scene(service);
        service.getWindow().display();
    }
    
    return nullptr;
    
}

void RestartState::Enter (polyComponentVector& scenes,
                          Service& service) {
    
    spdlog::get("main_logger")->info("Entering RestartState");
    
    return;
    
}
