
#include <vector>

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
    
    int buflength = 200;
    samplerate = espeak_Initialize(AUDIO_OUTPUT_RETRIEVAL, buflength, NULL, 0);
    espeak_SetSynthCallback(&espeakCallBack);
    espeak_SetVoiceByName("ar");
    
}

sf::SoundBuffer Voice::getBuffer () {
    
    int buflength = 200;
    int options = 0;
    unsigned int position = 0;
    espeak_POSITION_TYPE position_type = espeak_POSITION_TYPE::POS_WORD;
    unsigned int end_position = 0;
    unsigned int flags = espeakCHARS_AUTO;
    std::vector<short> user_data;
   
    espeak_Synth("A",
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
