#ifndef SIM_BUFFERQUEUEPLAYER_H
#define SIM_BUFFERQUEUEPLAYER_H

////////////////////////////////////////////////////////////////////////////////

#include <stdint.h>
#include <string>

#include <sys/types.h>

#include <SLES/OpenSLES.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** OpenSLES buffer queue player class. */
class BufferQueuePlayer
{
public:

    /** Constructor. */
    BufferQueuePlayer( const std::string &bufferPath, bool looping = false );

    /** Destructor. */
    virtual ~BufferQueuePlayer();

    void onFinished();

    void play();
    void stop();

    SLBufferQueueItf getItfBufferQueue() { return m_itfBufferQueue; }

    void setPlaybackRate( float coef );

    void setVolume( float coef );

private:

    SLEngineItf m_soundEngine;              ///<
    SLObjectItf m_outputMixer;              ///<

    SLObjectItf m_player;                   ///<

    SLPlayItf         m_itfPlay;            ///<
    SLBufferQueueItf  m_itfBufferQueue;     ///<
    SLVolumeItf       m_itfVolume;          ///<
    SLPlaybackRateItf m_itfPlaybackRate;    ///<

    uint8_t *m_buffer;                      ///<
    off_t    m_bufferLength;                ///<

    bool m_playing;                         ///<
    bool m_looping;                         ///<

    void readBuffer( const std::string &bufferPath );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BUFFERQUEUEPLAYER_H