
#include <memory>
#include <iostream>

#include "sound.h"
#include "window.h"
#include "game.h"
#include "specialsound.h"

int main() {
    
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  std::make_unique<SoundMaker<>>()};
    //my_game.EventLoop();
    
    auto comp = SpecialSound(my_game, "TEST");
    auto copy = SpecialSound(comp);
    
    comp = SpecialSound(my_game, "TEST", std::make_unique<sf::Color>(sf::Color::Black));
    copy = SpecialSound(comp);
    comp = std::move(copy);
    
    return 0;
    
}
