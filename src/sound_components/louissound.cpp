
#include <cstring>

#include "louissound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

#include <iostream>

bool LouisSound::update() {
    
    auto elapsed = clock.getElapsedTime();
    
    std::cout << "elapsed: " << elapsed.asSeconds() << std::endl;
    
    if (elapsed.asSeconds() < 0.5f) {
        return false;
    } else if (!say_it) {
        say_it = true;
        return true;
    }
    
    return false;
    
}

bool LouisSound::isCompleted() {
    
    std::cout << "LouisSound::isCompleted" << std::endl;
    
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

void LouisSound::operator() (Service& service) {
    
    std::cout << "LouisSound::operator()" << std::endl;
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!say_it) {
        return;
    }
    
    Voice voice {};
    
    char word[6] = "LOUIS";
    buffer = std::make_unique<sf::SoundBuffer>(voice.getBuffer(word));
    
    sound = service.makeSoundPtr();
    sound->setBuffer(*buffer);
    sound->play();
    clock.restart();
    
}
