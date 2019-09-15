#ifndef SIM_SFX_H
#define SIM_SFX_H

////////////////////////////////////////////////////////////////////////////////

#ifdef __ANDROID__
#   define SIM_SFX_OPENSLES
#else
#endif

#include <sim/sim_Data.h>

#include <sim/utils/sim_Inertia.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Sound effects class. */
class SFX
{
public:

    /** Constructor. */
    SFX();

    /** Destructor. */
    virtual ~SFX();

    /** Initializes sound effects. */
    void init();

    /** Pauses sounds replaying. */
    void pause();

    /** Unpauses sounds replaying. */
    void unpause();

    /** Stops sound effects. */
    void stop();

    /** Updates sound effects. */
    void update();

private:

    bool m_inited;              ///<
    bool m_paused;              ///<

    Inertia< float > *m_rpm;    ///< engine RPM inertia

    bool m_destroyed;           ///< ownship destroy flag (to play explosion only once)

    UInt8 m_ownship_hits;       ///< number of ownship hits

    float m_hit_time;           ///< [s] until when hit sound should be played
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_SFX_H
