
#include "gtest/gtest.h"
#include "mock.h"

#include "lettersound.h"

TEST (LetterSound, PlayLetter) { 
    
    MockService service {};
    LetterSound test {service};
    test.set_active_event(simulateTextEntered(50), service);
    test.play(service);
    ASSERT_TRUE(!test.isCompleted());
    
}
