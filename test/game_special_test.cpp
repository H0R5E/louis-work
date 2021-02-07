
#include <memory>

#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "stateholder.h"

class GameSpecialTest : public ::testing::Test {
public:
    static void SetUpTestSuite() {
        
        std::queue<DelayEvent> eventQueue;
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateTextEntered(108));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(111));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(117));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(105));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(115));
        eventQueue.push(simulateKeyReleased(1));
        
        test_game = std::make_unique<Game>(
                        std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                            SoundMaker<MockSound>>(),
                        &makeSingleLetterSpoken);
        
        auto& window = dynamic_cast<MockWindow&>(test_game->getWindow());
        window.setEventQueue(eventQueue);
        test_game->EventLoop();
    
    }
    
    static void TearDownTestSuite() {
        test_game.reset();
        test_game = nullptr;
    }
    
    static std::unique_ptr<Game> test_game;
    
};

std::unique_ptr<Game> GameSpecialTest::test_game = nullptr;

TEST_F (GameSpecialTest, HandleKeyPressed) { 
    
    auto another_game = *test_game;
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateOtherPress());
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    
}

TEST_F (GameSpecialTest, DrawSomething) { 
    
    auto another_game = *test_game;
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateOtherPress(1));
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    ASSERT_EQ(1, window.nDraws);
}


TEST_F (GameSpecialTest, TestSpecialStateToStart) {
    
    auto another_game = *test_game;
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, another_game.getCurrentState());
    
}

TEST_F (GameSpecialTest, TestSpecialStateToPlay) { 
    
    auto another_game = *test_game;
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateKeyReleased(3));
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, another_game.getCurrentState());
    
}
