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

#include <gui/MainWindow.h>
#include <ui_MainWindow.h>

#include <iostream>

#include <QCloseEvent>
#include <QDir>
#include <QFile>
#include <QMessageBox>

#include <hid/hid_Manager.h>
#include <sim/sim_Manager.h>

#include <sim/entities/sim_Entities.h>
#include <sim/sim_Languages.h>

////////////////////////////////////////////////////////////////////////////////

MainWindow::MainWindow( QWidget *parent ) :
    QMainWindow ( parent ),
    m_ui ( new Ui::MainWindow ),

    m_dialogCtrl ( 0 ),
    m_dialogData ( 0 ),

    m_dialogQuickAction ( 0 ),

    m_shortcutPause ( 0 ),
    m_shortcutAbort ( 0 ),

    m_shortcutAuto ( 0 ),

    m_shortcutCtrl ( 0 ),
    m_shortcutData ( 0 ),
    m_shortcutExit ( 0 ),

    m_shortcutViewFull   ( 0 ),
    m_shortcutViewToggle ( 0 ),

    m_shortcutTimeFaster ( 0 ),
    m_shortcutTimeSlower ( 0 ),

    m_timer ( 0 ),
    m_timerId ( 0 ),

    m_timeCoef ( 1.0 ),

    m_autopilot ( false ),

    m_inited ( false ),
    m_paused ( false ),

    m_throttleInited ( false ),

    m_fullScreen ( false ),

    m_pending ( true ),

    m_heading ( 0.0f )
{
    m_ui->setupUi( this );

    m_dialogCtrl = new DialogCtrl( this );
    m_dialogData = new DialogData( this );

    m_dialogQuickAction = new DialogQuickAction( this );

    connect( m_dialogQuickAction, SIGNAL(accepted()), this, SLOT(dialogQuickAction_accepted()) );
    connect( m_dialogQuickAction, SIGNAL(rejected()), this, SLOT(dialogQuickAction_rejected()) );

    m_shortcutPause = new QShortcut( QKeySequence(Qt::Key_Pause)  , this, SLOT(on_actionPause_triggered()) );
    m_shortcutAbort = new QShortcut( QKeySequence(Qt::Key_Escape) , this, SLOT(on_actionAbort_triggered()) );

    m_shortcutAuto = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_A), this, SLOT(on_actionAuto_triggered()) );

    m_shortcutCtrl = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_C), this, SLOT(on_actionCtrl_triggered()) );
    m_shortcutData = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_D), this, SLOT(on_actionData_triggered()) );
    m_shortcutExit = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_Q), this, SLOT(on_actionQuit_triggered()) );

    m_shortcutViewFull   = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_F), this, SLOT(on_actionViewFull_triggered()) );
    m_shortcutViewToggle = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_T), this, SLOT(on_actionViewToggle_triggered()) );

    m_shortcutTimeFaster = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_Equal), this, SLOT(on_actionTimeFaster_triggered()) );
    m_shortcutTimeSlower = new QShortcut( QKeySequence(Qt::CTRL + Qt::Key_Minus), this, SLOT(on_actionTimeSlower_triggered()) );

    m_timer = new QElapsedTimer();

    initUnits();

    settingsRead();
}

////////////////////////////////////////////////////////////////////////////////

MainWindow::~MainWindow()
{
    if ( m_fullScreen ) showNormal();

    if ( m_timer ) delete m_timer;
    m_timer = 0;

    if ( m_timerId ) killTimer( m_timerId );

    settingsSave();

    if ( m_dialogCtrl ) delete m_dialogCtrl;
    m_dialogCtrl = 0;

    if ( m_dialogData ) delete m_dialogData;
    m_dialogData = 0;

    if ( m_dialogQuickAction ) delete m_dialogQuickAction;
    m_dialogQuickAction = 0;

    if ( m_shortcutPause ) delete m_shortcutPause;
    m_shortcutPause = 0;

    if ( m_shortcutAbort ) delete m_shortcutAbort;
    m_shortcutAbort = 0;

    if ( m_shortcutAuto ) delete m_shortcutAuto;
    m_shortcutAuto = 0;

    if ( m_shortcutCtrl ) delete m_shortcutCtrl;
    m_shortcutCtrl = 0;

    if ( m_shortcutData ) delete m_shortcutData;
    m_shortcutData = 0;

    if ( m_shortcutExit ) delete m_shortcutExit;
    m_shortcutExit = 0;

    if ( m_shortcutViewFull ) delete m_shortcutViewFull;
    m_shortcutViewFull = 0;

    if ( m_shortcutViewToggle ) delete m_shortcutViewToggle;
    m_shortcutViewToggle = 0;

    if ( m_shortcutTimeFaster ) delete m_shortcutTimeFaster;
    m_shortcutTimeFaster = 0;

    if ( m_shortcutTimeSlower ) delete m_shortcutTimeSlower;
    m_shortcutTimeSlower = 0;

    if ( m_ui ) delete m_ui;
    m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::init()
{
    hid::Manager::instance()->init();

    for ( unsigned int i = 0; i < sim::Languages::instance()->getCount(); i++ )
    {
        m_ui->comboBoxLanguage->addItem( QString( sim::Languages::instance()->getCodeByIndex( i ).c_str() ) );
    }

    m_ui->comboBoxLanguage->setCurrentIndex( sim::Languages::instance()->getDefault() );

    m_dialogCtrl->readData();
    m_dialogCtrl->updateAssignments();

    m_timer->start();
    m_timerId = startTimer( 1000.0f * 1.0f / 60.0f );

    m_ui->stackedMain->setCurrentIndex( 1 );
    std::cout << m_ui->widgetCGI->geometry().width() << " x " << m_ui->widgetCGI->geometry().height() << std::endl;
    m_ui->stackedMain->setCurrentIndex( 0 );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::closeEvent( QCloseEvent *event )
{
    QString title = windowTitle();
    QString text = "Do you really want to quit?";

    QMessageBox::StandardButton result = QMessageBox::question( this, title, text,
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::No );

    if ( result == QMessageBox::Yes )
    {
        /////////////////////////////////
        QMainWindow::closeEvent( event );
        /////////////////////////////////
    }
    else
    {
        event->ignore();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::timerEvent( QTimerEvent *event )
{
    /////////////////////////////////
    QMainWindow::timerEvent( event );
    /////////////////////////////////

    double timeStep = (double)m_timer->restart() / 1000.0;

     QString text = "";

     text += "FR: " + QString::number( 1.0 / timeStep, 'd', 2 );
     text += " ";
     text += "TC: " + QString::number( m_timeCoef, 'd', 1 );

     if ( sim::Manager::instance()->isPaused() )
     {
         text += " (PAUSED)";
     }
     else if ( m_autopilot )
     {
         text += " (AUTOPILOT)";
     }

    m_ui->statusBar->showMessage( text );

    if ( m_ui->widgetCGI->isVisible() && m_inited )
    {
        m_ui->widgetCGI->update();
    }

    if ( m_pending && !sim::Data::get()->ownship.destroyed )
    {
        m_heading = sim::Data::get()->ownship.heading;
    }
    else
    {
        if ( sim::Success == sim::Data::get()->mission.status
          || sim::Data::get()->ownship.destroyed )
        {
            if ( !m_autopilot ) toggleAutopilot();

            if ( sim::Manager::instance()->isReady()
              && sim::Data::get()->camera.type != sim::ViewOrbit )
            {
                sim::Manager::instance()->setViewOrbit();

                osg::ref_ptr<sim::ManipulatorOrbit> manipulator =
                        dynamic_cast< sim::ManipulatorOrbit* >( sim::Manager::instance()->getCameraManipulator() );

                if ( manipulator.valid() )
                {
                    m_ui->widgetCGI->setCameraManipulator( manipulator.get() );

                    manipulator->setElevation( osg::DegreesToRadians( 10.0 ) );
                    manipulator->setDistance( 25.0 );
                    manipulator->setHeading( -M_PI_2 - m_heading - M_PI_4 );
                }
            }
        }

        if ( sim::Manager::instance()->isFinished() )
        {
            simulationAbort();
        }
    }

    hid::Manager::instance()->update( m_timeCoef * timeStep );
    sim::Manager::instance()->update( m_timeCoef * timeStep );

    if ( !m_throttleInited && sim::Manager::instance()->isReady() )
    {
        hid::Manager::instance()->setThrottle( sim::Data::get()->ownship.init_throttle );

        m_throttleInited = true;
    }

    sim::Manager::instance()->setControls( hid::Manager::instance()->getTriggerBasic(),
                                           hid::Manager::instance()->getCtrlRoll(),
                                           hid::Manager::instance()->getCtrlPitch(),
                                           hid::Manager::instance()->getCtrlYaw(),
                                           hid::Manager::instance()->getThrottle() );

    m_pending = sim::Manager::instance()->isPending();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::askIfAbort()
{
    m_paused = true;
    sim::Manager::instance()->pause();

    QString title = windowTitle();
    QString text = "Do you really want to abort mission?";

    QMessageBox::StandardButton result = QMessageBox::question( this, title, text,
                                                                QMessageBox::Yes | QMessageBox::No,
                                                                QMessageBox::No );

    if ( result == QMessageBox::Yes )
    {
        simulationAbort();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::initUnits()
{
    QDir dir( sim::Base::getPath( "" ).c_str() );
    QFile file( dir.filePath( "units.xml" ) );

    if ( file.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &file, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "units" )
        {
            QDomElement nodeAerial = rootNode.firstChildElement( "aerial" );
            QDomElement nodeMarine = rootNode.firstChildElement( "marine" );
            QDomElement nodeGround = rootNode.firstChildElement( "ground" );

            if ( !nodeAerial.isNull() ) readUnits( nodeAerial );
            if ( !nodeMarine.isNull() ) readUnits( nodeMarine );
            if ( !nodeGround.isNull() ) readUnits( nodeGround );

            for ( Units::iterator it = m_units.begin(); it != m_units.end(); it++ )
            {
                m_ui->comboBoxUnits->addItem( (*it) );
            }
        }

        file.close();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::readUnits( QDomElement &node )
{
    QString lang = sim::Languages::instance()->getCodeByIndex( sim::Languages::instance()->getCurrent() ).c_str();

    QDomElement nodeUnit = node.firstChildElement( "unit" );

    while ( !nodeUnit.isNull() )
    {
        QDomElement nodeName = nodeUnit.firstChildElement( "name" );

        if ( !nodeName.isNull() )
        {
            QDomElement nodeText = nodeName.firstChildElement( "text" );

            while ( !nodeText.isNull() )
            {
                if ( lang == nodeText.attribute( "lang" ) )
                {
                    QString name = nodeText.text();

                    if ( name.length() > 0 )
                    {
                        m_units.push_back( name );
                    }

                    break;
                }

                nodeText = nodeText.nextSiblingElement( "text" );
            }
        }

        nodeUnit = nodeUnit.nextSiblingElement( "unit" );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsRead()
{
    QSettings settings( SIM_ORG_NAME, SIM_APP_NAME );

    settings.beginGroup( "main_window" );

    restoreState( settings.value( "state" ).toByteArray() );
    restoreGeometry( settings.value( "geometry" ).toByteArray() );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::settingsSave()
{
    QSettings settings( SIM_ORG_NAME, SIM_APP_NAME );

    settings.beginGroup( "main_window" );

    settings.setValue( "state", saveState() );
    settings.setValue( "geometry", saveGeometry() );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::simulationStart()
{
    if ( !m_inited )
    {
        m_inited = true;
        m_paused = true;

        m_throttleInited = false;

        m_pending = true;

        m_heading = 0.0f;

        m_timeCoef = 1.0;

        m_ui->stackedMain->setCurrentIndex( 1 );

        m_ui->actionStart->setEnabled( false );
        m_ui->actionPause->setEnabled( true );
        m_ui->actionAbort->setEnabled( true );

        m_ui->actionAuto->setEnabled( true );

        m_ui->menuView->setEnabled( true );
        m_ui->menuTime->setEnabled( true );

        m_ui->pushButtonStartUnitView->setEnabled( false );
        m_ui->pushButtonStartCampaign->setEnabled( false );
        m_ui->pushButtonStartQuickAction->setEnabled( false );

        int w = m_ui->widgetCGI->width();
        int h = m_ui->widgetCGI->height();

        sim::Manager::instance()->init( w, h, false, m_ui->widgetCampaign->getMissionIndex() );

        m_ui->widgetCGI->init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::simulationPause()
{
    if ( m_inited )
    {
        m_paused = !sim::Manager::instance()->isPaused();

        if ( m_paused )
        {
            sim::Manager::instance()->pause();
        }
        else
        {
            sim::Manager::instance()->unpause();
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::simulationAbort()
{
    if ( m_autopilot )
    {
        toggleAutopilot();
    }

    m_inited  = false;
    m_paused  = false;

    m_throttleInited = false;

    m_pending = true;

    m_timeCoef = 1.0;

    if ( m_fullScreen )
    {
        m_ui->menuBar->setVisible( true );
        m_ui->statusBar->setVisible( true );

        showNormal();

        m_fullScreen = false;
    }

    m_ui->stackedMain->setCurrentIndex( 0 );

    m_ui->actionStart->setEnabled( true );
    m_ui->actionPause->setEnabled( false );
    m_ui->actionAbort->setEnabled( false );

    m_ui->actionAuto->setEnabled( false );

    m_ui->menuView->setEnabled( false );
    m_ui->menuTime->setEnabled( false );

    m_ui->actionViewToggle->setEnabled( false );

    m_ui->pushButtonStartUnitView->setEnabled( true );
    m_ui->pushButtonStartCampaign->setEnabled( true );
    m_ui->pushButtonStartQuickAction->setEnabled( true );

    m_ui->widgetCGI->stop();

    sim::Manager::instance()->destroy();

    std::cout << "Friendly units destroyed: "
              << sim::Statistics::instance()->getFriendsDestroyed()
              << " out of "
              << sim::Statistics::instance()->getFriendsActivated()
              << std::endl;

    std::cout << "Hostile  units destroyed: "
              << sim::Statistics::instance()->getEnemiesDestroyed()
              << " out of "
              << sim::Statistics::instance()->getEnemiesActivated()
              << std::endl;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::toggleAutopilot()
{
    if ( m_inited )
    {
        m_autopilot = !m_autopilot;
        sim::Manager::instance()->setAutopilot( m_autopilot );
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::dialogQuickAction_accepted()
{
    if ( !m_inited )
    {
        m_inited = true;
        m_paused = true;

        m_throttleInited = false;

        m_pending = true;

        m_heading = 0.0f;

        m_timeCoef = 1.0;

        m_ui->stackedMain->setCurrentIndex( 1 );

        m_ui->actionStart->setEnabled( false );
        m_ui->actionPause->setEnabled( true );
        m_ui->actionAbort->setEnabled( true );

        m_ui->actionAuto->setEnabled( true );

        m_ui->menuView->setEnabled( true );
        m_ui->menuTime->setEnabled( true );

        int w = m_ui->widgetCGI->width();
        int h = m_ui->widgetCGI->height();

        sim::Manager::instance()->init( w, h, false,
            m_dialogQuickAction->getIndexScenery(),
            m_dialogQuickAction->getIndexOwnship()   , m_dialogQuickAction->getIndexLiveryOwnship(),
            m_dialogQuickAction->getIndexWingman()   , m_dialogQuickAction->getIndexLiveryWingman(),
            m_dialogQuickAction->getIndexAlly1()     , m_dialogQuickAction->getIndexLiveryAlly1(),
            m_dialogQuickAction->getIndexAlly2()     , m_dialogQuickAction->getIndexLiveryAlly2(),
            m_dialogQuickAction->getIndexOpponent1() , m_dialogQuickAction->getIndexLiveryOpponent1(),
            m_dialogQuickAction->getIndexOpponent2() , m_dialogQuickAction->getIndexLiveryOpponent2(),
            m_dialogQuickAction->getIndexOpponent3() , m_dialogQuickAction->getIndexLiveryOpponent3(),
            m_dialogQuickAction->getIndexOpponent4() , m_dialogQuickAction->getIndexLiveryOpponent4() );

        m_ui->widgetCGI->init();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::dialogQuickAction_rejected()
{
    m_ui->pushButtonStartCampaign->setEnabled( true );
    m_ui->pushButtonStartQuickAction->setEnabled( true );
    m_ui->pushButtonStartUnitView->setEnabled( true );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionStart_triggered()
{
    simulationStart();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionPause_triggered()
{
    simulationPause();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionAbort_triggered()
{
    if ( m_fullScreen )
    {
        on_actionViewFull_triggered();
    }

    if ( m_inited )
    {
        askIfAbort();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionAuto_triggered()
{
    toggleAutopilot();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionCtrl_triggered()
{
    m_dialogCtrl->readData();

    if ( m_dialogCtrl->exec() == QDialog::Accepted )
    {
        m_dialogCtrl->saveData();
        m_dialogCtrl->updateAssignments();
    }
    else
    {
        m_dialogCtrl->readData();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionData_triggered()
{
    m_dialogData->show();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionQuit_triggered()
{
    if ( m_fullScreen )
    {
        on_actionViewFull_triggered();
    }
    else
    {
        close();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewChase_triggered()
{
    sim::Manager::instance()->setViewChase();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_ui->actionViewToggle->setEnabled( false );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewFlyby_triggered()
{
    sim::Manager::instance()->setViewFlyby();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_ui->actionViewToggle->setEnabled( false );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewFront_triggered()
{
    sim::Manager::instance()->setViewFront();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_ui->actionViewToggle->setEnabled( false );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewOrbit_triggered()
{
    sim::Manager::instance()->setViewOrbit();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    osg::ref_ptr<sim::ManipulatorOrbit> manipulator =
            dynamic_cast< sim::ManipulatorOrbit* >( sim::Manager::instance()->getCameraManipulator() );

    if ( manipulator.valid() )
    {
        // normal
        double distance = 35.0;

        // mission image
        if ( 0 )
        {
            distance = 25.0;
        }

        manipulator->setElevation( osg::DegreesToRadians( 10.0 ) );
        manipulator->setDistance( distance );
        manipulator->setHeading( -M_PI_2 - m_heading - M_PI_4 );
    }

    m_ui->actionViewToggle->setEnabled( true );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewPilot_triggered()
{
    sim::Manager::instance()->setViewPilot();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_ui->actionViewToggle->setEnabled( false );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewShift_triggered()
{
    sim::Manager::instance()->setViewShift();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_ui->actionViewToggle->setEnabled( false );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewWorld_triggered()
{
    sim::Manager::instance()->setViewWorld();
    m_ui->widgetCGI->setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );

    m_ui->actionViewToggle->setEnabled( false );
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewToggle_triggered()
{
    sim::Manager::instance()->toggleOrbitUnit();

    osg::ref_ptr<sim::ManipulatorOrbit> manipulator =
            dynamic_cast< sim::ManipulatorOrbit* >( sim::Manager::instance()->getCameraManipulator() );

    if ( manipulator.valid() )
    {
        double unit_heading = m_heading;

        sim::UInt32 id = sim::Manager::instance()->getOrbitedUnitId();
        sim::Unit *unit = dynamic_cast< sim::Unit* >( sim::Entities::instance()->getEntityById( id ) );

        if ( unit )
        {
            unit_heading = -unit->getAngles().psi() + 1.5 * M_PI;
        }

        // normal
        double distance = 35.0;
        double elevation = osg::DegreesToRadians( 10.0 );
        double heading = -M_PI_2 - unit_heading - M_PI_4;
        //double heading = -M_PI_2 - unit_heading - osg::DegreesToRadians( 60.0 );

        // formation
        if ( 0 )
        {
            distance = 120.0;
            elevation = osg::DegreesToRadians( 20.0 );
            heading = -M_PI_2;
        }

        // mission image
        if ( 0 )
        {
            distance = 25.0;
        }

        // ship
        if ( 0 )
        {
            distance = 300.0;
            heading = -M_PI_2 - unit_heading - osg::DegreesToRadians( 60.0 );
        }

        manipulator->setDistance( distance );
        manipulator->setElevation( elevation );
        manipulator->setHeading( heading );
    }
    else if ( sim::Data::get()->camera.type == sim::ViewFlyby )
    {
        sim::Manager::instance()->setViewFlyby();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionViewFull_triggered()
{
    if ( m_fullScreen )
    {
        m_ui->menuBar->setVisible( true );
        m_ui->statusBar->setVisible( true );

        showNormal();

        m_fullScreen = false;
    }
    else if ( m_inited )
    {
        m_ui->menuBar->setVisible( false );
        m_ui->statusBar->setVisible( false );

        showFullScreen();

        m_fullScreen = true;
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionTimeFaster_triggered()
{
    if ( m_inited )
    {
        if ( m_timeCoef > 0.9 )
        {
            if ( m_timeCoef < 10.0 )
            {
                m_timeCoef += 1.0;
            }
            else
            {
                m_timeCoef = 10.0;
            }
        }
        else
        {
            m_timeCoef += 0.1;
        }
    }

    if ( m_timeCoef > 10.0 ) m_timeCoef = 10.0;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_actionTimeSlower_triggered()
{
    if ( m_inited )
    {
        if ( m_timeCoef > 1.0 )
        {
            m_timeCoef -= 1.0;
        }
        else
        {
            if ( m_timeCoef > 0.0 )
            {
                m_timeCoef -= 0.1;
            }
            else
            {
                m_timeCoef = 0.0;
            }
        }
    }

    if ( m_timeCoef < 0.0 ) m_timeCoef = 0.0;
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_comboBoxLanguage_currentIndexChanged( int index )
{
    sim::Manager::instance()->setLanguage( index );

    m_ui->widgetCampaign->reinit();

    m_units.clear();
    m_ui->comboBoxUnits->clear();

    initUnits();

}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStartCampaign_clicked()
{
    simulationStart();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStartQuickAction_clicked()
{
    m_ui->pushButtonStartCampaign->setEnabled( false );
    m_ui->pushButtonStartQuickAction->setEnabled( false );
    m_ui->pushButtonStartUnitView->setEnabled( false );

    m_dialogQuickAction->show();
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_pushButtonStartUnitView_clicked()
{
    m_ui->actionStart->setEnabled( false );
    m_ui->actionPause->setEnabled( false );
    m_ui->actionAbort->setEnabled( false );

    m_ui->pushButtonStartUnitView->setEnabled( false );
    m_ui->pushButtonStartCampaign->setEnabled( false );
    m_ui->pushButtonStartQuickAction->setEnabled( false );

    if ( !m_inited )
    {
        m_inited = true;

        m_ui->stackedMain->setCurrentIndex( 1 );

        int w = m_ui->widgetCGI->width();
        int h = m_ui->widgetCGI->height();

        int unitId = m_ui->comboBoxUnits->currentIndex();

        sim::Manager::instance()->init( w, h, unitId );

        m_ui->widgetCGI->init();

        sim::Manager::instance()->resetViewer();
    }
}

////////////////////////////////////////////////////////////////////////////////

void MainWindow::on_widgetCampaign_changed()
{
    if ( m_ui->widgetCampaign->getMissionIndex() == -1 )
    {
        m_ui->pushButtonStartCampaign->setEnabled( false );
    }
    else
    {
        m_ui->pushButtonStartCampaign->setEnabled( true );
    }
}
