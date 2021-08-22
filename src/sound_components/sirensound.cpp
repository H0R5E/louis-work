
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

#include "sirensound.h"
#include "service.h"
#include "window.h"


void SirenSound::init (Service& service) {
    spdlog::debug("SirenSound::init");
    auto& sound_buffer = service.getSoundBuffer("Alarm_or_siren");
    sound = service.makeSoundPValue();
    sound->setBuffer(sound_buffer);
}

void SirenSound::setActiveEvent ( const sf::Event& event, Service& service ) {
    should_replay = true;
}

void SirenSound::setActiveEvent ( Service& service ) {
    should_replay = false;
}

bool SirenSound::update() {
    spdlog::debug("SirenSound::update");
    return should_replay;
}

bool SirenSound::isCompleted() {
    
    spdlog::debug("SirenSound::isCompleted");
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.75f && !aborted)
        return false;
    
    sound->stop();
    return true;
    
}

void SirenSound::abort () {
    spdlog::debug("SirenSound::abort");
    aborted = true;
}

void SirenSound::operator() (Service& service) {
    
    spdlog::debug("SirenSound::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!should_replay) {
        return;
    }
    
    sound->play();
    should_replay = false;
    clock.restart();
    
}
