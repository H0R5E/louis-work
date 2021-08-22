
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

#pragma once

#include <chrono>
#include <memory>
#include <queue>
#include <thread>
#include <spdlog/spdlog.h>

#include "game.h"
#include "singleletterdraw.h"
#include "specialdraw.h"
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

inline const DelayEvent simulateReturn() {
    return simulateKeyPressed(sf::Keyboard::Return,
                              false,
                              false,
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
        
        std::stringstream log_msg;
        log_msg << "eventQueue.size(): " << eventQueue.size();
        spdlog::info(log_msg.str());
        
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
        totalDraws++;
        if (typeid(drawable) == typeid(sf::Text)) {
            auto& text = dynamic_cast<const sf::Text&>(drawable);
            last_text = std::make_unique<sf::Text>(text);
        }
    }
    virtual void display () override {};
    void setEventQueue (std::queue<DelayEvent> eventQueue) {
        this->eventQueue = eventQueue;
    }
    int nDraws {0};
    int totalDraws {0};
    bool isClear {false};
    bool isClosed {false};
    std::unique_ptr<sf::Text> last_text {nullptr};
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
    }
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
    MockService () = default;
    MockService (const std::string& word) :
        letter_store(word) {}
    const sf::Font& getFont (std::string_view name) const override {
        return font;
    }
    const sf::SoundBuffer& getSoundBuffer (std::string_view name) const override {
        return buffer;
    }
    Window& getWindow () override {
        return *window;
    }
    bool triggerSpecial () const override {
        return false;
    }
    const std::optional<int> getMaxSpecialLength () const override {
        return 10;
    }
    void storeLetter (const char letter) override {}
    const std::string getWord () const override {
        return letter_store;
    }
    void clearLetters () override {}
    polymorphic_value<Component> makeScenePValue () override {
        return make_polymorphic_value<Component,
                                      SingleLetterDraw>(*this,
                                                        sf::Color::Yellow);
    }
    polymorphic_value<Component> makeSpecialScenePValue (
                                            std::string_view word) override {
        return make_polymorphic_value<Component, SpecialDraw>(*this,
                                                              sf::Color::Yellow,
                                                              "Test");
    }
    polymorphic_value<Sound> makeSoundPValue () override {
        return make_polymorphic_value<Sound, MockSound>();
    }
private:
    sf::SoundBuffer buffer {};
    sf::Font font {};
    std::shared_ptr<Window> window {std::make_unique<MockWindow>()};
    std::string letter_store {};
};

class MockGame : public Game {
public:
    MockGame(std::unique_ptr<Window>&& window,
             polymorphic_value<SoundMakerBase>&& sound_maker) :
             Game(std::move(window), std::move(sound_maker), true) {}
    MockGame(std::unique_ptr<Window>&& window,
             polymorphic_value<SoundMakerBase>&& sound_maker,
             fPtrBasic&& sceneFPtr)  :
            Game(std::move(window), std::move(sound_maker), *sceneFPtr, true) {}
    MockGame(std::unique_ptr<Window>&& window,
             polymorphic_value<SoundMakerBase>&& sound_maker,
             fPtrColor&& sceneFPtr)  :
                Game(std::move(window),
                std::move(sound_maker),
                *sceneFPtr,
                true) {}
             Component* getScenePtr () {
        return scenes[0].operator->();
    }
    void clearScenes () {
        scenes.clear();
    }
    void addScene(polymorphic_value<Component>&& scene) {
        scenes.push_back(std::move(scene));
    }
    const Component& getCurrentScene() {
        return *(scenes.front());
    }
    void updateScene () {
        Game::updateScene();
    }
};

class NotComplete : public Component {
public:
    NotComplete (Service& service) :
        Component(service) {}
    NotComplete (Service& service,
                 std::unique_ptr<sf::Color>&& background) :
        Component(service, std::move(background)) {}
    void setActiveEvent (const sf::Event& event,
                         Service& service) override {}
    void setActiveEvent (Service& service) override {}
    bool update () override {return true;}
    bool isCompleted () override {
        if (aborted) {
            return true;
        } else {
            return false;
        }}
    void abort () override {aborted = true;}
    void operator () (Service& service) override {};
private:
    bool aborted {false};
};
