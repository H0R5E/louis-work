
#include <memory>
#include <iostream>

#include "sound.h"
#include "window.h"
#include "game.h"
#include "sirensound.h"

int main() {
    
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  std::make_unique<SoundMaker<>>()};
    //my_game.EventLoop();
    
    auto comp = SirenSound(my_game);
    auto copy = SirenSound(comp);
    
    comp = SirenSound(my_game, std::make_unique<sf::Color>(sf::Color::Black));
    copy = SirenSound(comp);
    comp = std::move(copy);
    
    return 0;
    
}
