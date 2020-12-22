
#pragma once

#include <filesystem>
#include <stdexcept>
#include <string_view>
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

#include "pathconfig.h"

namespace fs = std::filesystem;

template <typename T>
void LoadIt (T& it, std::string_view name) {
    
    fs::path dir (ASSETS_DIR);
    fs::path file (name);
    fs::path full_path = dir / file;
    
    if (!it.loadFromFile(full_path)) {
        throw std::runtime_error("It failed to load");
    }
    
    return;
    
}

bool CtrlC ();
