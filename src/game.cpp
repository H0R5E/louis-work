
#include "game.h"
#include "stateholder.h"

#include <assert.h> 
#include <sstream>
#include <stdexcept>

Game::Game(std::unique_ptr<Window>&& window,
           std::unique_ptr<SoundMakerBase>&& sound_maker) :
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
    // Load resources
    initResources();
    
}

Game::Game (std::unique_ptr<Window> && window,
            std::unique_ptr<SoundMakerBase>&& sound_maker,
            fPtrType&& sceneFPtr ) :
        factory(std::move(sceneFPtr)),
        sound_maker(std::move(sound_maker)),
        window(std::move(window)) {
    
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
    
    uniqueComponent new_scene = std::move(scenes.back());
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
        
        updateScene();
        
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
                                                                  *(scenes[0]),
                                                                  *this);
                    
                    if (check_state) {
                        
                        current_state = check_state;
                        current_state->Enter(scenes, *this);
                        
                        break_loop = true;
                        
                    }
                    
                    break;
                
                case sf::Event::TextEntered:
                    
                    check_state = current_state->HandleTextEntered(event,
                                                                   *(scenes[0]),
                                                                   *this);
                    
                    if (check_state) {
                        
                        current_state = check_state;
                        current_state->Enter(scenes, *this);
                        
                        break_loop = true;
                        
                    }
                    
                    break;
                
                case sf::Event::KeyReleased:
                    
                    check_state = current_state->HandleKeyReleased(event,
                                                                   *(scenes[0]),
                                                                   *this);
                    
                    if (check_state) {
                        
                        current_state = check_state;
                        current_state->Enter(scenes, *this);
                        
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
        
        check_state = current_state->Update(*(scenes[0]), *this);
            
        if (check_state) {
            
            current_state = check_state;
            current_state->Enter(scenes, *this);
            
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

Window& Game::getWindow() const {
    return *window;
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

uniqueComponent Game::makeScenePtr() {
    return factory.makeScene(*this);
}

std::unique_ptr<Sound> Game::makeSoundPtr () const {
    return sound_maker->Get();
}
