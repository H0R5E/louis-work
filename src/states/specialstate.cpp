
#include "specialstate.h"

#include "factory.h"
#include "scene.h"
#include "service.h"
#include "stateholder.h"
#include "window.h"

#include <iostream>

State* SpecialState::HandleKeyPressed (const sf::Event& event,
                                       Component& scene,
                                       Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        scene.abort();
        return &StateHolder::start;
    }
    
    return nullptr;
    
}

State* SpecialState::Update (uniqueComponentVector& scenes, Service& service) {
    
    std::cout << "SpecialState::Update" << std::endl;
    
    auto& scene = *(scenes[0]);
    
    if (scene.isCompleted()) {
        auto new_scene = service.makeScenePtr();
        scenes.push_back(std::move(new_scene));
        return &StateHolder::play;
    } else if (scene.update()) {
        scene(service);
        service.getWindow().display();
    }
    
    return nullptr;
    
}

void SpecialState::Enter (uniqueComponentVector& scenes,
                          Service& service) {
    
    std::cout << "SpecialState::Enter" << std::endl;
    
    auto word = service.getWord();
    
    if (word == "louis") {
        auto new_scene = makeSpecial(service, word);
        scenes.push_back(std::move(new_scene));
    }
    
    service.clearLetters();
    
    return;
    
}
