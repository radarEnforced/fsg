#include <hid/hid_Joysticks.h>

#include <math.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>

////////////////////////////////////////////////////////////////////////////////

using namespace hid;

////////////////////////////////////////////////////////////////////////////////

#ifdef HID_LINUX_JOYSTICK
const std::string Joysticks::m_axisNames[] = { "X", "Y", "Z",
                                               "RX", "RY", "RZ",
                                               "Throttle",
                                               "Rudder",
                                               "Wheel",
                                               "Gas",
                                               "Brake",
                                               "Hat0X", "Hat0Y",
                                               "Hat1X", "Hat1Y",
                                               "Hat2X", "Hat2Y",
                                               "Hat3X", "Hat3Y",
                                               "Pressure",
                                               "Distance",
                                               "Tilt X", "Tilt Y",
                                               "Tool Width"
                                             };
#endif

#ifdef HID_WINMM_JOYSTICK
const std::string Joysticks::m_axisNames[] = { "X", "Y", "Z",
                                               "R", "U", "V" };
#endif

////////////////////////////////////////////////////////////////////////////////

Joysticks::Joysticks() :
    m_joysCount ( 0 )
{
#   ifdef HID_WINMM_JOYSTICK
    m_buttons[  0 ] = JOY_BUTTON1;
    m_buttons[  1 ] = JOY_BUTTON2;
    m_buttons[  2 ] = JOY_BUTTON3;
    m_buttons[  3 ] = JOY_BUTTON4;
    m_buttons[  4 ] = JOY_BUTTON5;
    m_buttons[  5 ] = JOY_BUTTON6;
    m_buttons[  6 ] = JOY_BUTTON7;
    m_buttons[  7 ] = JOY_BUTTON8;
    m_buttons[  8 ] = JOY_BUTTON9;
    m_buttons[  9 ] = JOY_BUTTON10;
    m_buttons[ 10 ] = JOY_BUTTON11;
    m_buttons[ 11 ] = JOY_BUTTON12;
    m_buttons[ 12 ] = JOY_BUTTON13;
    m_buttons[ 13 ] = JOY_BUTTON14;
    m_buttons[ 14 ] = JOY_BUTTON15;
    m_buttons[ 15 ] = JOY_BUTTON16;
    m_buttons[ 16 ] = JOY_BUTTON17;
    m_buttons[ 17 ] = JOY_BUTTON18;
    m_buttons[ 18 ] = JOY_BUTTON19;
    m_buttons[ 19 ] = JOY_BUTTON20;
    m_buttons[ 20 ] = JOY_BUTTON21;
    m_buttons[ 21 ] = JOY_BUTTON22;
    m_buttons[ 22 ] = JOY_BUTTON23;
    m_buttons[ 23 ] = JOY_BUTTON24;
    m_buttons[ 24 ] = JOY_BUTTON25;
    m_buttons[ 25 ] = JOY_BUTTON26;
    m_buttons[ 26 ] = JOY_BUTTON27;
    m_buttons[ 27 ] = JOY_BUTTON28;
    m_buttons[ 28 ] = JOY_BUTTON29;
    m_buttons[ 29 ] = JOY_BUTTON30;
    m_buttons[ 30 ] = JOY_BUTTON31;
    m_buttons[ 31 ] = JOY_BUTTON32;

#       if ( HID_MAX_BUTT != 32 )
#           error 'HID_MAX_BUTT' has been changed! Check code following this line!
#       endif
#   endif

    for ( int i = 0; i < HID_MAX_JOYS; i++ )
    {
        m_joyData[ i ].name = "";

        for ( int a = 0; a < HID_MAX_AXES; a++ ) m_joyData[ i ].axis[ a ] = 0.0f;
        for ( int b = 0; b < HID_MAX_BUTT; b++ ) m_joyData[ i ].butt[ b ] = false;
        for ( int p = 0; p < HID_MAX_POVS; p++ ) m_joyData[ i ].povs[ p ] = -1;

        m_joyData[ i ].axisCount = 0;
        m_joyData[ i ].buttCount = 0;
        m_joyData[ i ].povsCount = 0;

        m_joyData[ i ].active   = false;
        m_joyData[ i ].feedback = false;

        for ( int a = 0; a < HID_MAX_AXES; a++ ) m_joyData[ i ].hasAxis[ a ] = false;

#       ifdef HID_LINUX_JOYSTICK
        for ( short i_pov = 0; i_pov < HID_MAX_POVS; i_pov++ )
        {
            m_joyData[ i ].hasPOV[ i_pov ] = false;
        }

        m_joysFD[ i ] = 0;
#       endif

#       ifdef HID_WINMM_JOYSTICK
        m_joyData[ i ].hasPOV = false;
#       endif
    }
}

////////////////////////////////////////////////////////////////////////////////

Joysticks::~Joysticks() {}

////////////////////////////////////////////////////////////////////////////////

#ifdef HID_LINUX_JOYSTICK
void Joysticks::init()
{
    for ( int i = 0; i < HID_MAX_JOYS; i++ )
    {
        char tempDev[ 255 ];

        sprintf( tempDev, "/dev/input/js%d", i );

        int joyFD = open( tempDev, O_NONBLOCK );

        if ( joyFD > 0 )
        {
            m_joysFD[ m_joysCount ] = joyFD;

            char tempAxisCount = 0;
            char tempButtCount = 0;
            char tempName[ 512 ];
            char tempAxesMap[ HID_MAX_AXES + 2 * HID_MAX_POVS ];

            ioctl( m_joysFD[ m_joysCount ], JSIOCGAXES     , &tempAxisCount );
            ioctl( m_joysFD[ m_joysCount ], JSIOCGBUTTONS  , &tempButtCount );
            ioctl( m_joysFD[ m_joysCount ], JSIOCGNAME(64) , tempName );
            ioctl( m_joysFD[ m_joysCount ], JSIOCGAXMAP    , tempAxesMap );

            m_joyData[ m_joysCount ].name = tempName;

            m_joyData[ m_joysCount ].axisCount = std::min( (int)tempAxisCount, HID_MAX_AXES );
            m_joyData[ m_joysCount ].buttCount = std::min( (int)tempButtCount, HID_MAX_BUTT );
            m_joyData[ m_joysCount ].povsCount = 0;

            m_joyData[ m_joysCount ].active   = true;
            m_joyData[ m_joysCount ].feedback = false;

            for ( int j = 0; j < HID_MAX_AXES + 2 * HID_MAX_POVS; j++ )
            {
                switch ( tempAxesMap[ j ] )
                {
                case ABS_X:
                    m_joyData[ m_joysCount ].hasAxis[ AxisX ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = AxisX;
                    break;

                case ABS_Y:
                    m_joyData[ m_joysCount ].hasAxis[ AxisY ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = AxisY;
                    break;

                case ABS_Z:
                    m_joyData[ m_joysCount ].hasAxis[ AxisZ ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = AxisZ;
                    break;

                case ABS_RX:
                    m_joyData[ m_joysCount ].hasAxis[ AxisRX ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = AxisRX;
                    break;

                case ABS_RY:
                    m_joyData[ m_joysCount ].hasAxis[ AxisRY ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = AxisRY;
                    break;

                case ABS_RZ:
                    m_joyData[ m_joysCount ].hasAxis[ AxisRZ ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = AxisRZ;
                    break;

                case ABS_THROTTLE:
                    m_joyData[ m_joysCount ].hasAxis[ Throttle ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Throttle;
                    break;

                case ABS_RUDDER:
                    m_joyData[ m_joysCount ].hasAxis[ Rudder ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Rudder;
                    break;

                case ABS_WHEEL:
                    m_joyData[ m_joysCount ].hasAxis[ Wheel ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Wheel;
                    break;

                case ABS_GAS:
                    m_joyData[ m_joysCount ].hasAxis[ Gas ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Gas;
                    break;

                case ABS_BRAKE:
                    m_joyData[ m_joysCount ].hasAxis[ Brake ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Brake;
                    break;

                case ABS_HAT0X:
                    m_joyData[ m_joysCount ].hasAxis[ Hat0X ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat0X;
                    break;

                case ABS_HAT0Y:
                    m_joyData[ m_joysCount ].hasAxis[ Hat0Y ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat0Y;
                    break;

                case ABS_HAT1X:
                    m_joyData[ m_joysCount ].hasAxis[ Hat1X ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat1X;
                    break;

                case ABS_HAT1Y:
                    m_joyData[ m_joysCount ].hasAxis[ Hat1Y ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat1Y;
                    break;

                case ABS_HAT2X:
                    m_joyData[ m_joysCount ].hasAxis[ Hat2X ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat2X;
                    break;

                case ABS_HAT2Y:
                    m_joyData[ m_joysCount ].hasAxis[ Hat2Y ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat2Y;
                    break;

                case ABS_HAT3X:
                    m_joyData[ m_joysCount ].hasAxis[ Hat3X ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat3X;
                    break;

                case ABS_HAT3Y:
                    m_joyData[ m_joysCount ].hasAxis[ Hat3Y ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Hat3Y;
                    break;

                case ABS_PRESSURE:
                    m_joyData[ m_joysCount ].hasAxis[ Pressure ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Pressure;
                    break;

                case ABS_DISTANCE:
                    m_joyData[ m_joysCount ].hasAxis[ Distance ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = Distance;
                    break;

                case ABS_TILT_X:
                    m_joyData[ m_joysCount ].hasAxis[ TiltX ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = TiltX;
                    break;

                case ABS_TILT_Y:
                    m_joyData[ m_joysCount ].hasAxis[ TiltY ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = TiltY;
                    break;

                case ABS_TOOL_WIDTH:
                    m_joyData[ m_joysCount ].hasAxis[ ToolWidth ] = true;
                    m_joyData[ m_joysCount ].axesMap[ j ] = ToolWidth;
                    break;
                }
            }

            if ( m_joyData[ m_joysCount ].hasAxis[ Hat0X ]
              || m_joyData[ m_joysCount ].hasAxis[ Hat0Y ] )
            {
                m_joyData[ m_joysCount ].hasPOV[ 0 ] = true;
                m_joyData[ m_joysCount ].povsCount++;
            }

            if ( m_joyData[ m_joysCount ].hasAxis[ Hat1X ]
              || m_joyData[ m_joysCount ].hasAxis[ Hat1Y ] )
            {
                m_joyData[ m_joysCount ].hasPOV[ 1 ] = true;
                m_joyData[ m_joysCount ].povsCount++;
            }

            if ( m_joyData[ m_joysCount ].hasAxis[ Hat2X ]
              || m_joyData[ m_joysCount ].hasAxis[ Hat2Y ] )
            {
                m_joyData[ m_joysCount ].hasPOV[ 2 ] = true;
                m_joyData[ m_joysCount ].povsCount++;
            }

            if ( m_joyData[ m_joysCount ].hasAxis[ Hat3X ]
              || m_joyData[ m_joysCount ].hasAxis[ Hat3Y ] )
            {
                m_joyData[ m_joysCount ].hasPOV[ 3 ] = true;
                m_joyData[ m_joysCount ].povsCount++;
            }

            m_joysCount++;
        }
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef HID_WINMM_JOYSTICK
void Joysticks::init()
{
    UINT joyIdTemp = JOYSTICKID1;
    JOYCAPS joyCaps;

    for ( int i = 0; i < HID_MAX_JOYS; i++ )
    {
        if ( m_joysCount > (short)joyGetNumDevs() ) break;

        if ( joyGetDevCaps( joyIdTemp, &joyCaps, sizeof(JOYCAPS) ) == JOYERR_NOERROR )
        {
            char tempNameChar[ MAXPNAMELEN ];

            for ( int j = 0; j < MAXPNAMELEN; j++ )
            {
                tempNameChar[ j ] = (char)joyCaps.szPname[ j ];
                if ( tempNameChar[ j ] == '\0' ) break;
            }

            //if ( joySetCapture( winId, joyIdTemp, 10, false ) == JOYERR_NOERROR )
            {
                m_joyData[ m_joysCount ].name = tempNameChar;

                m_joyData[ m_joysCount ].axisCount = joyCaps.wNumAxes;
                m_joyData[ m_joysCount ].buttCount = joyCaps.wNumButtons;
                m_joyData[ m_joysCount ].povsCount = 0;

                m_joyData[ m_joysCount ].active   = true;
                m_joyData[ m_joysCount ].feedback = false;

                m_joyData[ m_joysCount ].hasAxis[ AxisX ] = true;
                m_joyData[ m_joysCount ].hasAxis[ AxisY ] = true;

                if ( joyCaps.wCaps & JOYCAPS_HASZ ) m_joyData[ m_joysCount ].hasAxis[ AxisZ ] = true;
                if ( joyCaps.wCaps & JOYCAPS_HASR ) m_joyData[ m_joysCount ].hasAxis[ AxisR ] = true;
                if ( joyCaps.wCaps & JOYCAPS_HASU ) m_joyData[ m_joysCount ].hasAxis[ AxisU ] = true;
                if ( joyCaps.wCaps & JOYCAPS_HASV ) m_joyData[ m_joysCount ].hasAxis[ AxisZ ] = true;

                if ( joyCaps.wCaps & JOYCAPS_HASPOV )
                {
                    m_joyData[ m_joysCount ].hasPOV = true;
                    m_joyData[ m_joysCount ].povsCount = 1;
                }

                m_joysCount++;
            }
        }

        if ( joyIdTemp == JOYSTICKID2 ) break;
        if ( joyIdTemp == JOYSTICKID1 ) joyIdTemp = JOYSTICKID2;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef HID_LINUX_JOYSTICK
void Joysticks::update()
{
    for( short i = 0; i < m_joysCount && i < HID_MAX_JOYS; i++ )
    {
        while( read( m_joysFD[ i ], &m_joyEvent, sizeof(js_event) ) > 0 )
        {
            // buttons
            if ( m_joyEvent.type == JS_EVENT_BUTTON )
            {
                if ( m_joyEvent.number < HID_MAX_BUTT )
                {
                    m_joyData[ i ].butt[ m_joyEvent.number ] = ( m_joyEvent.value ) ? 1 : 0;
                }
            }

            // axes
            if ( m_joyEvent.type == JS_EVENT_AXIS )
            {
                float value = m_joyEvent.value / (double)HID_AXIS_RANGE;

                switch ( m_joyData[ i ].axesMap[ m_joyEvent.number ] )
                {
                    case AxisX:  m_joyData[ i ].axis[ AxisX  ] = value; break;
                    case AxisY:  m_joyData[ i ].axis[ AxisY  ] = value; break;
                    case AxisZ:  m_joyData[ i ].axis[ AxisZ  ] = value; break;
                    case AxisRX: m_joyData[ i ].axis[ AxisRX ] = value; break;
                    case AxisRY: m_joyData[ i ].axis[ AxisRY ] = value; break;
                    case AxisRZ: m_joyData[ i ].axis[ AxisRZ ] = value; break;

                    case Throttle: m_joyData[ i ].axis[ Throttle ] = value; break;
                    case Rudder:   m_joyData[ i ].axis[ Rudder   ] = value; break;
                    case Gas:      m_joyData[ i ].axis[ Gas      ] = value; break;
                    case Wheel:    m_joyData[ i ].axis[ Wheel    ] = value; break;
                    case Brake:    m_joyData[ i ].axis[ Brake    ] = value; break;

                    case Hat0X: m_joyData[ i ].axis[ Hat0X ] = value; break;
                    case Hat0Y: m_joyData[ i ].axis[ Hat0Y ] = value; break;
                    case Hat1X: m_joyData[ i ].axis[ Hat1X ] = value; break;
                    case Hat1Y: m_joyData[ i ].axis[ Hat1Y ] = value; break;
                    case Hat2X: m_joyData[ i ].axis[ Hat2X ] = value; break;
                    case Hat2Y: m_joyData[ i ].axis[ Hat2Y ] = value; break;
                    case Hat3X: m_joyData[ i ].axis[ Hat3X ] = value; break;
                    case Hat3Y: m_joyData[ i ].axis[ Hat3Y ] = value; break;

                    case Pressure:  m_joyData[ i ].axis[ Pressure  ] = value; break;
                    case Distance:  m_joyData[ i ].axis[ Distance  ] = value; break;
                    case TiltX:     m_joyData[ i ].axis[ TiltX     ] = value; break;
                    case TiltY:     m_joyData[ i ].axis[ TiltY     ] = value; break;
                    case ToolWidth: m_joyData[ i ].axis[ ToolWidth ] = value; break;
                }

                for ( short i_pov = 0; i_pov < HID_MAX_POVS; i_pov++ )
                {
                    m_joyData[ i ].povs[ i_pov ] = -1;

                    if ( m_joyData[ i ].hasPOV[ i_pov ]
                         && (
                                m_joyData[ i ].axis[ Hat0X + i_pov ] != 0.0f
                             || m_joyData[ i ].axis[ Hat0Y + i_pov ] != 0.0f
                            )
                       )
                    {
                        float angle_rad = atan2( m_joyData[ i ].axis[ Hat0X + i_pov ],
                                                -m_joyData[ i ].axis[ Hat0Y + i_pov ] );

                        short angle_deg = 180 * angle_rad / M_PI;

                        while ( angle_deg <   0 ) angle_deg += 360;
                        while ( angle_deg > 360 ) angle_deg -= 360;

                        m_joyData[ i ].povs[ i_pov ] = angle_deg;
                    }
                }
            }
        }
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

#ifdef HID_WINMM_JOYSTICK
void Joysticks::update()
{
    JOYINFOEX joyInfoEx;

    joyInfoEx.dwSize = sizeof(JOYINFOEX);
    joyInfoEx.dwFlags = JOY_RETURNALL;

    UINT joyIdTemp = JOYSTICKID1;

    for ( int i = 0; i < m_joysCount; i++ )
    {
        if ( joyGetPosEx( joyIdTemp, &joyInfoEx ) == JOYERR_NOERROR )
        {
            for ( int j = 0; j < m_joyData[ i ].buttCount; j++ )
            {
                m_joyData[ i ].butt[ j ] = ( m_buttons[ j ] & joyInfoEx.dwButtons ) ? 1 : 0;
            }
        }

        m_joyData[ i ].axis[ AxisX ] = 2.0f * ( (float)joyInfoEx.dwXpos / HID_AXIS_RANGE ) - 1.0f;
        m_joyData[ i ].axis[ AxisY ] = 2.0f * ( (float)joyInfoEx.dwYpos / HID_AXIS_RANGE ) - 1.0f;

        if ( m_joyData[ i ].hasAxis[ AxisZ ] ) m_joyData[ i ].axis[ AxisZ ] = 2.0f * ( (float)joyInfoEx.dwZpos / HID_AXIS_RANGE ) - 1.0f;
        if ( m_joyData[ i ].hasAxis[ AxisR ] ) m_joyData[ i ].axis[ AxisR ] = 2.0f * ( (float)joyInfoEx.dwRpos / HID_AXIS_RANGE ) - 1.0f;
        if ( m_joyData[ i ].hasAxis[ AxisU ] ) m_joyData[ i ].axis[ AxisU ] = 2.0f * ( (float)joyInfoEx.dwUpos / HID_AXIS_RANGE ) - 1.0f;
        if ( m_joyData[ i ].hasAxis[ AxisV ] ) m_joyData[ i ].axis[ AxisV ] = 2.0f * ( (float)joyInfoEx.dwVpos / HID_AXIS_RANGE ) - 1.0f;

        m_joyData[ i ].povs[ 0 ] = -1;

        if ( m_joyData[ i ].hasPOV && joyInfoEx.dwPOV != JOY_POVCENTERED )
        {
            m_joyData[ i ].povs[ 0 ] = (short)( joyInfoEx.dwPOV / 100 );
        }

        if ( joyIdTemp == JOYSTICKID2 ) break;
        if ( joyIdTemp == JOYSTICKID1 ) joyIdTemp = JOYSTICKID2;
    }
}
#endif

////////////////////////////////////////////////////////////////////////////////

short Joysticks::getJoysCount() const
{
    return m_joysCount;
}

////////////////////////////////////////////////////////////////////////////////

Joysticks::Data Joysticks::getJoyData( short joyNum ) const
{
    if ( joyNum < 0 && joyNum >= HID_MAX_JOYS )
    {
        std::cerr << "ERROR! Wrong joystick index number." << std::endl;

#       ifdef HID_EXITONERROR
        exit( EXIT_FAILURE );
#       endif
    }

    return m_joyData[ joyNum ];
}
