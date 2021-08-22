
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

#include "playstate.h"

#include "service.h"
#include "scene.h"
#include "stateholder.h"
#include "window.h"

#include <iostream>

State* PlayState::HandleKeyPressed (const sf::Event& event,
                                    polyComponentVector& scenes,
                                    Service& service) {
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        return &StateHolder::start;
    }
    
    auto& scene = *(scenes[0]);
    
    if (scene.restartKey(event.key)) {
        return &StateHolder::restart;
    }
    
    return nullptr;
    
}

State* PlayState::HandleTextEntered (const sf::Event& event,
                                     polyComponentVector& scenes,
                                     Service& service) {
    
    spdlog::debug("PlayState::HandleTextEntered");
    
    if (event.text.unicode < 128) {
        
        auto& scene = *(scenes[0]);
        
        scene.setActiveEvent(event, service);
        auto convert = static_cast<char>(event.text.unicode);
        service.storeLetter(convert);
        
        auto word = service.getWord();
        return &StateHolder::draw;
        
     }
    
    // Just return null for now as not yet transitioning states
    return nullptr;
    
}

void PlayState::Enter (polyComponentVector& scenes,
                       Service& service) {
    
    spdlog::debug("PlayState::Enter");
    
    std::stringstream log_msg;
    log_msg << "PlayState::Enter letters stored: " <<
                                                    service.getWord().size();
    spdlog::debug(log_msg.str());
    
    (*scenes[0])(service);
    service.getWindow().display();
    
    spdlog::info("Entering PlayState");
    
    return;
    
}
