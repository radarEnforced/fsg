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
#ifndef HID_ASSIGNMENT_H
#define HID_ASSIGNMENT_H

////////////////////////////////////////////////////////////////////////////////

#define HID_MAX_ACTIONS 14
#define HID_MAX_KEYS    57

////////////////////////////////////////////////////////////////////////////////

namespace hid
{

/** */
struct Assignment
{
    /** */
    enum Action
    {
        TriggerBasic     = 0,   ///< 0:  Primary Trigger
        TriggerExtra     = 1,   ///< 1:  Secondary Trigger
        RollAxis         = 2,   ///< 2:  Roll (Axis)
        RollBankLeft     = 3,   ///< 3:  Roll: Bank Left
        RollBankRight    = 4,   ///< 4:  Roll: Bank Right
        PitchAxis        = 5,   ///< 5:  Pitch (Axis)
        PitchNoseUp      = 6,   ///< 6:  Pitch: Nose Up
        PitchNoseDown    = 7,   ///< 7:  Pitch: Nose Down
        YawAxis          = 8,   ///< 8:  Yaw (Axis)
        YawTurnLeft      = 9,   ///< 9:  Yaw: Turn Left
        YawTurnRight     = 10,  ///< 10: Yaw: Turn Right
        ThrottleAxis     = 11,  ///< 11: Throttle (Axis)
        ThrottleIncrease = 12,  ///< 12: Throttle: Increase
        ThrottleDecrease = 13   ///< 13: Throttle: Decrease
    };

#   if ( HID_MAX_ACTIONS != 14 )
#       error 'HID_MAX_ACTIONS' has been changed! Check code above this line!
#   endif

    /** */
    enum DeviceType
    {
        None     = 0,               ///< 0: none
        Keyboard = 1,               ///< 1: keyboard
        Joystick = 2                ///< 2: joystick
    };

    /** */
    enum Key
    {
        Key0 = 0,                   ///< 0:  "0"
        Key1,                       ///< 1:  "1"
        Key2,                       ///< 2:  "2"
        Key3,                       ///< 3:  "3"
        Key4,                       ///< 4:  "4"
        Key5,                       ///< 5:  "5"
        Key6,                       ///< 6:  "6"
        Key7,                       ///< 7:  "7"
        Key8,                       ///< 8:  "8"
        Key9,                       ///< 9:  "9"

        KeyA,                       ///< 10: "a"
        KeyB,                       ///< 11: "b"
        KeyC,                       ///< 12: "c"
        KeyD,                       ///< 13: "d"
        KeyE,                       ///< 14: "e"
        KeyF,                       ///< 15: "f"
        KeyG,                       ///< 16: "g"
        KeyH,                       ///< 17: "h"
        KeyI,                       ///< 18: "i"
        KeyJ,                       ///< 19: "j"
        KeyK,                       ///< 20: "k"
        KeyL,                       ///< 21: "l"
        KeyM,                       ///< 22: "m"
        KeyN,                       ///< 23: "n"
        KeyO,                       ///< 24: "o"
        KeyP,                       ///< 25: "p"
        KeyQ,                       ///< 26: "q"
        KeyR,                       ///< 27: "r"
        KeyS,                       ///< 28: "s"
        KeyT,                       ///< 29: "t"
        KeyU,                       ///< 30: "u"
        KeyV,                       ///< 31: "v"
        KeyW,                       ///< 32: "w"
        KeyX,                       ///< 33: "x"
        KeyY,                       ///< 34: "y"
        KeyZ,                       ///< 35: "z"

        KeyBackquote,               ///< 36: "`"
        KeyMinus,                   ///< 37: "-"
        KeyEquals,                  ///< 38: "="
        KeyLeftBracket,             ///< 39: "["
        KeyRightBracket,            ///< 40: "]"
        KeySemicolon,               ///< 41: ";"
        KeyQuote,                   ///< 42: "'"
        KeyComma,                   ///< 43: ","
        KeyPeriod,                  ///< 44: "."
        KeySlash,                   ///< 45: "/"

        KeySpace,                   ///< 46: space

        KeyLeft,                    ///< 47: left
        KeyRight,                   ///< 48: right
        KeyUp,                      ///< 49: up
        KeyDown,                    ///< 50: down

        KeyInsert,                  ///< 51: insert
        KeyDelete,                  ///< 52: delete
        KeyHome,                    ///< 53: home
        KeyEnd,                     ///< 54: end
        KeyPageUp,                  ///< 55: page up
        KeyPageDown                 ///< 56: page down
    };

#   if ( HID_MAX_KEYS != 57 )
#       error 'HID_MAX_KEYS' has been changed! Check code following this line!
#   endif

    /** */
    enum POVs
    {
        Centered = 0x00,            ///<
        North    = 0x01,            ///<
        East     = 0x02,            ///<
        South    = 0x04,            ///<
        West     = 0x08,            ///<

        NorthEast = North | East,   ///<
        SouthEast = South | East,   ///<
        SouthWest = South | West,   ///<
        NorthWest = North | West    ///<
    };

    /** */
    struct KeyboardData
    {
        short keyId;                ///< key ID
    };

    /** */
    struct JoystickData
    {
        short joystickId;           ///< joystick ID
        short axisId;               ///< axis ID
        bool  inverted;             ///< is inverted
        short buttonId;             ///< button ID
        short povId;                ///< POV ID
        POVs  direction;            ///< POV direction
    };

    /** */
    union DeviceData
    {
        KeyboardData keyboard;      ///< keyboard data
        JoystickData joystick;      ///< joystick data
    };

    DeviceType type;                ///< input device type
    DeviceData data;                ///< input device data
};

} // end of hid namepsace

////////////////////////////////////////////////////////////////////////////////

#endif // HID_ASSIGNMENT_H
