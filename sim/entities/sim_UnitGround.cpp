#include <sim/entities/sim_UnitGround.h>
#include <sim/entities/sim_WreckageSurface.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

UnitGround::UnitGround( Affiliation affiliation ) : UnitSurface( affiliation ) {}

////////////////////////////////////////////////////////////////////////////////

UnitGround::~UnitGround() {}

////////////////////////////////////////////////////////////////////////////////

void UnitGround::destroy()
{
    if ( isActive() )
    {
        WreckageSurface *wreckage = new WreckageSurface( m_model.get() );
        wreckage->setPos( m_pos );
        wreckage->setAtt( m_att );

        if ( m_ownship )
        {
            wreckage->setName( "ownship" );
        }
    }

    ///////////////////////
    UnitSurface::destroy();
    ///////////////////////
}
