
#include "gtest/gtest.h"
#include "mock.h"

#include "typewriterdraw.h"

TEST (TypeWriterDraw, Copy) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.abort();
    TypeWriterDraw copy (test);
    ASSERT_TRUE(copy.isCompleted());
    
}

TEST (TypeWriterDraw, setActiveEvent) { 
    
    MockService service {};
    TypeWriterDraw test {service, sf::Color::Yellow};
    test.setActiveEvent(simulateTextEntered(50), service);
    
}

TEST (TypeWriterDraw, setNoActiveEvent) { 
    
    MockService service {};
    TypeWriterDraw test {service, sf::Color::Yellow};
    test.setActiveEvent(service);
    
}

TEST (TypeWriterDraw, DrawLetter) { 
    
    MockService service {};
    TypeWriterDraw test {service, sf::Color::Yellow};
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (TypeWriterDraw, DrawLetterBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (TypeWriterDraw, DrawLetterNoUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test(service);
    ASSERT_TRUE(!test.update());
    
}

TEST (TypeWriterDraw, DrawLetterUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(test.update());
    
}

TEST (TypeWriterDraw, DrawLetterNoUpdateWait) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    test.update();
    ASSERT_TRUE(!test.update());
    
}

TEST (TypeWriterDraw, Abort) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.abort();
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (TypeWriterDraw, Completed) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (TypeWriterDraw, DrawSomething) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.update();
    test(service);
    auto& window = dynamic_cast<MockWindow&>(service.getWindow());
    ASSERT_TRUE(window.nDraws == 1);
    
}

TEST (TypeWriterDraw, DrawTwoLetters) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.update();
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    auto& window = dynamic_cast<MockWindow&>(service.getWindow());
    const auto* text = dynamic_cast<const sf::Text*>(window.last_drawn);
    ASSERT_TRUE(text->getString().getSize() == 2);
    
}

TEST (TypeWriterDraw, DrawLineBreak) { 
    
    std::queue<DelayEvent> eventQueue;
    Game service {std::make_unique<MockWindow>(eventQueue),
                  make_polymorphic_value<SoundMakerBase,
                                         SoundMaker<MockSound>>()};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    
    for (int i = 0; i < 20; ++i) {
        test.setActiveEvent(simulateTextEntered(50), service);
        test.update();
        test(service);
    }
    
    auto& window = dynamic_cast<MockWindow&>(service.getWindow());
    const auto* text = dynamic_cast<const sf::Text*>(window.last_drawn);
    std::string word = text->getString();
    
    auto found = word.find("\n");
    ASSERT_TRUE(found != std::string::npos);
    
}

TEST (TypeWriterDraw, Assign) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    TypeWriterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.update();
    test(service);
    test.abort();
    TypeWriterDraw test2 {service, sf::Color::Yellow};
    test2 = test;
    ASSERT_TRUE(test2.isCompleted());
    
}
