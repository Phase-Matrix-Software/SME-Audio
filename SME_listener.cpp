#include "SME_listener.h"
#include <AL/al.h>
#include <vector>

using namespace SME::Audio;

std::vector<Listener *> listeners;

void setActiveListener(Listener* l) {
    for (Listener *lv : listeners) {
        lv->_active = false;
    }
    l->_active = true;
}

Listener::Listener() {
    listeners.push_back(this);
}

void Listener::setPosition(glm::vec3 pos) {
    px = pos.x;
    py = pos.y;
    pz = pos.z;
    
    if (!_active) return;
    alListener3f(AL_POSITION, pos.x, pos.y, pos.z);
}

void Listener::setVelocity(glm::vec3 vel) {
    vx = vel.x;
    vy = vel.y;
    vz = vel.z;
    
    if (!_active) return;
    alListener3f(AL_VELOCITY, vel.x, vel.y, vel.z);
}

void Listener::setOrientation(glm::vec3 f, glm::vec3 u) {
    fx = f.x; fy = f.y; fz = f.z;
    ux = u.x; uy = u.y; uz = u.z;
    
    if (!_active) return;
    ALfloat ori [] = {f.x, f.y, f.z, u.x, u.y, u.z};
    alListenerfv(AL_ORIENTATION, ori);
}

void Listener::setActive() {
    setActiveListener(this);
    
    alListener3f(AL_POSITION, px, py, pz);
    alListener3f(AL_VELOCITY, vx, vy, vz);
    ALfloat ori [] = {fx, fy, fz, ux, uy, uz};
    alListenerfv(AL_ORIENTATION, ori);
}

ListenerAttachment::ListenerAttachment(SME::Level::Entity::Entity* e)
: Listener::Listener(), SME::Level::Entity::Attachment::Attachment(e) {}

void ListenerAttachment::onPosChanged(glm::vec3 pos) { setPosition(pos); }
void ListenerAttachment::onVelChanged(glm::vec3 vel) { setVelocity(vel); }
void ListenerAttachment::onRotChanged(glm::vec3 rot) {
    setOrientation(entity->getForwardVector(), entity->getUpwardVector());
}
void ListenerAttachment::onUpdate() {}
