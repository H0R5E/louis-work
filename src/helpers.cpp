
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "helpers.h"

fs::path FindAsset (std::string_view name, std::string_view assetDir) {
    
    fs::path dir (assetDir);
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
