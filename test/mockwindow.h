
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
    int nDraws {0};
    bool isClear {false};
    virtual void close () override {
        isClosed = true;
    };
    virtual bool isOpen () override {
        if (isClosed) {
            return false;
        } else {
            return true;
        }
    };
    virtual bool pollEvent (sf::Event &event) override {
        event = simulateKeypress(sf::Keyboard::C,
                                 false,
                                 true,
                                 false,
                                 false);
        
        if (isPolled) {
            return false;
        } else {
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
private:
    bool isPolled {false};
    bool isClosed {false};
};
