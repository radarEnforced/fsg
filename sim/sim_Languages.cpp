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

#include <sim/sim_Languages.h>

#include <sim/sim_Base.h>

#include <sim/utils/sim_String.h>
#include <sim/utils/sim_XmlDoc.h>
#include <sim/utils/sim_XmlUtils.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Languages::Languages() :
    m_current ( 0 ),
    m_default ( 0 )
{
    readLanguages();
}

////////////////////////////////////////////////////////////////////////////////

Languages::~Languages() {}

////////////////////////////////////////////////////////////////////////////////

std::string Languages::getCodeByIndex( UInt8 index ) const
{
    if ( index < m_list.size() )
    {
        return m_list.at( index );
    }

    return std::string();
}

////////////////////////////////////////////////////////////////////////////////

int Languages::getIndexByCode( const std::string &code ) const
{
    for ( UInt8 i = 0; i < m_list.size(); i++ )
    {
        if ( 0 == String::icompare( m_list[ i ], code ) )
        {
            return i;
        }
    }

    return -1;
}

////////////////////////////////////////////////////////////////////////////////

bool Languages::isCodeValid( const std::string &code ) const
{
    return -1 != getIndexByCode( code );
}

////////////////////////////////////////////////////////////////////////////////

void Languages::setCurrent( UInt8 current )
{
    if ( current < m_list.size() )
    {
        m_current = current;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Languages::readLanguages()
{
    XmlDoc doc( Base::getPath( "languages.xml" ) );

    if ( doc.isOpen() )
    {
        XmlNode rootNode = doc.getRootNode();

        if ( rootNode.isValid() )
        {
            if ( 0 == String::icompare( rootNode.getName(), "languages" ) )
            {
                XmlNode languageNode = rootNode.getFirstChildElement( "language" );

                while ( languageNode.isValid() )
                {
                    m_list.push_back( languageNode.getAttribute( "code" ) );

                    if ( String::toBool( languageNode.getAttribute( "default" ) ) )
                    {
                        m_default = m_list.size() - 1;
                    }

                    languageNode = languageNode.getNextSiblingElement( "language" );
                }
            }
        }
    }

    m_current = m_default;
}
