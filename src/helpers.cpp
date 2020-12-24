
#include <stdexcept>
#include "SFML/Graphics.hpp"

#include "pathconfig.h"
#include "helpers.h"

namespace fs = std::filesystem;

fs::path FindAsset (std::string_view name) {
    
    fs::path dir (ASSETS_DIR);
    fs::path file (name);
    fs::path search_path = dir / file;
    
    for (const auto & entry : fs::directory_iterator(dir)) {
        auto check_path = entry.path();
        check_path.replace_extension();
        if (check_path == search_path) {
            return entry.path();
        }
    }
    
    throw std::runtime_error("Asset not found");
    
}


bool CtrlC() {
    return sf::Keyboard::isKeyPressed(sf::Keyboard::C) &&
           (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) ||
            sf::Keyboard::isKeyPressed(sf::Keyboard::RControl));
}
