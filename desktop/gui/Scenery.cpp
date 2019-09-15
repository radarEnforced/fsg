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

#include "Scenery.h"

#include <QDomElement>
#include <QDir>
#include <QFile>

#include <sim/sim_Base.h>

////////////////////////////////////////////////////////////////////////////////

Scenery::Scenery()
{
    readScenery();
}

////////////////////////////////////////////////////////////////////////////////

unsigned int Scenery::getCount()
{
    return m_sceneryList.size();
}

////////////////////////////////////////////////////////////////////////////////

QString Scenery::getSceneryName( unsigned int index )
{
    return m_sceneryList[ index ];
}

////////////////////////////////////////////////////////////////////////////////

void Scenery::readScenery()
{
    QDir dir( sim::Base::getPath( "" ).c_str() );
    QFile file( dir.filePath( "scenery.xml" ) );

    if ( file.open(QFile::ReadOnly | QFile::Text) )
    {
        QDomDocument doc;

        doc.setContent( &file, false );

        QDomElement rootNode = doc.documentElement();

        if ( rootNode.tagName() == "scenery_list" )
        {
            QDomElement sceneryNode = rootNode.firstChildElement( "scenery" );

            while ( !sceneryNode.isNull() )
            {
                m_sceneryList.push_back( sceneryNode.attributeNode( "name" ).value() );

                sceneryNode = sceneryNode.nextSiblingElement( "scenery" );
            }
        }
    }
}
