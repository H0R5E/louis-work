
/*  louis-work: a game
 *  Copyright (C) 2021  Mathew Topper
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

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
