/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

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
