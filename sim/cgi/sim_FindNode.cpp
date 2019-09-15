#include <sim/cgi/sim_FindNode.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

osg::Node* FindNode::findFirst( osg::Node* node, const std::string &name )
{
    if ( node )
    {
        FindNode findNode( name );
        node->accept( findNode );
        return dynamic_cast<osg::Node*>( findNode.getFirst().get() );
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

FindNode::Nodes FindNode::findNodes( osg::Node* node, const std::string &name )
{
    if ( node )
    {
        FindNode findNode( name, true );
        node->accept( findNode );
        return findNode.getNodes();
    }

    return Nodes();
}

////////////////////////////////////////////////////////////////////////////////

FindNode::FindNode() :
    osg::NodeVisitor( TRAVERSE_ALL_CHILDREN ),

    m_findAll ( false )
{
    m_name = "";
    m_nodes.clear();
}

////////////////////////////////////////////////////////////////////////////////

FindNode::FindNode( const std::string &name, bool findAll ) :
    osg::NodeVisitor( TRAVERSE_ALL_CHILDREN ),

    m_findAll ( findAll )
{
    m_name = name;
    m_nodes.clear();
}

////////////////////////////////////////////////////////////////////////////////

void FindNode::apply( osg::Node &searchNode )
{
    if ( m_name == searchNode.getName() || m_name.length() == 0 )
    {
        osg::ref_ptr<osg::Node> tempNode = &searchNode;

        m_nodes.push_back( tempNode.get() );

        if ( m_findAll ) traverse( searchNode );
    }
    else
    {
        traverse( searchNode );
    }
}

////////////////////////////////////////////////////////////////////////////////

osg::ref_ptr<osg::Node> FindNode::getFirst()
{
    if ( m_nodes.empty() )
    {
        return 0;
    }
    else
    {
        return m_nodes[ 0 ];
    }
}

////////////////////////////////////////////////////////////////////////////////

FindNode::Nodes FindNode::getNodes()
{
    return m_nodes;
}
