/* 
 * File:   SME_audio.h
 * Author: Sam
 *
 * Created on 23 July 2016, 23:53
 */

#ifndef SME_AUDIO_H
#define	SME_AUDIO_H

#include <string>

namespace SME {
    namespace Audio {
        void init();
        void cleanup();
        
        bool loadOGG(std::string file, std::string alias);
    }
}

#endif	/* SME_AUDIO_H */

