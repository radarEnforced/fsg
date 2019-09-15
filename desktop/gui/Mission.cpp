#include <gui/Mission.h>

#include <QFile>

#include <sim/sim_Languages.h>

////////////////////////////////////////////////////////////////////////////////

Mission::Mission() {}

////////////////////////////////////////////////////////////////////////////////

Mission::Mission( const Mission &mission ) :
    m_fileInfo ( mission.m_fileInfo ),
    m_name ( mission.m_name ),
    m_introduction ( mission.m_introduction ),
    m_summaryFailure ( mission.m_summaryFailure ),
    m_summarySuccess ( mission.m_summarySuccess )
{}

////////////////////////////////////////////////////////////////////////////////

Mission::Mission( const QFileInfo &fileInfo ) :
    m_fileInfo( fileInfo )
{
    QFile missionFile( m_fileInfo.filePath() );

    if ( missionFile.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &missionFile, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "mission" )
        {
            QDomElement dataNode = rootNode.firstChildElement( "data" );

            if ( !dataNode.isNull() )
            {
                QDomElement nameNode = dataNode.firstChildElement( "name" );
                QDomElement introductionNode = dataNode.firstChildElement( "introduction" );
                QDomElement summaryFailureNode = dataNode.firstChildElement( "summary_failure" );
                QDomElement summarySuccessNode = dataNode.firstChildElement( "summary_success" );

                readText( nameNode, m_name );
                readText( introductionNode, m_introduction );
                readText( summaryFailureNode, m_summaryFailure );
                readText( summarySuccessNode, m_summarySuccess );
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

QString Mission::getName() const
{
    Text::const_iterator it = m_name.find( sim::Languages::instance()->getCurrent() );

    if ( it != m_name.end() )
    {
        return (*it);
    }

    return QString();
}

////////////////////////////////////////////////////////////////////////////////

QString Mission::getIntroduction() const
{
    Text::const_iterator it = m_introduction.find( sim::Languages::instance()->getCurrent() );

    if ( it != m_introduction.end() )
    {
        return (*it);
    }

    return QString();
}

////////////////////////////////////////////////////////////////////////////////

QString Mission::getSummaryFailure() const
{
    Text::const_iterator it = m_summaryFailure.find( sim::Languages::instance()->getCurrent() );

    if ( it != m_summaryFailure.end() )
    {
        return (*it);
    }

    return QString();
}

////////////////////////////////////////////////////////////////////////////////

QString Mission::getSummarySuccess() const
{
    Text::const_iterator it = m_summarySuccess.find( sim::Languages::instance()->getCurrent() );

    if ( it != m_summarySuccess.end() )
    {
        return (*it);
    }

    return QString();
}

////////////////////////////////////////////////////////////////////////////////

void Mission::readText( const QDomElement &node, Text &text )
{
    if ( !node.isNull() )
    {
        QDomElement textNode = node.firstChildElement( "text" );

        while ( !textNode.isNull() )
        {
            if ( textNode.hasAttribute( "lang" ) )
            {
                QString value = textNode.text();
                int index = sim::Languages::instance()->getIndexByCode( textNode.attribute( "lang", "en" ).toStdString() );

                text.insert( index, value );
            }

            textNode = textNode.nextSiblingElement( "text" );
        }
    }
}
