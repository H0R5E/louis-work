
#include "soundcommand.h"
#include "helpers.h"
#include "game.h"

void SoundCommand::Execute (const sf::Event& event,
                            Game& game ) {
    
    auto& sound_buffer = game.buffer_holder.Get("Alarm_or_siren");
    sound.setBuffer(sound_buffer);
    sound.play();
    
}

void SoundCommand::Stop() {
    sound.stop();
}

bool SoundCommand::IsCompleted () {
    return true;
}
