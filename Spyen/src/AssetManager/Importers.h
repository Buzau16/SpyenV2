#pragma once
#include <memory>
#include <filesystem>

namespace Spyen{
    class Texture;

    class TextureImporter{
        static std::shared_ptr<Texture> LoadTexture(const std::filesystem::path& path);
    }

}