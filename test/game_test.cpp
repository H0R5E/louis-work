
#include <memory>

#include "gtest/gtest.h"

#include "game.h"
#include "mock.h"

TEST (GameTest, TestStartStateEnter) {
    
    std::stack<sf::Event> eventStack;
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestStartStateExit) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    ASSERT_NO_THROW(test_game.EventLoop());

    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(true, mockPointer->isClosed);
    
}

TEST (GameTest, TestStartStateDraw) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(3, mockPointer->nDraws);
    
}

TEST (GameTest, TestPlayStateEnter) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.play, test_game.current_state);
    
}

TEST (GameTest, TestPlayStateClear) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_TRUE(mockPointer->isClear);
    
}

TEST (GameTest, TestPlayStateToStart) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestPlayStateToDraw) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.draw, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateDraw) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_GT(mockPointer->nDraws, 0);
    
}

TEST (GameTest, TestDrawStateToStart) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateToPlay) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateKeyReleased(2));
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.play, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateToWait) { 
    
    std::stack<sf::Event> eventStack;
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateTextEntered(10));
    eventStack.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventStack),
                    std::make_unique<CommandFactory>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.wait, test_game.current_state);
    
}

