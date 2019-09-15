#include <sim/missions/sim_ObjectiveDefend.h>

#include <sim/entities/sim_Entities.h>
#include <sim/utils/sim_String.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveDefend* ObjectiveDefend::read( const XmlNode &node )
{
    ObjectiveDefend *objective = new ObjectiveDefend();

    if ( node.isValid() )
    {
        std::string minimum = node.getAttribute( "minimum" );

        if ( minimum.length() )
        {
            objective->m_minimum = String::toInt( minimum );
        }

        XmlNode unitNode = node.getFirstChildElement( "unit" );

        while ( unitNode.isValid() )
        {
            std::string unitName = unitNode.getAttribute( "name" );

            if ( unitName.length() > 0 )
            {
                Unit *unit = Entities::instance()->getUnitByName( unitName );

                if ( unit )
                {
                    objective->m_unitsId.push_back( unit->getId() );
                }
            }
            else
            {
                //////////////////////////////////
                if ( objective ) delete objective;
                objective = 0;
                //////////////////////////////////

                return 0;
            }

            unitNode = unitNode.getNextSiblingElement( "unit" );
        }

        if ( objective->m_minimum > objective->m_unitsId.size() )
        {
            objective->m_minimum = objective->m_unitsId.size();
        }

        return objective;
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveDefend::ObjectiveDefend() {}

////////////////////////////////////////////////////////////////////////////////

ObjectiveDefend::~ObjectiveDefend() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveDefend::update()
{
    m_status = Success;

    // faillure if unit destroyed
    if ( m_unitsId.size() > 0 )
    {
        UnitsId::iterator it = m_unitsId.begin();

        unsigned int count = 0;

        while ( it != m_unitsId.end() )
        {
            Unit *unit = dynamic_cast< Unit* >( Entities::instance()->getEntityById( *it ) );

            if ( unit )
            {
                if ( unit->getHP() > 0 )
                {
                    count++;
                }
            }

            ++it;
        }

        if ( count < m_minimum )
        {
            m_status = Failure;
        }
    }
}
