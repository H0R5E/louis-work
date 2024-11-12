
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

#include <cassert>
#include <memory>
#include <map>
#include <stdexcept>
#include <string_view>

#include "helpers.h"
#include "pathconfig.h"

template <typename Resource>
class ResourceHolder {
public:
    ResourceHolder<Resource> (const bool& test=false) {
        if (test) {
            assetDir = ASSETS_DIR_TEST;
        } else {
            assetDir = ASSETS_DIR_RELEASE;
        }
    }
    ResourceHolder<Resource> (const std::string_view subdir,
                              const bool& test=false) {
        if (test) {
            assetDir = joinPaths(ASSETS_DIR_TEST, subdir).generic_string();
        } else {
            assetDir = joinPaths(ASSETS_DIR_RELEASE, subdir).generic_string();
        }
    }
    ResourceHolder<Resource> (const ResourceHolder<Resource>& copy) {
        *this = copy;
    }
    ResourceHolder<Resource> (ResourceHolder<Resource>&& temp) = default;
    void Load(std::string_view resourcename);
    Resource& Get(std::string_view resourcename);
    const Resource& Get(std::string_view resourcename) const;
    int Size () const;
    ResourceHolder<Resource>& operator= (const ResourceHolder<Resource>& copy);
    ResourceHolder<Resource>& operator= (ResourceHolder<Resource>&& temp)
                                                                    = default;
private:
    std::string assetDir;
    std::map<std::string_view, std::unique_ptr<Resource>> mResourceMap;
};

template <typename Resource>
void ResourceHolder<Resource>::Load(std::string_view resourcename) {
    
    // Don't load resources twice
    if (mResourceMap.find(resourcename) != mResourceMap.end()) {
        return;
    }
    
    std::unique_ptr<Resource> resource(new Resource());
    auto filename = FindAsset(resourcename, assetDir);
    
    if (!resource->loadFromFile(filename.generic_string())) {
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
    
    if (found == mResourceMap.end()) {
        std::string msg = "ResourceHolder::Get - Failed to get ";
        msg.append(resourcename);
        throw std::runtime_error(msg);
    }
    
    return *found->second;
}

template <typename Resource>
const Resource& ResourceHolder<Resource>::Get(
                                    std::string_view resourcename) const {
    
    auto found = mResourceMap.find(resourcename);
    
    if (found == mResourceMap.end()) {
        std::string msg = "ResourceHolder::Get - Failed to get ";
        msg.append(resourcename);
        throw std::runtime_error(msg);
    }
    
    return *found->second;
    
    
}

template<typename Resource>
int ResourceHolder<Resource>::Size() const {
    return mResourceMap.size();
}

template<typename Resource>
ResourceHolder<Resource>& ResourceHolder<Resource>::operator= (
                                        const ResourceHolder<Resource>& copy) {
    
    assetDir = copy.assetDir;
    
    for (auto const& [key, val] : copy.mResourceMap) {
        
        std::unique_ptr<Resource> resource {nullptr};
        
        if (val) {
            resource = std::make_unique<Resource>(*val);
        }
        
        mResourceMap.insert(std::make_pair(key, std::move(resource)));
    
    }
    
    return *this;
    
}

