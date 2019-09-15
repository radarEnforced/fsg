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
#ifndef SIM_ANGLES_H
#define SIM_ANGLES_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Quat>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/**
 * Bryant (rotation angles in z-y-x convention) angles class.
 * @see https://en.wikipedia.org/wiki/Euler_angles
 */
class Angles
{
public:

    /** Constructor. */
    Angles();

    /** Copy constructor. */
    Angles( const Angles &angl );

    /**
     * Constructor.
     * @param [rad] angle of rotation along x-axis
     * @param [rad] angle of rotation along y-axis
     * @param [rad] angle of rotation along z-axis
     */
    Angles( double phi, double tht, double psi );

    /** Constructor. */
    Angles( const osg::Quat &quat );

    /** Normalizes angles. */
    void normalize();

    inline double   phi() const { return m_phi; }
    inline double   tht() const { return m_tht; }
    inline double   psi() const { return m_psi; }
    inline double & phi()       { return m_phi; }
    inline double & tht()       { return m_tht; }
    inline double & psi()       { return m_psi; }

    osg::Quat getRotate() const;

    /** Sets angles values. */
    void set( double phi, double tht, double psi );

    /** */
    void set( const osg::Quat &quat );

    /** Assignment operator. */
    Angles& operator= ( const Angles &angl );

    /** Equality operator. */
    bool operator== ( const Angles &angl ) const;

    /** Inequality operator. */
    bool operator!= ( const Angles &angl ) const;

private:

    double m_phi;   ///< [rad] angle of rotation about x-axis
    double m_tht;   ///< [rad] angle of rotation about y-axis
    double m_psi;   ///< [rad] angle of rotation about z-axis
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_ANGLES_H
