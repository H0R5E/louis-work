
#pragma once

#include <chrono>
#include <memory>
#include <queue>
#include <thread>

#include "scene.h"
#include "service.h"
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

inline const DelayEvent simulateOtherPress(int delay) {
    auto event = simulateOtherPress();
    event.delay = delay;
    return event;
}

inline const DelayEvent simulateCtrlC(bool isPolled) {
    auto event = simulateCtrlC();
    event.isPolled = isPolled;
    return event;
}

class MockWindow : public Window {
public:
    MockWindow () = default;
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
        status = sf::Sound::Status::Playing;
        isReset = false;
        clock.restart();
    }
    void pause () override {
        if (status == sf::Sound::Status::Stopped) {
            return;
        }
        status = sf::Sound::Status::Paused;
        elapsedTime += clock.getElapsedTime();
    }
    void stop () override {
        if (status == sf::Sound::Status::Stopped) {
            return;
        };
        status = sf::Sound::Status::Stopped;
        isReset = true;
    }
    void setBuffer (const sf::SoundBuffer &buffer) override {
        this->buffer = sf::SoundBuffer(buffer);
        bufferSet = true;
    }
    void setLoop (bool loop) override {
        isLooping = loop;
        if (!loop) {
            clock.restart();
        }
    }
    sf::Sound::Status getStatus () const override {
        if (!isLooping) {
            auto totalTime = clock.getElapsedTime() + elapsedTime;
            if (totalTime > buffer.getDuration()) {
                return sf::Sound::Status::Stopped;
            }
        }
        return status;
    };
    sf::Sound::Status status {sf::Sound::Status::Stopped};
    bool bufferSet {false};
    bool isPlaying {false};
    bool isPaused {false};
    bool isLooping {false};
    bool isReset {true};
private:
    sf::SoundBuffer buffer;
    sf::Clock clock;
    sf::Time elapsedTime {sf::seconds(0.0f)};
};

class MockService : public Service {
public:
    void setScene () override {}
    Scene* getScenePtr () override {
        return scene.get();
    }
    sf::Font& getFont (std::string_view name) override {
        return font;
    }
    sf::SoundBuffer& getSoundBuffer (std::string_view name) override {
        return buffer;
    }
    Window* getWindowPtr () override {
        return window.get();
    }
    std::unique_ptr<Sound> makeSoundPtr () override {
        return std::make_unique<MockSound>();
    }
private:
    sf::SoundBuffer buffer {};
    sf::Font font {};
    std::unique_ptr<Scene> scene {std::make_unique<Scene>()};
    std::unique_ptr<Window> window {std::make_unique<MockWindow>()};
};
