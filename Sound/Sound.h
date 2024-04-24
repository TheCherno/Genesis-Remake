#pragma once
#include <filesystem>

#include "raylib.h"

namespace Genesis {

    class Sound
    {
    public:
        Sound(const std::filesystem::path& path, bool stream = false);

        void Play();
        void Stop();

        static void StopAll();

        const Music& GetMusic() const { return m_Music; };
    private:
        ::Sound m_Sound;
        ::Music m_Music;

        bool m_Stream = false;
    };

    namespace Sounds {

        inline Sound Breed = { "res/sound/breed.wav" };
        inline Sound GameOver = { "res/sound/gameover.wav" };
        inline Sound Start = { "res/sound/start.wav"};
        inline Sound Menu = { "res/sound/menu.wav"};
        inline Sound MenuCycle = { "res/sound/menucycle.wav"};

        inline Sound MenuTheme = { "res/sound/menutheme.wav", true };
        inline Sound Theme = { "res/sound/theme.wav", true };

        inline Sound* MusicCurrentlyPlaying = nullptr;
    }

} // Genesis