
#include <memory>
#include <iostream>

#include "sound.h"
#include "window.h"
#include "game.h"
#include "singleletterdraw.h"

int main() {
    
    
    Game my_game {std::make_unique<WindowAdapter>(),
                  std::make_unique<SoundMaker<>>()};
    //my_game.EventLoop();
    
    
    auto comp = SingleLetterDraw(my_game);
    auto copy = SingleLetterDraw(comp);
    
    comp = SingleLetterDraw(my_game, std::make_unique<sf::Color>(sf::Color::Black));
    copy = SingleLetterDraw(comp);
    comp.checkit = true;
    
    if (!copy.checkit) {
        std::cout << "YES" << std::endl;
    }
    
    comp = std::move(copy);
    
    if (!comp.checkit) {
        std::cout << "YES" << std::endl;
    } else {
        std::cout << "NO" << std::endl;
    }
    
    return 0;
    
}
