
#pragma once

#include <chrono>
#include <stack>
#include <thread>

#include "sound.h"
#include "window.h"

const sf::Event simulateKeyPressed(sf::Keyboard::Key key,
                                   bool alt,
                                   bool control,
                                   bool shift,
                                   bool system)
{
    sf::Event::KeyEvent data;
    data.code = key;
    data.alt = alt;
    data.control = control;
    data.shift = shift;
    data.system = system;
    
    sf::Event event;
    event.type = sf::Event::KeyPressed;
    event.key = data;
    return event;
}

const sf::Event simulateTextEntered(sf::Uint32 value)
{
    sf::Event::TextEvent data;
    data.unicode = value;
    
    sf::Event event;
    event.type = sf::Event::TextEntered;
    event.text = data;
    return event;
}

const sf::Event simulateTextEntered(sf::Uint32 value,
                                    int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    return simulateTextEntered(value);
}

const sf::Event simulateKeyReleased()
{
    sf::Event event;
    event.type = sf::Event::KeyReleased;
    return event;
}

const sf::Event simulateKeyReleased(int delay) {
    std::this_thread::sleep_for(std::chrono::seconds(delay));
    return simulateKeyReleased();
}

const sf::Event simulateCtrlC() {
    return simulateKeyPressed(sf::Keyboard::C,
                              false,
                              true,
                              false,
                              false);
}

class MockWindow : public Window {
public:
    MockWindow (std::stack<sf::Event> eventStack) : 
        eventStack {eventStack} {}
    virtual void close () override {
        isClosed = true;
    }
    virtual bool isOpen () override {
        
        if (isPolled) {
            eventStack.pop();
            isPolled = false;
        };
        
        if (isClosed || eventStack.size() == 0) {
            return false;
        } else {
            return true;
        }
    }
    virtual bool pollEvent (sf::Event &event) override {
        if (isPolled) {
            return false;
        } else {
            event = eventStack.top();
            isPolled = true;
            return true;
        }
    }
    virtual void clear (
            const sf::Color &color=sf::Color(0, 0, 0, 255)) override {
        isClear = true;
        nDraws = 0;
    }
    virtual void draw (const sf::Drawable &drawable) override {
        nDraws++;
    }
    virtual void display () override {};
    int nDraws {0};
    bool isClear {false};
    bool isClosed {false};
private:
    std::stack<sf::Event> eventStack; 
    bool isPolled {false};
};

enum Status { Stopped, Paused, Playing };

class MockSound : public Sound {
public:
    void play () override {
        if (!bufferSet) {
            return;
        }
        status = Status::Playing;
        isReset = false;
    }
    void pause () override {
        if (status == Status::Stopped) {
            return;
        }
        status = Status::Paused;
    }
    void stop () override {
        if (status == Status::Stopped) {
            return;
        };
        status = Status::Stopped;
        isReset = true;
    }
    void setBuffer (const sf::SoundBuffer &buffer) override {
        bufferSet = true;
    }
    void setLoop (bool loop) override {
        isLooping = loop;
    }
    Status status {Status::Stopped};
    bool bufferSet {false};
    bool isPlaying {false};
    bool isPaused {false};
    bool isLooping {false};
    bool isReset {true};
};
