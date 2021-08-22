
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

#pragma once

#include <algorithm>
#include <filesystem>
#include <random>
#include <string_view>

namespace fs = std::filesystem;

fs::path FindAsset (std::string_view name, std::string_view assetDir);

template<typename T, typename... Args>
fs::path joinPaths (T in, Args... args) {
    fs::path path (in);
    return (path / ... / args);
}

template<typename T>
T getRandomSample(const std::vector<T>& in) {
    
    std::vector<T> out;
    size_t nelems = 1;
    
    std::sample(
        in.begin(),
        in.end(),
        std::back_inserter(out),
        nelems,
        std::mt19937{std::random_device{}()}
    );
    
    return out.front();
    
}
