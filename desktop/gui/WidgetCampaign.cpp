#include "WidgetCampaign.h"
#include "ui_WidgetCampaign.h"

#include <QDomElement>
#include <QDir>
#include <QFile>

#include <sim/sim_Base.h>

////////////////////////////////////////////////////////////////////////////////

WidgetCampaign::WidgetCampaign( QWidget *parent ) :
    QWidget ( parent ),
    m_ui ( new Ui::WidgetCampaign ),

    m_missionIndex ( -1 )
{
    m_ui->setupUi( this );

    initMissions();

    m_ui->listWidgetMissions->setCurrentRow( 0 );
}

////////////////////////////////////////////////////////////////////////////////

WidgetCampaign::~WidgetCampaign()
{
    if ( m_ui ) delete m_ui;
    m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCampaign::reinit()
{
    m_missions.clear();

    int currentMissionRow = m_ui->listWidgetMissions->currentRow();

    m_ui->listWidgetMissions->clear();

    initMissions();

    m_ui->listWidgetMissions->setCurrentRow( currentMissionRow );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCampaign::initMissions()
{
    QDir dir( sim::Base::getPath( "missions" ).c_str() );
    QFile file( dir.filePath( "campaign.xml" ) );

    if ( file.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &file, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "campaign" )
        {
            QDomElement missionNode = rootNode.firstChildElement( "mission" );

            while ( !missionNode.isNull() )
            {
                QFileInfo fileInfo( dir.filePath( missionNode.attributeNode( "file" ).value() ) );

                m_missions.push_back( Mission( fileInfo ) );

                missionNode = missionNode.nextSiblingElement( "mission" );
            }
        }
    }

    int index = 1;

    for ( Missions::iterator it = m_missions.begin(); it != m_missions.end(); it++ )
    {
        QString itemText =
                //"#" + QString::number( index ) + ": " +
                (*it).getFileInfo().baseName() + ") "
                + (*it).getName();

        m_ui->listWidgetMissions->addItem( itemText );

        index++;
    }

    m_ui->listWidgetMissions->setCurrentRow( 0 );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCampaign::on_listWidgetMissions_currentRowChanged( int currentRow )
{
    if ( currentRow >= 0 && currentRow < (int)m_missions.size() )
    {
        m_missionIndex = currentRow;

        m_ui->lineMissionName->setText( m_missions.at( m_missionIndex ).getName() );
        m_ui->textMissionIntroduction->setPlainText( m_missions.at( m_missionIndex ).getIntroduction() );
        m_ui->textMissionSummaryFailure->setPlainText( m_missions.at( m_missionIndex ).getSummaryFailure() );
        m_ui->textMissionSummarySuccess->setPlainText( m_missions.at( m_missionIndex ).getSummarySuccess() );
    }
    else
    {
        m_missionIndex = -1;

        m_ui->lineMissionName->setText( "" );
        m_ui->textMissionIntroduction->setPlainText( "" );
        m_ui->textMissionSummaryFailure->setPlainText( "" );
        m_ui->textMissionSummarySuccess->setPlainText( "" );
    }

    emit( changed() );
}
