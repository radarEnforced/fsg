#include <sim/cgi/sim_OTW.h>

#include <sim/cgi/sim_FogScene.h>
#include <sim/cgi/sim_Gates.h>
#include <sim/cgi/sim_SkyDome.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

OTW::OTW( float linesWidth, Module *parent ) :
    Module( new osg::Group(), parent ),

    m_linesWidth ( linesWidth )
{
    osg::ref_ptr<osg::StateSet> stateSet = m_root->getOrCreateStateSet();

    stateSet->setMode( GL_RESCALE_NORMAL , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHTING       , osg::StateAttribute::ON  );
    stateSet->setMode( GL_LIGHT0         , osg::StateAttribute::ON  );
    stateSet->setMode( GL_BLEND          , osg::StateAttribute::ON  );
    stateSet->setMode( GL_ALPHA_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DEPTH_TEST     , osg::StateAttribute::ON  );
    stateSet->setMode( GL_DITHER         , osg::StateAttribute::OFF );
}

////////////////////////////////////////////////////////////////////////////////

OTW::~OTW() {}

////////////////////////////////////////////////////////////////////////////////

void OTW::init()
{
    addChild( new FogScene( this ) );
    addChild( new Gates( m_linesWidth, this ) );
    addChild( new SkyDome( this ) );
}
