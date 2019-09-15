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
#ifndef SIM_SCENERY_H
#define SIM_SCENERY_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>
#include <osg/PositionAttitudeTransform>
#include <osg/Switch>

#ifdef SIM_DESKTOP
#   include <osg/MatrixTransform>
#   include <osgSim/OverlayNode>
#endif

#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Scenery module class. */
class Scenery : public Module
{
public:

    typedef std::vector< std::string > ObjectFiles;

    static const float m_size_2;        ///< [m]
    static const float m_size;          ///< [m]
    static const float m_limit;         ///< [m] minimum distance in main directions from scenery center when generic terrain tiles are visible

    static std::string m_terrainFile;   ///< terrain file
    static std::string m_genericFile;   ///< generic terrain file
    static ObjectFiles m_objectFiles;   ///< object files

    /** */
    inline static osg::Node* getTerrainNode()
    {
        return m_terrainNode.get();
    }

    /** Constructor. */
    Scenery( Module *parent = 0 );

    /** Destructor. */
    virtual ~Scenery();

    /** Loads terrain. */
    void load();

    /** Updates scenery. */
    void update();

private:

#   ifdef SIM_DESKTOP
    osg::ref_ptr<osgSim::OverlayNode> m_overlayNode;        ///< aircraft shadow
    osg::ref_ptr<osg::MatrixTransform> m_mt;                ///<
#   endif

    static osg::ref_ptr<osg::Node> m_terrainNode;           ///< static terrain node for world view camera manipulator

    osg::ref_ptr<osg::Switch> m_switchGeneric;              ///< generic terrain tile switch

    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat_0;   ///< center
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat_x;   ///< EW (x) horizontal
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat_y;   ///< NS (y) vertical
    osg::ref_ptr<osg::PositionAttitudeTransform> m_pat_c;   ///< NE/NW/SE/SW (xy) corner

    UInt16 m_counter;                                       ///< generic terrain update counter

    void createGeneric();
    void createObjects();
#   ifdef SIM_SHADOW
    void createShadow();
#   endif

    void loadGeneric();
    void loadTerrain();

    void setPositionC( float xc, float yc, short ix, short iy, short dix, short diy );
    void setPositionX( float xc, float yc, short ix, short iy, short dix );
    void setPositionY( float xc, float yc, short ix, short iy, short diy );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_SCENERY_H
