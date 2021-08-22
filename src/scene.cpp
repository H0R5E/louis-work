
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <sstream>
#include <spdlog/spdlog.h>

#include "scene.h"
#include "window.h"

void Scene::setActiveEvent ( const sf::Event& event, Service& service ) {
    
    spdlog::debug("Scene::setActiveEvent (event)");
    
    draw_component->setActiveEvent(event, service);
    
    if (sound_component) {
        sound_component->setActiveEvent(event, service);
        replay = true;
    }
    
}

void Scene::setActiveEvent ( Service& service ) {
    
    spdlog::debug("Scene::setActiveEvent ()");
    
    draw_component->setActiveEvent(service);
    
    if (sound_component) {
        sound_component->setActiveEvent(service);
        replay = false;
    }
    
}

bool Scene::isCompleted () {
    
    spdlog::debug("Scene::isCompleted");
    
    auto draw_completed = draw_component->isCompleted();
    bool sound_completed {true};
    
    if (sound_component) {
        sound_completed = sound_component->isCompleted();
    }
    
    return draw_completed & sound_completed;
    
}

void Scene::abort () {
    
    spdlog::debug("Scene::abort");
    
    draw_component->abort();
    sound_component->abort();
    
}

bool Scene::update () {
    
    spdlog::debug("Scene::update");
    
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

bool Scene::restartService (const Service& service) {
    
    auto restart = false;
    restart |= draw_component->restartService(service);
    restart |= sound_component->restartService(service);
    
    return restart;
    
}


bool Scene::restartKey ( const sf::Event::KeyEvent& event ) {
    
    auto restart = false;
    restart |= draw_component->restartKey(event);
    restart |= sound_component->restartKey(event);
    
    return restart;
    
}

void Scene::operator() ( Service& service ) {
    
    spdlog::debug("Scene::operator()");
    
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
