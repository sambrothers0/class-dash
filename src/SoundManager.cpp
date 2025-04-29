#include "SoundManager.hpp"
#include <iostream>

// Initialize static instance
SoundManager* SoundManager::instance = nullptr;

SoundManager* SoundManager::getInstance() {
    if (instance == nullptr) {
        instance = new SoundManager();
    }
    return instance;
}

SoundManager::SoundManager() : currentMusic(MusicTrack::TITLE_THEME) {
    // Private constructor
}

bool SoundManager::initialize() {
    // Initialize SDL_mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        std::cerr << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
        return false;
    }

    // Set number of channels for sound effects (default is 8)
    Mix_AllocateChannels(16);

    return loadSounds();
}

bool SoundManager::loadSounds() {
    // Load sound effects
    const char* soundFiles[] = {
        "../assets/audio/jump.wav",
        "../assets/audio/shoot.wav",
        "../assets/audio/button-switch.wav",
        "../assets/audio/button-select.wav",
        "../assets/audio/level-complete.wav",
        "../assets/audio/level-lose.wav",
        "../assets/audio/clock-tick.wav"
    };

    // Load each sound effect
    for (int i = 0; i < 7; i++) {
        Mix_Chunk* sound = Mix_LoadWAV(soundFiles[i]);
        if (sound == nullptr) {
            std::cerr << "Failed to load sound effect: " << soundFiles[i] << " SDL_mixer Error: " << Mix_GetError() << std::endl;
            // Continue loading other sounds
        } else {
            soundEffects[static_cast<SoundEffect>(i)] = sound;
        }
    }

    // Load music tracks
    const char* musicFiles[] = {
        "../assets/audio/alma-mater.mp3",
        "../assets/audio/Level-1.mp3",
        "../assets/audio/Level-2.mp3",
        "../assets/audio/Level-3.mp3",
        "../assets/audio/Level-4.mp3",
        "../assets/audio/Level-5.mp3",
        "../assets/audio/Finale.mp3"
    };

    // Load each music track
    for (int i = 0; i < 7; i++) {
        Mix_Music* music = Mix_LoadMUS(musicFiles[i]);
        if (music == nullptr) {
            std::cerr << "Failed to load music: " << musicFiles[i] << " SDL_mixer Error: " << Mix_GetError() << std::endl;
            // Continue loading other music
        } else {
            musicTracks[static_cast<MusicTrack>(i)] = music;
        }
    }

    return true;
}

void SoundManager::playSound(SoundEffect effect, bool loop) {
    auto it = soundEffects.find(effect);
    if (it != soundEffects.end()) {
        Mix_PlayChannel(-1, it->second, loop ? -1 : 0);
    }
}

void SoundManager::playMusic(MusicTrack track, bool loop) {
    if (currentMusic == track && musicPlaying) {
        return; // Music is already playing
    }
    auto it = musicTracks.find(track);
    if (it != musicTracks.end()) {
        // Stop any currently playing music
        Mix_HaltMusic();

        // Play the new music track
        Mix_PlayMusic(it->second, loop ? -1 : 0);
        currentMusic = track;
    }
    musicPlaying = true;
}

void SoundManager::stopMusic() {
    Mix_HaltMusic();
    Mix_HaltChannel(-1);
    musicPlaying = false;
}

void SoundManager::pauseMusic() {
    if (Mix_PlayingMusic()) {
        Mix_PauseMusic();
    }

    if (Mix_Playing(-1)) {
        Mix_Pause(-1);
    }
}

void SoundManager::resumeMusic() {
    if (Mix_PausedMusic()) {
        Mix_ResumeMusic();
    }

    if (Mix_Paused(-1)) {
        Mix_Resume(-1);
    }
}

void SoundManager::cleanup() {
    // Free sound effects
    for (auto& pair : soundEffects) {
        Mix_FreeChunk(pair.second);
    }
    soundEffects.clear();

    // Free music
    for (auto& pair : musicTracks) {
        Mix_FreeMusic(pair.second);
    }
    musicTracks.clear();

    // Quit SDL_mixer
    Mix_CloseAudio();
}

SoundManager::~SoundManager() {
    cleanup();
}