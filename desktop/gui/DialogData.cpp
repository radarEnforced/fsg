#include <gui/DialogData.h>
#include <ui_DialogData.h>

#include <defs.h>

#include <sim/sim_Manager.h>

////////////////////////////////////////////////////////////////////////////////

DialogData::DialogData( QWidget *parent ) :
    QDialog( parent ),
    m_ui( new Ui::DialogData ),

    m_timerId ( 0 )
{
    m_ui->setupUi( this );

    m_timerId = startTimer( 1000.0f * 1.0f / 60.0f );
}

////////////////////////////////////////////////////////////////////////////////

DialogData::~DialogData()
{
    if ( m_timerId ) killTimer( m_timerId );

    if ( m_ui ) delete m_ui;
    m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void DialogData::timerEvent( QTimerEvent *event )
{
    /////////////////////////////
    QDialog::timerEvent( event );
    /////////////////////////////

    m_ui->timeEdit->setTime( QTime().addSecs( sim::Data::get()->mission.real_time ) );

    m_ui->spinBoxAltitudeASL->setValue( sim::Data::get()->ownship.altitude_asl );
    m_ui->spinBoxAltitudeAGL->setValue( sim::Data::get()->ownship.altitude_agl );

    m_ui->spinBoxAirspeed->setValue( sim::Data::get()->ownship.airspeed );
    m_ui->spinBoxClimbRate->setValue( sim::Data::get()->ownship.climbRate );

    m_ui->spinBoxAngleOfAttack->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.angleOfAttack ) );
    m_ui->spinBoxSideslipAngle->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.sideslipAngle ) );

    m_ui->spinBoxRollAngle->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.rollAngle ) );
    m_ui->spinBoxPitchAngle->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.pitchAngle ) );
    m_ui->spinBoxHeading->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.heading ) );

    m_ui->spinBoxRollRate->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.rollRate ) );
    m_ui->spinBoxPitchRate->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.pitchRate ) );
    m_ui->spinBoxYawRate->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.yawRate ) );
    m_ui->spinBoxTurnRate->setValue( osg::RadiansToDegrees( sim::Data::get()->ownship.turnRate ) );
}
