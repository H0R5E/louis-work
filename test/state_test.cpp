
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
};

TEST_F (StateTest, HandleKeyPressed) { 
    
    State state;
    auto test = state.HandleKeyPressed(event, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, HandleTextEntered) { 
    
    State state;
    auto test = state.HandleTextEntered(event, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, HandleKeyReleased) { 
    
    State state;
    auto test = state.HandleKeyReleased(event, game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, Update) { 
    
    State state;
    auto test = state.Update(game);
    ASSERT_TRUE(!test);
    
}

TEST_F (StateTest, Enter) { 
    
    State state;
    ASSERT_NO_THROW(state.Enter(game));
    
}
