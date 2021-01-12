
#include <memory>

#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "stateholder.h"

TEST (GameTest, TestConstruct) {
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>()};
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestStartStateEnter) {
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestStartStateExit) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    ASSERT_NO_THROW(test_game.EventLoop());

    MockWindow *mockPointer = dynamic_cast<MockWindow*>(
                                                test_game.getWindowPtr());
    ASSERT_EQ(true, mockPointer->isClosed);
    
}

TEST (GameTest, TestStartStateDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(
                                                test_game.getWindowPtr());
    ASSERT_EQ(3, mockPointer->nDraws);
    
}

TEST (GameTest, TestPlayStateEnter) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateOtherPress());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateScene) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateOtherPress());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_TRUE(test_game.getScenePtr() != nullptr);
    
}


TEST (GameTest, TestPlayStateClear) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(
                                                test_game.getWindowPtr());
    ASSERT_TRUE(mockPointer->isClear);
    
}

TEST (GameTest, TestPlayStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestStartStateSkipEvents) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC(false));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateToDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateOtherPress());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::draw, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateTextNotHandled) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(999));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, test_game.getCurrentState());
    
}

TEST (GameTest, TestDrawStateDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    MockWindow *mockPointer = dynamic_cast<MockWindow*>(
                                                test_game.getWindowPtr());
    ASSERT_GT(mockPointer->nDraws, 0);
    
}

TEST (GameTest, TestDrawStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestDrawStateToPlay) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSiren};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, test_game.getCurrentState());
    
}

TEST (GameTest, TestDrawStateToWait) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased());
    eventQueue.push(simulateOtherPress());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::wait, test_game.getCurrentState());
    
}

TEST (GameTest, TestWaitStateToPlay) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased());
    eventQueue.push(simulateOtherPress(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, test_game.getCurrentState());
    
}

TEST (GameTest, TestWaitStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased());
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}


TEST (GameTest, TestDrawStatePlaying) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
    test_game.EventLoop();
    MockSound *mockPointer = dynamic_cast<MockSound*>(
        test_game.getScenePtr()->getSoundComponentPtr()->getSoundPtr());
    ASSERT_EQ(mockPointer->status, sf::Sound::Status::Playing);
    
}

TEST (GameTest, TestPlayStateSoundStopped) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>(),
                    &makeSingleLetterSiren};
    test_game.EventLoop();
    MockSound *mockPointer = dynamic_cast<MockSound*>(
        test_game.getScenePtr()->getSoundComponentPtr()->getSoundPtr());
    ASSERT_EQ(mockPointer->status, sf::Sound::Status::Stopped);
    
}
