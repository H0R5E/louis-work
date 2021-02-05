
#include "gtest/gtest.h"
#include "mock.h"

#include "specialsound.h"

TEST (SpecialSound, setActiveEvent) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    test.setActiveEvent(simulateTextEntered(50), service);
    
}

TEST (SpecialSound, setNoActiveEvent) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    test.setActiveEvent(service);
    
}

TEST (SpecialSound, NoUpate) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialSound, PlayWord) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (SpecialSound, PlayWordBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SpecialSound, NoSecondUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialSound, NoSoundCompleted) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialSound test {service, "TEST", std::move(color)};
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SpecialSound, SoundFinishedCompleted) { 
    
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

TEST (SpecialSound, NoPlayWord) { 
    
    MockService service {};
    SpecialSound test {service, "TEST"};
    test(service);
    ASSERT_THROW(test.getSoundPtr(), std::runtime_error);
    
}
