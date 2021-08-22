
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

#include "sirensound.h"

TEST (GameTest, TestConstruct) {
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    true};
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestConstructSpecial) {
    
    std::queue<DelayEvent> eventQueue;
    std::unordered_set<std::string> special_words {"test"};
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    special_words,
                    true};
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestConstructSpecialComponent) { 
    
    std::queue<DelayEvent> eventQueue;
    std::unordered_set<std::string> special_words {"test"};
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    special_words,
                    drawComponentMaker<SingleLetterDraw>(),
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestConstructSpecialScene) { 
    
    std::queue<DelayEvent> eventQueue;
    std::unordered_set<std::string> special_words {"test"};
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    special_words,
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestNoWindow) {
    
    ASSERT_THROW(Game (std::unique_ptr<MockWindow>(),
                       make_polymorphic_value<SoundMakerBase,
                                                SoundMaker<MockSound>>(),
                       true),
                 std::runtime_error);
    
}

TEST (GameTest, TestNoScenes) {
    
    std::queue<DelayEvent> eventQueue;
    MockGame test_game {std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                               SoundMaker<MockSound>>()};
    test_game.clearScenes();
    ASSERT_THROW(test_game.updateScene();, std::runtime_error);
}

TEST (GameTest, TestSceneNotComplete) {
    
    std::queue<DelayEvent> eventQueue;
    MockGame test_game {std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                               SoundMaker<MockSound>>(),
                        componentMaker<NotComplete>()};
    test_game.addScene(make_polymorphic_value<Component,
                                              NotComplete>(test_game));
    ASSERT_THROW(test_game.updateScene();, std::runtime_error);
    
}

TEST (GameTest, TestStartStateEnter) {
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    true};
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestStartStateExit) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    ASSERT_NO_THROW(test_game.EventLoop());

    MockWindow& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    ASSERT_EQ(true, window.isClosed);
    
}

TEST (GameTest, TestStartStateDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    MockWindow& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    ASSERT_EQ(3, window.nDraws);
    
}

TEST (GameTest, TestPlayStateEnter) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateOtherPress());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateScene) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateOtherPress());
    MockGame test_game {std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                               SoundMaker<MockSound>>(),
                        &makeSingleLetterSpoken};
    test_game.EventLoop();
    ASSERT_TRUE(test_game.getScenePtr() != nullptr);
    
}

TEST (GameTest, TestPlayStateClear) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    MockWindow& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    ASSERT_TRUE(window.isClear);
    
}

TEST (GameTest, TestPlayStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestStartStateSkipEvents) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC(false));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateToDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateOtherPress());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::draw, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateTextNotHandled) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(999));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::play, test_game.getCurrentState());
    
}

TEST (GameTest, TestDrawStateDraw) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    MockWindow& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    ASSERT_GT(window.nDraws, 0);
    
}

TEST (GameTest, TestDrawStateToStart) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestDrawStateToSpecial) { 
    
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
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::special, test_game.getCurrentState());
    
}

TEST (GameTest, TestPlayStateClearSecond) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateCtrlC());
    eventQueue.push(simulateTextEntered(10));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    MockWindow& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    ASSERT_TRUE(window.isClear);
    
}


TEST (GameTest, TestDrawStateToPlay) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSiren,
                    true};
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
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::wait, test_game.getCurrentState());
    
}

TEST (GameTest, TestWaitStateUpdate) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased());
    eventQueue.push(simulateOtherPress());
    auto test = componentMaker<SirenSound>();
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    componentMaker<NotComplete>(),
                    true};
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
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
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
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::start, test_game.getCurrentState());
    
}

TEST (GameTest, TestWaitStateToSpecial) { 
    
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
    eventQueue.push(simulateKeyReleased());
    eventQueue.push(simulateOtherPress(1));
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    &makeSingleLetterSpoken,
                    true};
    test_game.EventLoop();
    ASSERT_EQ(&StateHolder::special, test_game.getCurrentState());
    
}


TEST (GameTest, TestDrawStatePlaying) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    MockGame test_game {std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                               SoundMaker<MockSound>>(),
                        &makeSingleLetterSpoken};
    test_game.EventLoop();
    
    Scene* scenePtr = dynamic_cast<Scene*>(test_game.getScenePtr());
    
    if (scenePtr == nullptr) {
        FAIL() << "scenePtr is NULL";
    }
    
    MockSound *soundPtr = dynamic_cast<MockSound*>(
        scenePtr->getSoundComponentPtr()->getSoundPtr());
    
    if (soundPtr == nullptr) {
        FAIL() << "soundPtr is NULL";
    }
    
    ASSERT_EQ(soundPtr->getStatus(), sf::Sound::Status::Playing);
    
}

TEST (GameTest, TestPlayStateSoundStopped) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    MockGame test_game {std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                               SoundMaker<MockSound>>(),
                        &makeSingleLetterSiren};
    test_game.EventLoop();
    Scene* scenePtr = dynamic_cast<Scene*>(test_game.getScenePtr());
    
    if (scenePtr == nullptr) {
        FAIL() << "scenePtr is NULL";
    }
    
    MockSound *soundPtr = dynamic_cast<MockSound*>(
        scenePtr->getSoundComponentPtr()->getSoundPtr());
    
    if (soundPtr == nullptr) {
        FAIL() << "soundPtr is NULL";
    }
    
    ASSERT_EQ(soundPtr->getStatus(), sf::Sound::Status::Stopped);
    
}

TEST (GameTest, SceneRestartSpecial) { 
    
    std::queue<DelayEvent> eventQueue;
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateTextEntered(10));
    eventQueue.push(simulateKeyReleased(1));
    MockGame test_game {std::make_unique<MockWindow>(eventQueue),
                        make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                        &makeTypeWriterSpoken};
    test_game.EventLoop();
    
    auto& first_scene = test_game.getCurrentScene();
    auto& test_scene = test_game.getCurrentScene();
    
    std::queue<DelayEvent> eventQueueTwo;
    eventQueueTwo.push(simulateReturn());
    eventQueueTwo.push(simulateTextEntered(10));
    eventQueueTwo.push(simulateKeyReleased(1));
    auto& window = dynamic_cast<MockWindow&>(test_game.getWindow());
    window.setEventQueue(eventQueueTwo);
    test_game.EventLoop();
    
    auto& second_scene = test_game.getCurrentScene();
    
    ASSERT_NE(&first_scene, &second_scene);
    
}

TEST (GameTest, NoSpecialLength) { 
    
    std::unordered_set<std::string> special_words {};
    Game test_game {std::make_unique<MockWindow>(),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>(),
                    special_words,
                    &makeSingleLetterSpoken,
                    true};
    
    auto test = test_game.getMaxSpecialLength();
    
    ASSERT_TRUE(!test);
    
}
