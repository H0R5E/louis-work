
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

#include <assert.h> 
#include <sstream>
#include <stdexcept>
#include <spdlog/spdlog.h>

#include "game.h"
#include "stateholder.h"

Game::Game(std::unique_ptr<Window>&& window,
           polymorphic_value<SoundMakerBase>&& sound_maker,
           const bool& test_assets) :
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
    // Load resources
    initResources(test_assets);
    
}

Game::Game (std::unique_ptr<Window> && window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            fPtrBasic&& sceneFPtr,
            const bool& test_assets ) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
    // Load resources
    initResources(test_assets);
    
}

Game::Game (std::unique_ptr<Window> && window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            fPtrColor&& sceneFPtr,
            const bool& test_assets ) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
    // Load resources
    initResources(test_assets);
    
}

Game::Game (std::unique_ptr<Window>&& window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            const std::unordered_set<std::string>& special_words,
            const bool& test_assets) :
        sound_maker(std::move(sound_maker)),
        window(std::move(window)),
        special_words(special_words) {
    
    // Load resources
    initResources(test_assets);
    
}

Game::Game (std::unique_ptr<Window>&& window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            const std::unordered_set<std::string>& special_words,
            fPtrBasic&& sceneFPtr,
            const bool& test_assets) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)),
        special_words(special_words) {
    
    // Load resources
    initResources(test_assets);
    
}

Game::Game (std::unique_ptr<Window>&& window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            const std::unordered_set<std::string>& special_words,
            fPtrColor&& sceneFPtr,
            const bool& test_assets) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)),
        special_words(special_words) {
    
    // Load resources
    initResources(test_assets);
    
}

void Game::initResources (const bool& test_assets) {
    
    if (test_assets) {
        font_holder = ResourceHolder<sf::Font>("fonts", true);
        buffer_holder = ResourceHolder<sf::SoundBuffer>("sounds", true);
    } else {
         // GCOVR_EXCL_START
         font_holder = ResourceHolder<sf::Font>("fonts", false);
         buffer_holder = ResourceHolder<sf::SoundBuffer>("sounds", false);
         // GCOVR_EXCL_STOP
    }
    
    font_holder.Load("Monofett-Regular");
    font_holder.Load("JetBrainsMono-Light");
    buffer_holder.Load("Alarm_or_siren");
    
    auto dummy = factory.makeScene(*this);
    scenes.push_back(std::move(dummy));
    
    current_state = &StateHolder::start;
    current_state->Enter(scenes, *this);
    current_state->skipEvents = false;
    
}

void Game::updateScene () {
    
    if (scenes.size() == 1) {
        return;
    }
    
    if (scenes.size() == 0) {
        throw std::runtime_error("Scene stack is empty");
    }
    
    auto& current_scene = *(scenes[0]);
    
    if (!current_scene.isCompleted()) {
        throw std::runtime_error("Tried to delete scene before completed");
    }
    
    // Start the new scene
    polyComponent new_scene = std::move(scenes.back());
    (*new_scene)(*this);
    getWindow().display();
    
    // Replace the old scenes
    scenes.clear();
    scenes.push_back(std::move(new_scene));
    
    assert (scenes.size() == 1);
    
}

void Game::EventLoop() {
    
    State* check_state;
    constexpr float fps = 1.f / 60.f;
    
    while ( window->isOpen() ) {
        
        sf::Event event;
        bool break_loop {false};
        
        // while there are pending events...
        while (window->pollEvent(event)) {
            
            if (current_state->skipEvents) {
                continue;
            }
            
            // check the type of the event...
            switch (event.type) {
                
                // catch 
                case sf::Event::KeyPressed:
                    
                    check_state = current_state->HandleKeyPressed(event,
                                                                  scenes,
                                                                  *this);
                    
                    if (check_state) {
                        
                        current_state = check_state;
                        current_state->Enter(scenes, *this);
                        updateScene();
                        
                        break_loop = true;
                        
                    }
                    
                    break;
                
                case sf::Event::TextEntered:
                    
                    check_state = current_state->HandleTextEntered(event,
                                                                   scenes,
                                                                   *this);
                    updateScene();
                    
                    if (check_state) {
                        
                        current_state = check_state;
                        current_state->Enter(scenes, *this);
                        updateScene();
                        
                        break_loop = true;
                        
                    }
                    
                    break;
                
                case sf::Event::KeyReleased:
                    
                    check_state = current_state->HandleKeyReleased(event,
                                                                   scenes,
                                                                   *this);
                    
                    if (check_state) {
                        
                        current_state = check_state;
                        current_state->Enter(scenes, *this);
                        updateScene();
                        
                        break_loop = true;
                    }
                
                // we don't process other types of events
                default:
                    break;
                
            }
            
            if (!current_state->skipEvents && break_loop) {
                break;
            }
            
        }
        
        check_state = current_state->Update(scenes, *this);
        updateScene();
            
        if (check_state) {
            
            current_state = check_state;
            current_state->Enter(scenes, *this);
            updateScene();
            
        }
        
        sf::sleep(sf::seconds(fps));
        
    }
    
}

State* Game::getCurrentState() const {
    return current_state;
}

const sf::Font& Game::getFont ( std::string_view name ) const {
    return font_holder.Get(name);
}

const sf::SoundBuffer& Game::getSoundBuffer ( std::string_view name ) const {
    return buffer_holder.Get(name);
}

Window& Game::getWindow() {
    if (!window) {
        throw std::runtime_error("No window");
    }
    return *window;
}

bool Game::triggerSpecial () const {
    
    auto word = getWord();
    
    if (special_words.find(word) != special_words.end()) {
        return true;
    } else {
        return false;
    }
    
}

const std::optional<int> Game::getMaxSpecialLength() const {
    
    if (special_words.empty()) {
        return {};
    }
    
    int max_length {0};
    
    for ( auto it = special_words.begin(); it != special_words.end(); ++it ) {
        auto word_length {it->length()};
        if (word_length > max_length) {
            max_length = word_length;
        }
    }
    
    return max_length;
    
}

void Game::storeLetter(const char letter) {
    
    std::stringstream log_msg;
    log_msg << "Storing letter: " << letter;
    spdlog::info(log_msg.str());
    
    letter_store.push_back(letter);
    
}

const std::string Game::getWord () const {
    
    std::ostringstream out;
    
    for (char c: letter_store) {
        out << c;
    }
 
    std::string word {out.str()};
    
    return word;
}

void Game::clearLetters() {
    letter_store.clear();
}

polyComponent Game::makeScenePValue() {
    return factory.makeScene(*this);
}

polyComponent Game::makeSpecialScenePValue(std::string_view word) {
    return factory.makeSpecialScene(*this, word);
}

polymorphic_value<Sound> Game::makeSoundPValue () {
    return sound_maker->Get();
}
