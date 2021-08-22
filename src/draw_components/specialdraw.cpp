
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

#include <sstream>
#include <spdlog/spdlog.h>

#include "specialdraw.h"
#include "service.h"
#include "window.h"

bool SpecialDraw::update() {
    
    auto elapsed = clock.getElapsedTime();
    
    std::stringstream log_msg;
    log_msg << "SpecialDraw::update time elapsed: " << elapsed.asSeconds();
    spdlog::debug(log_msg.str());
    
    if (elapsed.asSeconds() < 0.5f) {
        return false;
    } else if (!draw_it) {
        draw_it = true;
        return true;
    }
    
    return false;
    
}

bool SpecialDraw::isCompleted () {
    
    spdlog::debug("SpecialDraw::isCompleted");
    
    if (aborted) {
        return true;
    }
    
    auto elapsed = clock.getElapsedTime();
    
    std::stringstream log_msg;
    log_msg << "SpecialDraw::isCompleted time elapsed: " << elapsed.asSeconds();
    spdlog::debug(log_msg.str());
    
    if (elapsed.asSeconds() < 2.0f)
        return false;
    
    return true;
    
}

void SpecialDraw::abort () {
    aborted = true;
}

void SpecialDraw::operator() (Service& service) {
    
    spdlog::debug("SpecialDraw::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!draw_it) {
        return;
    }
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& letter_font = service.getFont("JetBrainsMono-Light");
    
    std::string out {word};
    
    std::for_each(out.begin(), out.end(), [](char & c) {
        c = ::toupper(c);
    });
    
    text.setFont(letter_font); 
    text.setString(out);
    text.setCharacterSize(120); // in pixels, not points!
    text.setFillColor(foreground);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    auto& window = service.getWindow();
    window.draw(text);
    
    clock.restart();
    
}
