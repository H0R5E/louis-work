
#pragma once

#include <algorithm>
#include <filesystem>
#include <random>
#include <string_view>

std::filesystem::path FindAsset (std::string_view name);

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
