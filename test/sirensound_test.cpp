
#include "gtest/gtest.h"
#include "mock.h"

#include "sirensound.h"

TEST (SirenSoundTest, PlayLetter) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SirenSoundTest, PlayLetterStop) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SirenSoundTest, EmptyEvent) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SirenSoundTest, NoReplay) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    ASSERT_TRUE(!test.update());
    
}
