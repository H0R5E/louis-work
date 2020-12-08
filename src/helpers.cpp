
#include <filesystem>
#include <stdexcept>

#include "pathconfig.h"
#include "helpers.h"

namespace fs = std::filesystem;

sf::Font GetFont ( std::string_view name ) {
    
    fs::path dir (ASSETS_DIR);
    fs::path file (name);
    fs::path full_path = dir / file;
    
    sf::Font font;
    
    if (!font.loadFromFile(full_path)) {
        throw std::runtime_error("Font failed to load");
    }
    
    return font;
    
}


