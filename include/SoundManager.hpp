#ifndef _SOUND_MANAGER_H
#define _SOUND_MANAGER_H

#include <SDL_mixer.h>
#include <string>
#include <unordered_map>
#include <memory>

#include "SoundEffect.hpp"
#include "MusicTrack.hpp"


class SoundManager {
    private:
        static SoundManager* instance;
        
        std::unordered_map<SoundEffect, Mix_Chunk*> soundEffects;
        std::unordered_map<MusicTrack, Mix_Music*> musicTracks;
        
        MusicTrack currentMusic;
    
        bool musicPlaying = false;
        bool soundEffectPlaying = false;
        
        SoundManager();
        
    public:
        static SoundManager* getInstance();
        
        // Initialize sound system
        bool initialize();
        
        // Load all sounds and music
        bool loadSounds();
        
        // Play a sound effect
        void playSound(SoundEffect effect);
        
        // Play music track
        void playMusic(MusicTrack track, bool loop = true);
        
        // Stop music
        void stopMusic();
        
        // Pause/resume music
        void pauseMusic();
        void resumeMusic();

        bool isMusicPlaying() const { return musicPlaying; }
        bool isSoundEffectPlaying() const { return soundEffectPlaying; }
        
        // Clean up resources
        void cleanup();
        
        ~SoundManager();
    };

#endif
