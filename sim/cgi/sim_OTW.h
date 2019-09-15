#ifndef SIM_OTW_H
#define SIM_OTW_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Group>

#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * @brief Out-the-Window view class.
 * <p>This is parent module for all world sub-modules.</p>
 */
class OTW : public Module
{
public:

    /** Constructor. */
    OTW( float linesWidth, Module *parent = 0 );

    /** Destructor. */
    virtual ~OTW();

    /** Initializes OTW. */
    void init();

private:

    const float m_linesWidth;   ///< [px] lines width
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_OTW_H
