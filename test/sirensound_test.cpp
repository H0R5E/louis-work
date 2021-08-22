
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

#include "sirensound.h"

TEST (SirenSoundTest, PlayLetter) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (SirenSoundTest, PlayBackground) { 
    
    MockService service {};
    SirenSound test {service,
                     std::make_unique<sf::Color>(sf::Color::Black)};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}


TEST (SirenSoundTest, PlayLetterStop) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(simulateTextEntered(50), service);
    test(service);
    std::this_thread::sleep_for(std::chrono::milliseconds(800));
    ASSERT_TRUE(test.isCompleted());
    
}

TEST (SirenSoundTest, EmptyEvent) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(service);
    test(service);
    ASSERT_TRUE(!test.isCompleted());
    
}

TEST (SirenSoundTest, NoReplay) { 
    
    MockService service {};
    SirenSound test {service};
    test.setActiveEvent(simulateTextEntered(1), service);
    test(service);
    ASSERT_TRUE(!test.update());
    
}
