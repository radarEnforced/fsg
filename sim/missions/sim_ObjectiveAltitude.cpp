#include <sim/missions/sim_ObjectiveAltitude.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveAltitude* ObjectiveAltitude::read( const XmlNode &node )
{
    ObjectiveAltitude *objective = new ObjectiveAltitude();

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

ObjectiveAltitude::ObjectiveAltitude() :
    m_above ( 0.0f ),
    m_below ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveAltitude::~ObjectiveAltitude() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveAltitude::update()
{
    Aircraft *aircraft = Ownship::instance()->getAircraft();

    if ( aircraft )
    {
        float altitude = aircraft->getAltitudeASL();

        if ( altitude > m_above && altitude < m_below )
        {
            m_status = Success;
        }
    }
}
