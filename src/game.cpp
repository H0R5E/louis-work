
#include "game.h"
#include "stateholder.h"

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
    
    current_state = &StateHolder::start;
    current_state->Enter(*this);
    current_state->skipEvents = false;
    
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
                                                                  *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
                        break_loop = true;
                    }
                    
                    break;
                
                case sf::Event::TextEntered:
                    
                    check_state = current_state->HandleTextEntered(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
                        break_loop = true;
                    }
                    
                    break;
                
                case sf::Event::KeyReleased:
                    
                    check_state = current_state->HandleKeyReleased(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
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
        
        check_state = current_state->Update(*this);
            
        if (check_state) {
            current_state = check_state;
            current_state->Enter(*this);
        }
        
        window->display();
        sf::sleep(sf::seconds(fps));
        
    }
    
}

State* Game::getCurrentState() const {
    return current_state;
}

bool Game::hasScene() const {
    if (scene) {
        return true;
    } else {
        return false;
    }
}

void Game::setScene() {
    scene = factory.makeScene(*this);
}

Scene& Game::getScene() const {
    return *scene;
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

const std::vector<char>& Game::getLetters() const {
    return letter_store;
}

void Game::clearLetters() {
    letter_store.clear();
}

std::unique_ptr<Sound> Game::makeSoundPtr () const {
    return sound_maker->Get();
}
