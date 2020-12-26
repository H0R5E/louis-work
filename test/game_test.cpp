
#include "gtest/gtest.h"

#include "game.h"
#include "mockwindow.h"

TEST (GameTest, TestStartStateEnter) { 
    
    std::stack<sf::Event> eventStack;
    Game test_game {std::make_unique<MockWindow>(eventStack)};
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestStartStateExit) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateKeypress(sf::Keyboard::C,
                                     false,
                                     true,
                                     false,
                                     false));
    Game test_game {std::make_unique<MockWindow>(eventStack)};
    ASSERT_NO_THROW(test_game.EventLoop());

    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(true, mockPointer->isClosed);
    
}

TEST (GameTest, TestStartStateDraw) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateKeypress(sf::Keyboard::C,
                                     false,
                                     true,
                                     false,
                                     false));
    Game test_game {std::make_unique<MockWindow>(eventStack)};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(3, mockPointer->nDraws);
    
}
