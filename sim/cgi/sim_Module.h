#ifndef SIM_MODULE_H
#define SIM_MODULE_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <sim/sim_Base.h>
#include <sim/sim_Data.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Simulation CGI module base class.
 */
class Module : public Base
{
public:

    typedef std::vector< Module* > List;

    /**
     * Constructor.
     * <p>root parameter is intended to make possible using osg::Group derived
     * object type instead of pure osg::Group type (e.i. osg::LOD, osg::Switch,
     * osg::PositionAttitudeTransform, etc.) as root node without need
     * to create another scene graph level.</p>
     * @param root OSG module root node object
     * @param parent parent module
     */
    Module( osg::Group *root, Module *parent = 0 );

    /** Destructor. */
    virtual ~Module();

    /** Adds child to the module. */
    virtual void addChild( Module *child );

    /** Initializes module and all its children. */
    virtual void load();

    /** Updates module and all its children. */
    virtual void update();

    /** Returns module OSG node.  */
    inline osg::Group* getNode() { return m_root.get(); }

protected:

    osg::ref_ptr<osg::Group> m_root;    ///< OSG module root node

    List m_children;                    ///< children nodes

    Module *m_parent;                   ///< parent node

    /** Removes all children. */
    virtual void removeAllChildren();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_MODULE_H
