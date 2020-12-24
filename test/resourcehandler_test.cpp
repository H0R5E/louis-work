
#include "gtest/gtest.h"

#include <SFML/Graphics.hpp>
#include "resourceholder.h"

TEST (ResourceHolderTest, LoadFont) { 
    
    ResourceHolder<sf::Font> FontHolder {};
    FontHolder.Load("Monofett-Regular");
    auto font = FontHolder.Get("Monofett-Regular");
    ASSERT_EQ ("Monofett", font.getInfo().family);
    
}

TEST (ResourceHolderTest, GetFontConst) { 
    
    ResourceHolder<sf::Font> FontHolder {};
    FontHolder.Load("Monofett-Regular");
    const ResourceHolder<sf::Font>* p = &FontHolder;
    auto font = p->Get("Monofett-Regular");
    ASSERT_EQ ("Monofett", font.getInfo().family);
    
}

TEST (ResourceHolderTest, OnlyLoadOnce) { 
    
    ResourceHolder<sf::Font> FontHolder {};
    FontHolder.Load("Monofett-Regular");
    FontHolder.Load("Monofett-Regular");
    ASSERT_EQ (1, FontHolder.Size());
    
}
