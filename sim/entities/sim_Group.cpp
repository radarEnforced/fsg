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

#include <sim/entities/sim_Group.h>

#include <sim/entities/sim_Entity.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Group::Group( Group *parent ) :
    m_parent ( parent )
{
    m_root = new osg::Group();

    m_children.clear();
}

////////////////////////////////////////////////////////////////////////////////

Group::~Group()
{
    deleteAllEntities();
}

////////////////////////////////////////////////////////////////////////////////

void Group::attachEntity( Entity *entity )
{
    if ( entity )
    {
        m_children.push_back( entity );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Group::deleteAllEntities()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        if ( *it ) delete (*it);
        (*it) = 0;

        it = m_children.erase( it );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Group::deleteEntity( Entity *entity )
{
    if ( entity )
    {
        List::iterator it = m_children.begin();

        while ( it != m_children.end() )
        {
            if ( (*it) == entity )
            {
                if ( *it ) delete (*it);
                (*it) = 0;
                m_children.erase( it );

                return;
            }

            ++it;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

void Group::dettachEntity( Entity *entity )
{
    if ( entity )
    {
        List::iterator it = m_children.begin();

        while ( it != m_children.end() )
        {
            if ( (*it) == entity )
            {
                m_children.erase( it );

                return;
            }

            ++it;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

Group::List* Group::getEntities()
{
    return &( m_children );
}

////////////////////////////////////////////////////////////////////////////////

Entity* Group::getEntityById( UInt32 id )
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        if ( (*it)->getId() == id )
        {
            return (*it);
        }

        ++it;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Group::load()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        if ( (*it) )
        {
            (*it)->load();
        }

        ++it;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Group::update( double timeStep )
{
    List::iterator it = m_children.begin();

    // delete innactive entities (before updating)
    while ( it != m_children.end() )
    {
        if ( (*it) )
        {
            if ( (*it)->getState() == Inactive )
            {
                delete (*it);
                (*it) = 0;
                it = m_children.erase( it );
            }
            else
            {
                ++it;
            }
        }
    }

    // due to the fact that vector can be modified in update loop.
    List children = m_children;

    // updating after deleting due to keep innactive entities for one more step
    for ( List::iterator it = children.begin(); it != children.end(); ++it )
    {
        if ( (*it)->isActive() ) (*it)->update( timeStep );
    }
}
