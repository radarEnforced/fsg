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
#ifndef HID_MANAGER_H
#define HID_MANAGER_H

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <sim/utils/sim_Singleton.h>

#include "hid_Assignment.h"

////////////////////////////////////////////////////////////////////////////////

namespace hid
{

/** HID manager class. */
class Manager : public sim::Singleton< Manager >
{
    friend class sim::Singleton< Manager >;

public:

    static const std::string m_actionNames[ HID_MAX_ACTIONS ];
    static const std::string m_keysNames[ HID_MAX_KEYS ];

    /** */
    static Assignment::POVs getPOV( short pov_deg );

    /** */
    static bool isAxis( Assignment::Action action );

private:

    /** Using this constructor is forbidden. */
    Manager( const Manager & ) : sim::Singleton< Manager >() {}

    /** Constructor. */
    Manager();

public:

    /** Destructor. */
    virtual ~Manager();

    /** */
    void init();

    /** */
    void update( double timeStep );

    inline bool getTriggerBasic() const { return m_trigger_basic; }
    inline bool getTriggerExtra() const { return m_trigger_extra; }

    inline float getCtrlRoll()  const { return m_ctrlRoll;  }
    inline float getCtrlPitch() const { return m_ctrlPitch; }
    inline float getCtrlYaw()   const { return m_ctrlYaw;   }
    inline float getThrottle()  const { return m_throttle;  }

    void setThrottle( float throttle );

    /** */
    void setAssingment( Assignment::Action action, const Assignment &assignment );

    /** */
    inline void setKeysState( const bool *keysState )
    {
        for ( int i = 0; i < HID_MAX_KEYS; i++ )
        {
            m_keysState[ i ] = keysState[ i ];
        }
    }

private:

    Assignment m_assignments[ HID_MAX_ACTIONS ];

    bool m_keysState[ HID_MAX_KEYS ];

    bool m_trigger_basic;       ///< primary trigger
    bool m_trigger_extra;       ///< secondary trigger

    float m_speedControls;      ///< [1/s]
    float m_speedThrottle;      ///< [1/s]

    double m_timeStep;          ///< [s]

    float m_ctrlRoll;           ///< -1.0 ... 1.0
    float m_ctrlPitch;          ///< -1.0 ... 1.0
    float m_ctrlYaw;            ///< -1.0 ... 1.0
    float m_throttle;           ///<  0.0 ... 1.0

    /** */
    void getAxisValue( const Assignment &assignment, float &value, int absolute = 0 );

    /** */
    void getCtrlValue( Assignment::Action decreaseAction,
                       Assignment::Action increaseAction,
                       float &value,
                       float speed,
                       float min,
                       float max );

    /** */
    void getRealValue( Assignment::Action decreaseAction,
                       Assignment::Action increaseAction,
                       float &value,
                       float speed,
                       float min,
                       float max );

    /** */
    void getRealValue( Assignment::Action applyAction,
                       float &value,
                       float speed,
                       float min,
                       float max );

    /** */
    void getRealValue( Assignment::Action toggleAction,
                       bool  &togglePrev,
                       bool  &state,
                       float &value,
                       float speed,
                       float min,
                       float max );

    /** */
    bool getButtState( const Assignment &assignment );

    /** */
    void reset();

    /** */
    void updateAxisActions();

    /** */
    void updateMiscActions();
};

} // end of hid namepsace

////////////////////////////////////////////////////////////////////////////////

#endif // HID_MANAGER_H
