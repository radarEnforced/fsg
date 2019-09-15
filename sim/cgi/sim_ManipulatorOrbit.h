#ifndef SIM_MANIPULATORORBIT_H
#define SIM_MANIPULATORORBIT_H

////////////////////////////////////////////////////////////////////////////////

#include <osgGA/NodeTrackerManipulator>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Orbit view camera manipulator class. */
class ManipulatorOrbit : public osgGA::NodeTrackerManipulator
{
public:

    /** Constructor. */
    ManipulatorOrbit();

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

#endif // SIM_MANIPULATORORBIT_H
