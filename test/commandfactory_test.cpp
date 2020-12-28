
#include "gtest/gtest.h"

#include "sound.h"
#include "factory.h"

TEST (CommandFactoryTest, NoThrow) { 
    ASSERT_NO_THROW(CommandFactory());
}
