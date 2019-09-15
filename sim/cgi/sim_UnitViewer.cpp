#include <sim/cgi/sim_UnitViewer.h>

#include <osg/Fog>
#include <osg/LightSource>
#include <osg/Material>
#include <osg/PositionAttitudeTransform>

#include <sim/sim_ListUnits.h>

#include <sim/cgi/sim_Color.h>
#include <sim/cgi/sim_FindNode.h>
#include <sim/cgi/sim_Geometry.h>
#include <sim/cgi/sim_Models.h>
#include <sim/cgi/sim_Textures.h>

#ifdef SIM_DESKTOP
#   include <sim/entities/sim_UnitMarine.h>
#endif

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

UnitViewer::UnitViewer( int width, int height, UInt32 index, Module *parent ):
    Module( new osg::Group(), parent ),

    m_index ( index ),
    m_distCoef ( std::max( ( 4.0f * (float)height ) / ( 3.0f * (float)width ), 1.0f ) ),

    m_prop_angle ( 0.0 ),
    m_real_time  ( 0.0 )
{
    m_patUnit  = new osg::PositionAttitudeTransform();
    m_patModel = new osg::PositionAttitudeTransform();

    osg::ref_ptr<osg::StateSet> stateSet = m_root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );

    m_manipulatorOrbit = new ManipulatorOrbit();

    load();
}

////////////////////////////////////////////////////////////////////////////////

UnitViewer::~UnitViewer() {}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::load()
{
    if ( m_root->getNumChildren() > 0 )
    {
        m_root->removeChildren( 0, m_root->getNumChildren() );
    }

    m_root->addChild( m_patUnit.get() );
    m_root->addChild( m_patModel.get() );

    m_propeller1 = 0;
    m_propeller2 = 0;
    m_propeller3 = 0;
    m_propeller4 = 0;

    createSky();
    createSun();

    if ( m_index < ListUnits::instance()->getCount() )
    {
        if ( ListUnits::instance()->getData( m_index ).type == ListUnits::Marine )
        {
            createOcean();
        }
        else
        {
            createGround();
        }
    }
    else
    {
        createGround();
    }

    loadUnit();
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::resetViewer()
{
    double distance = 35.0;
    double elevation = osg::DegreesToRadians( 10.0 );
    double heading = -M_PI_2;

    if ( m_index < ListUnits::instance()->getCount() )
    {
        distance = ListUnits::instance()->getData( m_index ).distance;
        heading  = -M_PI_2 + osg::DegreesToRadians( ListUnits::instance()->getData( m_index ).heading );
    }

    m_manipulatorOrbit->setDistance( m_distCoef * distance );
    m_manipulatorOrbit->setElevation( elevation );
    m_manipulatorOrbit->setHeading( heading );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::update( double timeStep )
{
    /////////////////
    Module::update();
    /////////////////

    m_prop_angle = m_prop_angle + timeStep * 2.0 * ( 2.0 * M_PI ) * ( 0.5 + 0.5 * 0.25 );
    m_real_time += timeStep;

    if ( m_propeller1.valid() ) m_propeller1->setAttitude( Quat( -m_prop_angle, osg::X_AXIS ) );
    if ( m_propeller2.valid() ) m_propeller2->setAttitude( Quat(  m_prop_angle, osg::X_AXIS ) );
    if ( m_propeller3.valid() ) m_propeller3->setAttitude( Quat( -m_prop_angle, osg::X_AXIS ) );
    if ( m_propeller4.valid() ) m_propeller4->setAttitude( Quat(  m_prop_angle, osg::X_AXIS ) );

    if ( m_index < ListUnits::instance()->getCount() )
    {
        ListUnits::UnitData data = ListUnits::instance()->getData( m_index );

        if ( data.type == ListUnits::Aerial )
        {
            double phi = osg::DegreesToRadians( 2.0 ) * sin( 2.0 * M_PI * m_real_time / 10.0 );
            double tht = osg::DegreesToRadians( 1.0 ) * sin( 2.0 * M_PI * m_real_time / 12.0 );
            double psi = osg::DegreesToRadians( 1.0 ) * sin( 2.0 * M_PI * m_real_time / 12.0 );

            m_att.makeRotate( phi, osg::X_AXIS,
                              tht, osg::Y_AXIS,
                              psi, osg::Z_AXIS );

            m_pos += ( m_att * Vec3( -10.0, 0.0, 0.0 ) ) * timeStep;
            m_pos.x() = 0.0;
        }
    }

    m_patModel->setPosition( m_pos );
    m_patModel->setAttitude( m_att );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::createSky()
{
    osg::ref_ptr<osg::Geode> geodeSky = new osg::Geode();
    m_root->addChild( geodeSky.get() );

    createDome( geodeSky, Textures::get( getPath( "textures/sky_1.rgb" ) ), 2048.0f );

    geodeSky->getOrCreateStateSet()->setRenderBinDetails( SIM_DEPTH_SORTED_BIN_SKY, "DepthSortedBin" );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::createSun()
{
    osg::ref_ptr<osg::PositionAttitudeTransform> patSun = new osg::PositionAttitudeTransform();
    m_root->addChild( patSun.get() );

    patSun->setAttitude( osg::Quat( -M_PI_2 - M_PI_4, osg::Z_AXIS, M_PI_4, osg::Y_AXIS, 0.0, osg::X_AXIS ) );

    osg::ref_ptr<osg::LightSource> lightSourceSun = new osg::LightSource();
    patSun->addChild( lightSourceSun.get() );

    osg::ref_ptr<osg::Light> lightSun = new osg::Light();

    lightSun->setLightNum( SIM_LIGHT_SUN_NUM );

    lightSun->setPosition( osg::Vec4d( 2048.0f, 0.0f, 0.0f, 0.0f ) );

    lightSun->setAmbient( osg::Vec4( Color::sun, 1.0f ) );
    lightSun->setDiffuse( osg::Vec4( Color::sun, 1.0f ) );
    lightSun->setSpecular( osg::Vec4( Color::sun, 1.0f ) );

    lightSun->setConstantAttenuation( 1.0 );

    lightSourceSun->setLight( lightSun.get() );

    lightSourceSun->setLocalStateSetModes( osg::StateAttribute::ON );
    lightSourceSun->setStateSetModes( *m_root->getOrCreateStateSet(), osg::StateAttribute::ON );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::createDome( osg::Geode *dome, osg::Texture2D *texture,
                      float radius, bool blend )
{
    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    dome->addDrawable( geom.get() );

    Geometry::createDome( geom, radius, true, Geometry::Azimuthal, 18, 36 );

    // state set
    osg::ref_ptr<osg::StateSet> stateSet = dome->getOrCreateStateSet();
    stateSet->setMode( GL_LIGHTING, osg::StateAttribute::OFF );

    // texture
    if ( texture != 0 )
    {
        if ( blend )
        {
            stateSet->setMode( GL_BLEND, osg::StateAttribute::ON );
            stateSet->setRenderingHint( osg::StateSet::TRANSPARENT_BIN );
        }

        stateSet->setTextureAttributeAndModes( 0, texture, osg::StateAttribute::ON );
    }

    // material
    osg::ref_ptr<osg::Material> material = new osg::Material();

    material->setColorMode( osg::Material::AMBIENT_AND_DIFFUSE );
    material->setAmbient( osg::Material::FRONT, osg::Vec4( Color::white, 1.0f ) );
    material->setDiffuse( osg::Material::FRONT, osg::Vec4( Color::white, 1.0f ) );

    stateSet->setAttribute( material.get() );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::createGround()
{
    createPlane( "textures/grass.rgb" );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::createOcean()
{
    createPlane( "textures/water.rgb" );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::createPlane( const std::string &textureFile )
{
    osg::ref_ptr<osg::Geode> geode = new osg::Geode();
    m_root->addChild( geode.get() );

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry();
    geode->addDrawable( geom.get() );

    osg::ref_ptr<osg::StateSet> stateSet = geode->getOrCreateStateSet();

    Geometry::createPlane( geom.get(), 4096.0, 16, -2048.0, -2048.0, true, 4 );

    osg::ref_ptr<osg::Texture2D> texture = Textures::get( getPath( textureFile ), 1.0f, osg::Texture::REPEAT );

    if ( texture != 0 )
    {
        stateSet->setTextureAttributeAndModes( 0, texture, osg::StateAttribute::ON );
    }

    osg::ref_ptr<osg::Fog> fog = new osg::Fog();
    fog->setMode( osg::Fog::LINEAR );
    fog->setDensity( 0.5f );
    fog->setColor( osg::Vec4( Color::fog_light, 0.0f ) );
    fog->setStart( 0.0f );
    fog->setEnd( 1920.0f );

    stateSet->setAttributeAndModes( fog.get(), osg::StateAttribute::ON );
    stateSet->setMode( GL_FOG, osg::StateAttribute::ON );
}

////////////////////////////////////////////////////////////////////////////////

void UnitViewer::loadUnit()
{
    if ( m_patModel->getNumChildren() > 0 )
    {
        m_patModel->removeChildren( 0, m_patModel->getNumChildren() );
    }

    if ( m_index < ListUnits::instance()->getCount() )
    {
        ListUnits::UnitData data = ListUnits::instance()->getData( m_index );

        std::string aircraftFile = getPath( data.model );

        osg::ref_ptr<osg::Node> model = Models::readNodeFile( aircraftFile );

        if ( model.valid() )
        {
            m_patModel->addChild( model.get() );

            m_manipulatorOrbit->setTrackNode( m_patUnit.get() );

            Vec3 pos( data.offset_x, 0.0, 0.0 );

            if ( data.type == ListUnits::Aerial )
            {
                pos.z() = 100.0;

                m_pos = Vec3( 0.0, 0.0, pos.z() );

                m_patModel->setPosition( m_pos );

                if ( data.texture.length() > 0 )
                {
                    osg::ref_ptr<osg::Texture2D> texture = Textures::get( getPath( data.texture ), 8.0f );

                    if ( texture.valid() )
                    {
                        model->getOrCreateStateSet()->setTextureAttributeAndModes( 0, texture.get(), osg::StateAttribute::ON | osg::StateAttribute::OVERRIDE );
                    }
                }
            }
#           ifdef SIM_WATER_REFLECTIONS
            else if ( data.type == ListUnits::Marine )
            {
                UnitMarine::createReflection( model.get(), m_root.get() );
            }
#           endif

            m_patUnit->setPosition( pos );

            m_propeller1 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "Propeller1" ) );
            m_propeller2 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "Propeller2" ) );
            m_propeller3 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "Propeller3" ) );
            m_propeller4 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "Propeller4" ) );

            if ( !m_propeller1.valid() || !m_propeller2.valid() )
            {
                m_propeller1 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "PropellerL" ) );
                m_propeller2 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "PropellerR" ) );
            }

            if ( !m_propeller1.valid() )
            {
                m_propeller1 = dynamic_cast<osg::PositionAttitudeTransform*>( FindNode::findFirst( model, "Propeller" ) );
            }
        }
        else
        {
            osg::notify(osg::ALWAYS) << "ERROR! Cannot open aircraft file: " << aircraftFile << std::endl;
        }
    }
    else
    {
        osg::notify(osg::ALWAYS) << "ERROR! Wrong unit index: " << m_index << std::endl;
    }
}
