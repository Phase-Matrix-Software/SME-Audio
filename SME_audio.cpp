#include "SME_audio.h"
#include <SME_core.h>
#include <SME_entity.h>
#include <AL/alut.h>
#include <vorbis/vorbisfile.h>
#include <iostream>

#define BUFFER_SIZE 4096

ALCdevice *device;
ALCcontext *context;

std::map<std::string, ALuint> buffers;

void SME::Audio::init() {
    device = alcOpenDevice(NULL);
    context = alcCreateContext(device, NULL);
    alcMakeContextCurrent(context);
    
    alDistanceModel(AL_LINEAR_DISTANCE_CLAMPED);
    
    SME::Core::addCleanupHook(cleanup);
}

void SME::Audio::cleanup() {
    for (std::map<std::string, ALuint>::iterator it = buffers.begin(); it != buffers.end(); ++it) {
        alDeleteBuffers(1, &it->second);
    }
    
    alcMakeContextCurrent(NULL);
    alcDestroyContext(context);
    alcCloseDevice(device);
}

bool SME::Audio::loadOGG(std::string file, std::string alias) {
    bool bigEndian = false;

    OggVorbis_File oggFile;
    int err = ov_fopen(file.c_str(), &oggFile);
    if (err != 0) {
        std::cerr << "Failed to load ogg file (" << file << ") " <<
                (err == OV_EREAD ? "OV_EREAD" : "") <<
                (err == OV_ENOTVORBIS ? "OV_ENOTVORBIS" : "") <<
                (err == OV_EVERSION ? "OV_EVERSION" : "") <<
                (err == OV_EBADHEADER ? "OV_EBADHEADER" : "") <<
                (err == OV_EFAULT ? "OV_EFAULT" : "") << std::endl;
        return false;
    }

    long bytes;
    char data[BUFFER_SIZE];
    
    std::vector<char> prepro;
    do {
        bytes = ov_read(&oggFile, data, BUFFER_SIZE, bigEndian, 2, 1, nullptr);

        if (bytes < 0) {
            std::cout << "Failed to load ogg data (" << file << ") " <<
                    (bytes == OV_HOLE ? "OV_HOLE" : "") <<
                    (bytes == OV_EBADLINK ? "OV_EBADLINK" : "") <<
                    (bytes == OV_EINVAL ? "OV_EINVAL" : "") << std::endl;
            return false;
        }
        
        prepro.insert(prepro.end(), data, data + bytes);
    } while (bytes > 0);

    vorbis_info *info = ov_info(&oggFile, -1);

    std::vector<char> mono;
    //convert to mono
    for (unsigned long i = 0; i < prepro.size(); i += info->channels * 2) { //llrr|llrr|llrr|llrr (channels*2 bytes)
        long sample [2] = {0, 0}; //{0} = LlRr, {1} = lLrR, ie 1st byte, second byte
        for (int j = 0; j < info->channels; j += 2) {
            sample[0] += prepro[i + j]; //add first byte of all channels
            sample[1] += prepro[i + j + 1]; //add second byte of all channels
        }
        mono.push_back(sample[0] / info->channels);
        mono.push_back(sample[1] / info->channels);
    }

    ALuint format = AL_FORMAT_MONO16;
    ALuint bitRate = info->rate;

    ALuint bufferID;
    alGenBuffers(1, &bufferID);
    alBufferData(bufferID, format, &mono[0], static_cast<ALsizei> (mono.size()), bitRate);
    buffers[alias] = bufferID;

    ov_clear(&oggFile);
    return true;
}