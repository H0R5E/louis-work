
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
            std::unique_ptr<Command> && command ) :
        factory(std::move(command)),
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
    
    command = factory.makeCommand();
    
}

void Game::EventLoop() {
    
    State* check_state;
    constexpr float fps = 1.f / 60.f;
    
    while ( window->isOpen() ) {
        
        sf::Event event;
        
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
                    }
                    
                    break;
                
                case sf::Event::TextEntered:
                    
                    check_state = current_state->HandleTextEntered(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
                    }
                    
                    break;
                
                case sf::Event::KeyReleased:
                    
                    check_state = current_state->HandleKeyReleased(event,
                                                                   *this);
                    
                    if (check_state) {
                        current_state = check_state;
                        current_state->Enter(*this);
                    }
                
                // we don't process other types of events
                default:
                    break;
                
            }
            
        }
        
        check_state = current_state->Update(*this);
        
        if (check_state) {
            current_state = check_state;
            current_state->Enter(*this);
        }
        
        sf::sleep(sf::seconds(fps));
        
    }
    
}

Command* Game::getCommandPtr() {
    return command.get();
}

State* Game::getCurrentState() {
    return current_state;
}

sf::Font& Game::getFont ( std::string_view name ) {
    return font_holder.Get(name);
}

sf::SoundBuffer& Game::getSoundBuffer ( std::string_view name ) {
    return buffer_holder.Get(name);
}

Window* Game::getWindowPtr() {
    return window.get();
}

std::unique_ptr<Sound> Game::makeSoundPtr () {
    return sound_maker->Get();
}
