
#pragma once

#include <SFML/Graphics.hpp>

class Window {
public:
    virtual void close () = 0;
    virtual bool isOpen () = 0;
    virtual bool pollEvent (sf::Event &event) = 0;
    virtual void clear (const sf::Color &color=sf::Color(0, 0, 0, 255)) = 0;
    virtual void draw (const sf::Drawable &drawable) = 0;
    virtual void display () = 0;
    virtual ~Window () = default;
};

class WindowAdapter: public Window, private sf::RenderWindow
{
public:
    WindowAdapter():
      sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width,
                                     sf::VideoMode::getDesktopMode().height),
                       "Louis' Work",
                       sf::Style::Fullscreen) {};
    virtual void close () override {
        sf::RenderWindow::close();
    };
    virtual bool isOpen () override {
        return sf::RenderWindow::isOpen();
    };
    virtual bool pollEvent (sf::Event &event) override {
        return sf::RenderWindow::pollEvent(event);
    };
    virtual void clear (
                const sf::Color &color=sf::Color(0, 0, 0, 255)) override {
        sf::RenderWindow::clear(color);
    };
    virtual void draw (const sf::Drawable &drawable) override {
        sf::RenderWindow::draw(drawable);
    };
    virtual void display () override {
        sf::RenderWindow::display();
    };
};
