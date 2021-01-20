
#include "gtest/gtest.h"
#include "mock.h"

#include <SFML/Graphics.hpp>
#include "state.h"
#include "game.h"

class StateTest : public ::testing::Test {
protected:
    std::queue<DelayEvent> eventQueue {};
    Game game {std::make_unique<MockWindow>(eventQueue),
               std::make_unique<SoundMaker<MockSound>>()};;
    sf::Event event {simulateTextEntered(10)};
    SingleLetterDraw scene {SingleLetterDraw(game)};
};

TEST_F (StateTest, HandleKeyPressed) { 
    
    State state;
    auto test = state.HandleKeyPressed(event, scene, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, HandleTextEntered) { 
    
    State state;
    auto test = state.HandleTextEntered(event, scene, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, HandleKeyReleased) { 
    
    State state;
    auto test = state.HandleKeyReleased(event, scene, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, Update) { 
    
    State state;
    auto test = state.Update(scene, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, Enter) { 
    
    State state;
    ASSERT_NO_THROW(state.Enter(&scene, game));
    
}
