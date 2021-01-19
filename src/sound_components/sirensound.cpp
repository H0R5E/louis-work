
#include "sirensound.h"
#include "service.h"

void SirenSound::init (Service& service) {
    auto& sound_buffer = service.getSoundBuffer("Alarm_or_siren");
    sound = service.makeSoundPtr();
    sound->setBuffer(sound_buffer);
}

void SirenSound::setActiveEvent ( const sf::Event& event, Service& service ) {
    should_replay = true;
}

bool SirenSound::update() {
    return should_replay;
}

bool SirenSound::isCompleted() {
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.75f)
        return false;
    
    sound->stop();
    return true;
    
}

void SirenSound::operator() (Service& service) {
    sound->play();
    should_replay = false;
    clock.restart();
}
