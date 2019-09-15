#ifndef SIM_GROUP_H
#define SIM_GROUP_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <sim/sim_Base.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{
class Entity;

/** Entities group class. */
class Group : public Base
{
public:

    typedef std::vector< Entity* > List;

    /** Constructor */
    Group( Group *parent = 0 );

    /** Destructor */
    virtual ~Group();

    /** Attaches child entity. */
    virtual void attachEntity( Entity *entity );

    /** Deletes all children entities. */
    virtual void deleteAllEntities();

    /** Deletes entity. */
    virtual void deleteEntity( Entity *entity );

    /** Detaches entity. */
    virtual void dettachEntity( Entity *entity );

    /** Returns all children entities list. */
    virtual List* getEntities();

    /**
     * Returns entity of a given ID if exists, otherwise returns 0.
     * @param id entity unique ID
     */
    virtual Entity* getEntityById( UInt32 id );

    /** Returns parent node. */
    inline Group* getParent() { return m_parent; }

    /** Returns OSG node.  */
    inline osg::Group* getNode() { return m_root.get(); }

    /** Loads entities. */
    virtual void load();

    /** Updates all children entities. */
    virtual void update( double timeStep );

protected:

    Group *m_parent;    ///< parent node
    List m_children;    ///< children nodes

    osg::ref_ptr<osg::Group> m_root;    ///< root group node
};

}

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_GROUP_H
