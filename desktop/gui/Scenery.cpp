#include "Scenery.h"

#include <QDomElement>
#include <QDir>
#include <QFile>

#include <sim/sim_Base.h>

////////////////////////////////////////////////////////////////////////////////

Scenery::Scenery()
{
    readScenery();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int Scenery::getCount()
{
    return m_sceneryList.size();
}

////////////////////////////////////////////////////////////////////////////////

QString Scenery::getSceneryName( unsigned int index )
{
    return m_sceneryList[ index ];
}

////////////////////////////////////////////////////////////////////////////////

void Scenery::readScenery()
{
    QDir dir( sim::Base::getPath( "" ).c_str() );
    QFile file( dir.filePath( "scenery.xml" ) );

    if ( file.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &file, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "scenery_list" )
        {
            QDomElement sceneryNode = rootNode.firstChildElement( "scenery" );

            while ( !sceneryNode.isNull() )
            {
                m_sceneryList.push_back( sceneryNode.attributeNode( "name" ).value() );

                sceneryNode = sceneryNode.nextSiblingElement( "scenery" );
            }
        }
    }
}
