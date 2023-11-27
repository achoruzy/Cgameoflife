// Copyright (C) Arkadiusz Choruży

#ifndef SOUND_H_
#define SOUND_H_

#include <raylib.h>

void InitializeAudio();
void DeinitializeAudio();

void PlaySoundSpawn();
void PlaySoundDeath();

#endif