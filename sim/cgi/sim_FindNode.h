#ifndef SIM_FINDNODE_H
#define SIM_FINDNODE_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <osg/NodeVisitor>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Finding node visitor class. */
class FindNode : public osg::NodeVisitor
{
public:

    typedef std::vector< osg::ref_ptr<osg::Node> > Nodes;

    /** */
    static osg::Node* findFirst( osg::Node* node, const std::string &name );

    /** */
    static Nodes findNodes( osg::Node* node, const std::string &name );

    /** Constructor. */
    FindNode();

    /** Constructor. */
    FindNode( const std::string &name, bool findAll = false );

    /** */
    virtual void apply( osg::Node &searchNode );

    /** Returns first found node. */
    osg::ref_ptr<osg::Node> getFirst();

    /** Returns list of found nodes. */
    Nodes getNodes();

private:

    bool m_findAll;     ///< specifies if search should be continued after finding first matching node
    std::string m_name; ///< name of the nodes to be looking for
    Nodes m_nodes;      ///< found nodes list
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FINDNODE_H
