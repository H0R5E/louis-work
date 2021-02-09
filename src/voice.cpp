
#include <string_view>
#include <vector>
#include <iostream>

#include "voice.h"

int espeakCallBack (short* wav, int numsamples, espeak_EVENT* events){
    
    if (wav == NULL) {
        return 1;
    }
    
    std::vector<short>* sound_data 
        {static_cast<std::vector<short>*>(events[0].user_data)};
    sound_data->insert(sound_data->end(), wav, wav + numsamples);
    
    return 0;
    
}

Voice::Voice () {
    
    samplerate = espeak_Initialize(AUDIO_OUTPUT_RETRIEVAL, buflength, NULL, 0);
    espeak_SetSynthCallback(&espeakCallBack);
    espeak_SetVoiceByName("en-GB-x-rp");
    espeak_SetParameter(espeakVOLUME, 300, 0);
    
}

sf::SoundBuffer Voice::getBuffer (const char s[]) {
    
    int options = 0;
    unsigned int position = 0;
    espeak_POSITION_TYPE position_type = espeak_POSITION_TYPE::POS_WORD;
    unsigned int end_position = 0;
    unsigned int flags = espeakCHARS_AUTO | espeakPHONEMES;
    std::vector<short> user_data;
    
    espeak_Synth(s,
                 buflength,
                 position,
                 position_type,
                 end_position,
                 flags,
                 NULL,
                 &user_data);
    
    espeak_Synchronize ();
    
    sf::SoundBuffer buffer {}; 
    buffer.loadFromSamples(user_data.data(),
                           user_data.size(),
                           1,
                           samplerate);
    
    return buffer;
    
}
