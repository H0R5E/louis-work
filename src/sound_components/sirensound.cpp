
#include "sirensound.h"
#include "service.h"

SirenSound::SirenSound (Service& service) :
    SoundComponent(service) {
    auto& sound_buffer = service.getSoundBuffer("Alarm_or_siren");
    sound = service.makeSoundPtr();
    sound->setBuffer(sound_buffer);
}

void SirenSound::set_active_event ( const sf::Event& event, Service& service ) {
    should_replay = true;
}

void SirenSound::play (Service& service) {
    sound->play();
    should_replay = false;
    clock.restart();
}

bool SirenSound::replay() {
    return should_replay;
}

bool SirenSound::isCompleted() {
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.75f)
        return false;
    
    sound->stop();
    return true;
    
}
