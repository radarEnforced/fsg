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
#ifndef SIMULATIONOSG_H
#define SIMULATIONOSG_H

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <android/log.h>

//osg
#include <osg/GL>
#include <osg/GLExtensions>
#include <osg/Node>
#include <osg/Notify>
//osgDB
#include <osgDB/DatabasePager>
#include <osgDB/Registry>
//osg_viewer
#include <osgViewer/Viewer>
#include <osgViewer/Renderer>

////////////////////////////////////////////////////////////////////////////////

//Static plugins Macro
USE_OSGPLUGIN(freetype)
USE_OSGPLUGIN(ive)
USE_OSGPLUGIN(osg)
USE_OSGPLUGIN(osg2)
USE_OSGPLUGIN(rgb)
//USE_OSGPLUGIN(terrain)
//USE_OSGPLUGIN(OpenFlight)
//USE_OSGPLUGIN(dds)
//Static DOTOSG
USE_DOTOSGWRAPPER_LIBRARY(osg)
USE_DOTOSGWRAPPER_LIBRARY(osgFX)
USE_DOTOSGWRAPPER_LIBRARY(osgParticle)
USE_DOTOSGWRAPPER_LIBRARY(osgText)
USE_DOTOSGWRAPPER_LIBRARY(osgViewer)
USE_DOTOSGWRAPPER_LIBRARY(osgVolume)
//Static serializer
USE_SERIALIZER_WRAPPER_LIBRARY(osg)
USE_SERIALIZER_WRAPPER_LIBRARY(osgAnimation)
USE_SERIALIZER_WRAPPER_LIBRARY(osgFX)
USE_SERIALIZER_WRAPPER_LIBRARY(osgManipulator)
USE_SERIALIZER_WRAPPER_LIBRARY(osgParticle)
USE_SERIALIZER_WRAPPER_LIBRARY(osgText)
USE_SERIALIZER_WRAPPER_LIBRARY(osgVolume)

////////////////////////////////////////////////////////////////////////////////

/** */
class SimulationOSG
{
public:

    static const double m_zNear;    ///<
    static const double m_zFar;     ///<

    /** */
    class OSG_EXPORT AndroidNotifyHandler : public osg::NotifyHandler
    {
    public:

        void setTag( std::string tag );

        void notify( osg::NotifySeverity severity, const char *message );

    private:

        std::string m_tag;
    };

    /** */
    SimulationOSG();

    /** */
    ~SimulationOSG();

    /**
     * @param x
     * @param y
     * @param w viewport width in pixels
     * @param h viewport height in pixels
     * @param silent
     * @param mission_index mission file index (as defined in missions/missions.xml
     */
    void initCampaign( int x, int y, int w, int h, bool silent,
                       int mission_index );

    /**
     * @param x
     * @param y
     * @param w
     * @param h
     * @param silent
     * @param scenery_index scenery index
     * @param type_index_ownship ownship unit type index
     * @param livery_index_ownship ownship livery index
     * @param type_index_wingman wingman unit type index
     * @param livery_index_wingman wingman livery index
     * @param type_index_ally_1 1st ally unit type index
     * @param livery_index_ally_1 1st ally livery index
     * @param type_index_ally_2 2nd ally unit type index
     * @param livery_index_ally_2 2nd ally livery index
     * @param type_index_enemy_1 1st enemy unit type index
     * @param livery_index_enemy_1 1st enemy livery index
     * @param type_index_enemy_2 1nd enemy unit type index
     * @param livery_index_enemy_2 1nd enemy livery index
     * @param type_index_enemy_3 3rd enemy unit type index
     * @param livery_index_enemy_3 3rd enemy livery index
     * @param type_index_enemy_4 4th enemy unit type index
     * @param livery_index_enemy_4 4th enemy livery index
     */
    void initSkirmish( int x, int y, int w, int h, bool silent,
                       int scenery_index,
                       int type_index_ownship , int livery_index_ownship,
                       int type_index_wingman , int livery_index_wingman,
                       int type_index_ally_1  , int livery_index_ally_1,
                       int type_index_ally_2  , int livery_index_ally_2,
                       int type_index_enemy_1 , int livery_index_enemy_1,
                       int type_index_enemy_2 , int livery_index_enemy_2,
                       int type_index_enemy_3 , int livery_index_enemy_3,
                       int type_index_enemy_4 , int livery_index_enemy_4 );

    /**
     * @param x
     * @param y
     * @param w viewport width in pixels
     * @param h viewport height in pixels
     * @param unitId
     */
    void initUnitView( int x, int y, int w, int h,
                       int unit_index );

    /** */
    void pause();

    /** */
    void unpause();

    /** */
    void restart();

    /** */
    void destroy();

    /** */
    void update( double timeStep );

    /** */
    float getInitThrottle() const;

    /** */
    int getStatus() const;

    int getFriendsActivated() const;
    int getFriendsDestroyed() const;
    int getEnemiesActivated() const;
    int getEnemiesDestroyed() const;
    int getOwnshipDestroyed() const;

    int getFlightTime() const;

    /** */
    inline bool isFinished() const { return m_finished; }

    /** */
    inline bool isPaused() const { return m_paused; }

    /** */
    inline bool isPending() const { return m_pending; }

    /** */
    void setBasePath( const std::string &basePath );

    /** */
    void setControls( bool trigger,
                      float ctrlRoll,
                      float ctrlPitch,
                      float ctrlYaw,
                      float throttle );

    /** */
    void setLanguage( int index );

private:

    AndroidNotifyHandler *m_notifyHandler;

    osg::ref_ptr<osgViewer::Viewer> m_viewer;

    osg::ref_ptr<osg::Group> m_nodeHUD;
    osg::ref_ptr<osg::Group> m_nodeOTW;

    int m_initX;            ///<
    int m_initY;            ///<
    int m_initW;            ///<
    int m_initH;            ///<

    bool m_finished;        ///< specifies if simulation is finished
    bool m_paused;          ///< specifies if simulation is paused
    bool m_pending;         ///< specifies if mission is pending

    float m_heading;        ///< [rad] last valid heading

    void createViewer( int x, int y, int w, int h );
};

////////////////////////////////////////////////////////////////////////////////

#endif // SIMULATIONOSG_H
