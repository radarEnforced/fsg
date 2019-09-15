#include <sim/sim_ListUnits.h>

#include <sim/sim_Base.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlDoc.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ListUnits::ListUnits()
{
    readUnits();
}

////////////////////////////////////////////////////////////////////////////////

ListUnits::~ListUnits() {}

////////////////////////////////////////////////////////////////////////////////

ListUnits::UnitData ListUnits::getData( UInt32 index )
{
    return m_data[ index ];
}

////////////////////////////////////////////////////////////////////////////////

void ListUnits::readUnits()
{
    XmlDoc doc( Base::getPath( "units.xml" ) );

    if ( doc.isOpen() )
    {
        XmlNode rootNode = doc.getRootNode();

        if ( rootNode.isValid() )
        {
            if ( 0 == String::icompare( rootNode.getName(), "units" ) )
            {
                XmlNode aerialNode = rootNode.getFirstChildElement( "aerial" );
                XmlNode marineNode = rootNode.getFirstChildElement( "marine" );
                XmlNode groundNode = rootNode.getFirstChildElement( "ground" );

                if ( aerialNode.isValid() ) readUnits( Aerial, aerialNode );
                if ( marineNode.isValid() ) readUnits( Marine, marineNode );
                if ( groundNode.isValid() ) readUnits( Ground, groundNode );
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void ListUnits::readUnits( UnitType type, const XmlNode &node )
{
    XmlNode unitNode = node.getFirstChildElement( "unit" );

    while ( unitNode.isValid() )
    {
        readUnit( type, unitNode );
        unitNode = unitNode.getNextSiblingElement( "unit" );
    }
}

////////////////////////////////////////////////////////////////////////////////

void ListUnits::readUnit( UnitType type, const XmlNode &node )
{
    std::string sTemp;
    float fTemp;

    UnitData data;
    data.type = type;

    data.fighter = String::toBool( node.getAttribute( "fighter" ) );

    XmlNode nodeLiveries = node.getFirstChildElement( "liveries" );

    if ( nodeLiveries.isValid() )
    {
        XmlNode nodeLivery = nodeLiveries.getFirstChildElement( "livery" );

        while ( nodeLivery.isValid() )
        {
            if ( SIM_SUCCESS == XmlUtils::read( nodeLivery, sTemp ) )
            {
                data.liveries.push_back( sTemp );
            }

            nodeLivery = nodeLivery.getNextSiblingElement( "livery" );
        }
    }

    XmlNode nodeFile = node.getFirstChildElement( "file" );
    XmlNode nodeView = node.getFirstChildElement( "view" );

    if ( SIM_SUCCESS == XmlUtils::read( nodeFile, sTemp ) )
    {
        data.file = sTemp;

        XmlDoc docUnit( Base::getPath( sTemp ) );

        if ( docUnit.isOpen() )
        {
            XmlNode rootNode = docUnit.getRootNode();

            if ( rootNode.isValid() )
            {
                if ( 0 == String::icompare( rootNode.getName(), "unit" ) )
                {
                    XmlNode nodeModel = rootNode.getFirstChildElement( "model" );

                    if ( SIM_SUCCESS == XmlUtils::read( nodeModel, sTemp ) )
                    {
                        data.model = sTemp;
                    }
                }
            }
        }
    }

    if ( nodeView.isValid() )
    {
        XmlNode nodeTexture  = nodeView.getFirstChildElement( "texture"  );
        XmlNode nodeDistance = nodeView.getFirstChildElement( "distance" );
        XmlNode nodeHeading  = nodeView.getFirstChildElement( "heading"  );
        XmlNode nodeOffsetX  = nodeView.getFirstChildElement( "offset_x" );

        if ( SIM_SUCCESS == XmlUtils::read( nodeTexture, sTemp ) )
        {
            data.texture = sTemp;
        }

        if ( SIM_SUCCESS == XmlUtils::read( nodeDistance, fTemp ) )
        {
            data.distance = fTemp;

            if ( data.distance <= 0.1f )
            {
                data.distance = 35.0f;
            }
        }

        if ( SIM_SUCCESS == XmlUtils::read( nodeHeading, fTemp ) )
        {
            data.heading = fTemp;
        }

        if ( SIM_SUCCESS == XmlUtils::read( nodeOffsetX, fTemp ) )
        {
            data.offset_x = fTemp;
        }
    }

    m_data.push_back( data );
}
