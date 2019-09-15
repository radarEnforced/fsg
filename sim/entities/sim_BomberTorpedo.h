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
#ifndef SIM_BOMBERTORPEDO_H
#define SIM_BOMBERTORPEDO_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/entities/sim_Bomber.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Torpedo bomber class. */
class BomberTorpedo : public Bomber
{
public:

    static const std::string m_tagName; ///<

    static const float m_dropAltMin;    ///< [m]
    static const float m_dropAltMax;    ///< [m]
    static const float m_dropDistMax;   ///< [m]
    static const float m_tanMaxTht;     ///<

    /** Constructor. */
    BomberTorpedo( Affiliation affiliation = Unknown );

    /** Destructor. */
    virtual ~BomberTorpedo();

    /**
     * Reads bomber data.
     * @return SIM_SUCCESS on success or SIM_FAILURE on failure.
     */
    virtual int read( const XmlNode &node );

protected:

    bool m_attack;          ///< specifies if aircraft is attacking

    virtual void limitTht( float &tht );

    virtual void updateTarget();
    virtual void updateWeapons();

};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_BOMBERTORPEDO_H
