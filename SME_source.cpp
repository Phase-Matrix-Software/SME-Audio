#include "SME_source.h"
#include <vector>
#include <algorithm>

using namespace SME::Audio;

extern std::map<std::string, ALuint> buffers;

std::vector<Source *> sources;

Source::Source() {
    alGenSources(1, &id);

    ALfloat sPos [] = {0.f, 0.f, 0.f}; //positive x == left
    ALfloat sVel [] = {0.f, 0.f, 0.f};
    alSourcef(id, AL_PITCH, 1.f);
    alSourcef(id, AL_GAIN, 1.f);
    alSourcef(id, AL_MIN_GAIN, 0.f);
    alSourcefv(id, AL_POSITION, sPos);
    alSourcefv(id, AL_VELOCITY, sVel);
    alSourcei(id, AL_LOOPING, AL_FALSE);
    alSourcef(id, AL_REFERENCE_DISTANCE, 1); //min
    alSourcef(id, AL_MAX_DISTANCE, 32); //range
    
    sources.push_back(this);
}

SME::Audio::Source::~Source() {
    alDeleteSources(1, &id);
    
    sources.erase(std::remove(sources.begin(), sources.end(), this), sources.end());
}

void Source::playSound(std::string name) {
    alSourcei(id, AL_BUFFER, buffers[name]);
    alSourcePlay(id);
}

void Source::setPitch(float p) {alSourcef(id, AL_PITCH, p);}
void Source::setGain(float g) {alSourcef(id, AL_GAIN, g);}
void Source::setMaxDistance(float d) {alSourcef(id, AL_MAX_DISTANCE, d);}

void Source::setPos(glm::vec3 pos) {
    alSource3f(id, AL_POSITION, pos.x, pos.y, pos.z);
}

void Source::setVel(glm::vec3 vel) {
    alSource3f(id, AL_VELOCITY, vel.x, vel.y, vel.z);
}

SourceAttachment::SourceAttachment(SME::Level::Entity::Entity *e)
: Source::Source(), SME::Level::Entity::Attachment::Attachment(e) {}

void SourceAttachment::onPosChanged(glm::vec3 pos) { setPos(pos); }
void SourceAttachment::onVelChanged(glm::vec3 vel) { setVel(vel); }
void SourceAttachment::onRotChanged(glm::vec3 rot) {}
void SourceAttachment::onUpdate() {}

std::vector<ALuint> pausedSources;

void SME::Audio::pauseAll() {
    for (Source *s : sources) {
        ALint state;
        alGetSourcei(s->id, AL_SOURCE_STATE, &state);
        
        if (state == AL_PLAYING) {
            pausedSources.push_back(s->id);
            alSourcePause(s->id);
        }
    }
}

void SME::Audio::resumeAll() {
    for (ALuint id : pausedSources) {
        alSourcePlay(id);
    }
    
    pausedSources.clear();
}