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
#ifndef SIM_CAPTIONS_H
#define SIM_CAPTIONS_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <sim/sim_Types.h>

#include <sim/utils/sim_Singleton.h>
#include <sim/utils/sim_Text.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** */
class Captions : public sim::Singleton< Captions >
{
    friend class sim::Singleton< Captions >;

private:

    /** Default constructor. */
    Captions();

    /** Copy constructor. */
    Captions( const Captions & ) : sim::Singleton< Captions >() {}

public:

    /** Destructor. */
    virtual ~Captions();

    inline std::string getLoading() const { return m_loading.get(); }
    inline std::string getResume() const { return m_resume.get(); }
    inline std::string getBegin() const { return m_begin.get(); }
    inline std::string getMissionAccomplished() const { return m_mission_accomplished.get(); }
    inline std::string getMissionFailed() const { return m_mission_failed.get(); }
    inline std::string getFriendlyFire() const { return m_friendly_fire.get(); }
    inline std::string getTargetKilled() const { return m_target_killed.get(); }
    inline std::string getTargetHit() const { return m_target_hit.get(); }

private:

    Text m_loading;
    Text m_resume;
    Text m_begin;
    Text m_mission_accomplished;
    Text m_mission_failed;
    Text m_friendly_fire;
    Text m_target_killed;
    Text m_target_hit;

    void readCaptions();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_CAPTIONS_H
