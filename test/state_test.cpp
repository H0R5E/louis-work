
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
                                      SoundMaker<MockSound>>()};
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
