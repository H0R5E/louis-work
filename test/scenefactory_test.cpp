
#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "sound.h"
#include "factory.h"

TEST (SceneFactoryTest, init) { 
    ASSERT_NO_THROW(SceneFactory());
}

TEST (SceneFactoryTest, makeCommand) { 
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    std::make_unique<SoundMaker<MockSound>>()};
    
    auto factory = SceneFactory();
    auto scene = factory.makeScene(test_game);
    
    ASSERT_TRUE(scene != nullptr);
    
}
