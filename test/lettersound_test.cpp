
#include "gtest/gtest.h"
#include "mock.h"

#include "lettersound.h"

TEST (LetterSoundTest, PlayLetter) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (LetterSoundTest, PlayUmmm) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (LetterSoundTest, EmptyEvent) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(service);
    test(service);
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (LetterSoundTest, NoReplay) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    ASSERT_TRUE(!test.update());
    
}

TEST (LetterSoundTest, Replay) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(1100));
    ASSERT_TRUE(test.update());
    
}

