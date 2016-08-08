/* 
 * File:   SME_listener.h
 * Author: Sam
 *
 * Created on 29 July 2016, 22:27
 */

#ifndef SME_LISTENER_H
#define	SME_LISTENER_H

#include <glm/glm.hpp>
#include <SME_level.h>

namespace SME {
    namespace Audio {
        class Listener {
        public:
            Listener();
            
            void setPosition(glm::vec3 pos);
            void setVelocity(glm::vec3 vel);
            void setOrientation(glm::vec3 f, glm::vec3 u);
            
            void setActive();
            
            bool _active = false;
        private:
            float px, py, pz;
            float vx, vy, vz;
            float fx, fy, fz, ux, uy, uz;
        };
        
        struct ListenerAttachment
        : public Listener, public SME::Level::Entity::Attachment {
            ListenerAttachment(SME::Level::Entity::Entity *entity);
            
            void onPosChanged(glm::vec3 pos);
            void onVelChanged(glm::vec3 vel);
            void onRotChanged(glm::vec3 rot);
            void onUpdate();
        };
    }
}

#endif	/* SME_LISTENER_H */

