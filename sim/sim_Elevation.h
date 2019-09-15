#ifndef SIM_ELEVATION_H
#define SIM_ELEVATION_H

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Ground elevation class. */
class Elevation : public Singleton< Elevation >
{
    friend class Singleton< Elevation >;

private:

    /** Constructor. */
    Elevation();

public:

    /** Destructor. */
    virtual ~Elevation();

    /** Returns terrain elevation at given coordinates. */
    float getElevation( float x, float y );

    /** Reads ground elevation data file. */
    void readFile( const std::string &fileName );

    /** Resets ground elevation data. */
    void reset();

private:

    bool m_valid;   ///< specifies if elevation data is valid

    int m_num;      ///< number of nodes along side

    float m_half;   ///< [m] half size (maximum valid range)
    float m_side;   ///< [m] side length
    float m_step;   ///< [m] nodes step

    float *m_elev;  ///< [m] ground elevation data array
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_ELEVATION_H
