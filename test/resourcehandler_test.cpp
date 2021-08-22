
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

#include <stdexcept>

#include "gtest/gtest.h"

#include <SFML/Graphics.hpp>
#include "resourceholder.h"

TEST (ResourceHolderTest, LoadFont) { 
    
    ResourceHolder<sf::Font> FontHolder {"fonts", true};
    FontHolder.Load("Monofett-Regular");
    auto font = FontHolder.Get("Monofett-Regular");
    ASSERT_EQ ("Monofett", font.getInfo().family);
    
}

TEST (ResourceHolderTest, NotAFont) { 
    
    ResourceHolder<sf::Font> FontHolder {"fonts", true};
    ASSERT_THROW(FontHolder.Load("Alarm_or_siren");, std::runtime_error);
    
}

TEST (ResourceHolderTest, GetFontMissing) { 
    
    ResourceHolder<sf::Font> FontHolder {"fonts", true};
    ASSERT_THROW(FontHolder.Get("Anything");, std::runtime_error);
    
}

TEST (ResourceHolderTest, GetFontConst) { 
    
    ResourceHolder<sf::Font> FontHolder {"fonts", true};
    FontHolder.Load("Monofett-Regular");
    const ResourceHolder<sf::Font>* p = &FontHolder;
    auto font = p->Get("Monofett-Regular");
    ASSERT_EQ ("Monofett", font.getInfo().family);
    
}

TEST (ResourceHolderTest, GetFontMissingConst) { 
    
    ResourceHolder<sf::Font> FontHolder {"fonts", true};
    const ResourceHolder<sf::Font>* p = &FontHolder;
    ASSERT_THROW(p->Get("Anything");, std::runtime_error);
    
}

TEST (ResourceHolderTest, OnlyLoadOnce) { 
    
    ResourceHolder<sf::Font> FontHolder {"fonts", true};
    FontHolder.Load("Monofett-Regular");
    FontHolder.Load("Monofett-Regular");
    ASSERT_EQ (1, FontHolder.Size());
    
}
