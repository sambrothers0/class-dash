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
        
        // Store sound effects
        std::unordered_map<SoundEffect, Mix_Chunk*> soundEffects;
        
        // Store music tracks
        std::unordered_map<MusicTrack, Mix_Music*> musicTracks;
        
        // Current music track
        MusicTrack currentMusic;
        
        // Volumes
        int musicVolume = MIX_MAX_VOLUME;
        int soundVolume = MIX_MAX_VOLUME;
        
        // Private constructor for singleton
        SoundManager();
        
    public:
        // Get singleton instance
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
        
        // Volume control
        void setMusicVolume(int volume); // 0-100
        void setSoundVolume(int volume); // 0-100
        
        // Clean up resources
        void cleanup();
        
        ~SoundManager();
    };

#endif
