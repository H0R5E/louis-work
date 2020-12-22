
#include "soundcommand.h"
#include "helpers.h"
#include "game.h"

SoundCommand::SoundCommand() {
    LoadIt<sf::SoundBuffer>(buffer, "Alarm_or_siren.ogg");
}

void SoundCommand::Execute (const sf::Event& event,
                            Game& game ) {
    
    sound.setBuffer(buffer);
    sound.play();
    
}

void SoundCommand::Stop() {
    sound.stop();
}

bool SoundCommand::IsCompleted () {
    return true;
}
