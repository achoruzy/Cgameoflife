// Copyright (C) Arkadiusz Choruży

#include "sound.h"

static const char *SPAWN_SOUND = "assets/spawn.wav";
static const char *DEATH_SOUND = "assets/death.wav";

static Sound spawnSound;
static Sound deathSound;

void InitializeAudio()
{
    InitAudioDevice();
    spawnSound = LoadSound(SPAWN_SOUND);
    deathSound = LoadSound(DEATH_SOUND);
}

void DeinitializeAudio()
{
    CloseAudioDevice();
    UnloadSound(spawnSound);
    UnloadSound(deathSound);
}

void PlaySoundSpawn()
{
    PlaySound(spawnSound);
}

void PlaySoundDeath()
{
    PlaySound(deathSound);
}