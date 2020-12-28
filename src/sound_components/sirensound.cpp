
#include "sirensound.h"
#include "command.h"
#include "game.h"

void SirenSound::start (const sf::Event& event,
                        Command& command,
                        Game& game ) {
    
    auto& sound_buffer = game.buffer_holder.Get("Alarm_or_siren");
    command.sound->setBuffer(sound_buffer);
    command.sound->play();
    
}

void SirenSound::stop(Command& command) {
    command.sound->stop();
}
