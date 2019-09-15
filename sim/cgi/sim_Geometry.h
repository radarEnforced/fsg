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
#ifndef SIM_GEOMETRY_H
#define SIM_GEOMETRY_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Geode>
#include <osg/Geometry>
#include <osg/Group>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** CGI geometry class. */
class Geometry
{
public:

    /** Dome projection types. */
    enum Projection
    {
        Azimuthal = 0,  ///< azimuthal projection
        Cylindrical     ///< cylindrical projection
    };

    /**
     * Creates dome.
     * @param geom
     * @param radius
     * @param texCoords
     * @param projection
     * @param lat_segments
     * @param lon_segments
     */
    static void createDome( osg::Geometry *geom, float radius,
                            bool texCoords = false, Projection projection = Cylindrical,
                            int lat_segments = 18, int lon_segments = 36 );

    /**
     * Creates round face.
     * @param geom
     * @param radius
     * @param texCoords
     * @param segments
     */
    static void createFace( osg::Geometry *geom, float radius, bool texCoords = false,
                            int segments = 32 );

    /**
     * Creates flat square plane.
     * @param geom
     * @param size
     * @param segments
     * @param origin_x
     * @param origin_y
     * @param texCoords
     * @param segmentsPerTexture
     */
    static void createPlane( osg::Geometry *geom, double size, int segments,
                             double origin_x = 0.0, double origin_y = 0.0,
                             bool texCoords = false, int segmentsPerTexture = 1 );

    /**
     * Creates quad.
     * @param geom
     * @param v
     * @param texCoords
     * @param alpha
     */
    static void createQuad( osg::Geometry *geom, osg::Vec3Array *v,
                            bool texCoords = false, bool color = false,
                            float alpha = 1.0f );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_GEOMETRY_H
