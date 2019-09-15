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

#include <hid/hid_Manager.h>

#include <memory.h>

#include <sim/sim_Defs.h>
#include <hid/hid_Joysticks.h>

////////////////////////////////////////////////////////////////////////////////

using namespace hid;

////////////////////////////////////////////////////////////////////////////////

const std::string Manager::m_actionNames[] = {
    "Primary Trigger",
    "Secondary Trigger",
    "Roll (Axis)",
    "Roll: Bank Left",
    "Roll: Bank Right",
    "Pitch (Axis)",
    "Pitch: Nose Up",
    "Pitch: Nose Down",
    "Yaw (Axis)",
    "Yaw: Turn Left",
    "Yaw: Turn Right",
    "Throttle (Axis)",
    "Throttle: Increase",
    "Throttle: Decrease"
};

#if ( HID_MAX_ACTIONS != 14 )
#   error 'HID_MAX_ACTIONS' has been changed! Check code above this line!
#endif

const std::string Manager::m_keysNames[] = {
    "0", "1", "2", "3", "4", "5", "6", "7", "8", "9",
    "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M",
    "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    "`", "-", "=", "[", "]", ";", "'", ",", ".", "/",
    "Space",
    "Left", "Right", "Up", "Down",
    "Insert", "Delete", "Home", "End", "Page Up", "Page Down"
};

#if ( HID_MAX_KEYS != 57 )
#   error 'HID_MAX_KEYS' has been changed! Check code following this line!
#endif

////////////////////////////////////////////////////////////////////////////////

Assignment::POVs Manager::getPOV( short pov_deg )
{
    Assignment::POVs result = Assignment::Centered;

    if ( !( pov_deg < 0 ) )
    {
        if ( pov_deg < 90 )
        {
            if ( pov_deg > 0 )
                result = Assignment::NorthEast;
            else
                result = Assignment::North;
        }
        else if ( pov_deg < 180 )
        {
            if ( pov_deg > 90 )
                result = Assignment::SouthEast;
            else
                result = Assignment::East;
        }
        else if ( pov_deg < 270 )
        {
            if ( pov_deg > 180 )
                result = Assignment::SouthWest;
            else
                result = Assignment::South;
        }
        else
        {
            if ( pov_deg > 270 )
                result = Assignment::NorthWest;
            else
                result = Assignment::West;
        }
    }

    return result;
}

////////////////////////////////////////////////////////////////////////////////

bool Manager::isAxis( Assignment::Action action )
{
    return ( action == Assignment::RollAxis
          || action == Assignment::PitchAxis
          || action == Assignment::YawAxis
          || action == Assignment::ThrottleAxis );

#   if ( HID_MAX_ACTIONS != 14 )
#       error 'HID_MAX_ACTIONS' has been changed! Check code above this line!
#   endif
}

////////////////////////////////////////////////////////////////////////////////

Manager::Manager() :
    m_speedControls ( 1.0f ),
    m_speedThrottle ( 0.5f ),

    m_timeStep ( 0.0 )
{
    for ( int i = 0; i < HID_MAX_ACTIONS; i++ )
    {
        m_assignments[ i ].type = Assignment::None;

        memset( &(m_assignments[ i ].data), 0, sizeof(Assignment::DeviceData) );
    }

    for ( int i = 0; i < HID_MAX_KEYS; i++ ) m_keysState[ i ] = false;

    reset();
}

////////////////////////////////////////////////////////////////////////////////

Manager::~Manager() {}

////////////////////////////////////////////////////////////////////////////////

void Manager::init()
{
    Joysticks::instance()->init();
}

////////////////////////////////////////////////////////////////////////////////

void Manager::update( double timeStep )
{
    m_timeStep =  timeStep;

    Joysticks::instance()->update();

    updateAxisActions();
    updateMiscActions();
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setThrottle( float throttle )
{
    m_throttle = throttle;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::setAssingment( Assignment::Action action, const Assignment &assignment )
{
    m_assignments[ action ] = assignment;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::getAxisValue( const Assignment &assignment, float &value, int absolute )
{
    if ( assignment.type == Assignment::Joystick )
    {
        Joysticks::Data joyData = Joysticks::instance()->getJoyData( assignment.data.joystick.joystickId );

        if ( joyData.active )
        {
            value = joyData.axis[ assignment.data.joystick.axisId ];

            if ( assignment.data.joystick.inverted ) value *= -1.0f;

            if ( absolute ) value = ( value + 1.0f ) / 2.0f;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Manager::getCtrlValue( Assignment::Action decreaseAction,
                         Assignment::Action increaseAction,
                         float &value,
                         float speed,
                         float min,
                         float max )
{
    bool tempDecrease = getButtState( m_assignments[ decreaseAction ] );
    bool tempIncrease = getButtState( m_assignments[ increaseAction ] );

    if ( !tempDecrease && !tempIncrease )
    {
        if      ( value > 0.0 ) value = value - speed * m_timeStep;
        else if ( value < 0.0 ) value = value + speed * m_timeStep;
    }
    else if ( tempDecrease && value > min ) value = value - speed * m_timeStep;
    else if ( tempIncrease && value < max ) value = value + speed * m_timeStep;

    if ( value < min ) value = min;
    if ( value > max ) value = max;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::getRealValue( Assignment::Action decreaseAction,
                         Assignment::Action increaseAction,
                         float &value,
                         float speed,
                         float min,
                         float max )
{
    bool tempDecrease = getButtState( m_assignments[ decreaseAction ] );
    bool tempIncrease = getButtState( m_assignments[ increaseAction ] );

    if ( tempDecrease && value > min ) value = value - speed * m_timeStep;
    if ( tempIncrease && value < max ) value = value + speed * m_timeStep;

    if ( value < min ) value = min;
    if ( value > max ) value = max;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::getRealValue( Assignment::Action applyAction,
                         float &value,
                         float speed,
                         float min,
                         float max )
{
    bool tempApply = getButtState( m_assignments[ applyAction ] );

    if ( !tempApply && value > min ) value = value - speed * m_timeStep;
    if (  tempApply && value < max ) value = value + speed * m_timeStep;

    if ( value < min ) value = min;
    if ( value > max ) value = max;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::getRealValue( Assignment::Action toggleAction,
                         bool  &togglePrev,
                         bool  &state,
                         float &value,
                         float speed,
                         float min,
                         float max )
{
    bool toggle = getButtState( m_assignments[ toggleAction ] );

    if ( toggle && !togglePrev )
    {
        state = !state;
    }

    togglePrev = toggle;

    if ( !state && value > min ) value  = value - speed * m_timeStep;
    if (  state && value < max ) value  = value + speed * m_timeStep;

    if ( value < min ) value = min;
    if ( value > max ) value = max;
}

////////////////////////////////////////////////////////////////////////////////

bool Manager::getButtState( const Assignment &assignment )
{
    bool state = false;

    if ( assignment.type == Assignment::Joystick )
    {
        Joysticks::Data joyData = Joysticks::instance()->getJoyData( assignment.data.joystick.joystickId );

        if ( joyData.active )
        {
            if ( assignment.data.joystick.buttonId >= 0
              && assignment.data.joystick.buttonId < joyData.buttCount )
            {
                state = joyData.butt[ assignment.data.joystick.buttonId ];
            }
            else if ( assignment.data.joystick.povId >= 0
                   && assignment.data.joystick.povId < joyData.povsCount )
            {
                if ( assignment.data.joystick.direction != Assignment::Centered )
                {
                    state = ( getPOV( joyData.povs[ assignment.data.joystick.povId ] )
                          & assignment.data.joystick.direction ) != 0;
                }
            }
        }
    }
    else if ( assignment.type == Assignment::Keyboard )
    {
        if ( assignment.data.keyboard.keyId != -1 )
        {
            state = m_keysState[ assignment.data.keyboard.keyId ];
        }
    }

    return state;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::reset()
{
    m_trigger_basic = false;
    m_trigger_extra = false;

    m_ctrlRoll  = 0.0f;
    m_ctrlPitch = 0.0f;
    m_ctrlYaw   = 0.0f;
    m_throttle  = 0.0f;
}

////////////////////////////////////////////////////////////////////////////////

void Manager::updateAxisActions()
{
    // roll
    if ( m_assignments[ Assignment::RollAxis ].type == Assignment::None )
    {
        getCtrlValue( Assignment::RollBankLeft,
                      Assignment::RollBankRight,
                      m_ctrlRoll, m_speedControls, -1.0f, 1.0f );
    }
    else
    {
        getAxisValue( m_assignments[ Assignment::RollAxis ], m_ctrlRoll );
    }

    // pitch
    if ( m_assignments[ Assignment::PitchAxis ].type == Assignment::None )
    {
        getCtrlValue( Assignment::PitchNoseDown,
                      Assignment::PitchNoseUp,
                      m_ctrlPitch, m_speedControls, -1.0f, 1.0f );
    }
    else
    {
        getAxisValue( m_assignments[ Assignment::PitchAxis ], m_ctrlPitch );
    }

    // yaw
    if ( m_assignments[ Assignment::YawAxis ].type == Assignment::None )
    {
        getCtrlValue( Assignment::YawTurnLeft,
                      Assignment::YawTurnRight,
                      m_ctrlYaw, m_speedControls, -1.0f, 1.0f );
    }
    else
    {
        getAxisValue( m_assignments[ Assignment::YawAxis ], m_ctrlYaw );
    }

    // throttle
    if ( m_assignments[ Assignment::ThrottleAxis ].type == Assignment::None )
    {
        getRealValue( Assignment::ThrottleDecrease,
                      Assignment::ThrottleIncrease,
                      m_throttle, m_speedThrottle, 0.0f, 1.0f );
    }

    getAxisValue( m_assignments[ Assignment::ThrottleAxis ], m_throttle, 1 );
}

////////////////////////////////////////////////////////////////////////////////

void Manager::updateMiscActions()
{
    m_trigger_basic = getButtState( m_assignments[ Assignment::TriggerBasic ] );
    m_trigger_extra = getButtState( m_assignments[ Assignment::TriggerExtra ] );
}
