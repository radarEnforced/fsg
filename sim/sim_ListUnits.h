#ifndef SIM_LISTUNITS_H
#define SIM_LISTUNITS_H

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
class ListUnits : public sim::Singleton< ListUnits >
{
    friend class sim::Singleton< ListUnits >;

public:

    /** Unit types. */
    enum UnitType
    {
        Aerial = 0,             ///< aerial unit
        Marine,                 ///< marine vessel
        Ground                  ///< ground vehicle
    };

    /** Unit data. */
    struct UnitData
    {
        UnitType type;          ///< unit type

        bool fighter;           ///<

        std::string file;       ///< unit data file
        std::string model;      ///< unit model file
        std::string texture;    ///< unit texture file (aircrafts only)

        std::vector< std::string > liveries;    ///<

        float distance;         ///< [m] camera distance
        float heading;          ///< [deg] camera heading
        float offset_x;         ///< [m] camera offset along x-axis
    };

    typedef std::vector< UnitData > UnitsList;  ///<

private:

    ListUnits();

public:

    virtual ~ListUnits();

    inline UInt32 getCount() const { return m_data.size(); }

    UnitData getData( UInt32 index );

private:

    UnitsList m_data;       ///< list of all units

    void readUnits();
    void readUnits( UnitType type, const XmlNode &node );
    void readUnit( UnitType type, const XmlNode &node );

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_LISTUNITS_H