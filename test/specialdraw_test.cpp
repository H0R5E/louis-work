
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "gtest/gtest.h"
#include "mock.h"

#include "specialdraw.h"

TEST (SpecialDraw, setActiveEvent) { 
    
    MockService service {};
    SpecialDraw test {service, sf::Color::Yellow, "TEST"};
    test.setActiveEvent(simulateTextEntered(50), service);
    
}

TEST (SpecialDraw, setNoActiveEvent) { 
    
    MockService service {};
    SpecialDraw test {service, sf::Color::Yellow, "TEST"};
    test.setActiveEvent(service);
    
}

TEST (SpecialDraw, DrawLetter) { 
    
    MockService service {};
    SpecialDraw test {service, sf::Color::Yellow, "TEST"};
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SpecialDraw, DrawLetterBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (SpecialDraw, DrawLetterNoUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
    test(service);
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialDraw, DrawLetterUpdate) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test(service);
    ASSERT_TRUE(test.update());
    
}

TEST (SpecialDraw, DrawLetterNoUpdateAgain) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test(service);
    test.update();
    ASSERT_TRUE(!test.update());
    
}

TEST (SpecialDraw, Abort) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
    test.abort();
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SpecialDraw, Completed) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
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
    SpecialDraw test {service, sf::Color::Yellow, "TEST", std::move(color)};
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    test.update();
    test(service);
    auto& window = dynamic_cast<MockWindow&>(service.getWindow());
    ASSERT_TRUE(window.nDraws == 1);
    
}
