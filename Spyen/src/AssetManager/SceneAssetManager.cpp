#include <spypch.h>
#include <AssetManager/SceneAssetManager.h>
#include "SceneAssetManager.h"
#include <Core/UUID.h>
#include <AssetManager/Importers.h>

namespace Spyen{
    std::shared_ptr<Asset> SceneAssetManager::GetAsset(AssetHandle handle)
    {
       // can be constexpr with c++26
        
        if(!IsAssetHandleValid(handle)){
            return nullptr;
        }
        std::shared_ptr<Asset> asset;
        if(IsAssetLoaded(handle)){
            asset = m_AssetMap.at(handle);
        }else{
            asset = TextureImporter::LoadTexture(/*need some metadata*/)
        }        
    }

    constexpr bool SceneAssetManager::IsAssetHandleValid(AssetHandle handle) const
    {
        return handle != 0;
    }
    bool SceneAssetManager::IsAssetLoaded(AssetHandle handle) const
    {
        return m_AssetMap.contains(handle);
    }
}
