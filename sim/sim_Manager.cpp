#include <sim/sim_Manager.h>

#include <sim/sim_Captions.h>
#include <sim/sim_Languages.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

std::string Base::m_basePath = SIM_DATA_PATH;

Data::SimulationData Data::m_data;

////////////////////////////////////////////////////////////////////////////////

Manager::Manager() :
    m_simulation ( 0 ),

    m_mode ( Campaign ),

    m_mission_index ( 0 ),
    m_scenery_index ( 0 ),

    m_type_index_ownship ( 0 ),
    m_type_index_wingman ( 0 ),
    m_type_index_ally_1  ( 0 ),
    m_type_index_ally_2  ( 0 ),
    m_type_index_enemy_1 ( 0 ),
    m_type_index_enemy_2 ( 0 ),
    m_type_index_enemy_3 ( 0 ),
    m_type_index_enemy_4 ( 0 ),

    m_livery_index_ownship ( 0 ),
    m_livery_index_wingman ( 0 ),
    m_livery_index_ally_1  ( 0 ),
    m_livery_index_ally_2  ( 0 ),
    m_livery_index_enemy_1 ( 0 ),
    m_livery_index_enemy_2 ( 0 ),
    m_livery_index_enemy_3 ( 0 ),
    m_livery_index_enemy_4 ( 0 ),

    m_status ( Pending ),

    m_timeStep ( 0.0 ),
    m_timeInit ( 0.0 ),

    m_autopilot ( false ),
    m_finished  ( false ),
    m_inited    ( false ),
    m_paused    ( false ),
    m_pending   ( false ),
    m_started   ( false )
{
    Data::reset();
}

////////////////////////////////////////////////////////////////////////////////

Manager::~Manager()
{
    if ( m_simulation ) delete m_simulation;
    m_simulation = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::init( int width, int height, bool silentMode,
                    UInt32 mission_index )
{
    if ( m_simulation != 0 )
    {
        reset();
    }

    m_simulation = new Simulation( width, height, silentMode );

    m_mode = Campaign;

    m_mission_index = mission_index;
    m_scenery_index = -1;

    m_type_index_ownship = -1;
    m_type_index_wingman = -1;
    m_type_index_ally_1  = -1;
    m_type_index_ally_2  = -1;
    m_type_index_enemy_1 = -1;
    m_type_index_enemy_2 = -1;
    m_type_index_enemy_3 = -1;
    m_type_index_enemy_4 = -1;

    m_livery_index_ownship = -1;
    m_livery_index_wingman = -1;
    m_livery_index_ally_1  = -1;
    m_livery_index_ally_2  = -1;
    m_livery_index_enemy_1 = -1;
    m_livery_index_enemy_2 = -1;
    m_livery_index_enemy_3 = -1;
    m_livery_index_enemy_4 = -1;

    setViewChase();

    m_cameraManipulator = m_simulation->getCameraManipulator();

    m_nodeHUD = m_simulation->getNodeHUD();
    m_nodeOTW = m_simulation->getNodeOTW();

    m_status = Pending;

    m_autopilot = false;
    m_finished  = false;
    m_inited    = false;
    m_paused    = true;
    m_pending   = true;
    m_started   = false;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::init( int width, int height, bool silentMode,
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
    if ( m_simulation != 0 )
    {
        reset();
    }

    m_simulation = new Simulation( width, height, silentMode );

    m_mode = Skirmish;

    m_mission_index = 0;
    m_scenery_index = scenery_index;

    m_type_index_ownship = type_index_ownship;
    m_type_index_wingman = type_index_wingman;
    m_type_index_ally_1  = type_index_ally_1;
    m_type_index_ally_2  = type_index_ally_2;
    m_type_index_enemy_1 = type_index_enemy_1;
    m_type_index_enemy_2 = type_index_enemy_2;
    m_type_index_enemy_3 = type_index_enemy_3;
    m_type_index_enemy_4 = type_index_enemy_4;

    m_livery_index_ownship = livery_index_ownship;
    m_livery_index_wingman = livery_index_wingman;
    m_livery_index_ally_1  = livery_index_ally_1;
    m_livery_index_ally_2  = livery_index_ally_2;
    m_livery_index_enemy_1 = livery_index_enemy_1;
    m_livery_index_enemy_2 = livery_index_enemy_2;
    m_livery_index_enemy_3 = livery_index_enemy_3;
    m_livery_index_enemy_4 = livery_index_enemy_4;

    setViewChase();

    m_cameraManipulator = m_simulation->getCameraManipulator();

    m_nodeHUD = m_simulation->getNodeHUD();
    m_nodeOTW = m_simulation->getNodeOTW();

    m_status = Pending;

    m_autopilot = false;
    m_finished  = false;
    m_inited    = false;
    m_paused    = true;
    m_pending   = true;
    m_started   = false;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::init( int width, int height, UInt32 unit_index )
{
    if ( m_simulation != 0 )
    {
        reset();
    }

    m_simulation = new Simulation( width, height, unit_index );

    m_mode = UnitView;

    m_cameraManipulator = m_simulation->getCameraManipulator();

    m_nodeOTW = m_simulation->getNodeViewer();
}

////////////////////////////////////////////////////////////////////////////////

void Manager::reload()
{
    if ( m_simulation )
    {
        m_simulation->load();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::update( double timeStep )
{
    m_timeStep = timeStep;

    if ( m_timeStep < SIM_TIME_STEP_MIN ) m_timeStep = SIM_TIME_STEP_MIN;
    if ( m_timeStep > SIM_TIME_STEP_MAX ) m_timeStep = SIM_TIME_STEP_MAX;

    if ( m_simulation != 0 )
    {
        if ( m_simulation->getViewerMode() )
        {
            m_simulation->update( m_timeStep );
        }
        else
        {
            if ( !m_inited )
            {
                if ( m_timeInit > 1.0 )
                {
                    switch ( m_mode )
                    {
                    case Campaign:
                        m_simulation->init( m_mission_index );
                        break;

                    case Skirmish:
                        m_simulation->init( m_scenery_index,
                                            m_type_index_ownship , m_livery_index_ownship,
                                            m_type_index_wingman , m_livery_index_wingman,
                                            m_type_index_ally_1  , m_livery_index_ally_1,
                                            m_type_index_ally_2  , m_livery_index_ally_2,
                                            m_type_index_enemy_1 , m_livery_index_enemy_1,
                                            m_type_index_enemy_2 , m_livery_index_enemy_2,
                                            m_type_index_enemy_3 , m_livery_index_enemy_3,
                                            m_type_index_enemy_4 , m_livery_index_enemy_4 );
                        break;

                    case UnitView:
                        m_simulation->init();
                        break;
                    }

                    m_simulation->load();

                    m_inited = true;
                }

                m_timeInit += m_timeStep;
            }
            else
            {
                Data::get()->controls.autopilot = m_autopilot;

                if ( m_paused )
                {
                    if ( !Data::get()->paused )
                    {
                        Data::get()->message.visible = true;
                        Data::get()->message.overlay = true;

                        if ( m_started )
                        {
                            strcpy( Data::get()->message.text, Captions::instance()->getResume().c_str() );
                        }
                        else
                        {
                            strcpy( Data::get()->message.text, Captions::instance()->getBegin().c_str() );
                        }
                    }
                }
                else
                {
                    m_started = true;

                    if ( !m_pending )
                    {
                        if ( Data::get()->mission.time_end > SIM_END_DELAY )
                        {
                            m_finished = true;
                            m_paused   = true;
                        }
                    }
                }

                Data::get()->paused = m_paused;

                ///////////////////////////////////
                m_simulation->update( m_timeStep );
                ///////////////////////////////////

                m_status = Data::get()->mission.status;

                m_pending = m_status == Pending;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::pause()
{
    if ( m_inited )
    {
        m_paused = true;

        if ( m_simulation )
        {
            m_simulation->pause();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::unpause()
{
    if ( m_inited )
    {
        m_paused = false;

        if ( m_simulation )
        {
            m_simulation->unpause();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::restart()
{
    if ( m_simulation )
    {
        m_simulation->restart();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::destroy()
{
    reset();
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setControls( bool trigger,
                           float ctrlRoll,
                           float ctrlPitch,
                           float ctrlYaw,
                           float throttle )
{
    Data::get()->controls.trigger = trigger;

    Data::get()->controls.ctrlRoll  = ctrlRoll;
    Data::get()->controls.ctrlPitch = ctrlPitch;
    Data::get()->controls.ctrlYaw   = ctrlYaw;
    Data::get()->controls.throttle  = throttle;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setLanguage( int index )
{
    sim::Languages::instance()->setCurrent( index );
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewChase()
{
    if ( m_simulation )
    {
        m_simulation->setViewChase();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewFlyby()
{
    if ( m_simulation )
    {
        m_simulation->setViewFlyby();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewFront()
{
    if ( m_simulation )
    {
        m_simulation->setViewFront();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewOrbit()
{
    if ( m_simulation )
    {
        m_simulation->setViewOrbit();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewPilot()
{
    if ( m_simulation )
    {
        m_simulation->setViewPilot();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewShift()
{
    if ( m_simulation )
    {
        m_simulation->setViewShift();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setViewWorld()
{
    if ( m_simulation )
    {
        m_simulation->setViewWorld();
        m_cameraManipulator = m_simulation->getCameraManipulator();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::toggleOrbitUnit()
{
    if ( m_simulation )
    {
        m_simulation->toggleOrbitUnit();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::reset()
{
    Data::reset();

    if ( m_simulation ) delete m_simulation;
    m_simulation = 0;

    m_nodeHUD = 0;
    m_nodeOTW = 0;

    m_timeStep = 0.0;
    m_timeInit = 0.0;

    m_autopilot = false;
    m_finished  = false;
    m_inited    = false;
    m_paused    = false;
    m_pending   = false;
    m_started   = false;
}
