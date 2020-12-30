
#include "gtest/gtest.h"
#include "mock.h"

#include "sound.h"
#include "factory.h"

TEST (CommandFactoryTest, init) { 
    ASSERT_NO_THROW(CommandFactory());
}

TEST (CommandFactoryTest, makeCommand) { 
    auto factory = CommandFactory();
    auto command = factory.makeCommand();
    ASSERT_TRUE(command != nullptr);
}
