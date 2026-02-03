#pragma once
#include <unordered_map>
#include <AssetManager/Asset.h>


namespace Spyen{
    class SceneAssetManager{
    public:
        std::shared_ptr<Asset> GetAsset(AssetHandle handle);
        bool IsAssetHandleValid(AssetHandle handle) const;
        constexpr bool IsAssetLoaded(AssetHandle handle) const;
    private:
        // implement asset map and get the asset based on the type and handle so templates
        std::unordered_map<AssetHandle, std::shared_ptr<Asset>> m_AssetMap;
        // maybe useless
        std::unordered_map<std::string, AssetHandle> m_AssetRegistry;
    };
}