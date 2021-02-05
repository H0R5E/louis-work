
#include "helpers.h"
#include "scene.h"
#include "window.h"

#include "singleletterdraw.h"

#include <iostream>

void Scene::setActiveEvent ( const sf::Event& event, Service& service ) {
    
    std::cout << "Scene::setActiveEvent(event)" << std::endl;
    
    draw_component->setActiveEvent(event, service);
    
    if (sound_component) {
        sound_component->setActiveEvent(event, service);
        replay = true;
    }
    
}

void Scene::setActiveEvent ( Service& service ) {
    
    std::cout << "Scene::setActiveEvent()" << std::endl;
    
    draw_component->setActiveEvent(service);
    
    if (sound_component) {
        sound_component->setActiveEvent(service);
        replay = false;
    }
    
}

bool Scene::isCompleted () {
    
    std::cout << "Scene::isCompleted()" << std::endl;
    
    auto draw_completed = draw_component->isCompleted();
    bool sound_completed {true};
    
    if (sound_component) {
        sound_completed = sound_component->isCompleted();
    }
    
    return draw_completed & sound_completed;
    
}

void Scene::abort () {
    
    std::cout << "Scene::abort" << std::endl;
    
    draw_component->abort();
    sound_component->abort();
    
}

bool Scene::update () {
    
    std::cout << "Scene::update" << std::endl;
    
    bool update {false};
    
    if (draw_component->update()) {
        update = true;
    }
    
    if (sound_component->update()) {
        update = true;
        replay = true;
    }
    
    return update;
    
}

void Scene::operator () ( Service& service ) {
    
    std::cout << "Scene::operator ()" << std::endl;
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    (*draw_component)(service);
    
    if (replay) {
        (*sound_component)(service);
        replay = false;
    }
    
}
