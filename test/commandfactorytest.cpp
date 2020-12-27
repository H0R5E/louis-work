
#include "gtest/gtest.h"

#include "sound.h"
#include "commandfactory.h"

TEST (CommandFactoryTest, NoThrow) { 
    ASSERT_NO_THROW(CommandFactory<SoundAdapter>());
}
