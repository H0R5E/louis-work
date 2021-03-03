
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
    
    Voice voice {};
    
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
