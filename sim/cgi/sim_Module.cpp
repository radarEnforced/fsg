#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Module::Module( osg::Group *root, Module *parent ) :
    m_root ( root ),
    m_parent ( parent )
{
    m_children.clear();
}

////////////////////////////////////////////////////////////////////////////////

Module::~Module()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Module::addChild( Module *child )
{
    if ( child )
    {
        m_children.push_back( child );
        m_root->addChild( child->getNode() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Module::load()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        (*it)->load();

        ++it;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Module::update()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        (*it)->update();

        ++it;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Module::removeAllChildren()
{
    if ( m_root->getNumChildren() > 0 )
    {
        m_root->removeChildren( 0, m_root->getNumChildren() );
    }

    for ( unsigned int i = 0; i < m_children.size(); i++ )
    {
        if ( m_children[ i ] ) delete m_children[ i ];
        m_children[ i ] = 0;
    }

    m_children.clear();
}
