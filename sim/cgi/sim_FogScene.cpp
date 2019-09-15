#include <sim/cgi/sim_FogScene.h>

#include <osg/Fog>

#include <sim/cgi/sim_Color.h>
#include <sim/cgi/sim_Scenery.h>
#include <sim/cgi/sim_SkyDome.h>

#include <sim/entities/sim_Entities.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

int FogScene::m_visibility = 7200;

////////////////////////////////////////////////////////////////////////////////

FogScene::FogScene( Module *parent ) :
    Module( new osg::Group(), parent )
{
    if ( m_visibility > 0.9f * SIM_SKYDOME_RAD )
    {
        m_visibility = 0.9f * SIM_SKYDOME_RAD;
    }
    else if ( m_visibility < 0.6f * SIM_SKYDOME_RAD )
    {
        m_visibility = 0.6f * SIM_SKYDOME_RAD;
    }

    m_fog = new osg::Fog();

    osg::ref_ptr<osg::StateSet> stateSet = m_root->getOrCreateStateSet();

    osg::Vec4 color( Color::fog_light, 0.0f );

    if ( m_visibility < 7200 )
    {
        color = osg::Vec4( Color::fog_heavy, 0.0f );
    }

    m_fog->setMode( osg::Fog::LINEAR );
    m_fog->setDensity( 0.5f );
    m_fog->setColor( color );
    m_fog->setStart( 0.0f );
    m_fog->setEnd( m_visibility );

    stateSet->setAttributeAndModes( m_fog.get(), osg::StateAttribute::ON );
    stateSet->setMode( GL_FOG, osg::StateAttribute::ON );

    addChild( new Scenery( this ) );

    m_root->addChild( Entities::instance()->getNode() );
}

////////////////////////////////////////////////////////////////////////////////

FogScene::~FogScene() {}

////////////////////////////////////////////////////////////////////////////////

void FogScene::update()
{
    /////////////////
    Module::update();
    /////////////////

#   ifdef SIM_DESKTOP
    osg::ref_ptr<osg::StateSet> stateSet = m_root->getOrCreateStateSet();

    if ( Data::get()->camera.type == ViewWorld )
    {
        stateSet->setMode( GL_FOG, osg::StateAttribute::OFF );
    }
    else
    {
        stateSet->setMode( GL_FOG, osg::StateAttribute::ON );
    }
#   endif
}
