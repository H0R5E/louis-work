
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

#include "helpers.h"
#include "pathconfig.h"

#include <spdlog/spdlog.h>

#include <cassert>
#include <filesystem>
#include <map>
#include <memory>
#include <stdexcept>
#include <string_view>

template <typename Resource>
class ResourceHolder {
   public:
    ResourceHolder<Resource>(bool const& test = false)
        : ResourceHolder<Resource>(".", test) {}
    ResourceHolder<Resource>(std::string_view const subdir,
                             bool const& test = false) {
        char const* env_data = std::getenv("LOUIS_DATA_PATH");
        std::string baseDir;

        if (test) {
            baseDir = DATA_DIR_TEST;
        } else if (env_data) {
            baseDir = env_data;
        } else {
            baseDir = "/usr/share/louis-work";
        }

        assetDir = joinPaths(DATA_DIR_TEST, "assets", subdir)
                       .lexically_normal()
                       .generic_string();

        std::stringstream log_msg;
        log_msg << "Setting asset directory to: " << assetDir;
        spdlog::debug(log_msg.str());

        if (!std::filesystem::exists(assetDir)) {
            std::stringstream err_msg;
            err_msg << "Asset directory '" << assetDir << "' not found!";
            throw std::runtime_error(err_msg.str());
        }
    }
    ResourceHolder<Resource>(ResourceHolder<Resource> const& copy) {
        *this = copy;
    }
    ResourceHolder<Resource>(ResourceHolder<Resource>&& temp) = default;
    void Load(std::string_view resourcename);
    Resource& Get(std::string_view resourcename);
    Resource const& Get(std::string_view resourcename) const;
    int Size() const;
    ResourceHolder<Resource>& operator=(ResourceHolder<Resource> const& copy);
    ResourceHolder<Resource>& operator=(ResourceHolder<Resource>&& temp) =
        default;

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

    auto inserted =
        mResourceMap.insert(std::make_pair(resourcename, std::move(resource)));
    assert(inserted.second);
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
Resource const& ResourceHolder<Resource>::Get(
    std::string_view resourcename) const {
    auto found = mResourceMap.find(resourcename);

    if (found == mResourceMap.end()) {
        std::string msg = "ResourceHolder::Get - Failed to get ";
        msg.append(resourcename);
        throw std::runtime_error(msg);
    }

    return *found->second;
}

template <typename Resource>
int ResourceHolder<Resource>::Size() const {
    return mResourceMap.size();
}

template <typename Resource>
ResourceHolder<Resource>& ResourceHolder<Resource>::operator=(
    ResourceHolder<Resource> const& copy) {
    assetDir = copy.assetDir;

    for (auto const& [key, val] : copy.mResourceMap) {
        std::unique_ptr<Resource> resource{nullptr};

        if (val) {
            resource = std::make_unique<Resource>(*val);
        }

        mResourceMap.insert(std::make_pair(key, std::move(resource)));
    }

    return *this;
}
