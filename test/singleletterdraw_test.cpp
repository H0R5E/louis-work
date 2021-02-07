
#include "gtest/gtest.h"
#include "mock.h"

#include "singleletterdraw.h"

TEST (SingleLetterDraw, Copy) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.abort();
    SingleLetterDraw copy (test);
    ASSERT_TRUE(copy.isCompleted());
    
}

TEST (SingleLetterDraw, Assign) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.abort();
    SingleLetterDraw test2 {service};
    test2 = test;
    ASSERT_TRUE(test2.isCompleted());
    
}

TEST (SingleLetterDraw, DrawLetterBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}
