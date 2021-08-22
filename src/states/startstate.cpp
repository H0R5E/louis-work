
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

#include <spdlog/spdlog.h>

#include "startstate.h"

#include "service.h"
#include "stateholder.h"
#include "window.h"

State* StartState::HandleKeyPressed (const sf::Event& event,
                                     polyComponentVector& scenes,
                                     Service& service) {
    
    spdlog::debug("StartState::HandleKeyPressed");
    
    // Using Ctrl + C to exit
    if (event.key.control && event.key.code == sf::Keyboard::C) {
        auto& window = service.getWindow();
        window.close();
    }
    
    return nullptr;
    
}

State* StartState::HandleTextEntered (const sf::Event& event,
                                      polyComponentVector& scenes,
                                      Service& service) {
    
    spdlog::debug("StartState::HandleTextEntered");
    
    auto& scene = *(scenes[0]);
    scene.abort();
    
    auto new_scene = service.makeScenePValue();
    scenes.push_back(std::move(new_scene));
    service.clearLetters();
    return &StateHolder::play;
    
}

State* StartState::Update (polyComponentVector& scenes,
                           Service& service) {
    skipEvents = false;
    return nullptr;
}

void StartState::Enter (polyComponentVector& scenes,
                        Service& service) {
    
    skipEvents = true;
    
    auto& window = service.getWindow();
    window.clear(sf::Color::Blue);
    
    auto width = sf::VideoMode::getDesktopMode().width;
    auto height = sf::VideoMode::getDesktopMode().height;
    
    sf::Text text;
    auto& title_font = service.getFont("Monofett-Regular");
    auto& menu_font = service.getFont("JetBrainsMono-Light");
    
    text.setFont(title_font); 
    text.setString("Louis' Work");
    text.setCharacterSize(96); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    sf::FloatRect textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f));
    
    window.draw(text);
    
    text.setFont(menu_font); 
    text.setString("Press Any Key to Start");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 80.0f));
    
    window.draw(text);
    
    text.setString("Press Ctrl-C to Quit");
    text.setCharacterSize(30); // in pixels, not points!
    text.setFillColor(sf::Color::Yellow);
    
    //center text
    textRect = text.getLocalBounds();
    text.setOrigin(textRect.left + textRect.width / 2.0f,
                   textRect.top + textRect.height / 2.0f);
    text.setPosition(sf::Vector2f(width / 2.0f, height / 2.0f + 120.0f));
    
    window.draw(text);
    window.display();
    
    spdlog::info("Entering StartState");
    
    return;
    
}
