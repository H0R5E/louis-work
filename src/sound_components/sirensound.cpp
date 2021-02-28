
#include <sstream>
#include <spdlog/spdlog.h>

#include "sirensound.h"
#include "service.h"
#include "window.h"


void SirenSound::init (Service& service) {
    spdlog::get("file_logger")->debug("SirenSound::init");
    auto& sound_buffer = service.getSoundBuffer("Alarm_or_siren");
    sound = service.makeSoundPValue();
    sound->setBuffer(sound_buffer);
}

void SirenSound::setActiveEvent ( const sf::Event& event, Service& service ) {
    should_replay = true;
}

void SirenSound::setActiveEvent ( Service& service ) {
    should_replay = false;
}

bool SirenSound::update() {
    spdlog::get("file_logger")->debug("SirenSound::update");
    return should_replay;
}

bool SirenSound::isCompleted() {
    
    spdlog::get("file_logger")->debug("SirenSound::isCompleted");
    
    auto elapsed = clock.getElapsedTime();
    
    if (elapsed.asSeconds() < 0.75f && !aborted)
        return false;
    
    sound->stop();
    return true;
    
}

void SirenSound::abort () {
    spdlog::get("file_logger")->debug("SirenSound::abort");
    aborted = true;
}

void SirenSound::operator() (Service& service) {
    
    spdlog::get("file_logger")->debug("SirenSound::operator()");
    
    if (background) {
        auto& window = service.getWindow();
        window.clear(*background);
    };
    
    if (!should_replay) {
        return;
    }
    
    sound->play();
    should_replay = false;
    clock.restart();
    
}
