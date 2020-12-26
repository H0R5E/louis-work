
#include "gtest/gtest.h"

#include "game.h"
#include "mockwindow.h"

TEST (GameTest, TestStartStateExit) { 
    
    Game test_game {std::make_unique<MockWindow>()};
    ASSERT_NO_THROW(test_game.EventLoop());
    
}

TEST (GameTest, TestStartStateDraw) { 
    
    Game test_game {std::make_unique<MockWindow>()};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(3, mockPointer->nDraws);
    
}
