
#include <memory>

#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "stateholder.h"

class GameSpecialTest : public ::testing::Test {
public:
    GameSpecialTest () {
        
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
        
        auto& window = dynamic_cast<MockWindow&>(test_game.getWindow());
        window.setEventQueue(eventQueue);
        test_game.EventLoop();
    
    }
protected:
    Game test_game {std::make_unique<MockWindow>(),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken};
};

TEST_F (GameSpecialTest, HandleKeyPressed) { 
    
    auto another_game = test_game;
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateOtherPress());
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    
}

TEST_F (GameSpecialTest, HandleKeyPressedAgain) { 
    
    auto another_game = test_game;
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateOtherPress());
    eventQueue.push(simulateOtherPress());
    auto& window = dynamic_cast<MockWindow&>(another_game.getWindow());
    window.setEventQueue(eventQueue);
    another_game.EventLoop();
    
}
