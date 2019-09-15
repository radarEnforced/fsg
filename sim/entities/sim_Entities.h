#ifndef SIM_ENTITIES_H
#define SIM_ENTITIES_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Unit.h>

#include <sim/utils/sim_Singleton.h>

#include <sim/entities/sim_Group.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Top level entities class.
 * <p>This singleton class should be used to access top level entities.</p>
 */
class Entities : public Group, public Singleton< Entities >
{
    friend class Singleton< Entities >;

private:

    /** Constructor. */
    Entities();

    /** Constructor. */
    Entities( const Entities & ) : Group( 0 ), Singleton< Entities >() {}

public:

    /** Destructor. */
    virtual ~Entities();

    /**
     * Returns first unit of a given name if exists, otherwise returns 0.
     * @param name entity name
     */
    Unit* getUnitByName( const std::string &name );

    /** Returns ownship entity if exists, otherwise returns 0. */
    Unit* getOwnship();

    /** */
    void listAll();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_ENTITIES_H
