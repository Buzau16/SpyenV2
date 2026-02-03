#pragma once
#include <memory>
#include <Core/Director.h>
#include <AssetManager/Asset.h>

namespace Spyen{
    class AssetManager{
    public:
        template<typename TAsset>
        static std::shared_ptr<TAsset> GetAsset(AssetHandle handle){
            auto asset = Director::GetActiveScene()->m_AssetManager.GetAsset(handle);
            return std::static_pointer_cast<TAsset>(asset);
        }
        
        static bool IsAssetHandleValid(AssetHandle handle);

        static bool IsAssetLoaded(AssetHandle handle);

    };
}