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
#ifndef SIM_SIMULATION_H
#define SIM_SIMULATION_H

////////////////////////////////////////////////////////////////////////////////

#include <sim/sim_Base.h>
#include <sim/sim_Statistics.h>

#include <sim/cgi/sim_Camera.h>
#include <sim/cgi/sim_HUD.h>
#include <sim/cgi/sim_OTW.h>
#include <sim/cgi/sim_UnitViewer.h>

#include <sim/missions/sim_Mission.h>

#include <sim/sfx/sim_SFX.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Main simulation class. */
class Simulation : public Base
{
public:

    /**
     * Constructor.
     * @param width viewport width in pixels
     * @param height viewport height in pixels
     * @param silentMode
     */
    Simulation( int width, int height, bool silentMode );

    /**
     * Constructor.
     * @param width viewport width in pixels
     * @param height viewport height in pixels
     * @param index unit index
     */
    Simulation( int width, int height, UInt32 index );

    /** Destructor. */
    virtual ~Simulation();

    /**
     * Initialized simulation (reads config files, creates scene, etc.).
     */
    void init();

    /**
     * Initialized simulation (reads config files, creates scene, etc.).
     * @param mission_index mission file index
     */
    void init( UInt32 mission_index );

    /**
     * Initialized simulation (reads config files, creates scene, etc.).
     * @param scenery_index scenery index
     * @param type_index_ownship ownship unit type index
     * @param livery_index_ownship ownship livery index
     * @param type_index_wingman wingman unit type index
     * @param livery_index_wingman wingman livery index
     * @param type_index_ally_1 1st ally unit type index
     * @param livery_index_ally_1 1st ally livery index
     * @param type_index_ally_2 2nd ally unit type index
     * @param livery_index_ally_2 2nd ally livery index
     * @param type_index_enemy_1 1st enemy unit type index
     * @param livery_index_enemy_1 1st enemy livery index
     * @param type_index_enemy_2 1nd enemy unit type index
     * @param livery_index_enemy_2 1nd enemy livery index
     * @param type_index_enemy_3 3rd enemy unit type index
     * @param livery_index_enemy_3 3rd enemy livery index
     * @param type_index_enemy_4 4th enemy unit type index
     * @param livery_index_enemy_4 4th enemy livery index
     */
    void init( int scenery_index,
               int type_index_ownship , int livery_index_ownship,
               int type_index_wingman , int livery_index_wingman,
               int type_index_ally_1  , int livery_index_ally_1,
               int type_index_ally_2  , int livery_index_ally_2,
               int type_index_enemy_1 , int livery_index_enemy_1,
               int type_index_enemy_2 , int livery_index_enemy_2,
               int type_index_enemy_3 , int livery_index_enemy_3,
               int type_index_enemy_4 , int livery_index_enemy_4 );

    /** Loads and reloads simulation (models, textures, etc.). */
    void load();

    /** Pauses simulation. */
    void pause();

    /** Unpauses simulation. */
    void unpause();

    /** Restarts simulation after freeze (resumes sound replaying, etc.). */
    void restart();

    /**
     * Updates simulation.
     * @param timeStep [s] simulation time step
     */
    void update( double timeStep );

    /** */
    inline osgGA::CameraManipulator* getCameraManipulator()
    {
        if ( m_viewerMode )
        {
            return m_viewer->getCameraManipulator();
        }
        else
        {
            return m_camera->getManipulator();
        }
    }

    inline osg::Group* getNodeHUD()    { return m_hud->getNode(); }
    inline osg::Group* getNodeOTW()    { return m_otw->getNode(); }
    inline osg::Group* getNodeViewer() { return m_viewer->getNode(); }

    inline bool getSilentMode() const { return m_silentMode; }
    inline bool getViewerMode() const { return m_viewerMode; }

    inline UInt32 getOrbitedUnitId() const { return m_orbitedUnitId; }

    /** Resets unit viewer camera position and attitude. */
    inline void resetViewer()
    {
        if ( m_viewer ) m_viewer->resetViewer();
    }

    void setViewChase();
    void setViewFlyby();
    void setViewFront();
    void setViewOrbit();
    void setViewPilot();
    void setViewShift();
    void setViewWorld();

    /** Toggles through units to be orbited. */
    void toggleOrbitUnit();

private:

    typedef std::vector< std::string > Missions;

    Missions m_missions;        ///< missions files list

    OTW *m_otw;                 ///< Out-the-Window
    HUD *m_hud;                 ///< Head-up-Display
    SFX *m_sfx;                 ///< sound effects

    UnitViewer *m_viewer;       ///< unit viewer

    Camera  *m_camera;          ///< camera control
    Mission *m_mission;         ///< mission management

    bool m_silentMode;          ///< specifies if silent mode is active
    bool m_viewerMode;          ///< specified if viewer mode is active

    UInt32 m_orbitedUnitId;     ///< current orbited unit ID

    /** Using this constructor is forbidden. */
    Simulation( const Simulation & ) {}

    /**
     * @brief create
     * @param width viewport width in pixels
     * @param height viewport height in pixels
     * @param mission
     */
    void createSimulation( int width, int height );

    /** Reads campaign XML file and initializes missions files list.*/
    void readMissions();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_SIMULATION_H
