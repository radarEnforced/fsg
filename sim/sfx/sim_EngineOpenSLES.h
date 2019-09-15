#ifndef SIM_ENGINEOPENSLES_H
#define SIM_ENGINEOPENSLES_H

////////////////////////////////////////////////////////////////////////////////

#include <SLES/OpenSLES.h>
#include <SLES/OpenSLES_Android.h>
#include <SLES/OpenSLES_AndroidConfiguration.h>

#include <sim/utils/sim_Singleton.h>

#include <sim/sfx/sim_BufferQueuePlayer.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** OpenSLES sound engine singleton class. */
class EngineOpenSLES : public Singleton< EngineOpenSLES >
{
    friend class Singleton< EngineOpenSLES >;

public:

    /** Loop playing callback. */
    static void bufferQueuePlayerlayerCallback( SLBufferQueueItf buff, void *context );

private:

    /** Constructor. */
    EngineOpenSLES();

public:

    /** Destructor. */
    virtual ~EngineOpenSLES();

    /** Initializes sound engine. */
    void init();

    /** Stops sound engine. */
    void stop();

    inline SLEngineItf getSoundEngine() { return m_soundEngine; }
    inline SLObjectItf getOutputMixer() { return m_outputMixer; }

    inline void setPlayerBombs( bool play )     { setPlayer( play, m_playerBombs     ); }
    inline void setPlayerCrash( bool play )     { setPlayer( play, m_playerCrash     ); }
    inline void setPlayerEngine( bool play )    { setPlayer( play, m_playerEngine    ); }
    inline void setPlayerGunfire( bool play )   { setPlayer( play, m_playerGunfire   ); }
    inline void setPlayerHeartbeat( bool play ) { setPlayer( play, m_playerHeartbeat ); }
    inline void setPlayerHit( bool play )       { setPlayer( play, m_playerHit       ); }
    inline void setPlayerWaypoint( bool play )  { setPlayer( play, m_playerWaypoint  ); }

    inline void setPlayerEngineRPM( float rpm )
    {
        if ( m_playerEngine )
        {
            m_playerEngine->setPlaybackRate( rpm );
        }
    }

private:

    SLObjectItf m_soundObject;              ///<
    SLEngineItf m_soundEngine;              ///<
    SLObjectItf m_outputMixer;              ///<

    BufferQueuePlayer *m_playerBombs;       ///<
    BufferQueuePlayer *m_playerCrash;       ///<
    BufferQueuePlayer *m_playerEngine;      ///<
    BufferQueuePlayer *m_playerGunfire;     ///<
    BufferQueuePlayer *m_playerHit;         ///<
    BufferQueuePlayer *m_playerHeartbeat;   ///<
    BufferQueuePlayer *m_playerWaypoint;    ///<

    void setPlayer( bool play, BufferQueuePlayer *player );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_ENGINEOPENSLES_H