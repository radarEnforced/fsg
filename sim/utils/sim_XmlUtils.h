#ifndef SIM_XMLUTILS_H
#define SIM_XMLUTILS_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/sim_Types.h>

#include <sim/utils/sim_Text.h>
#include <sim/utils/sim_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** XML utilities class. */
class XmlUtils
{
public:

    /** @return SIM_SUCCESS on success or SIM_FAILURE on failure. */
    static int read( const XmlNode &node, int &value );

    /** @return SIM_SUCCESS on success or SIM_FAILURE on failure. */
    static int read(const XmlNode &node, float &value );

    /** @return SIM_SUCCESS on success or SIM_FAILURE on failure. */
    static int read( const XmlNode &node, std::string &str );

    /** @return SIM_SUCCESS on success or SIM_FAILURE on failure. */
    static int read( const XmlNode &node, Text &text );

    /** @return FDM_SUCCESS on success or FDM_FAILURE on failure. */
    static int read( const XmlNode &node, Vec3 &vect );
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_XMLUTILS_H
