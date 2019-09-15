#ifndef SIM_LISTSCENERY_H
#define SIM_LISTSCENERY_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <sim/sim_Types.h>

#include <sim/utils/sim_Singleton.h>
#include <sim/utils/sim_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** */
class ListScenery : public sim::Singleton< ListScenery >
{
    friend class sim::Singleton< ListScenery >;

public:

    typedef std::vector< std::string > ObjectFiles;

    /** Unit data. */
    struct SceneryData
    {
        std::string elevationFile;  ///<
        std::string terrainFile;    ///<
        std::string genericFile;    ///<
        ObjectFiles objectFiles;    ///<

        Vec3 initialPosition;       ///< [m]
    };

    typedef std::vector< SceneryData > SceneryList; ///<

private:

    ListScenery();

public:

    virtual ~ListScenery();

    inline UInt32 getCount() const { return m_data.size(); }

    SceneryData getData( UInt32 index );

private:

    SceneryList m_data;     ///< list of scenery data

    void readScenery();
    void readScenery( const XmlNode &node );

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_LISTSCENERY_H
