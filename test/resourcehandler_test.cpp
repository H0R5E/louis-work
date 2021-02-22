
#include <stdexcept>

#include "gtest/gtest.h"

#include <SFML/Graphics.hpp>
#include "resourceholder.h"

TEST (ResourceHolderTest, LoadFont) { 
    
    ResourceHolder<sf::Font> FontHolder {true};
    FontHolder.Load("Monofett-Regular");
    auto font = FontHolder.Get("Monofett-Regular");
    ASSERT_EQ ("Monofett", font.getInfo().family);
    
}

TEST (ResourceHolderTest, NotAFont) { 
    
    ResourceHolder<sf::Font> FontHolder {true};
    ASSERT_THROW(FontHolder.Load("Alarm_or_siren");, std::runtime_error);
    
}

TEST (ResourceHolderTest, GetFontMissing) { 
    
    ResourceHolder<sf::Font> FontHolder {true};
    ASSERT_THROW(FontHolder.Get("Anything");, std::runtime_error);
    
}

TEST (ResourceHolderTest, GetFontConst) { 
    
    ResourceHolder<sf::Font> FontHolder {true};
    FontHolder.Load("Monofett-Regular");
    const ResourceHolder<sf::Font>* p = &FontHolder;
    auto font = p->Get("Monofett-Regular");
    ASSERT_EQ ("Monofett", font.getInfo().family);
    
}

TEST (ResourceHolderTest, GetFontMissingConst) { 
    
    ResourceHolder<sf::Font> FontHolder {true};
    const ResourceHolder<sf::Font>* p = &FontHolder;
    ASSERT_THROW(p->Get("Anything");, std::runtime_error);
    
}

TEST (ResourceHolderTest, OnlyLoadOnce) { 
    
    ResourceHolder<sf::Font> FontHolder {true};
    FontHolder.Load("Monofett-Regular");
    FontHolder.Load("Monofett-Regular");
    ASSERT_EQ (1, FontHolder.Size());
    
}
