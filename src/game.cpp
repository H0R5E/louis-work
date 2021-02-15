
#include "game.h"
#include "stateholder.h"

#include <assert.h> 
#include <iostream>
#include <sstream>
#include <stdexcept>

Game::Game(std::unique_ptr<Window>&& window,
           polymorphic_value<SoundMakerBase>&& sound_maker) :
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
    // Load resources
    initResources();
    
}

Game::Game (std::unique_ptr<Window> && window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            fPtrType&& sceneFPtr ) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
    // Load resources
    initResources();
    
}

Game::Game (std::unique_ptr<Window>&& window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            const std::unordered_set<std::string>& special_words) :
        sound_maker(std::move(sound_maker)),
        window(std::move(window)),
        special_words(special_words) {
    
    // Load resources
    initResources();
    
}

Game::Game (std::unique_ptr<Window>&& window,
            polymorphic_value<SoundMakerBase>&& sound_maker,
            const std::unordered_set<std::string>& special_words,
            fPtrType&& sceneFPtr) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)),
        special_words(special_words) {
    
    // Load resources
    initResources();
    
}

void Game::initResources () {
    
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
    
    std::cout << "Game::updateScene" << std::endl;
    std::cout << "scenes.size(): " << scenes.size() << std::endl;
    
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
