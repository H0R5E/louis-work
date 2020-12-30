
#include "sirensound.h"
#include "service.h"

void SirenSound::start (const sf::Event& event,
                        Service& service) {
    
    auto& sound_buffer = service.getSoundBuffer("Alarm_or_siren");
    sound = service.makeSoundPtr();
    sound->setBuffer(sound_buffer);
    sound->play();
    
}

void SirenSound::stop() {
    sound->stop();
}
