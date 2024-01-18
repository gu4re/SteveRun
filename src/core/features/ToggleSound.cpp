//
// Created by diegopicazo on 17/1/24.
//

#include "../../../include/core/features/ToggleSound.h"

std::thread audioThread;
bool shouldStopAudioThread = false;
bool isFirstPlay = true;

void toggleSound(ALuint SoundSource) {
    if (isSoundActive) {
        if (!audioThread.joinable()) {
            shouldStopAudioThread = false;
            audioThread = std::thread([&]() {
                while (!shouldStopAudioThread) {
                    ALint ALSourceState;
                    alGetSourcei(SoundSource, AL_SOURCE_STATE, &ALSourceState);
                    if (isFirstPlay || ALSourceState != AL_PLAYING) {
                        alSourcePlay(SoundSource);
                        isFirstPlay = false;
                    }
                    std::this_thread::sleep_for(std::chrono::milliseconds(100));
                }
            });
        }
    } else {
        if (audioThread.joinable()) {
            shouldStopAudioThread = true;
            alSourceStop(SoundSource);
            audioThread.join();
        }
    }
}
