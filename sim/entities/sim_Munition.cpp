#include <sim/entities/sim_Munition.h>

#include <sim/cgi/sim_Models.h>
#include <sim/entities/sim_Entities.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Munition::Munition( UInt16 dp, UInt32 shooterId, float life_span, Group *parent ) :
    Entity( parent, Active, life_span ),

    m_dp ( dp ),
    m_shooterId ( shooterId )
{}

////////////////////////////////////////////////////////////////////////////////

Munition::~Munition() {}

////////////////////////////////////////////////////////////////////////////////

void Munition::load()
{
    if ( m_model.valid() )
    {
        m_switch->removeChild( m_model.get() );
    }

    m_model = Models::get( m_modelFile );

    if ( m_model.valid() )
    {
        m_switch->addChild( m_model.get() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Munition::update( double timeStep )
{
    ///////////////////////////
    Entity::update( timeStep );
    ///////////////////////////

    if ( isActive() )
    {
        if ( isTopLevel() )
        {
            List::iterator it = Entities::instance()->getEntities()->begin();

            while ( it != Entities::instance()->getEntities()->end() )
            {
                Unit *target = dynamic_cast< Unit* >(*it);

                if ( target )
                {
                    if ( target->isActive() )
                    {
                        Vec3 v1 = m_att * ( m_vel * timeStep );
                        Vec3 v2 = target->getPos() - m_pos;

                        float len1 = v1.length();

                        Vec3 v1_norm = v1 * (1.0/len1);

                        float proj2 = v2 * v1_norm;

                        if ( proj2 >= 0.0 && proj2 <= len1 )
                        {
                            float dist2 = ( v2 - v1_norm * proj2 ).length2();

                            if ( dist2 < target->getRadius2() && m_shooterId != target->getId() )
                            {
                                hit( target );
                                setState( Inactive );
                                break;
                            }
                        }
                    }
                }

                ++it;
            }
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Munition::setModelFile( const std::string &modelFile )
{
    m_modelFile = modelFile;
    load();
}

////////////////////////////////////////////////////////////////////////////////

void Munition::hit( Unit *target )
{
    target->hit( m_dp, this );
    reportTargetHit( target );
}

////////////////////////////////////////////////////////////////////////////////

void Munition::reportTargetHit( Unit *target )
{
    Unit *shooter = dynamic_cast< Unit* >( Entities::instance()->getEntityById( m_shooterId ) );

    if ( shooter )
    {
        shooter->reportTargetHit( target );
    }
}
