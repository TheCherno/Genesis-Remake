#include "ImageUtils.h"

namespace Genesis {

    uint32_t* Utils::LoadImageBuffer(const std::filesystem::path& path, uint32_t& outWidth, uint32_t& outHeight)
    {
        uint32_t* resultBuffer = nullptr;

        std::string pathStr = path.string();
        Image image = LoadImage(pathStr.c_str());
        outWidth = image.width;
        outHeight = image.height;

        resultBuffer = new uint32_t[outWidth * outHeight];

        if (image.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8A8)
        {
            std::cout << "Loading RGBA image " << pathStr << std::endl;
            memcpy(resultBuffer, image.data, outWidth * outHeight * 4);
        }
        else if (image.format == PIXELFORMAT_UNCOMPRESSED_R8G8B8)
        {
            std::cout << "Loading RGB image " << pathStr << std::endl;
            uint8_t* imageData = (uint8_t*)image.data;
            for (int i = 0; i < outWidth * outHeight; i++)
            {
                uint8_t a = 0xff;
                uint8_t r = imageData[i * 3 + 0];
                uint8_t g = imageData[i * 3 + 1];
                uint8_t b = imageData[i * 3 + 2];
                resultBuffer[i] = a << 24 | b << 16 | g << 8 | r;
            }
        }
        UnloadImage(image);

        return resultBuffer;
    }

} // Genesis