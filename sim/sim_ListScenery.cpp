#include <sim/sim_ListScenery.h>

#include <sim/sim_Base.h>

#include <sim/utils/sim_Convert.h>
#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlDoc.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ListScenery::ListScenery()
{
    readScenery();
}

////////////////////////////////////////////////////////////////////////////////

ListScenery::~ListScenery() {}

////////////////////////////////////////////////////////////////////////////////

ListScenery::SceneryData ListScenery::getData( UInt32 index )
{
    return m_data[ index ];
}

////////////////////////////////////////////////////////////////////////////////

void ListScenery::readScenery()
{
    XmlDoc doc( Base::getPath( "scenery.xml" ) );

    if ( doc.isOpen() )
    {
        XmlNode rootNode = doc.getRootNode();

        if ( rootNode.isValid() )
        {
            if ( 0 == String::icompare( rootNode.getName(), "scenery_list" ) )
            {
                XmlNode sceneryNode = rootNode.getFirstChildElement( "scenery" );

                while ( sceneryNode.isValid() )
                {
                    readScenery( sceneryNode );
                    sceneryNode = sceneryNode.getNextSiblingElement( "scenery" );
                }
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void ListScenery::readScenery( const XmlNode &node )
{
    XmlNode terrainNode = node.getFirstChildElement( "terrain" );
    XmlNode genericNode = node.getFirstChildElement( "generic" );

    if ( terrainNode.isValid() && genericNode.isValid() )
    {
        std::string terrainFile;
        std::string genericFile;

        if ( SIM_SUCCESS == XmlUtils::read( terrainNode, terrainFile )
          && SIM_SUCCESS == XmlUtils::read( genericNode, genericFile ) )
        {
            SceneryData data;

            data.terrainFile = terrainFile;
            data.genericFile = genericFile;

            // elevation
            XmlNode elevationNode = node.getFirstChildElement( "elevation" );

            if ( elevationNode.isValid() )
            {
                std::string elevationFile;

                if ( SIM_SUCCESS == XmlUtils::read( elevationNode, elevationFile ) )
                {
                    data.elevationFile = elevationFile;
                }
            }

            // objects
            XmlNode objectsNode = node.getFirstChildElement( "objects" );

            if ( objectsNode.isValid() )
            {
                XmlNode objectNode = objectsNode.getFirstChildElement( "object" );

                while ( objectNode.isValid() )
                {
                    std::string objectFile;

                    if ( SIM_SUCCESS == XmlUtils::read( objectNode, objectFile ) )
                    {
                        data.objectFiles.push_back( objectFile );
                    }

                    objectNode = objectNode.getNextSiblingElement( "object" );
                }
            }

            XmlNode initPositionNode = node.getFirstChildElement( "initial_position" );

            XmlUtils::read( initPositionNode, data.initialPosition );

            m_data.push_back( data );
        }
    }
}
