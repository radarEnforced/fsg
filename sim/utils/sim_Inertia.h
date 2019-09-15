#ifndef SIM_INERTIA_H
#define SIM_INERTIA_H

////////////////////////////////////////////////////////////////////////////////

#include <math.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Inertia template class. */
template < class TYPE >
class Inertia
{
public:

    /** Static inertia function. */
    static TYPE update( TYPE timeStep, TYPE currentValue,
                        TYPE newValue, TYPE timeConstant )
    {
        return currentValue + ( 1.0 - exp( -timeStep / timeConstant ) ) * ( newValue - currentValue );
    }

    /** Constructor. */
    Inertia() :
        m_timeConstant( 1.0 ),
        m_currentValue( 0.0 )
    {}

    /** Constructor. */
    Inertia( TYPE timeConstant, TYPE currentValue = 0.0 ) :
        m_timeConstant( timeConstant ),
        m_currentValue( currentValue )
    {}

    /** Updates value due to time step and time constant. */
    void update( TYPE timeStep, TYPE newValue )
    {
        m_currentValue = update( timeStep, m_currentValue, newValue, m_timeConstant );
    }

    /** Returns inertia output. */
    inline TYPE getValue() const { return m_currentValue; }

    /** Sets inertia output. */
    inline void setValue( TYPE newValue ) { m_currentValue = newValue; }

private:

    TYPE m_timeConstant;    ///< time constant
    TYPE m_currentValue;    ///< current value

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_INERTIA_H
