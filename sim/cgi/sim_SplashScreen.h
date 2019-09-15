#ifndef SIM_SPLASHSCREEN_H
#define SIM_SPLASHSCREEN_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Splash screen class. */
class SplashScreen
{
public:

    /** Returns splash sreen node.  */
    static osg::Group* create( int width, int height );

private:

    /** Creates background. */
    static void createBack( osg::Group *parent, float maxX );

    /** Creates text. */
    static void createText( osg::Group *parent );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_SPLASHSCREEN_H
