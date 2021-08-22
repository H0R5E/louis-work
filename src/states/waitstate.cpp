
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
    
    spdlog::debug("WaitState::Update");
    
    auto& scene = *(scenes[0]);
    
    if (scene.isCompleted()) {
        
        if (service.triggerSpecial()) {
            return &StateHolder::special;
        } else if (scene.restartService(service)) {
            return &StateHolder::restart;
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
    
    spdlog::info("Entering WaitState");
    
    return;
    
}
