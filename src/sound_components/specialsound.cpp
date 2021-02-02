
#include <cstring>

#include "specialsound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

#include <iostream>

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
    
}

bool SpecialSound::update() {
    
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

bool SpecialSound::isCompleted() {
    
    std::cout << "SpecialSound::isCompleted" << std::endl;
    
    if (!sound) {
        return true;
    }
    
    if (sound->getStatus() == sf::Sound::Status::Playing) {
        return false;
    } else {
        return true;
    }
    
}

void SpecialSound::operator() (Service& service) {
    
    std::cout << "SpecialSound::operator()" << std::endl;
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!say_it) {
        return;
    }
    
    Voice voice {};
    
    std::string out {word};
    
    std::for_each(out.begin(), out.end(), [](char & c) {
        c = ::toupper(c);
    });
    
    buffer = std::make_unique<sf::SoundBuffer>(voice.getBuffer(&out[0]));
    
    sound = service.makeSoundPtr();
    sound->setBuffer(*buffer);
    sound->play();
    clock.restart();
    
}

SpecialSound& SpecialSound::operator= (const SpecialSound& copy) {
    
    SoundComponent::operator= (copy);
    init_copy(copy);
    return *this;
    
}
