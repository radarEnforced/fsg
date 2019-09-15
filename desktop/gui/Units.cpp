#include "Units.h"

#include <QDomElement>
#include <QDir>
#include <QFile>

#include <sim/sim_Base.h>

////////////////////////////////////////////////////////////////////////////////

Units::Units()
{
    readUnits();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int Units::getCountUnitData()
{
    return m_unitsData.size();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int Units::getCountAllyData()
{
    return m_allyData.size();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int Units::getCountOpponent()
{
    return m_opponents.size();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int Units::getCountPlayable()
{
    return m_playables.size();
}

////////////////////////////////////////////////////////////////////////////////

Units::UnitData Units::getUnitData( unsigned int index )
{
    return m_unitsData[ index ];
}

////////////////////////////////////////////////////////////////////////////////

Units::UnitData Units::getAllyData( unsigned int index )
{
    return m_allyData[ index ];
}

////////////////////////////////////////////////////////////////////////////////

Units::UnitData Units::getOpponent( unsigned int index )
{
    return m_opponents[ index ];
}

////////////////////////////////////////////////////////////////////////////////

Units::UnitData Units::getPlayable( unsigned int index )
{
    return m_playables[ index ];
}

////////////////////////////////////////////////////////////////////////////////

void Units::readUnits()
{
    unsigned int index = 0;

    QDir dir( sim::Base::getPath( "" ).c_str() );
    QFile file( dir.filePath( "units.xml" ) );

    if ( file.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &file, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "units" )
        {
            QDomElement aerialNode = rootNode.firstChildElement( "aerial" );

            if ( !aerialNode.isNull() )
            {
                QDomElement unitNode = aerialNode.firstChildElement( "unit" );

                while ( !unitNode.isNull() )
                {
                    UnitData data;

                    QDomElement nameNode = unitNode.firstChildElement( "name" );
                    QDomElement liveriesNode = unitNode.firstChildElement( "liveries" );

                    data.index = index;
                    data.fighter = unitNode.attributeNode( "fighter" ).value().toInt() != 0;
                    data.name = nameNode.text();

                    if ( !liveriesNode.isNull() )
                    {
                        QDomElement liveryNode = liveriesNode.firstChildElement( "livery" );

                        while ( !liveryNode.isNull() )
                        {
                            data.liveries.push_back( liveryNode.attributeNode( "name" ).value() );

                            liveryNode = liveryNode.nextSiblingElement( "livery" );
                        }
                    }

                    m_unitsData.push_back( data );

                    if ( unitNode.attributeNode( "opponent" ).value().toInt() != 0 )
                    {
                        m_opponents.push_back( data );
                    }
                    else
                    {
                        m_allyData.push_back( data );
                    }

                    if ( unitNode.attributeNode( "playable" ).value().toInt() != 0 )
                    {
                        m_playables.push_back( data );
                    }

                    unitNode = unitNode.nextSiblingElement( "unit" );

                    index++;
                }
            }
        }
    }
}
