
#include "sirensound.h"
#include "service.h"
#include "window.h"

#include <iostream>

void SirenSound::init (Service& service) {
    std::cout << "SirenSound::init" << std::endl;
    auto& sound_buffer = service.getSoundBuffer("Alarm_or_siren");
    sound = service.makeSoundPtr();
    sound->setBuffer(sound_buffer);
}

void SirenSound::setActiveEvent ( const sf::Event& event, Service& service ) {
    should_replay = true;
}

void SirenSound::setActiveEvent ( Service& service ) {
    should_replay = false;
}

bool SirenSound::update() {
    std::cout << "SirenSound::update" << std::endl;
    return should_replay;
}

bool SirenSound::isCompleted() {
    
    std::cout << "SirenSound::isCompleted" << std::endl;
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.75f && !aborted)
        return false;
    
    sound->stop();
    return true;
    
}

void SirenSound::abort () {
    std::cout << "SirenSound::abort()" << std::endl;
    aborted = true;
}

void SirenSound::operator() (Service& service) {
    std::cout << "SirenSound::operator()" << std::endl;
    
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
