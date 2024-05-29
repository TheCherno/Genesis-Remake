#include "SpriteSheet.h"

#include "ImageUtils.h"
#include "Utils/Utils.h"

namespace Genesis {

    SpriteSheet::SpriteSheet(const std::filesystem::path& path)
    {
        std::filesystem::path finalPath = Genesis::Utils::ResolvePath(path);

        if (!std::filesystem::exists(finalPath))
        {
            std::cerr << "Sprite sheet doesn't exist! " << finalPath << std::endl;
            ASSERT(false);
            return;
        }

        m_ImageBuffer = Utils::LoadImageBuffer(finalPath, m_Width, m_Height);
    }

    SpriteSheet::SpriteSheet(SpriteSheet&& other)
    {
        if (&other == this)
            return;

        m_ImageBuffer = other.m_ImageBuffer;
        m_Width = other.m_Width;
        m_Height = other.m_Height;
        other.m_ImageBuffer = nullptr;
    }

    SpriteSheet::~SpriteSheet()
    {
        delete[] m_ImageBuffer;
    }

    SpriteSheet& SpriteSheet::operator=(SpriteSheet&& other)
    {
        m_ImageBuffer = other.m_ImageBuffer;
        m_Width = other.m_Width;
        m_Height = other.m_Height;
        other.m_ImageBuffer = nullptr;
        return *this;
    }
} // Genesis
