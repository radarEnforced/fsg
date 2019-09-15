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

#include <sim/cgi/sim_Module.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Module::Module( osg::Group *root, Module *parent ) :
    m_root ( root ),
    m_parent ( parent )
{
    m_children.clear();
}

////////////////////////////////////////////////////////////////////////////////

Module::~Module()
{
    removeAllChildren();
}

////////////////////////////////////////////////////////////////////////////////

void Module::addChild( Module *child )
{
    if ( child )
    {
        m_children.push_back( child );
        m_root->addChild( child->getNode() );
    }
}

////////////////////////////////////////////////////////////////////////////////

void Module::load()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        (*it)->load();

        ++it;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Module::update()
{
    List::iterator it = m_children.begin();

    while ( it != m_children.end() )
    {
        (*it)->update();

        ++it;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Module::removeAllChildren()
{
    if ( m_root->getNumChildren() > 0 )
    {
        m_root->removeChildren( 0, m_root->getNumChildren() );
    }

    for ( unsigned int i = 0; i < m_children.size(); i++ )
    {
        if ( m_children[ i ] ) delete m_children[ i ];
        m_children[ i ] = 0;
    }

    m_children.clear();
}
