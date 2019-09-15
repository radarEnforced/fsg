#include <sim/sim_Creator.h>

#include <sim/sim_ListUnits.h>

#include <sim/entities/sim_Aircraft.h>
#include <sim/entities/sim_Balloon.h>
#include <sim/entities/sim_BomberDive.h>
#include <sim/entities/sim_BomberLevel.h>
#include <sim/entities/sim_BomberTorpedo.h>
#include <sim/entities/sim_Building.h>
#include <sim/entities/sim_Fighter.h>
#include <sim/entities/sim_Kamikaze.h>
#include <sim/entities/sim_Warship.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlDoc.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Aircraft* Creator::createAircraft( int index, int livery, Affiliation affiliation )
{
    if ( index >= 0 && index < (int)ListUnits::instance()->getCount() )
    {
        ListUnits::UnitData data = ListUnits::instance()->getData( index );

        if ( data.type == ListUnits::Aerial )
        {
            std::string type = data.fighter ? "fighter" : "aircraft";

            Unit *unit = createUnit( type, data.file, affiliation );

            Aircraft *aircraft = dynamic_cast< Aircraft* >( unit );

            if ( aircraft )
            {
                if ( livery >= 0 && livery < (int)data.liveries.size() )
                {
                    aircraft->setLivery( data.liveries[ livery ] );
                }
            }

            return aircraft;
        }
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

Unit* Creator::createUnit( const std::string &type, const std::string &file,
                           Affiliation affiliation )
{
    Unit *unit = 0;

    if ( 0 == String::icompare( type, Aircraft::m_tagName ) )
    {
        unit = new Aircraft( affiliation );
    }
    else if ( 0 == String::icompare( type, Balloon::m_tagName ) )
    {
        unit = new Balloon( affiliation );
    }
    else if ( 0 == String::icompare( type, BomberLevel::m_tagName ) )
    {
        unit = new BomberLevel( affiliation );
    }
    else if ( 0 == String::icompare( type, BomberDive::m_tagName ) )
    {
        unit = new BomberDive( affiliation );
    }
    else if ( 0 == String::icompare( type, BomberTorpedo::m_tagName ) )
    {
        unit = new BomberTorpedo( affiliation );
    }
    else if ( 0 == String::icompare( type, Building::m_tagName ) )
    {
        unit = new Building( affiliation );
    }
    else if ( 0 == String::icompare( type, Fighter::m_tagName ) )
    {
        unit = new Fighter( affiliation );
    }
    else if ( 0 == String::icompare( type, Kamikaze::m_tagName ) )
    {
        unit = new Kamikaze( affiliation );
    }
    else if ( 0 == String::icompare( type, Warship::m_tagName ) )
    {
        unit = new Warship( affiliation );
    }
    else
    {
        osg::notify(osg::ALWAYS) << "ERROR! Unknown unit type: \"" << type << "\"" << std::endl;
    }

    if ( unit )
    {
        std::string unitFile = Base::getPath( file );

        XmlDoc doc( unitFile );

        if ( doc.isOpen() )
        {
            if ( SIM_SUCCESS != unit->read( doc.getRootNode() ) )
            {
                delete unit;
                unit = 0;

                osg::notify(osg::ALWAYS) << "ERROR! Cannot read unit file: " << unitFile << std::endl;
            }
        }
        else
        {
            delete unit;
            unit = 0;

            osg::notify(osg::ALWAYS) << "ERROR! Cannot open unit file: " << unitFile << std::endl;
        }
    }

    return unit;
}
