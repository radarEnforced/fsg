#include <sim/cgi/sim_ManipulatorWorld.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ManipulatorWorld::ManipulatorWorld() :
    osgGA::TerrainManipulator()
{
    setWheelZoomFactor( -getWheelZoomFactor() );
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorWorld::handleFrame( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us )
{
    ///////////////////////////////////////////////////////////////
    bool result = osgGA::TerrainManipulator::handleFrame( ea, us );
    ///////////////////////////////////////////////////////////////

    boundDistance();

    return result;
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorWorld::performMovementRightMouseButton( const double /*eventTimeDelta*/,
                                                        const double /*dx*/,
                                                        const double /*dy*/ )
{
    return true;
}

////////////////////////////////////////////////////////////////////////////////

void ManipulatorWorld::boundDistance()
{
    if ( getDistance() > 10.0e4 )
    {
        setDistance( 10.0e4 );
    }
}
