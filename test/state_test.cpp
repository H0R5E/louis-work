
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

#include "gtest/gtest.h"
#include "mock.h"

#include <SFML/Graphics.hpp>
#include "state.h"
#include "game.h"

class StateTest : public ::testing::Test {
public:
    StateTest () {
        auto comp = make_polymorphic_value<Component,
                                           SingleLetterDraw>(game,
                                                             sf::Color::Yellow);
        scenes.push_back(std::move(comp));
    }
protected:
    std::queue<DelayEvent> eventQueue {};
    Game game {std::make_unique<MockWindow>(eventQueue),
               make_polymorphic_value<SoundMakerBase,
                                      SoundMaker<MockSound>>(),
               true};
    sf::Event event {simulateTextEntered(10)};
    polyComponentVector scenes {};
};

TEST_F (StateTest, HandleKeyPressed) { 
    
    State state;
    auto test = state.HandleKeyPressed(event, scenes, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, HandleTextEntered) { 
    
    State state;
    auto test = state.HandleTextEntered(event, scenes, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, HandleKeyReleased) { 
    
    State state;
    auto test = state.HandleKeyReleased(event, scenes, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, Update) { 
    
    State state;
    auto test = state.Update(scenes, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, Enter) { 
    
    State state;
    ASSERT_NO_THROW(state.Enter(scenes, game));
    
}
