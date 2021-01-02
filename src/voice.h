
#pragma once

#include <speak_lib.h>
#include <SFML/Audio.hpp>

int espeakCallBack (short* wav, int numsamples, espeak_EVENT* events);

class Voice {
public:
    Voice ();
    sf::SoundBuffer getBuffer ();
    int samplerate;
};