#ifndef SIM_MANIPULATORWORLD_H
#define SIM_MANIPULATORWORLD_H

////////////////////////////////////////////////////////////////////////////////

#include <osgGA/TerrainManipulator>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** World view camera manipulator class. */
class ManipulatorWorld : public osgGA::TerrainManipulator
{
public:

    /** Constructor. */
    ManipulatorWorld();

protected:

    /** */
    bool handleFrame( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &us );

    /** */
    bool performMovementRightMouseButton( const double /*eventTimeDelta*/,
                                          const double /*dx*/,
                                          const double /*dy*/ );

private:

    void boundDistance();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_MANIPULATORWORLD_H
