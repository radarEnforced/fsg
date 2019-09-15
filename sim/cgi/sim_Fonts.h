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
#ifndef SIM_FONTS_H
#define SIM_FONTS_H

////////////////////////////////////////////////////////////////////////////////

#include <osgText/Font>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Fonts container class. */
class Fonts : public Singleton< Fonts >
{
    friend class Singleton< Fonts >;

public:

    typedef std::vector< osg::ref_ptr<osgText::Font> > List;

    /** */
    static osgText::Font* get( const std::string &fontFile );

    /** Resets fonts list. */
    static void reset();

private:

    /**
     * You should use static function getInstance() due to get refernce
     * to Fonts class instance.
     */
    Fonts();

    /** Using this constructor is forbidden. */
    Fonts( const Fonts & ) : Singleton< Fonts >() {}

public:

    /** Destructor. */
    virtual ~Fonts();

private:

    List m_fonts;                           ///<
    std::vector< std::string > m_fileNames; ///<
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FONTS_H
