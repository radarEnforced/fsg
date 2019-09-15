#include <sim/cgi/sim_ManipulatorOrbit.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ManipulatorOrbit::ManipulatorOrbit() :
    osgGA::NodeTrackerManipulator()
{
    setTrackerMode( NODE_CENTER );

    setWheelZoomFactor( -getWheelZoomFactor() );
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorOrbit::handleFrame( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us )
{
    ///////////////////////////////////////////////////////////////////
    bool result = osgGA::NodeTrackerManipulator::handleFrame( ea, us );
    ///////////////////////////////////////////////////////////////////

    boundDistance();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorOrbit::performMovementRightMouseButton( const double /*eventTimeDelta*/,
                                                        const double /*dx*/,
                                                        const double /*dy*/ )
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void ManipulatorOrbit::boundDistance()
{
#   ifdef SIM_DESKTOP
    if ( getDistance() > 5000.0 )
    {
        setDistance( 5000.0 );
    }
    else if ( getDistance() < 10.0 )
    {
        setDistance( 10.0 );
    }
#   else
    if ( getDistance() > 300.0 )
    {
        setDistance( 300.0 );
    }
    else if ( getDistance() < 5.0 )
    {
        setDistance( 5.0 );
    }
#   endif
}
