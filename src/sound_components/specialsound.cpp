
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

#include <cstring>
#include <sstream>
#include <spdlog/spdlog.h>

#include "specialsound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

SpecialSound::SpecialSound (const SpecialSound& copy) :
            SoundComponent(copy) {
    init_copy(copy);
}

void SpecialSound::init_copy ( const SpecialSound& copy ) {
    
    if (copy.buffer) {
        buffer = std::make_unique<sf::SoundBuffer>(*copy.buffer);
    }
    
    word = copy.word;
    say_it = copy.say_it;
    aborted = copy.aborted;
    
}

bool SpecialSound::update() {
    
    auto elapsed = clock.getElapsedTime();
    
    std::stringstream log_msg;
    log_msg << "SpecialSound::update letters elapsed: " << elapsed.asSeconds();
    spdlog::debug(log_msg.str());
    
    if (elapsed.asSeconds() < 0.5f) {
        return false;
    } else if (!say_it) {
        say_it = true;
        return true;
    }
    
    return false;
    
}

bool SpecialSound::isCompleted() {
    
    spdlog::debug("SpecialSound::isCompleted");
    
    if (aborted) {
        return true;
    }
    
    if (!sound) {
        return true;
    }
    
    if (sound->getStatus() == sf::Sound::Status::Playing) {
        return false;
    } else {
        return true;
    }
    
}

void SpecialSound::abort () {
    if (sound) {
        sound->stop();
    }
    aborted = true;
}

void SpecialSound::operator() (Service& service) {
    
    spdlog::debug("SpecialSound::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!say_it) {
        return;
    }
    
    MyVoice voice {};
    
    std::string out {word};
    
    std::for_each(out.begin(), out.end(), [](char & c) {
        c = ::toupper(c);
    });
    
    buffer = std::make_unique<sf::SoundBuffer>(voice.getBuffer(&out[0]));
    
    sound = service.makeSoundPValue();
    sound->setBuffer(*buffer);
    sound->play();
    clock.restart();
    
}

SpecialSound& SpecialSound::operator= (const SpecialSound& copy) {
    
    SoundComponent::operator= (copy);
    init_copy(copy);
    return *this;
    
}
