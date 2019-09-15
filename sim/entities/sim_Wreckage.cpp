#include <sim/entities/sim_Wreckage.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Wreckage::Wreckage( osg::Node *model, float life_span ) :
    Entity( 0, Active, life_span )
{
    osg::ref_ptr<osg::Node> modelRefPtr = model;

    if ( modelRefPtr.valid() )
    {
        m_switch->addChild( modelRefPtr.get() );
    }
}

////////////////////////////////////////////////////////////////////////////////

Wreckage::~Wreckage() {}
