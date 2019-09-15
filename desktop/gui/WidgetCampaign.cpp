/****************************************************************************//*
 * Copyright (C) 2019 Marek M. Cel
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom
 * the Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
 * OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 ******************************************************************************/

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
