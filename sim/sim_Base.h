#ifndef SIM_BASE_H
#define SIM_BASE_H

////////////////////////////////////////////////////////////////////////////////

#include <memory.h>
#include <string>

#include <sim/sim_Defs.h>
#include <sim/sim_Types.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Base class. */
class Base
{
public:

    /**
     * Returns file path prefixed with base path.
     * @param path file path relative to the base path.
     */
    inline static std::string getPath( const std::string &path )
    {
        return m_basePath + path;
    }

    /**
     * @brief setBasePath
     * @param basePath
     */
    inline static void setBasePath( const std::string &basePath )
    {
        m_basePath = basePath;
    }

    /** Overloaded operator which initializes memory. */
    void* operator new( size_t st )
    {
        void *pv = ::operator new( st );
        if ( pv ) memset( pv , 0 , st );
        return pv;
    }

private:

    static std::string m_basePath;
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BASE_H
