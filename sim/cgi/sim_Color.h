#ifndef SIM_COLOR_H
#define SIM_COLOR_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Vec3>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Colors class. */
class Color
{
public:

    static const osg::Vec3 amber;       ///< amber
    static const osg::Vec3 black;       ///< black  (according to W3C)
    static const osg::Vec3 cyan;        ///< cyan   (according to W3C)
    static const osg::Vec3 green;       ///< green  (according to W3C)
    static const osg::Vec3 grey;        ///< grey   (according to W3C)
    static const osg::Vec3 lime;        ///< lime   (according to W3C)
    static const osg::Vec3 orange;      ///< orange (according to W3C)
    static const osg::Vec3 red;         ///< red    (according to W3C)
    static const osg::Vec3 white;       ///< white  (according to W3C)
    static const osg::Vec3 yellow;      ///< yellow (according to W3C)

    static const osg::Vec3 fog_light;   ///< light fog color
    static const osg::Vec3 fog_heavy;   ///< heavy fog color

    static const osg::Vec3 sun;         ///< sun light color
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_COLOR_H
