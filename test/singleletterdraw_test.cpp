
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

#include "singleletterdraw.h"

TEST (SingleLetterDraw, Copy) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.abort();
    SingleLetterDraw copy (test);
    ASSERT_TRUE(copy.isCompleted());
    
}

TEST (SingleLetterDraw, Assign) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test.abort();
    SingleLetterDraw test2 {service, sf::Color::Yellow};
    test2 = test;
    ASSERT_TRUE(test2.isCompleted());
    
}

TEST (SingleLetterDraw, DrawLetterBackground) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, sf::Color::Yellow, std::move(color)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SingleLetterDraw, restartService) { 
    
    MockService service {"longerthanten"};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, sf::Color::Yellow, std::move(color)};
    
    ASSERT_TRUE(test.restartService(service));
    
}

TEST (SingleLetterDraw, restartKeyTrue) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, sf::Color::Yellow, std::move(color)};
    
    ASSERT_TRUE(test.restartKey(simulateReturn().key));
    
}

TEST (SingleLetterDraw, restartKeyFalse) { 
    
    MockService service {};
    std::unique_ptr<sf::Color> color {
                            std::make_unique<sf::Color>(sf::Color::Black)};
    SingleLetterDraw test {service, sf::Color::Yellow, std::move(color)};
    
    ASSERT_FALSE(test.restartKey(simulateOtherPress().key));
    
}
