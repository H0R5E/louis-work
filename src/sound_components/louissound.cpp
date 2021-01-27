
#include <cstring>

#include "louissound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

#include <iostream>

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
    
    if (!buffer) {
        return;
    }
    
    sound = service.makeSoundPtr();
    sound->setBuffer(*buffer);
    sound->play();
    clock.restart();
    
}
