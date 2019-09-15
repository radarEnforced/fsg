#include <sim/sim_Simulation.h>

#include <math.h>

#include <sim/sim_Creator.h>
#include <sim/sim_Elevation.h>
#include <sim/sim_ListScenery.h>
#include <sim/sim_ListUnits.h>
#include <sim/sim_Ownship.h>

#include <sim/cgi/sim_FogScene.h>
#include <sim/cgi/sim_Models.h>
#include <sim/cgi/sim_Scenery.h>
#include <sim/cgi/sim_SkyDome.h>

#include <sim/missions/sim_ObjectiveDestroy.h>
#include <sim/missions/sim_ObjectiveTimeout.h>

#include <sim/utils/sim_Convert.h>
#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlDoc.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Simulation::Simulation( int width, int height, bool silentMode ) :
    m_otw ( 0 ),
    m_hud ( 0 ),
    m_sfx ( 0 ),

    m_viewer ( 0 ),

    m_camera  ( 0 ),
    m_mission ( 0 ),

    m_silentMode ( silentMode ),
    m_viewerMode ( false ),

    m_orbitedUnitId ( 0 )
{
    readMissions();

    float linesWidth = floor( (float)height / 200.0f + 0.5f );

    Models::createTracer( 1.2f * linesWidth );

    m_otw = new OTW( linesWidth );
    m_hud = new HUD( linesWidth, width, height );
    m_sfx = new SFX();

    m_camera = new Camera();
}

////////////////////////////////////////////////////////////////////////////////

Simulation::Simulation( int width, int height, UInt32 index ) :
    m_otw ( 0 ),
    m_hud ( 0 ),
    m_sfx ( 0 ),

    m_viewer ( 0 ),

    m_camera  ( 0 ),
    m_mission ( 0 ),

    m_silentMode ( true ),
    m_viewerMode ( true ),

    m_orbitedUnitId ( 0 )
{
    m_viewer = new UnitViewer( width, height, index );
}

////////////////////////////////////////////////////////////////////////////////

Simulation::~Simulation()
{
    Models::reset();

    if ( m_otw ) delete m_otw;
    m_otw = 0;

    if ( m_hud ) delete m_hud;
    m_hud = 0;

    if ( m_sfx ) delete m_sfx;
    m_sfx = 0;

    if ( m_viewer ) delete m_viewer;
    m_viewer = 0;

    if ( m_camera ) delete m_camera;
    m_camera = 0;

    if ( m_mission ) delete m_mission;
    m_mission = 0;
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::init() {}

////////////////////////////////////////////////////////////////////////////////

void Simulation::init( UInt32 mission_index )
{
    if ( m_viewerMode ) return;

    if ( mission_index < m_missions.size() )
    {
        m_mission = new Mission();
        m_mission->init( m_missions[ mission_index ] );
    }

    Ownship::instance()->init();

    m_otw->init();
    m_hud->init( m_mission->isTutorial() );
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::init( int scenery_index,
                       int type_index_ownship , int livery_index_ownship,
                       int type_index_wingman , int livery_index_wingman,
                       int type_index_ally_1  , int livery_index_ally_1,
                       int type_index_ally_2  , int livery_index_ally_2,
                       int type_index_enemy_1 , int livery_index_enemy_1,
                       int type_index_enemy_2 , int livery_index_enemy_2,
                       int type_index_enemy_3 , int livery_index_enemy_3,
                       int type_index_enemy_4 , int livery_index_enemy_4 )
{
    if ( m_viewerMode ) return;

    m_mission = new Mission();

    if ( type_index_ownship >= 0 && type_index_ownship < (int)ListUnits::instance()->getCount() )
    {
        Vec3 initialPosition;

        Elevation::instance()->reset();

        Scenery::m_objectFiles.clear();
        Scenery::m_terrainFile = ListScenery::instance()->getData( 0 ).terrainFile;
        Scenery::m_genericFile = ListScenery::instance()->getData( 0 ).genericFile;
        SkyDome::m_skyDomeFile = "textures/sky_1.rgb";

        FogScene::m_visibility = 0.9f * SIM_SKYDOME_RAD;
        SkyDome::m_sunCoef = 1.0f;

        if ( scenery_index >= 0 && scenery_index < (int)ListScenery::instance()->getCount() )
        {
            ListScenery::SceneryData sceneryData = ListScenery::instance()->getData( scenery_index );

            Scenery::m_terrainFile = sceneryData.terrainFile;
            Scenery::m_genericFile = sceneryData.genericFile;

            for ( UInt32 i = 0; i < sceneryData.objectFiles.size(); i++ )
            {
                Scenery::m_objectFiles.push_back( sceneryData.objectFiles[ i ] );
            }

            if ( sceneryData.elevationFile.length() > 0 )
            {
                Elevation::instance()->readFile( getPath( sceneryData.elevationFile ) );
            }

            initialPosition = sceneryData.initialPosition;
        }

        Aircraft *ownship = Creator::createAircraft( type_index_ownship , livery_index_ownship , Friend  );
        Aircraft *wingman = Creator::createAircraft( type_index_wingman , livery_index_wingman , Friend  );
        Aircraft *ally_1  = Creator::createAircraft( type_index_ally_1  , livery_index_ally_1  , Friend  );
        Aircraft *ally_2  = Creator::createAircraft( type_index_ally_2  , livery_index_ally_2  , Friend  );
        Aircraft *enemy_1 = Creator::createAircraft( type_index_enemy_1 , livery_index_enemy_1 , Hostile );
        Aircraft *enemy_2 = Creator::createAircraft( type_index_enemy_2 , livery_index_enemy_2 , Hostile );
        Aircraft *enemy_3 = Creator::createAircraft( type_index_enemy_3 , livery_index_enemy_3 , Hostile );
        Aircraft *enemy_4 = Creator::createAircraft( type_index_enemy_4 , livery_index_enemy_4 , Hostile );

        float initialAlt = 305.0f;

        Vec3 pos_ownship = initialPosition + Vec3(  0.0, -1500.0, initialAlt );
        Vec3 pos_wingman = initialPosition + Vec3( 50.0, -1600.0, initialAlt );

        Vec3 pos_ally_1 = initialPosition + Vec3(  0.0, -2000.0, initialAlt );
        Vec3 pos_ally_2 = initialPosition + Vec3( 50.0, -2100.0, initialAlt );

        Vec3 pos_opponent_1 = initialPosition + Vec3( 1500.0,   0.0, initialAlt );
        Vec3 pos_opponent_2 = initialPosition + Vec3( 1600.0, -50.0, initialAlt );
        Vec3 pos_opponent_3 = initialPosition + Vec3( 2000.0,   0.0, initialAlt );
        Vec3 pos_opponent_4 = initialPosition + Vec3( 2100.0, -50.0, initialAlt );

        Stage *stage_1 = new Stage();
        Stage *stage_2 = new Stage();

        ObjectiveDestroy *objectiveDestroy = new ObjectiveDestroy();
        ObjectiveTimeout *objectiveTimeout = new ObjectiveTimeout();

        float init_speed = 0.0f;

        float hdg_friends  = Convert::deg2rad(  30.0f );
        float hdg_enemies  = Convert::deg2rad( 240.0f );

        if ( ownship )
        {
            ownship->setName( "ownship" );

            init_speed = ( ownship->getSpeedMin() + ownship->getSpeedMax() ) / 2.0f;

            ownship->setPos( pos_ownship );
            ownship->setHeading( hdg_friends );
            ownship->setVelocity( init_speed );

            ownship->makeOwnship(); // after velocity
        }

        if ( wingman )
        {
            wingman->setName( "wingman" );
            stage_1->addInitUnit( wingman->getName() );

            wingman->setPos( pos_wingman );
            wingman->setHeading( hdg_friends );
            wingman->setVelocity( init_speed );
        }

        if ( ally_1 )
        {
            ally_1->setName( "ally_1" );
            stage_1->addInitUnit( ally_1->getName() );

            ally_1->setPos( pos_ally_1 );
            ally_1->setHeading( hdg_friends );
            ally_1->setVelocity( init_speed );
        }

        if ( ally_2 )
        {
            ally_2->setName( "ally_2" );
            stage_1->addInitUnit( ally_2->getName() );

            ally_2->setPos( pos_ally_2 );
            ally_2->setHeading( hdg_friends );
            ally_2->setVelocity( init_speed );
        }

        if ( enemy_1 )
        {
            enemy_1->setName( "enemy_1" );
            stage_1->addInitUnit( enemy_1->getName() );
            objectiveDestroy->addUnitId( enemy_1->getId() );

            enemy_1->setPos( pos_opponent_1 );
            enemy_1->setHeading( hdg_enemies );
            enemy_1->setVelocity( init_speed );
        }

        if ( enemy_2 )
        {
            enemy_2->setName( "enemy_2" );
            stage_1->addInitUnit( enemy_2->getName() );
            objectiveDestroy->addUnitId( enemy_2->getId() );

            enemy_2->setPos( pos_opponent_2 );
            enemy_2->setHeading( hdg_enemies );
            enemy_2->setVelocity( init_speed );
        }

        if ( enemy_3 )
        {
            enemy_3->setName( "enemy_3" );
            stage_1->addInitUnit( enemy_3->getName() );
            objectiveDestroy->addUnitId( enemy_3->getId() );

            enemy_3->setPos( pos_opponent_3 );
            enemy_3->setHeading( hdg_enemies );
            enemy_3->setVelocity( init_speed );
        }

        if ( enemy_4 )
        {
            enemy_4->setName( "enemy_4" );
            stage_1->addInitUnit( enemy_4->getName() );
            objectiveDestroy->addUnitId( enemy_4->getId() );

            enemy_4->setPos( pos_opponent_4 );
            enemy_4->setHeading( hdg_enemies );
            enemy_4->setVelocity( init_speed );
        }

        objectiveTimeout->setLimit( 3.0f );

        stage_1->addObjective( objectiveDestroy );
        stage_2->addObjective( objectiveTimeout );

        m_mission->addStage( stage_1 );
        m_mission->addStage( stage_2 );
    }

    m_mission->init();

    Ownship::instance()->init();

    m_otw->init();
    m_hud->init( m_mission->isTutorial() );
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::load()
{
    Models::instance()->reset();

    if ( !m_viewerMode )
    {
        // entities must be loaded before OTW
        Entities::instance()->load();

        m_otw->load();
        m_hud->load();

        if ( !m_silentMode ) m_sfx->init();
    }
    else
    {
        m_viewer->load();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::pause()
{
    if ( !m_viewerMode )
    {
        m_sfx->pause();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::unpause()
{
    if ( !m_viewerMode )
    {
        if ( !m_silentMode ) m_sfx->unpause();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::restart()
{
    if ( m_viewerMode )
    {
        m_viewer->load();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::update( double timeStep )
{
    if ( !m_viewerMode )
    {
        m_mission->update( timeStep );

        // ownship (after mission!)
        Ownship::instance()->update( timeStep );

        m_otw->update();
        m_hud->update();
        m_sfx->update();

        m_camera->update();
    }
    else
    {
        m_viewer->update( timeStep );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewChase()
{
    if ( m_camera ) m_camera->setViewChase();
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewFlyby()
{
    if ( m_camera ) m_camera->setViewFlyby();
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewFront()
{
    if ( m_camera ) m_camera->setViewFront();
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewOrbit()
{
    if ( m_camera )
    {
        m_orbitedUnitId = 0;

        Entity *ownship = Ownship::instance()->getEntity();

        if ( ownship )
        {
            if ( ownship->isActive() )
            {
                m_camera->setTrackNode( ownship->getEntityNode() );
                m_camera->setViewOrbit();

                Unit *unit = dynamic_cast< Unit* >( ownship );

                if ( unit )
                {
                    m_orbitedUnitId = unit->getId();
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewPilot()
{
    if ( m_camera ) m_camera->setViewPilot();
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewShift()
{
    if ( m_camera ) m_camera->setViewShift();
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::setViewWorld()
{
    if ( m_camera )
    {
        if ( !m_camera->isWorldNodeValid() )
        {
            osg::ref_ptr<osg::Node> worldNode = Scenery::getTerrainNode();

            if ( worldNode.valid() )
            {
                m_camera->setWorldNode( worldNode.get() );
            }
        }

        m_camera->setViewWorld();
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::toggleOrbitUnit()
{
    if ( m_camera )
    {
        std::vector< Unit* > units;

        unsigned int nextUnitIndex = 0;

        for ( unsigned int i = 0; i < Entities::instance()->getEntities()->size(); i++ )
        {
            Unit *unit = dynamic_cast< Unit* >( Entities::instance()->getEntities()->at( i ) );

            if ( unit )
            {
                if ( unit->isActive() )
                {
                    units.push_back( unit );

                    if ( unit->getId() == m_orbitedUnitId )
                    {
                        nextUnitIndex = i + 1;
                    }
                }
            }
        }

        if ( units.size() > 0 )
        {
            if ( nextUnitIndex > units.size() - 1 )
            {
                nextUnitIndex = 0;
            }

            m_orbitedUnitId = units[ nextUnitIndex ]->getId();

            m_camera->setTrackNode( units[ nextUnitIndex ]->getEntityNode() );
        }
        else
        {
            m_orbitedUnitId = 0;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Simulation::readMissions()
{
    std::string campaignFile = Base::getPath( "missions/campaign.xml" );

    XmlDoc doc( campaignFile );

    if ( doc.isOpen() )
    {
        XmlNode rootNode = doc.getRootNode();

        if ( rootNode.isValid() )
        {
            if ( 0 == String::icompare( rootNode.getName(), "campaign" ) )
            {
                XmlNode missionNode = rootNode.getFirstChildElement( "mission" );

                while ( missionNode.isValid() )
                {
                    std::string missionFile = missionNode.getAttribute( "file" );

                    if ( missionFile.length() > 0 )
                    {
                        m_missions.push_back( "missions/" + missionFile );
                    }

                    missionNode = missionNode.getNextSiblingElement( "mission" );
                }
            }
        }
    }
    else
    {
        osg::notify(osg::ALWAYS) << "ERROR! Cannot open campaign file: " << campaignFile << std::endl;
    }
}
