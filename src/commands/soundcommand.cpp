
#include "soundcommand.h"
#include "helpers.h"
#include "game.h"

void SoundCommand::Execute (const sf::Event& event,
                            Game& game ) {
    
    LoadAsset<sf::SoundBuffer>(game.buffer, "Alarm_or_siren.ogg");
    sound.setBuffer(game.buffer);
    sound.play();
    
}

void SoundCommand::Stop() {
    sound.stop();
}

bool SoundCommand::IsCompleted () {
    return true;
}
