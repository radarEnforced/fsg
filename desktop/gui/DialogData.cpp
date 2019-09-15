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
