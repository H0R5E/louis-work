
#include "gtest/gtest.h"
#include "mock.h"

#include "sound.h"
#include "factory.h"

TEST (SceneFactoryTest, init) { 
    ASSERT_NO_THROW(SceneFactory());
}

TEST (SceneFactoryTest, makeCommand) { 
    auto factory = SceneFactory();
    auto scene = factory.makeScene();
    ASSERT_TRUE(scene != nullptr);
}
