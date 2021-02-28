
#include <cstring>
#include <sstream>
#include <spdlog/spdlog.h>

#include "specialsound.h"
#include "service.h"
#include "voice.h"
#include "window.h"

SpecialSound::SpecialSound (const SpecialSound& copy) :
            SoundComponent(copy) {
    init_copy(copy);
}

void SpecialSound::init_copy ( const SpecialSound& copy ) {
    
    if (copy.buffer) {
        buffer = std::make_unique<sf::SoundBuffer>(*copy.buffer);
    }
    
    word = copy.word;
    say_it = copy.say_it;
    aborted = copy.aborted;
    
}

bool SpecialSound::update() {
    
    auto elapsed = clock.getElapsedTime();
    
    std::stringstream log_msg;
    log_msg << "SpecialSound::update letters elapsed: " << elapsed.asSeconds();
    spdlog::get("file_logger")->debug(log_msg.str());
    
    if (elapsed.asSeconds() < 0.5f) {
        return false;
    } else if (!say_it) {
        say_it = true;
        return true;
    }
    
    return false;
    
}

bool SpecialSound::isCompleted() {
    
    spdlog::get("file_logger")->debug("SpecialSound::isCompleted");
    
    if (aborted) {
        return true;
    }
    
    if (!sound) {
        return true;
    }
    
    if (sound->getStatus() == sf::Sound::Status::Playing) {
        return false;
    } else {
        return true;
    }
    
}

void SpecialSound::abort () {
    if (sound) {
        sound->stop();
    }
    aborted = true;
}

void SpecialSound::operator() (Service& service) {
    
    spdlog::get("file_logger")->debug("SpecialSound::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!say_it) {
        return;
    }
    
    Voice voice {};
    
    std::string out {word};
    
    std::for_each(out.begin(), out.end(), [](char & c) {
        c = ::toupper(c);
    });
    
    buffer = std::make_unique<sf::SoundBuffer>(voice.getBuffer(&out[0]));
    
    sound = service.makeSoundPValue();
    sound->setBuffer(*buffer);
    sound->play();
    clock.restart();
    
}

SpecialSound& SpecialSound::operator= (const SpecialSound& copy) {
    
    SoundComponent::operator= (copy);
    init_copy(copy);
    return *this;
    
}
