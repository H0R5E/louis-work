
#include <iostream>
#include <SFML/Graphics.hpp>

#include "resourceholder.h"

int main() {
    
    ResourceHolder<sf::Font> FontHolder {};
    FontHolder.Load("Monofett-Regular");
    auto font = FontHolder.Get("Monofett-Regular");
    std::cout << font.getInfo().family << std::endl;
    
    const ResourceHolder<sf::Font>* p = &FontHolder;
    font = p->Get("Monofett-Regular");
    std::cout << font.getInfo().family << std::endl;
    
    FontHolder.Load("Monofett-Regular");
    std::cout << FontHolder.Size() << std::endl;
    
}
