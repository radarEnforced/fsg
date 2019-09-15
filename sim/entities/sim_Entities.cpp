#include <sim/entities/sim_Entities.h>

#include <limits>

#include <sim/entities/sim_Unit.h>
#include <sim/utils/sim_String.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Entities::Entities() :
    Group( 0 )
{}

////////////////////////////////////////////////////////////////////////////////

Entities::~Entities() {}

////////////////////////////////////////////////////////////////////////////////

Unit* Entities::getUnitByName( const std::string &name )
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        Unit *unit = dynamic_cast< Unit* >( *it );

        if ( unit )
        {
            if ( 0 == String::icompare( unit->getName(), name ) )
            {
                return unit;
            }
        }

        ++it;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

Unit* Entities::getOwnship()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        Unit *unit = dynamic_cast< Unit* >( *it );

        if ( unit )
        {
            if ( unit->isOwnship() )
            {
                return unit;
            }
        }

        ++it;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Entities::listAll()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        osg::notify(osg::ALWAYS) << (*it)->getName() << std::endl;
        ++it;
    }
}
