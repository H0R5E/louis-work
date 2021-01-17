
#include "scene.h"
#include <iostream>

Scene::Scene (std::unique_ptr<DrawComponent>&& draw_component,
              std::unique_ptr<SoundComponent>&& sound_component) :
        draw_component(std::move(draw_component)),
        sound_component(std::move(sound_component)) {
}

void Scene::Initialize ( Service& service ) {
    
    std::cout << "Scene::Initialize" << std::endl;
    auto& window = service.getWindow();
    window.clear(sf::Color::Black);
    draw_component->draw(service);
    
}


void Scene::Modify ( const sf::Event& event, Service& service ) {
    
    std::cout << "Scene::Modify(event)" << std::endl;
    
    draw_component->set_active_event(event, service);
    
    if (sound_component) {
        sound_component->set_active_event(event, service);
    }
    
}

void Scene::Modify ( Service& service ) {
    
    std::cout << "Scene::Modify()" << std::endl;
    
    draw_component->set_active_event(service);
    
    if (sound_component) {
        sound_component->set_active_event(service);
    }
    
}

bool Scene::Ready () {
    
    auto draw_completed = draw_component->isCompleted();
    bool sound_completed {true};
    
    if (sound_component) {
        sound_completed = sound_component->isCompleted();
    }
    
    return draw_completed & sound_completed;
    
}

void Scene::Update ( Service& service ) {
    
    std::cout << "Scene::Update" << std::endl;
    
    if (draw_component->redraw()) {
        draw_component->draw(service);
    }
    
    if (sound_component->replay()) {
        sound_component->play(service);
    }
    
}
