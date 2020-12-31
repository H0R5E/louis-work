
#include <stdexcept>

#include "gtest/gtest.h"

#include "helpers.h"

TEST (FindAssetTest, FoundFile) { 
    
    auto asset_path = FindAsset ("Alarm_or_siren");
    ASSERT_EQ (asset_path.filename(), "Alarm_or_siren.ogg");
    
}

TEST (FindAssetTest, FileNotFound) { 
    
    ASSERT_THROW(FindAsset ("not_a_file");, std::runtime_error);
    
}
