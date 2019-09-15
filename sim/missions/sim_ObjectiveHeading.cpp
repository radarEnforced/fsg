#include <sim/missions/sim_ObjectiveHeading.h>

#include <sim/sim_Ownship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_Convert.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ObjectiveHeading* ObjectiveHeading::read( const XmlNode &node )
{
    ObjectiveHeading *objective = new ObjectiveHeading();

    if ( node.isValid() )
    {
        std::string above = node.getAttribute( "above" );
        std::string below = node.getAttribute( "below" );

        if ( above.length() > 0 && below.length() > 0 )
        {
            objective->m_above = Convert::deg2rad( String::toFloat( above ) );
            objective->m_below = Convert::deg2rad( String::toFloat( below ) );

            return objective;
        }
    }

    if ( objective ) delete objective;
    objective = 0;

    return objective;
}

////////////////////////////////////////////////////////////////////////////////

ObjectiveHeading::ObjectiveHeading() :
    m_above ( 0.0f ),
    m_below ( 0.0f )
{}

////////////////////////////////////////////////////////////////////////////////

ObjectiveHeading::~ObjectiveHeading() {}

////////////////////////////////////////////////////////////////////////////////

void ObjectiveHeading::update()
{
    Aircraft *aircraft = Ownship::instance()->getAircraft();

    if ( aircraft )
    {
        float heading = aircraft->getHeading();

        if ( heading > m_above && heading < m_below )
        {
            m_status = Success;
        }
    }
}
