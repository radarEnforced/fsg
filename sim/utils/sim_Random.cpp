#include <sim/utils/sim_Random.h>

#include <stdlib.h>
#include <time.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Random::Random()
{
    srand( time( NULL ) );
}

////////////////////////////////////////////////////////////////////////////////

Random::~Random() {}

////////////////////////////////////////////////////////////////////////////////

int Random::getRandom( int min, int max )
{
    if ( max > 0 && max > min && max <= RAND_MAX )
    {
        return min + rand() % ( max - min + 1 );
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

float Random::getRandom( float min, float max )
{
    int random = getRandom( 0, RAND_MAX );

    return min + ( max - min ) * ( (float)random / (float)RAND_MAX );
}
