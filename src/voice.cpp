
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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

MyVoice::MyVoice () {
    
    samplerate = espeak_Initialize(AUDIO_OUTPUT_RETRIEVAL, buflength, NULL, 0);
    espeak_SetSynthCallback(&espeakCallBack);
    espeak_SetVoiceByName("en-GB-x-rp");
    espeak_SetParameter(espeakVOLUME, 300, 0);
    
}

sf::SoundBuffer MyVoice::getBuffer (const char s[]) {
    
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
