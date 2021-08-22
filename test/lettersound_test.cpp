
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


