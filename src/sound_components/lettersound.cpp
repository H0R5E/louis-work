
#include <cstring>

#include "lettersound.h"
#include "service.h"
#include "voice.h"

void LetterSound::start (const sf::Event& event,
                        Service& service) {
    
    Voice voice {};
    sound = service.makeSoundPtr();
    
    if (((event.text.unicode > 47) && (event.text.unicode < 58)) ||
        ((event.text.unicode > 64) && (event.text.unicode < 91)) ||
        ((event.text.unicode > 96) && (event.text.unicode < 123))) {
        
        char word[2] {static_cast<char>(event.text.unicode)};
        
        for(int i=0;i<strlen(word);i++){
            word[i] = toupper(word[i]);
        }
        
        buffer = voice.getBuffer(word);
    
    } else {
        
        char word[9] = "[[V:mm]]";
        buffer = voice.getBuffer(word);
        
    }
    
    sound->setBuffer(buffer);
    sound->play();
    
}

bool LetterSound::stop() {
    if (sound->getStatus() == sf::Sound::Status::Playing) {
        return false;
    } else {
        return true;
    }
}
