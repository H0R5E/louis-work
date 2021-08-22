
#include <stdexcept>
#include <SFML/Graphics.hpp>

#include "helpers.h"

fs::path FindAsset (std::string_view name, std::string_view assetDir) {
    
    fs::path dir (assetDir);
    fs::path file (name);
    
    for (const auto & entry : fs::recursive_directory_iterator(dir)) {
        
        auto check_path = entry.path();
        
        if (fs::is_directory(check_path)) {
            continue;
        }
        
        check_path.replace_extension();
        
        if (check_path.filename() == file) {
            return entry.path();
        }
        
    }
    
    throw std::runtime_error("Asset not found");
    
}
