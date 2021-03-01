
#include <spdlog/spdlog.h>

#include "specialstate.h"

#include "factory.h"
#include "scene.h"
#include "service.h"
#include "stateholder.h"
#include "window.h"


State* SpecialState::HandleKeyPressed (const sf::Event& event,
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

State* SpecialState::Update (polyComponentVector& scenes, Service& service) {
    
    spdlog::get("main_logger")->debug("SpecialState::Update");
    
    auto& scene = *(scenes[0]);
    
    if (scene.isCompleted()) {
        auto new_scene = service.makeScenePValue();
        scenes.push_back(std::move(new_scene));
        return &StateHolder::play;
    } else if (scene.update()) {
        scene(service);
        service.getWindow().display();
    }
    
    return nullptr;
    
}

void SpecialState::Enter (polyComponentVector& scenes,
                          Service& service) {
    
    spdlog::get("main_logger")->debug("SpecialState::Enter");
    
    auto word = service.getWord();
    auto new_scene = service.makeSpecialScenePValue(word);
    scenes.push_back(std::move(new_scene));
    service.clearLetters();
    
    spdlog::get("main_logger")->info("Entering SpecialState");
    
    return;
    
}
