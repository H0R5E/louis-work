
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
    
    spdlog::debug("SpecialState::Update");
    
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
    
    spdlog::debug("SpecialState::Enter");
    
    auto word = service.getWord();
    service.clearLetters();
    
    if (word.length() > 0) {
        auto new_scene = service.makeSpecialScenePValue(word);
        scenes.push_back(std::move(new_scene));
    }
    
    spdlog::info("Entering SpecialState");
    
    return;
    
}
