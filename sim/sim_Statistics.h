#ifndef SIM_STATISTICS_H
#define SIM_STATISTICS_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/sim_Types.h>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Mission statistics class. */
class Statistics : public Singleton< Statistics >
{
    friend class Singleton< Statistics >;

private:

    /** Constructor. */
    Statistics();

public:

    /** Destructor. */
    virtual ~Statistics();

    inline void update( float realTime )
    {
        m_flightTime += realTime;
    }

    /** Resets statistics data. */
    void reset();

    /** This function should be called whenever unit is activated. */
    void reportActivated( Affiliation affiliation );

    /** This function should be called whenever unit is destroyed. */
    void reportDestroyed( Affiliation affiliation );

    /** */
    inline void reportOwnshipDestroyed()
    {
        m_ownshipDestroyed++;
    }

    inline UInt16 getActivated() const { return m_activated; }
    inline UInt16 getDestroyed() const { return m_destroyed; }

    inline UInt16 getFriendsActivated() const { return m_friendsActivated; }
    inline UInt16 getFriendsDestroyed() const { return m_friendsDestroyed; }
    inline UInt16 getEnemiesActivated() const { return m_enemiesActivated; }
    inline UInt16 getEnemiesDestroyed() const { return m_enemiesDestroyed; }
    inline UInt16 getOwnshipDestroyed() const { return m_ownshipDestroyed; }

    inline UInt16 getFlightTime() const { return (UInt16)m_flightTime; }

private:

    UInt16 m_activated;         ///< total number of activated units
    UInt16 m_destroyed;         ///< total number of destroyed units

    UInt16 m_friendsActivated;  ///< number of activated friend units
    UInt16 m_friendsDestroyed;  ///< number of destroyed friend units
    UInt16 m_enemiesActivated;  ///< number of activated enemy units
    UInt16 m_enemiesDestroyed;  ///< number of destroyed enemy units
    UInt16 m_ownshipDestroyed;  ///< number of units destroyed by ownship

    float m_flightTime;         ///< [s] total flight time
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_STATISTICS_H
