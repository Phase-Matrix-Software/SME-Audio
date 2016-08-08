/* 
 * File:   SME_source.h
 * Author: Sam
 *
 * Created on 29 July 2016, 22:45
 */

#ifndef SME_SOURCE_H
#define	SME_SOURCE_H

#include <AL/al.h>
#include <glm/glm.hpp>
#include <SME_level.h>

namespace SME {
    namespace Audio {
        struct Source {
            Source();
            ~Source();

            void playSound(std::string name);
            void setPitch(float p);
            void setGain(float g);
            void setMaxDistance(float d);
            
            void setPos(glm::vec3 pos);
            void setVel(glm::vec3 vel);

            ALuint id;
        };
        
        struct SourceAttachment
        : public Source, public SME::Level::Entity::Attachment {
            SourceAttachment(SME::Level::Entity::Entity *entity);
            
            void onPosChanged(glm::vec3 pos);
            void onVelChanged(glm::vec3 vel);
            void onRotChanged(glm::vec3 rot);
            void onUpdate();
        };
        
        void pauseAll();
        void resumeAll();
    }
}

#endif	/* SME_SOURCE_H */

