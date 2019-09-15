#include "DialogQuickAction.h"
#include "ui_DialogQuickAction.h"

////////////////////////////////////////////////////////////////////////////////

DialogQuickAction::DialogQuickAction( QWidget *parent ) :
    QDialog( parent ),
    m_ui ( new Ui::DialogQuickAction ),

    m_scenery ( 0 ),
    m_units ( 0 ),

    m_index_scenery ( 0 ),
    m_index_ownship ( 0 ),
    m_index_wingman ( -1 ),
    m_index_ally_1 ( -1 ),
    m_index_ally_2 ( -1 ),
    m_index_opponent_1 ( 0 ),
    m_index_opponent_2 ( -1 ),
    m_index_opponent_3 ( -1 ),
    m_index_opponent_4 ( -1 ),

    m_index_livery_ownship ( 0 ),
    m_index_livery_wingman ( 0 ),
    m_index_livery_ally_1 ( 0 ),
    m_index_livery_ally_2 ( 0 ),
    m_index_livery_opponent_1 ( 0 ),
    m_index_livery_opponent_2 ( 0 ),
    m_index_livery_opponent_3 ( 0 ),
    m_index_livery_opponent_4 ( 0 )
{
    m_ui->setupUi( this );

    m_scenery = new Scenery();
    m_units = new Units();

    init();
}

////////////////////////////////////////////////////////////////////////////////

DialogQuickAction::~DialogQuickAction()
{
    if ( m_scenery ) delete m_scenery;
    m_scenery = 0;

    if ( m_units ) delete m_units;
    m_units = 0;

    if ( m_ui ) delete m_ui;
    m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::init()
{
    for ( unsigned int i = 0; i < m_scenery->getCount(); i++ )
    {
        m_ui->comboBoxScenery->addItem( m_scenery->getSceneryName( i ) );
    }

    m_ui->comboBoxScenery->setCurrentIndex( 0 );

    for ( unsigned int i = 0; i < m_units->getCountPlayable(); i++ )
    {
        m_ui->comboBoxTypeOwnship->addItem( m_units->getPlayable( i ).name );
    }

    m_ui->comboBoxTypeOwnship->setCurrentIndex( 0 );

    for ( unsigned int i = 0; i < m_units->getCountAllyData(); i++ )
    {
        m_ui->comboBoxTypeWingman->addItem( m_units->getAllyData( i ).name );
    }

    m_ui->comboBoxTypeWingman->setCurrentIndex( -1 );

    for ( unsigned int i = 0; i < m_units->getCountAllyData(); i++ )
    {
        m_ui->comboBoxTypeAlly_1->addItem( m_units->getAllyData( i ).name );
    }

    m_ui->comboBoxTypeAlly_1->setCurrentIndex( -1 );

    for ( unsigned int i = 0; i < m_units->getCountAllyData(); i++ )
    {
        m_ui->comboBoxTypeAlly_2->addItem( m_units->getAllyData( i ).name );
    }

    m_ui->comboBoxTypeAlly_2->setCurrentIndex( -1 );

    for ( unsigned int i = 0; i < m_units->getCountOpponent(); i++ )
    {
        m_ui->comboBoxTypeOpponent_1->addItem( m_units->getOpponent( i ).name );
    }

    m_ui->comboBoxTypeOpponent_1->setCurrentIndex( -1 );

    for ( unsigned int i = 0; i < m_units->getCountOpponent(); i++ )
    {
        m_ui->comboBoxTypeOpponent_2->addItem( m_units->getOpponent( i ).name );
    }

    m_ui->comboBoxTypeOpponent_2->setCurrentIndex( -1 );

    for ( unsigned int i = 0; i < m_units->getCountOpponent(); i++ )
    {
        m_ui->comboBoxTypeOpponent_3->addItem( m_units->getOpponent( i ).name );
    }

    m_ui->comboBoxTypeOpponent_3->setCurrentIndex( -1 );

    for ( unsigned int i = 0; i < m_units->getCountOpponent(); i++ )
    {
        m_ui->comboBoxTypeOpponent_4->addItem( m_units->getOpponent( i ).name );
    }

    m_ui->comboBoxTypeOpponent_4->setCurrentIndex( -1 );
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxScenery_currentIndexChanged( int index )
{
    m_index_scenery = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeOwnship_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryOwnship->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getPlayable( index );

        m_index_ownship = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryOwnship->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryOwnship->setCurrentIndex( 0 );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryOwnship_currentIndexChanged( int index )
{
    m_index_livery_ownship = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeWingman_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryWingman->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getAllyData( index );

        m_index_wingman = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryWingman->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryWingman->setCurrentIndex( 0 );
    }
    else
    {
        m_index_wingman = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryWingman_currentIndexChanged( int index )
{
    m_index_livery_wingman = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeAlly_1_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryAlly_1->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getAllyData( index );

        m_index_ally_1 = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryAlly_1->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryAlly_1->setCurrentIndex( 0 );
    }
    else
    {
        m_index_ally_1 = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryAlly_1_currentIndexChanged( int index )
{
    m_index_livery_ally_1 = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeAlly_2_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryAlly_2->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getAllyData( index );

        m_index_ally_2 = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryAlly_2->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryAlly_2->setCurrentIndex( 0 );
    }
    else
    {
        m_index_ally_2 = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryAlly_2_currentIndexChanged( int index )
{
    m_index_livery_ally_2 = index;
}


////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeOpponent_1_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryOpponent_1->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getOpponent( index );

        m_index_opponent_1 = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryOpponent_1->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryOpponent_1->setCurrentIndex( 0 );
    }
    else
    {
        m_index_opponent_1 = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryOpponent_1_currentIndexChanged( int index )
{
    m_index_livery_opponent_1 = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeOpponent_2_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryOpponent_2->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getOpponent( index );

        m_index_opponent_2 = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryOpponent_2->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryOpponent_2->setCurrentIndex( 0 );
    }
    else
    {
        m_index_opponent_2 = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryOpponent_2_currentIndexChanged( int index )
{
    m_index_livery_opponent_2 = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeOpponent_3_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryOpponent_3->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getOpponent( index );

        m_index_opponent_3 = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryOpponent_3->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryOpponent_3->setCurrentIndex( 0 );
    }
    else
    {
        m_index_opponent_3 = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryOpponent_3_currentIndexChanged( int index )
{
    m_index_livery_opponent_3 = index;
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxTypeOpponent_4_currentIndexChanged( int index )
{
    m_ui->comboBoxLiveryOpponent_4->clear();

    if ( index >= 0 )
    {
        Units::UnitData data = m_units->getOpponent( index );

        m_index_opponent_4 = data.index;

        for ( int i = 0; i < data.liveries.size(); i++ )
        {
            m_ui->comboBoxLiveryOpponent_4->addItem( data.liveries[ i ] );
        }

        m_ui->comboBoxLiveryOpponent_4->setCurrentIndex( 0 );
    }
    else
    {
        m_index_opponent_4 = -1;
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogQuickAction::on_comboBoxLiveryOpponent_4_currentIndexChanged( int index )
{
    m_index_livery_opponent_4 = index;
}
