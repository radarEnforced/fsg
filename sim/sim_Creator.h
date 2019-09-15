#ifndef SIM_CREATOR_H
#define SIM_CREATOR_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Aircraft.h>
#include <sim/missions/sim_Mission.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** */
class Creator
{
public:

    /**
     * @brief Creates aircraft.
     * @param index
     * @param livery
     * @param affiliation
     * @return aircraft object
     */
    static Aircraft* createAircraft( int index, int livery, Affiliation affiliation );

    /**
     * @brief Creates unit due to unit type and file.
     * @param type unit type
     * @param file unit file
     * @return unit object
     */
    static Unit* createUnit( const std::string &type, const std::string &file,
                             Affiliation affiliation );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_CREATOR_H
