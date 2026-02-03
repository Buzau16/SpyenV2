#pragma once

namespace Spyen{
    class UUID;
    using AssetHandle = UUID;

    class Asset{
    public:
        AssetHandle Handle = UUID();    
    };
}