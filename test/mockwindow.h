
#pragma once

#include <stack>

#include "window.h"

const sf::Event simulateKeypress(sf::Keyboard::Key key,
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

class MockWindow : public Window {
public:
    MockWindow (std::stack<sf::Event> eventStack) : 
        eventStack {eventStack} {};
    virtual void close () override {
        isClosed = true;
    };
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
    };
    virtual bool pollEvent (sf::Event &event) override {
        if (isPolled) {
            return false;
        } else {
            event = eventStack.top();
            isPolled = true;
            return true;
        }
    };
    virtual void clear (
            const sf::Color &color=sf::Color(0, 0, 0, 255)) override {
        isClear = true;
        nDraws = 0;
    };
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
