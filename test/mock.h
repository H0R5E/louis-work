
#pragma once

#include <chrono>
#include <queue>
#include <thread>

#include "sound.h"
#include "window.h"

class DelayEvent : public sf::Event {
public:
    int delay {0};
    bool isPolled {true};
};

inline const DelayEvent simulateKeyPressed(sf::Keyboard::Key key,
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
    
    DelayEvent event;
    event.type = sf::Event::KeyPressed;
    event.key = data;
    return event;
}

inline const DelayEvent simulateTextEntered(sf::Uint32 value)
{
    sf::Event::TextEvent data;
    data.unicode = value;
    
    DelayEvent event;
    event.type = sf::Event::TextEntered;
    event.text = data;
    return event;
}

inline const DelayEvent simulateKeyReleased()
{
    DelayEvent event;
    event.type = sf::Event::KeyReleased;
    return event;
}

inline const DelayEvent simulateKeyReleased(int delay) {
    auto event = simulateKeyReleased();
    event.delay = delay;
    return event;
}

inline const DelayEvent simulateCtrlC() {
    return simulateKeyPressed(sf::Keyboard::C,
                              false,
                              true,
                              false,
                              false);
}

inline const DelayEvent simulateOtherPress() {
    return simulateKeyPressed(sf::Keyboard::D,
                              false,
                              false,
                              false,
                              false);
}

inline const DelayEvent simulateCtrlC(bool isPolled) {
    auto event = simulateCtrlC();
    event.isPolled = isPolled;
    return event;
}

class MockWindow : public Window {
public:
    MockWindow (std::queue<DelayEvent> eventQueue) : 
        eventQueue {eventQueue} {}
    virtual void close () override {
        isClosed = true;
    }
    virtual bool isOpen () override {
        
        if (isPolled) {
            eventQueue.pop();
            isPolled = false;
        };
        
        if (isClosed || eventQueue.size() == 0) {
            return false;
        } else {
            return true;
        }
    }
    virtual bool pollEvent (sf::Event &event) override {
        if (isPolled) {
            return false;
        } else {
            DelayEvent devent = eventQueue.front();
            if (devent.delay > 0) {
                std::this_thread::sleep_for(std::chrono::seconds(devent.delay));
            }
            isPolled = devent.isPolled;
            if (!isPolled) {
                eventQueue.pop();
            }
            event = devent;
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
    std::queue<DelayEvent> eventQueue; 
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
