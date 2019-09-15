#ifndef SIM_PID_H
#define SIM_PID_H

////////////////////////////////////////////////////////////////////////////////

#include <limits>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * Proportional-Integral-Derivative controller with anti-windup filter class.
 * @see Duzinkiewicz K., et al.: Zadania do cwiczen laboratoryjnych T10: Sterowanie predkoscia obrotowa silnika pradu stalego, Gdansk, 2016
 */
class PID
{
public:

    /** Constructor. */
    PID( float kp, float ki, float kd,
         float min = std::numeric_limits< float >::min(),
         float max = std::numeric_limits< float >::max(),
         bool reset = false, float coef = 1.0f );

    /** Destructor. */
    virtual ~PID();

    /** Updates controller. */
    void update( float timeStep, float error );

    /** Returns controller output. */
    inline float getValue() const { return m_value; }

    /** Sets controller gains. */
    inline void set( float kp, float ki, float kd )
    {
        m_kp = kp;
        m_ki = ki;
        m_kd = kd;
    }

    inline void setKp( float kp ) { m_kp = kp; }
    inline void setKi( float ki ) { m_ki = ki; }
    inline void setKd( float kd ) { m_kd = kd; }

    inline void setMin( float min ) { m_min = min; }
    inline void setMax( float max ) { m_max = max; }

    inline void setReset( bool reset ) { m_reset = reset; }

    /** Sets controller output (resets integer). */
    void setValue( float value );

private:

    float m_kp;         ///< proportional gain
    float m_ki;         ///< integral gain
    float m_kd;         ///< derivative gain

    float m_min;        ///< minimum output value
    float m_max;        ///< maximum output value

    float m_error;      ///< error
    float m_error_i;    ///< error integral sum
    float m_error_d;    ///< error derivative

    short m_error_s;    ///< error sign

    float m_value;      ///< output value
    float m_delta;      ///< difference between raw and saturated output values

    float m_coef;       ///< reset coefficient

    bool m_reset;       ///< reset integral sum of error on overshoot
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_PID_H
