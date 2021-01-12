
#include "scene.h"

void Scene::Modify ( const sf::Event& event, Service& service ) {
    
    draw_component->set_active_event(event, service);
    
    if (sound_component) {
        sound_component->set_active_event(event, service);
    }
    
}

void Scene::Modify ( Service& service ) {
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
    
    if (draw_component->redraw()) {
        draw_component->draw(service);
    }
    
    if (sound_component->replay()) {
        sound_component->play(service);
    }
    
}
