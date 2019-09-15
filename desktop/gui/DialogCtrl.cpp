#include <gui/DialogCtrl.h>
#include <ui_DialogCtrl.h>

#include <iostream>

#include <defs.h>

#include <hid/hid_Joysticks.h>
#include <gui/DialogAction.h>

////////////////////////////////////////////////////////////////////////////////

DialogCtrl::DialogCtrl( QWidget *parent ) :
    QDialog ( parent ),
    m_ui ( new Ui::DialogCtrl ),

    m_defaultAssignmentsInited ( false ),
    m_comboDeviceInited ( false )
{
    m_actionNames[ hid::Assignment::TriggerBasic     ] = "trigger_basic";        // 0
    m_actionNames[ hid::Assignment::TriggerExtra     ] = "trigger_extra";        // 1
    m_actionNames[ hid::Assignment::RollAxis         ] = "roll_axis";            // 2
    m_actionNames[ hid::Assignment::RollBankLeft     ] = "roll_bank_left";       // 3
    m_actionNames[ hid::Assignment::RollBankRight    ] = "roll_bank_right";      // 4
    m_actionNames[ hid::Assignment::PitchAxis        ] = "pitch_axis";           // 5
    m_actionNames[ hid::Assignment::PitchNoseUp      ] = "pitch_nose_up";        // 6
    m_actionNames[ hid::Assignment::PitchNoseDown    ] = "pitch_nose_down";      // 7
    m_actionNames[ hid::Assignment::YawAxis          ] = "yaw_axis";             // 8
    m_actionNames[ hid::Assignment::YawTurnLeft      ] = "yaw_turn_left";        // 9
    m_actionNames[ hid::Assignment::YawTurnRight     ] = "yaw_turn_right";       // 10
    m_actionNames[ hid::Assignment::ThrottleAxis     ] = "throttle_axis";        // 11
    m_actionNames[ hid::Assignment::ThrottleIncrease ] = "throttle_increase";    // 12
    m_actionNames[ hid::Assignment::ThrottleDecrease ] = "throttle_decrease";    // 13

#   if ( HID_MAX_ACTIONS != 14 )
#       error 'HID_MAX_ACTIONS' has been changed! Check code above this line!
#   endif

    m_ui->setupUi( this );

    for ( short i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        memset( &(m_assignments[ i ]), 0, sizeof(hid::Assignment) );
        m_assignments[ i ].type = hid::Assignment::None;
    }

    createTableControls();

    if ( m_ui->tableControls->rowCount() != HID_MAX_ACTIONS )
    {
        std::cerr << "ERROR! Wrong actions count: " << HID_MAX_ACTIONS << std::endl;

#       ifdef SIM_EXITONERROR
        exit( EXIT_FAILURE );
#       endif
    }

    settingsRead();
}

////////////////////////////////////////////////////////////////////////////////

DialogCtrl::~DialogCtrl()
{
    settingsSave();
    
    if ( m_ui ) delete m_ui;
    m_ui = 0;
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::getAssignments( hid::Assignment assignments[] )
{
    for ( short i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        assignments[ i ] = m_assignments[ i ];
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::readData()
{
    if ( !m_comboDeviceInited )
    {
        short joysCount = hid::Joysticks::instance()->getJoysCount();

        for ( short i = 0; i < joysCount; i++ )
        {
            hid::Joysticks::Data joyData = hid::Joysticks::instance()->getJoyData( i );

            m_ui->comboDevice->addItem( QString( joyData.name.c_str() ) );
        }

        m_comboDeviceInited = true;
    }

    settingsRead();

    updateTableControls();
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::saveData()
{
    settingsSave();
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::updateAssignments()
{
    for ( int i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        hid::Manager::instance()->setAssingment( (hid::Assignment::Action)i, m_assignments[ i ] );
    }
}

////////////////////////////////////////////////////////////////////////////////

bool DialogCtrl::isButtonAssignmentClearEnabled( int action )
{
    if ( action >= 0 && action < HID_MAX_ACTIONS )
    {
        if ( m_assignments[ action ].type == hid::Assignment::None )
        {
            return false;
        }
        else
        {
            return true;
        }
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

bool DialogCtrl::isButtonAssignmentChangeEnabled( int action, int device )
{
    if ( action >= 0 && action < HID_MAX_ACTIONS )
    {
        if ( device == 0 )
        {
            if ( hid::Manager::isAxis( (hid::Assignment::Action)action ) )
            {
                return false;
            }
            else
            {
                return true;
            }
        }
        else
        {
            return true;
        }
    }
    else

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::changeAssignment( int action )
{
    if ( action >= 0 && action < HID_MAX_ACTIONS )
    {
        hid::Assignment newAssignment;

        if ( m_ui->comboDevice->currentIndex() < 1 )
        {
            newAssignment = DialogAction::getKeyAssignment( this, m_assignments[ action ] );
        }
        else
        {
            int joystickId = m_ui->comboDevice->currentIndex() - 1;

            if ( hid::Manager::isAxis( (hid::Assignment::Action)action ) )
            {
                newAssignment = DialogAction::getJoyAxisAssignment( this, m_assignments[ action ], joystickId );
            }
            else
            {
                newAssignment = DialogAction::getJoyButtAssignment( this, m_assignments[ action ], joystickId );
            }
        }

        if ( newAssignment.type != hid::Assignment::None )
        {
            m_assignments[ action ] = newAssignment;
        }

        updateTableControls();

        setButtonsState( m_ui->tableControls->currentRow(), m_ui->comboDevice->currentIndex() );
    }
    else
    {
        std::cerr << "ERROR! Wrong action number: " << action << std::endl;

#       ifdef SIM_EXITONERROR
        exit( EXIT_FAILURE );
#       endif
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::clearAssignment( int action )
{
    if ( action >= 0 && action < HID_MAX_ACTIONS )
    {
        memset( &(m_assignments[ action ]), 0, sizeof(hid::Assignment) );

        m_assignments[ action ].type = hid::Assignment::None;

        updateTableControls();
        setButtonsState( m_ui->tableControls->currentRow(), m_ui->comboDevice->currentIndex() );
    }
    else
    {
        std::cerr << "ERROR! Wrong action number: " << action << std::endl;

#       ifdef SIM_EXITONERROR
        exit( EXIT_FAILURE );
#       endif
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::createTableControls()
{
    if ( m_ui->tableControls->rowCount() < HID_MAX_ACTIONS )
    {
        m_ui->tableControls->setRowCount( HID_MAX_ACTIONS );
    }

    for ( int i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        QTableWidgetItem *tableRowHeader = new QTableWidgetItem();
        tableRowHeader->setText( hid::Manager::m_actionNames[ i ].c_str() );
        m_ui->tableControls->setVerticalHeaderItem( i, tableRowHeader );

        QTableWidgetItem *tableItem = new QTableWidgetItem();
        m_ui->tableControls->setItem( i, 0, tableItem );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::updateTableControls()
{
    for ( int i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        QString itemText( "" );

        hid::Joysticks::Data joyData;

        switch ( m_assignments[ i ].type )
        {
        case hid::Assignment::Keyboard:
            itemText += "Keyboard: ";
            if ( m_assignments[ i ].data.keyboard.keyId >= 0
              && m_assignments[ i ].data.keyboard.keyId < HID_MAX_KEYS )
            {
                itemText += "\"";
                itemText += hid::Manager::m_keysNames[ m_assignments[ i ].data.keyboard.keyId ].c_str();
                itemText += "\"";
            }
            else
            {
                itemText += "NONE";
            }
            break;

        case hid::Assignment::Joystick:
            joyData = hid::Joysticks::instance()->getJoyData( m_assignments[ i ].data.joystick.joystickId );

            itemText += joyData.name.c_str();
            itemText += ": ";
            if ( hid::Manager::isAxis( (hid::Assignment::Action)i ) )
            {
                itemText += hid::Joysticks::m_axisNames[ m_assignments[ i ].data.joystick.axisId ].c_str();
                if ( m_assignments[ i ].data.joystick.inverted ) itemText += " (Inverted)";
            }
            else
            {
                if ( m_assignments[ i ].data.joystick.buttonId >= 0
                  && m_assignments[ i ].data.joystick.buttonId < joyData.buttCount )
                {
                    itemText += "Button ";
                    itemText += QString::number( m_assignments[ i ].data.joystick.buttonId + 1 );
                }
                else if ( m_assignments[ i ].data.joystick.povId >= 0
                       && m_assignments[ i ].data.joystick.povId < joyData.povsCount )
                {
                    itemText += "POV ";
                    itemText += QString::number( m_assignments[ i ].data.joystick.povId + 1 );

                    switch ( m_assignments[ i ].data.joystick.direction )
                    {
                        case hid::Assignment::North: itemText += " - N";  break;
                        case hid::Assignment::East:  itemText += " - E";  break;
                        case hid::Assignment::South: itemText += " - S";  break;
                        case hid::Assignment::West:  itemText += " - W";  break;
                        default:  itemText += " - NONE"; break;
                    }
                }
            }
            break;

        default:
            break;
        }

        m_ui->tableControls->item( i, 0 )->setText( itemText );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::setButtonsState( int action, int device )
{
    m_ui->buttonAssignmentClear->setEnabled( isButtonAssignmentClearEnabled( action ) );
    m_ui->buttonAssignmentChange->setEnabled( isButtonAssignmentChangeEnabled( action, device ) );
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::settingsRead()
{
    QSettings settings( SIM_ORG_NAME, SIM_APP_NAME );

    settings.beginGroup( "dialog_conf" );

    restoreGeometry( settings.value( "geometry" ).toByteArray() );

    assignmentsRead( settings );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::settingsSave()
{
    QSettings settings( SIM_ORG_NAME, SIM_APP_NAME );

    settings.beginGroup( "dialog_conf" );

    settings.setValue( "geometry" , saveGeometry() );

    assignmentsSave( settings );

    settings.endGroup();
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::initDefaultAssignments()
{
    if ( !m_defaultAssignmentsInited )
    {
        QSettings settings( SIM_ORG_NAME, SIM_APP_NAME );

        settings.beginGroup( "page_controls" );
        {
            m_defaultAssignmentsInited = settings.value( "default_assignments_inited", 0 ).toBool();
        }
        settings.endGroup(); // page_controls
    }

    if ( !m_defaultAssignmentsInited )
    {
        QSettings settings( SIM_ORG_NAME, SIM_APP_NAME );

        settings.beginGroup( "page_controls" );
        {
            settings.setValue( "default_assignments_inited" , (int)true );
        }
        settings.endGroup(); // page_controls

        int joysCount = hid::Joysticks::instance()->getJoysCount();

        if ( joysCount > 0 )
        {
            m_assignments[ hid::Assignment::TriggerBasic ].type = hid::Assignment::Joystick;
            m_assignments[ hid::Assignment::TriggerBasic ].data.joystick.joystickId = 0;
            m_assignments[ hid::Assignment::TriggerBasic ].data.joystick.axisId     = -1;
            m_assignments[ hid::Assignment::TriggerBasic ].data.joystick.inverted   = false;
            m_assignments[ hid::Assignment::TriggerBasic ].data.joystick.buttonId   = 0;
            m_assignments[ hid::Assignment::TriggerBasic ].data.joystick.povId      = -1;
            m_assignments[ hid::Assignment::TriggerBasic ].data.joystick.direction  = hid::Assignment::Centered;

            m_assignments[ hid::Assignment::TriggerExtra ].type = hid::Assignment::Joystick;
            m_assignments[ hid::Assignment::TriggerExtra ].data.joystick.joystickId = 0;
            m_assignments[ hid::Assignment::TriggerExtra ].data.joystick.axisId     = -1;
            m_assignments[ hid::Assignment::TriggerExtra ].data.joystick.inverted   = false;
            m_assignments[ hid::Assignment::TriggerExtra ].data.joystick.buttonId   = 1;
            m_assignments[ hid::Assignment::TriggerExtra ].data.joystick.povId      = -1;
            m_assignments[ hid::Assignment::TriggerExtra ].data.joystick.direction  = hid::Assignment::Centered;

            m_assignments[ hid::Assignment::RollAxis ].type = hid::Assignment::Joystick;
            m_assignments[ hid::Assignment::RollAxis ].data.joystick.joystickId = 0;
            m_assignments[ hid::Assignment::RollAxis ].data.joystick.axisId     = hid::Joysticks::AxisX;
            m_assignments[ hid::Assignment::RollAxis ].data.joystick.inverted   = false;
            m_assignments[ hid::Assignment::RollAxis ].data.joystick.buttonId   = -1;
            m_assignments[ hid::Assignment::RollAxis ].data.joystick.povId      = -1;
            m_assignments[ hid::Assignment::RollAxis ].data.joystick.direction  = hid::Assignment::Centered;

            m_assignments[ hid::Assignment::PitchAxis ].type = hid::Assignment::Joystick;
            m_assignments[ hid::Assignment::PitchAxis ].data.joystick.joystickId = 0;
            m_assignments[ hid::Assignment::PitchAxis ].data.joystick.axisId     = hid::Joysticks::AxisY;
            m_assignments[ hid::Assignment::PitchAxis ].data.joystick.inverted   = false;
            m_assignments[ hid::Assignment::PitchAxis ].data.joystick.buttonId   = -1;
            m_assignments[ hid::Assignment::PitchAxis ].data.joystick.povId      = -1;
            m_assignments[ hid::Assignment::PitchAxis ].data.joystick.direction  = hid::Assignment::Centered;
        }
        else
        {
            m_assignments[ hid::Assignment::TriggerBasic ].type = hid::Assignment::Keyboard;
            m_assignments[ hid::Assignment::TriggerBasic ].data.keyboard.keyId = hid::Assignment::KeySpace;

            // TODO
            m_assignments[ hid::Assignment::TriggerExtra ].type = hid::Assignment::Keyboard;
            m_assignments[ hid::Assignment::TriggerExtra ].data.keyboard.keyId = hid::Assignment::KeySpace;

            m_assignments[ hid::Assignment::RollBankLeft ].type = hid::Assignment::Keyboard;
            m_assignments[ hid::Assignment::RollBankLeft ].data.keyboard.keyId = hid::Assignment::KeyLeft;

            m_assignments[ hid::Assignment::RollBankRight ].type = hid::Assignment::Keyboard;
            m_assignments[ hid::Assignment::RollBankRight ].data.keyboard.keyId = hid::Assignment::KeyRight;

            m_assignments[ hid::Assignment::PitchNoseUp ].type = hid::Assignment::Keyboard;
            m_assignments[ hid::Assignment::PitchNoseUp ].data.keyboard.keyId = hid::Assignment::KeyDown;

            m_assignments[ hid::Assignment::PitchNoseDown ].type = hid::Assignment::Keyboard;
            m_assignments[ hid::Assignment::PitchNoseDown ].data.keyboard.keyId = hid::Assignment::KeyUp;
        }

        m_assignments[ hid::Assignment::YawTurnLeft ].type = hid::Assignment::Keyboard;
        m_assignments[ hid::Assignment::YawTurnLeft ].data.keyboard.keyId = hid::Assignment::KeyComma;

        m_assignments[ hid::Assignment::YawTurnRight ].type = hid::Assignment::Keyboard;
        m_assignments[ hid::Assignment::YawTurnRight ].data.keyboard.keyId = hid::Assignment::KeyPeriod;

        m_assignments[ hid::Assignment::ThrottleIncrease ].type = hid::Assignment::Keyboard;
        m_assignments[ hid::Assignment::ThrottleIncrease ].data.keyboard.keyId = hid::Assignment::KeyEquals;

        m_assignments[ hid::Assignment::ThrottleDecrease ].type = hid::Assignment::Keyboard;
        m_assignments[ hid::Assignment::ThrottleDecrease ].data.keyboard.keyId = hid::Assignment::KeyMinus;

#       if ( HID_MAX_ACTIONS != 14 )
#           error 'HID_MAX_ACTIONS' has been changed! Check code above this line!
#       endif

        settingsSave();
    }

    m_defaultAssignmentsInited = true;
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::assignmentsRead( QSettings &settings )
{
    initDefaultAssignments();

    for ( int i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        assignmentRead( settings, m_assignments[ i ], (hid::Assignment::Action)i );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::assignmentsSave( QSettings &settings )
{
    for ( int i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        assignmentSave( settings, m_assignments[ i ], (hid::Assignment::Action)i );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::assignmentRead( QSettings &settings, hid::Assignment &assignment, hid::Assignment::Action action )
{
    settings.beginGroup( "controls" );
    {
        settings.beginGroup( m_actionNames[ action ].c_str() );
        {
            int joysCount = hid::Joysticks::instance()->getJoysCount();

            int tempType       = 0;
            int tempKeyId      = 0;
            int tempJoystickId = 0;
            int tempAxisId     = 0;
            int tempInverted   = 0;
            int tempButtonId   = 0;
            int tempPovId      = 0;
            int tempDirection  = 0;

            tempType = settings.value( "type", hid::Assignment::None ).toInt();

            switch ( tempType )
            {
            case hid::Assignment::Keyboard:
                tempKeyId = settings.value( "key_id", -1 ).toInt();

                assignment.type = hid::Assignment::Keyboard;
                assignment.data.keyboard.keyId = (short)tempKeyId;
                break;

            case hid::Assignment::Joystick:
                tempJoystickId = settings.value( "joystick_id" , -1 ).toInt();
                tempAxisId     = settings.value( "axis_id"     , -1 ).toInt();
                tempInverted   = settings.value( "inverted"    , -1 ).toInt();
                tempButtonId   = settings.value( "button_id"   , -1 ).toInt();
                tempPovId      = settings.value( "pov_id"      , -1 ).toInt();
                tempDirection  = settings.value( "direction"   , -1 ).toInt();

                if ( tempJoystickId < joysCount )
                {
                    assignment.type = hid::Assignment::Joystick;
                    assignment.data.joystick.joystickId = (short)tempJoystickId;
                    assignment.data.joystick.axisId     = (short)tempAxisId;
                    assignment.data.joystick.inverted   = (bool)tempInverted;
                    assignment.data.joystick.buttonId   = (short)tempButtonId;
                    assignment.data.joystick.povId      = (short)tempPovId;
                    assignment.data.joystick.direction  = (hid::Assignment::POVs)tempDirection;
                }
                else
                {
                    assignment.type = hid::Assignment::None;
                    memset( &(assignment.data), 0, sizeof(hid::Assignment::DeviceData) );
                }
                break;

            default:
                assignment.type = hid::Assignment::None;
                break;
            }
        }
        settings.endGroup();
    }
    settings.endGroup(); // controls
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::assignmentSave( QSettings &settings, hid::Assignment &assignment, hid::Assignment::Action action )
{
    settings.beginGroup( "controls" );
    {
        settings.beginGroup( m_actionNames[ action ].c_str() );
        {
            switch ( assignment.type )
            {
            case hid::Assignment::Keyboard:
                settings.setValue( "type", hid::Assignment::Keyboard );
                settings.setValue( "key_id", (int)assignment.data.keyboard.keyId );
                break;

            case hid::Assignment::Joystick:
                settings.setValue( "type", hid::Assignment::Joystick );
                settings.setValue( "joystick_id" , (int)assignment.data.joystick.joystickId );
                settings.setValue( "axis_id"     , (int)assignment.data.joystick.axisId     );
                settings.setValue( "inverted"    , (int)assignment.data.joystick.inverted   );
                settings.setValue( "button_id"   , (int)assignment.data.joystick.buttonId   );
                settings.setValue( "pov_id"      , (int)assignment.data.joystick.povId      );
                settings.setValue( "direction"   , (int)assignment.data.joystick.direction  );
                break;

            default:
                settings.setValue( "type", hid::Assignment::None );
                settings.setValue( "key_id"      , 0 );
                settings.setValue( "joystick_id" , 0 );
                settings.setValue( "axis_id"     , 0 );
                settings.setValue( "inverted"    , 0 );
                settings.setValue( "button_id"   , 0 );
                settings.setValue( "pov_id"      , 0 );
                settings.setValue( "direction"   , 0 );
                break;
            }
        }
        settings.endGroup();

    }
    settings.endGroup(); // controls
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::on_buttonAssignmentClear_clicked()
{
    clearAssignment( m_ui->tableControls->currentRow() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::on_buttonAssignmentChange_clicked()
{
    changeAssignment( m_ui->tableControls->currentRow() );
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::on_comboDevice_currentIndexChanged( int index )
{
    setButtonsState( m_ui->tableControls->currentRow(), index );
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::on_tableControls_cellDoubleClicked( int row, int )
{
    if ( isButtonAssignmentChangeEnabled( row, m_ui->comboDevice->currentIndex() ) )
    {
        changeAssignment( row );
    }
}

////////////////////////////////////////////////////////////////////////////////

void DialogCtrl::on_tableControls_currentCellChanged( int row, int, int, int )
{
    setButtonsState( row, m_ui->comboDevice->currentIndex() );
}
