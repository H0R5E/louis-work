
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
