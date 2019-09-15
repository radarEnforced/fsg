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
#ifndef SIM_UNITVIEWER_H
#define SIM_UNITVIEWER_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <sim/cgi/sim_ManipulatorOrbit.h>
#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Unit viewer class.
 * <p>This class is used to display single unit object.</p>
 */
class UnitViewer : public Module
{
public:

    /** Constructor. */
    UnitViewer( int width, int height, UInt32 index, Module *parent = 0 );

    /** Destructor. */
    virtual ~UnitViewer();

    /** Loads and reloads view (models, textures, etc.). */
    void load();

    /** Resets camera position and attitude. */
    void resetViewer();

    /** Updates view. */
    void update( double timeStep );

    /** */
    inline osgGA::CameraManipulator* getCameraManipulator()
    {
        return m_manipulatorOrbit.get();
    }

private:

    const UInt32 m_index;   ///< current unit index

    const float m_distCoef; ///<

    osg::ref_ptr<ManipulatorOrbit> m_manipulatorOrbit;          ///<

    osg::ref_ptr<osg::PositionAttitudeTransform> m_patUnit;     ///< orbit manipulator center
    osg::ref_ptr<osg::PositionAttitudeTransform> m_patModel;    ///< model group node

    osg::ref_ptr<osg::PositionAttitudeTransform> m_propeller1;  ///<
    osg::ref_ptr<osg::PositionAttitudeTransform> m_propeller2;  ///<
    osg::ref_ptr<osg::PositionAttitudeTransform> m_propeller3;  ///<
    osg::ref_ptr<osg::PositionAttitudeTransform> m_propeller4;  ///<

    Vec3 m_pos;             ///< model position
    Quat m_att;             ///< model attitude

    double m_prop_angle;    ///< [rad] propeller angle
    double m_real_time;     ///< [s] real time

    void createSky();
    void createSun();

    void createDome( osg::Geode *dome, osg::Texture2D *texture,
                     float radius, bool blend = false );

    void createGround();
    void createOcean();
    void createPlane( const std::string &textureFile );

    void loadUnit();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_UNITVIEWER_H
