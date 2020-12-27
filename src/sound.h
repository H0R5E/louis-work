
#pragma once

#include <SFML/Audio.hpp>

class Sound {
public:
    virtual void play () = 0;
    virtual void pause () = 0;
    virtual void stop () = 0;
    virtual void setBuffer (const sf::SoundBuffer &buffer) = 0;
    virtual void setLoop (bool loop) = 0;
    virtual ~Sound () = default;
};

class SoundAdapter: public Sound, private sf::Sound
{
public:
    SoundAdapter() :
        sf::Sound() {};
    virtual void play () override {
        sf::Sound::play();
    };
    virtual void pause () override {
        sf::Sound::pause();
    };
    virtual void stop () override {
        sf::Sound::stop();
    }
    virtual void setBuffer (const sf::SoundBuffer &buffer) override {
        sf::Sound::setBuffer(buffer);
    };
    virtual void setLoop (bool loop) override {
        sf::Sound::setLoop(loop);
    };
};
