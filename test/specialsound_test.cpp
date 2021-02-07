
#include "gtest/gtest.h"
#include "mock.h"

#include "specialsound.h"

TEST (SpecialSoundTest, Copy) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    test.abort();
    SpecialSound copy (test);
    ASSERT_TRUE(copy.isCompleted());
    
}

TEST (SpecialSoundTest, setActiveEvent) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    test.setActiveEvent(simulateTextEntered(50), service);
    
}

TEST (SpecialSoundTest, setNoActiveEvent) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    test.setActiveEvent(service);
    
}

TEST (SpecialSoundTest, NoUpate) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialSoundTest, PlayWord) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (SpecialSoundTest, PlayWordBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SpecialSoundTest, NoSecondUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialSoundTest, NoSoundCompleted) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SpecialSoundTest, SoundFinishedCompleted) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SpecialSoundTest, NoPlayWord) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    test(service);
    ASSERT_THROW(test.getSoundPtr(), std::runtime_error);
    
}

TEST (SpecialSoundTest, Assign) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    test.abort();
    SpecialSound test2 {service, "TEST"};
    test2 = test;
    ASSERT_TRUE(test2.isCompleted());
    
}
