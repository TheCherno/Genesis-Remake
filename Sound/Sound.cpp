#include "Sound.h"
#include "Utils/Utils.h"

namespace Genesis {
    Sound::Sound(const std::filesystem::path& path, bool stream)
        : m_Stream(stream)
    {
        if (!IsAudioDeviceReady())
            InitAudioDevice();

        std::filesystem::path finalPath = Genesis::Utils::ResolvePath(path);

        ASSERT(IsAudioDeviceReady());
        ASSERT(std::filesystem::exists(finalPath));
        std::string pathStr = finalPath.string();

        if (stream)
        {
            m_Music = LoadMusicStream(pathStr.c_str());
            m_Music.looping = true;
        } else
        {
            m_Sound = LoadSound(pathStr.c_str());
            ASSERT(m_Sound.stream.buffer);
        }
    }

    void Sound::Play()
    {
        if (m_Stream)
        {
            PlayMusicStream(m_Music);
            Sounds::MusicCurrentlyPlaying = this;
        }
        else
            PlaySound(m_Sound);
    }

    void Sound::Stop()
    {
        if (m_Stream)
        {
            StopMusicStream(m_Music);
            Sounds::MusicCurrentlyPlaying = nullptr;
        }
        else
            StopSound(m_Sound);
    }

    void Sound::StopAll()
    {
        Sounds::Breed.Stop();
        Sounds::GameOver.Stop();
        Sounds::Start.Stop();
        Sounds::Menu.Stop();
        Sounds::MenuCycle.Stop();
        Sounds::MenuTheme.Stop();
        Sounds::Theme.Stop();
    }
} // Genesis
