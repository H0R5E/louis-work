
#include "gtest/gtest.h"
#include "mock.h"

#include "lettersound.h"

TEST (LetterSoundTest, Copy) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    LetterSound test {service, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.abort();
    LetterSound copy (test);
    ASSERT_TRUE(copy.isCompleted());
    
}

TEST (LetterSoundTest, Assign) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    LetterSound test {service, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.abort();
    LetterSound test2 {service};
    test2 = test;
    ASSERT_TRUE(test2.isCompleted());
    
}

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

TEST (LetterSoundTest, PlayBackground) { 
    
    MockService service {};
    LetterSound test {service,
                      std::make_unique<sf::Color>(sf::Color::Black)};
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

TEST (LetterSoundTest, NoBuffer) { 
    
    MockService service {};
    LetterSound test {service};
    ASSERT_TRUE(!test.update());
    
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

TEST (LetterSoundTest, ClearBuffer) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(1100));
    test.setActiveEvent(service);
    test.isCompleted();
    ASSERT_TRUE(!test.update());
    
}

TEST (LetterSoundTest, Abort) { 
    
    MockService service {};
    LetterSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    test.abort();
    ASSERT_TRUE(test.isCompleted());
    
}


