
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
