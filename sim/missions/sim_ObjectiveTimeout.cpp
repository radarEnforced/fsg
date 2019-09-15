#include <sim/missions/sim_ObjectiveTimeout.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveTimeout* ObjectiveTimeout::read( const XmlNode &node )
{
    ObjectiveTimeout *objective = new ObjectiveTimeout();

    if ( node.isValid() )
    {
        std::string limit = node.getAttribute( "limit" );

        if ( limit.length() > 0 )
        {
            objective->m_limit = String::toFloat( limit );

            return objective;
        }
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveTimeout::ObjectiveTimeout() :
    m_inited ( false ),
    m_limit ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveTimeout::~ObjectiveTimeout() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveTimeout::update()
{
    if ( !m_inited )
    {
        m_limit += Data::get()->mission.real_time;
        m_inited = true;
    }

    if ( Data::get()->mission.real_time > m_limit )
    {
        m_status = Success;
    }
}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveTimeout::setLimit( float limit )
{
    m_limit = limit;
}
