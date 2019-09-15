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

#include <osg/PolygonMode>

#include <sim/sim_Manager.h>

#include "SimulationOSG.h"

////////////////////////////////////////////////////////////////////////////////

const double SimulationOSG::m_zNear = 0.55;
const double SimulationOSG::m_zFar  = SIM_SKYDOME_RAD + 0.1f * SIM_SKYDOME_RAD;

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::AndroidNotifyHandler::setTag( std::string tag )
{
    m_tag = tag;
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::AndroidNotifyHandler::notify( osg::NotifySeverity severity, const char *message )
{
    switch ( severity )
    {
        case osg::DEBUG_FP:
            __android_log_write( ANDROID_LOG_VERBOSE, m_tag.c_str(), message );
            break;
        case osg::DEBUG_INFO:
            __android_log_write( ANDROID_LOG_DEBUG, m_tag.c_str(), message );
            break;
        case osg::NOTICE:
        case osg::INFO:
            __android_log_write( ANDROID_LOG_INFO, m_tag.c_str(), message );
            break;
        case osg::WARN:
            __android_log_write( ANDROID_LOG_WARN, m_tag.c_str(), message );
            break;
        case osg::FATAL:
        case osg::ALWAYS:
            __android_log_write( ANDROID_LOG_ERROR, m_tag.c_str(), message );
            break;
        default:
            __android_log_write( ANDROID_LOG_DEBUG, m_tag.c_str(), message );
            break;
    }
}

////////////////////////////////////////////////////////////////////////////////

SimulationOSG::SimulationOSG() :
    m_initX ( 0 ),
    m_initY ( 0 ),
    m_initW ( 0 ),
    m_initH ( 0 ),

    m_finished ( false ),
    m_paused   ( false ),
    m_pending  ( false ),

    m_heading ( 0.0f )
{
    m_notifyHandler = new AndroidNotifyHandler();
    m_notifyHandler->setTag( "Simulation" );
    osg::setNotifyHandler( m_notifyHandler );

    osg::setNotifyLevel( osg::WARN );
    //osg::setNotifyLevel( osg::DEBUG_INFO );
}

////////////////////////////////////////////////////////////////////////////////

SimulationOSG::~SimulationOSG() {}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::initCampaign( int x, int y, int w, int h, bool silent,
                                  int mission_index )
{
    if ( sim::Manager::instance()->isInited() )
    {
        sim::Manager::instance()->destroy();
    }

    if ( !sim::Manager::instance()->isInited() )
    {
        m_initX = x;
        m_initY = y;
        m_initW = w;
        m_initH = h;

        m_finished = false;
        m_pending  = true;

        m_heading = 0.0f;

        sim::Manager::instance()->init( m_initW, m_initH, silent, mission_index );
        sim::Manager::instance()->setViewChase();

        sim::Manager::instance()->setAutopilot( false );
    }
    else
    {
        sim::Manager::instance()->reload();
    }

    if ( m_viewer.valid() )
    {
        m_viewer = 0;

        m_nodeHUD = 0;
        m_nodeOTW = 0;
    }

    createViewer( m_initX, m_initY, m_initW, m_initH );
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::initSkirmish( int x, int y, int w, int h, bool silent,
                                  int scenery_index,
                                  int type_index_ownship , int livery_index_ownship,
                                  int type_index_wingman , int livery_index_wingman,
                                  int type_index_ally_1  , int livery_index_ally_1,
                                  int type_index_ally_2  , int livery_index_ally_2,
                                  int type_index_enemy_1 , int livery_index_enemy_1,
                                  int type_index_enemy_2 , int livery_index_enemy_2,
                                  int type_index_enemy_3 , int livery_index_enemy_3,
                                  int type_index_enemy_4 , int livery_index_enemy_4 )
{
    if ( sim::Manager::instance()->isInited() )
    {
        sim::Manager::instance()->destroy();
    }

    if ( !sim::Manager::instance()->isInited() )
    {
        m_initX = x;
        m_initY = y;
        m_initW = w;
        m_initH = h;

        m_finished = false;
        m_pending  = true;

        m_heading = 0.0f;

        sim::Manager::instance()->init( m_initW, m_initH, silent,
                                        scenery_index,
                                        type_index_ownship , livery_index_ownship,
                                        type_index_wingman , livery_index_wingman,
                                        type_index_ally_1  , livery_index_ally_1,
                                        type_index_ally_2  , livery_index_ally_2,
                                        type_index_enemy_1 , livery_index_enemy_1,
                                        type_index_enemy_2 , livery_index_enemy_2,
                                        type_index_enemy_3 , livery_index_enemy_3,
                                        type_index_enemy_4 , livery_index_enemy_4 );

        sim::Manager::instance()->setViewChase();

        sim::Manager::instance()->setAutopilot( false );
    }
    else
    {
        sim::Manager::instance()->reload();
    }

    if ( m_viewer.valid() )
    {
        m_viewer = 0;

        m_nodeHUD = 0;
        m_nodeOTW = 0;
    }

    createViewer( m_initX, m_initY, m_initW, m_initH );
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::initUnitView( int x, int y, int w, int h,
                                  int unit_index )
{
    if ( sim::Manager::instance()->isInited() )
    {
        sim::Manager::instance()->destroy();
    }

    if ( !sim::Manager::instance()->isInited() )
    {
        m_initX = x;
        m_initY = y;
        m_initW = w;
        m_initH = h;

        m_finished = false;
        m_pending  = true;

        m_heading = 0.0f;

        sim::Manager::instance()->init( m_initW, m_initH, unit_index );
    }
    else
    {
        sim::Manager::instance()->reload();
    }

    if ( m_viewer.valid() )
    {
        m_viewer = 0;

        m_nodeHUD = 0;
        m_nodeOTW = 0;
    }

    createViewer( m_initX, m_initY, m_initW, m_initH );
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::pause()
{
    sim::Manager::instance()->pause();
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::unpause()
{
    sim::Manager::instance()->unpause();
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::restart()
{
    m_nodeHUD = 0;
    m_nodeOTW = 0;

    if ( sim::Manager::instance()->isReady() )
    {
        sim::Manager::instance()->reload();
        sim::Manager::instance()->restart();
    }

    if ( m_viewer.valid() )
    {
        m_viewer->setSceneData( NULL );
        m_viewer = 0;
    }

    createViewer( m_initX, m_initY, m_initW, m_initH );

    //osg::notify(osg::ALWAYS) << __FILE__ << "(" << __LINE__ << ") ";
    //osg::notify(osg::ALWAYS) << SimulationOSG::restart()" << std::endl;

    if ( sim::Success == sim::Data::get()->mission.status || sim::Data::get()->ownship.destroyed )
    {
        if ( sim::Manager::instance()->isReady() )
        {
            sim::Manager::instance()->setViewOrbit();
            m_viewer->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::destroy()
{
    sim::Manager::instance()->destroy();

    if ( m_viewer.valid() )
    {
        m_viewer->setSceneData( NULL );
        m_viewer = 0;
    }
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::update( double timeStep )
{
    if ( m_viewer.valid() )
    {
        m_viewer->setSceneData( NULL );

        if ( sim::Manager::instance()->isInited() )
        {
            if ( m_nodeOTW.valid() )
            {
                m_viewer->setSceneData( m_nodeOTW.get() );

                //sim::Manager::getInstance()->getCameraManipulator()->getNode();
                m_viewer->home();

                //m_viewer->getDatabasePager()->clear();
                //m_viewer->getDatabasePager()->registerPagedLODs( sim::Manager::getInstance()->getNodeOTW() );
                //m_viewer->getDatabasePager()->setUpThreads( 3, 1 );
                //m_viewer->getDatabasePager()->setTargetMaximumNumberOfPageLOD( 2 );
                //m_viewer->getDatabasePager()->setUnrefImageDataAfterApplyPolicy( true, true );
            }

            if ( sim::Manager::instance()->isViewer() )
            {
                // TODO: this should be done only once
                // I dont know why this is not working
                m_viewer->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );
                sim::Manager::instance()->resetViewer();
            }
            else if ( m_pending && !sim::Data::get()->ownship.destroyed )
            {
                m_heading = sim::Data::get()->ownship.heading;
            }
            else if ( sim::Success == sim::Data::get()->mission.status
                   || sim::Data::get()->ownship.destroyed )
            {
                sim::Manager::instance()->setAutopilot( true );

                if ( sim::Manager::instance()->isReady()
                  && sim::Data::get()->camera.type != sim::ViewOrbit )
                {
                    sim::Manager::instance()->setViewOrbit();
                    m_viewer->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );
                }

                osg::ref_ptr<sim::ManipulatorOrbit> manipulator =
                    dynamic_cast< sim::ManipulatorOrbit* >( sim::Manager::instance()->getCameraManipulator() );

                if ( manipulator.valid() )
                {
                    manipulator->setElevation( osg::DegreesToRadians( 10.0 ) );
                    manipulator->setDistance( 25.0 );
                    manipulator->setHeading( -M_PI_2 - m_heading - M_PI_4 );
                }
            }
        }

        sim::Manager::instance()->update( timeStep );

        m_finished = sim::Manager::instance()->isFinished();
        m_paused   = sim::Manager::instance()->isPaused();
        m_pending  = sim::Manager::instance()->isPending();

        m_viewer->frame();
    }
}

////////////////////////////////////////////////////////////////////////////////

float SimulationOSG::getInitThrottle() const
{
    return sim::Data::get()->ownship.init_throttle;
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getStatus() const
{
    return sim::Manager::instance()->getStatus();
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getFriendsActivated() const
{
    return sim::Statistics::instance()->getFriendsActivated();
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getFriendsDestroyed() const
{
    return sim::Statistics::instance()->getFriendsDestroyed();
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getEnemiesActivated() const
{
    return sim::Statistics::instance()->getEnemiesActivated();
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getEnemiesDestroyed() const
{
    return sim::Statistics::instance()->getEnemiesDestroyed();
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getOwnshipDestroyed() const
{
    return sim::Statistics::instance()->getOwnshipDestroyed();
}

////////////////////////////////////////////////////////////////////////////////

int SimulationOSG::getFlightTime() const
{
    return sim::Statistics::instance()->getFlightTime();
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::setBasePath( const std::string &basePath )
{
    sim::Base::setBasePath( basePath );
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::setControls( bool trigger,
                                 float ctrlRoll,
                                 float ctrlPitch,
                                 float ctrlYaw,
                                 float throttle )
{
    sim::Manager::instance()->setControls( trigger,
                                           ctrlRoll,
                                           ctrlPitch,
                                           ctrlYaw,
                                           throttle );
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::setLanguage( int index )
{
    sim::Manager::instance()->setLanguage( index );
}

////////////////////////////////////////////////////////////////////////////////

void SimulationOSG::createViewer( int x, int y, int w, int h )
{
    const double w2h = (double)(w) / (double)(h);

    m_nodeHUD = sim::Manager::instance()->getNodeHUD();
    m_nodeOTW = sim::Manager::instance()->getNodeOTW();

    m_viewer = new osgViewer::Viewer();
    m_viewer->setUpViewerAsEmbeddedInWindow( x, y, w, h );

    //m_viewer->realize();

    // main camera
    osg::ref_ptr<osg::Camera> cameraOTW = m_viewer->getCamera();
    cameraOTW->setClearColor( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
    cameraOTW->setProjectionMatrixAsPerspective( 30.0f, w2h, m_zNear, m_zFar );
    cameraOTW->setNearFarRatio( m_zNear / m_zFar );

    m_viewer->setUpViewAcrossAllScreens();

    osgViewer::Viewer::Windows windows;
    m_viewer->getWindows( windows );

    if ( !windows.empty() && m_nodeHUD.valid() )
    {
        const double size = 100.0;

        // HUD camera
        osg::ref_ptr<osg::Camera> cameraHUD = new osg::Camera();
        cameraHUD->setGraphicsContext( windows[ 0 ] );

        cameraHUD->setProjectionMatrixAsOrtho2D(-size * w2h, size * w2h, -size, size);
        cameraHUD->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
        cameraHUD->setViewMatrix( osg::Matrix::identity() );
        cameraHUD->setClearMask( GL_DEPTH_BUFFER_BIT );
        cameraHUD->setRenderOrder( osg::Camera::POST_RENDER );
        cameraHUD->setAllowEventFocus( false );
        cameraHUD->setProjectionResizePolicy( osg::Camera::HORIZONTAL );
        cameraHUD->addChild( m_nodeHUD.get() );
        //cameraHUD->setViewport( new osg::Viewport( 0, 0, w, h ) );
        cameraHUD->setViewport( 0, 0, w, h );
        //cameraHUD->setViewport( 0, 0, windows[0]->getTraits()->width, windows[0]->getTraits()->height );

        m_viewer->addSlave( cameraHUD, false );
    }

    m_viewer->setSceneData( sim::Manager::instance()->getNodeOTW() );
    //m_viewer->addEventHandler( new osgViewer::StatsHandler() );
    m_viewer->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_viewer->setKeyEventSetsDone( 0 );

    m_viewer->assignSceneDataToCameras();
}
