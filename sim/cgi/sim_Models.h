#ifndef SIM_MODELS_H
#define SIM_MODELS_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/LOD>
#include <osg/NodeVisitor>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** 3D models container class. */
class Models : public Singleton< Models >
{
    friend class Singleton< Models >;

public:

    /**
     * OpenSceneGraph Level-of-Details visitor class.
     * It modifies every LOD node it visits so first child visibility range is set
     * to 1.0e8 meters. This is due to the fact that most LODs of terrain. models,
     * etc. are limited to achieve better application performance which is not
     * practical when used in mission editor. */
    class VisitorLOD : public osg::NodeVisitor
    {
    public:

        /** Constructor. */
        VisitorLOD();

        /** */
        void apply( osg::Node &searchNode );
    };

    typedef std::vector< osg::ref_ptr<osg::Node> > List;

    /**
     * Creates tracer bullet object.
     * @param linesWidth
     */
    static void createTracer( float linesWidth );

    /**
     * @param objectFile
     * @param straight
     * @return
     */
    static osg::Node* get( const std::string &objectFile, bool straight = false );

    /** Returns tracer bullet object. */
    inline static osg::LOD* getTracer() { return m_tracer.get(); }

    /** Reads object from file. */
    static osg::Node* readNodeFile( std::string objectFile );

    /** Resets object list. */
    static void reset();

private:

    /**
     * You should use static function getInstance() due to get refernce
     * to Models class instance.
     */
    Models();

    /** Using this constructor is forbidden. */
    Models( const Models & ) : Singleton< Models >() {}

public:

    /** Destructor. */
    virtual ~Models();

private:

    List m_objects;                         ///< objects list
    std::vector< std::string > m_fileNames; ///< file names

    static osg::ref_ptr<osg::LOD> m_tracer; ///< tracer bullet object
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_MODELS_H