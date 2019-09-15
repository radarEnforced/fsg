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
