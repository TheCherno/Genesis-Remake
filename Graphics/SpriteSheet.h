#pragma once

#include <filesystem>

namespace Genesis {

    class SpriteSheet
    {
    public:
        SpriteSheet() = default;
        SpriteSheet(const SpriteSheet&) = delete;
        SpriteSheet(SpriteSheet&& other);
        SpriteSheet(const std::filesystem::path& path);
        ~SpriteSheet();

        SpriteSheet& operator=(SpriteSheet&& other);

        uint32_t GetWidth() const { return m_Width;}
        uint32_t GetHeight() const { return m_Height;}
        uint32_t* GetImageBuffer() const { return m_ImageBuffer; }
    private:
        uint32_t* m_ImageBuffer = nullptr;
        uint32_t m_Width = 0, m_Height = 0;
    };

} // Genesis