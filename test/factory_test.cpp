
#include "gtest/gtest.h"
#include "mock.h"

#include "game.h"
#include "sound.h"
#include "factory.h"

TEST (FactoryTest, makeSpecial) { 
    MockService service {};
    auto special = makeSpecial (service, "TEST");
}

TEST (FactoryTest, SceneFactoryinit) { 
    ASSERT_NO_THROW(SceneFactory());
}

TEST (FactoryTest, SceneFactorymakeScene) { 
    
    std::queue<DelayEvent> eventQueue;
    Game test_game {std::make_unique<MockWindow>(eventQueue),
                    make_polymorphic_value<SoundMakerBase,
                                           SoundMaker<MockSound>>()};
    
    auto factory = SceneFactory();
    auto scene = factory.makeScene(test_game);
    
    ASSERT_TRUE(scene);
    
}
