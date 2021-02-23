
#pragma once

#include <algorithm>
#include <filesystem>
#include <random>
#include <string_view>

namespace fs = std::filesystem;

fs::path FindAsset (std::string_view name, std::string_view assetDir);

template<typename... Args>
fs::path joinPaths (const char* in, Args... args) {
    fs::path path (in);
    return (path / ... / args);
}

template<typename T>
const T getRandomSample(const std::vector<T>& in) {
    
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
