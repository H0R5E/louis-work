
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

#include "gtest/gtest.h"

#include "helpers.h"
#include "pathconfig.h"

namespace fs = std::filesystem;

TEST (FindAssetTest, FoundFile) { 
    
    fs::path assetPath = joinPaths(ASSETS_DIR_TEST, "sounds");
    auto asset_path = FindAsset ("Alarm_or_siren", assetPath.u8string());
    ASSERT_EQ (asset_path.filename(), "Alarm_or_siren.ogg");
    
}

TEST (FindAssetTest, FileNotFound) { 
    
    ASSERT_THROW(FindAsset ("not_a_file", ASSETS_DIR_TEST);,
                            std::runtime_error);
    
}
