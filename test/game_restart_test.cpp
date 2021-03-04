
#include <memory>

#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "stateholder.h"

class GameRestartTest : public ::testing::Test {
public:
    static void SetUpTestSuite() {
        
        std::queue<DelayEvent> eventQueue;
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        eventQueue.push(simulateTextEntered(10));
        eventQueue.push(simulateKeyReleased(1));
        
        test_game = std::make_unique<MockGame>(
                        std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                            SoundMaker<MockSound>>(),
                        &makeSingleLetterSiren);
        test_game->EventLoop();
    
    }
    
    static void TearDownTestSuite() {
        test_game.reset();
        test_game = nullptr;
    }
    
    static std::unique_ptr<MockGame> test_game;
    
};

std::unique_ptr<MockGame> GameRestartTest::test_game = nullptr;

TEST_F (GameRestartTest, DrawStateRestart) { 
    
    auto another_game = *test_game;
    auto& first_scene = another_game.getCurrentScene();
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    
    auto& second_scene = another_game.getCurrentScene();
    
    ASSERT_NE(&first_scene, &second_scene);
    
}

TEST_F (GameRestartTest, WaitStateRestart) { 
    
    auto another_game = *test_game;
    auto& first_scene = another_game.getCurrentScene();
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased());
    eventQueue.push(simulateKeyReleased(1));
    eventQueue.push(simulateKeyReleased());
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    
    auto& second_scene = another_game.getCurrentScene();
    
    ASSERT_NE(&first_scene, &second_scene);
    
}
