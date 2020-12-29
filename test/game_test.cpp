
#include <memory>

#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"

TEST (GameTest, TestStartStateEnter) {
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestStartStateExit) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    ASSERT_NO_THROW(test_game.EventLoop());

    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(true, mockPointer->isClosed);
    
}

TEST (GameTest, TestStartStateDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_EQ(3, mockPointer->nDraws);
    
}

TEST (GameTest, TestPlayStateEnter) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.play, test_game.current_state);
    
}

TEST (GameTest, TestPlayStateClear) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_TRUE(mockPointer->isClear);
    
}

TEST (GameTest, TestPlayStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestPlayStateToDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.draw, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(test_game.window.get());
    ASSERT_GT(mockPointer->nDraws, 0);
    
}

TEST (GameTest, TestDrawStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.start, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateToPlay) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.play, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateToWait) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    ASSERT_EQ(&test_game.wait, test_game.current_state);
    
}

TEST (GameTest, TestDrawStateToPlayStopped) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockSound *mockPointer = dynamic_cast<MockSound*>(
                                                test_game.command->sound.get());
    ASSERT_EQ(mockPointer->status, Status::Playing);
    
}

TEST (GameTest, TestDrawStatePlaying) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<CommandFactory<>>(
                                        makeSingleLetterSiren<MockSound>())};
    test_game.EventLoop();
    MockSound *mockPointer = dynamic_cast<MockSound*>(
                                                test_game.command->sound.get());
    ASSERT_EQ(mockPointer->status, Status::Stopped);
    
}
