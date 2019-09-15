#include <sim/missions/sim_ObjectiveAirspeed.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveAirspeed* ObjectiveAirspeed::read( const XmlNode &node )
{
    ObjectiveAirspeed *objective = new ObjectiveAirspeed();

    if ( node.isValid() )
    {
        std::string above = node.getAttribute( "above" );
        std::string below = node.getAttribute( "below" );

        if ( above.length() > 0 && below.length() > 0 )
        {
            objective->m_above = String::toFloat( above );
            objective->m_below = String::toFloat( below );

            return objective;
        }
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveAirspeed::ObjectiveAirspeed() :
    m_above ( 0.0f ),
    m_below ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveAirspeed::~ObjectiveAirspeed() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveAirspeed::update()
{
    Aircraft *aircraft = Ownship::instance()->getAircraft();

    if ( aircraft )
    {
        float airspeed = aircraft->getAirspeed();

        if ( airspeed > m_above && airspeed < m_below )
        {
            m_status = Success;
        }
    }
}
