
#include <cstring>

#include "lettersound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

#include <iostream>

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
        
        buffer = voice.getBuffer(word);
    
    } else {
        
        char word[9] = "[[V:mm]]";
        buffer = voice.getBuffer(word);
        
    }
    
    should_replay = true;
    
}

void LetterSound::setActiveEvent ( Service& service ) {
}

bool LetterSound::update() {
    
    std::cout << "LetterSound::update" << std::endl;
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() > 1.0f)
        return true;
    
    return should_replay;
    
}

bool LetterSound::isCompleted() {
    
    std::cout << "LetterSound::isCompleted" << std::endl;
    
    if (!sound) {
        return true;
    }
    
    if (sound->getStatus() == sf::Sound::Status::Playing) {
        return false;
    } else {
        return true;
    }
    
}

void LetterSound::operator() (Service& service) {
    
    std::cout << "LetterSound::operator()" << std::endl;
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!update()) {
        return;
    }
    
    sound = service.makeSoundPtr();
    sound->setBuffer(buffer);
    sound->play();
    should_replay = false;
    clock.restart();
    
}
