
#pragma once

#include <cassert>
#include <memory>
#include <map>
#include <stdexcept>
#include <string_view>

#include "helpers.h"

template <typename Resource>
class ResourceHolder {
public:
    void Load(std::string_view resourcename);
    Resource& Get(std::string_view resourcename);
    const Resource& Get(std::string_view resourcename) const;
    int Size () const;
private:
    std::map<std::string_view, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource>
void ResourceHolder<Resource>::Load(std::string_view resourcename) {
    
    // Don't load resources twice
    if (mResourceMap.find(resourcename) != mResourceMap.end()) {
        return;
    }
    
    std::unique_ptr<Resource> resource(new Resource());
    auto filename = FindAsset(resourcename);
    
    if (!resource->loadFromFile(filename)) {
        throw std::runtime_error("ResourceHolder::load - Failed to load " +
                                 filename.string());
    }
    
    auto inserted = mResourceMap.insert(
                            std::make_pair(resourcename, std::move(resource)));
    assert (inserted.second);
    
}

template <typename Resource>
Resource& ResourceHolder<Resource>::Get(std::string_view resourcename) {
    auto found = mResourceMap.find(resourcename);
    return *found->second;
}

template <typename Resource>
const Resource& ResourceHolder<Resource>::Get(std::string_view resourcename) const {
    auto found = mResourceMap.find(resourcename);
    return *found->second;
}

template<typename Resource>
int ResourceHolder<Resource>::Size() const {
    return mResourceMap.size();
}
