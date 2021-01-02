
#include <memory>

#include "sound.h"
#include "window.h"
#include "game.h"

#include <chrono>
#include <thread>
#include "voice.h"

int main() {
    
//     Game my_game {std::make_unique<WindowAdapter>(),
//                   std::make_unique<SoundMaker<>>()};
//     
//     try {
//        my_game.EventLoop();
//     } catch (...) {
//        return 1;
//     }
    
    auto sound = SoundAdapter {};
    auto test = Voice {};
    auto buf = test.getBuffer();
    sound.setBuffer(buf);
    sound.play();
    
    while (sound.getStatus() == sf::Sound::Status::Playing) {
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    
    return 0;
    
}
