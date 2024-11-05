
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

#include "lettersound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

LetterSound::LetterSound (const LetterSound& copy) :
            SoundComponent(copy) {
    
    if (copy.buffer) {
        buffer = std::make_unique<sf::SoundBuffer>(*copy.buffer);
    }
    
    clearBuffer = copy.clearBuffer;
    
}

void LetterSound::setActiveEvent (const sf::Event& event,
                                  Service& service ) {
    
    MyVoice voice {};
    
    if (((event.text.unicode > 47) && (event.text.unicode < 58)) ||
        ((event.text.unicode > 64) && (event.text.unicode < 91)) ||
        ((event.text.unicode > 96) && (event.text.unicode < 123))) {
        
        char word[2] {static_cast<char>(event.text.unicode)};
        
        for(int i=0;i<strlen(word);i++){
            word[i] = toupper(word[i]);
        }
        
        buffer = std::make_unique<sf::SoundBuffer>(voice.getBuffer(word));
    
    } else {
        
        char word[9] = "[[V:mm]]";
        buffer = std::make_unique<sf::SoundBuffer>(voice.getBuffer(word));
        
    }
    
    clearBuffer = false;
    
}

void LetterSound::setActiveEvent ( Service& service ) {
    clearBuffer = true;
}

bool LetterSound::update() {
    
    spdlog::debug("LetterSound::update");
    
    if (!buffer) {
        return false;
    }
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() > 1.0f)
        return true;
    
    return false;
    
}

bool LetterSound::isCompleted() {
    
    spdlog::debug("LetterSound::isCompleted");
    
    if (!sound) {
        return true;
    }
    
    if (sound->getStatus() == sf::Sound::Status::Playing) {
        
        return false;
        
    } else {
        
        if (clearBuffer) {
            buffer = nullptr;
        }
        
        return true;
        
    }
    
}

void LetterSound::abort () {
    spdlog::debug("LetterSound::abort");
    if (sound) {
        sound->stop();
    }
}

void LetterSound::operator() (Service& service) {
    
    spdlog::debug("LetterSound::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!buffer) {
        return;
    }
    
    sound = service.makeSoundPValue();
    sound->setBuffer(*buffer);
    sound->play();
    clock.restart();
    
}

LetterSound& LetterSound::operator= (const LetterSound& copy) {
    
    SoundComponent::operator= (copy);
    
    if (copy.buffer) {
        buffer = std::make_unique<sf::SoundBuffer>(*copy.buffer);
    }
    
    clearBuffer = copy.clearBuffer;
    
    return *this;
    
}
