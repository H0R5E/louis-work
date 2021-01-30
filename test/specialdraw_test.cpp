
#include "gtest/gtest.h"
#include "mock.h"

#include "specialdraw.h"

TEST (SpecialDraw, setActiveEvent) { 
    
    MockService service {};
    SpecialDraw test {service, "TEST"};
    test.setActiveEvent(simulateTextEntered(50), service);
    
}

TEST (SpecialDraw, setNoActiveEvent) { 
    
    MockService service {};
    SpecialDraw test {service, "TEST"};
    test.setActiveEvent(service);
    
}

TEST (SpecialDraw, DrawLetter) { 
    
    MockService service {};
    SpecialDraw test {service, "TEST"};
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SpecialDraw, DrawLetterBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (SpecialDraw, DrawLetterNoUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    test(service);
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialDraw, DrawLetterUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test(service);
    ASSERT_TRUE(test.update());
    
}

TEST (SpecialDraw, DrawLetterNoUpdateAgain) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test(service);
    test.update();
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialDraw, Abort) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    test.abort();
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SpecialDraw, Completed) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(1500));
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SpecialDraw, DrawSomething) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, "TEST", std::move(color)};
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    auto& window = dynamic_cast<MockWindow&>(service.getWindow());
    ASSERT_TRUE(window.nDraws == 1);
    
}
