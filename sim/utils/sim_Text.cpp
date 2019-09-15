#include <sim/utils/sim_Text.h>

#include <sim/sim_Languages.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

Text::Text() {}

////////////////////////////////////////////////////////////////////////////////

Text::Text( const Text &text )
{
    m_strings = text.m_strings;
}

////////////////////////////////////////////////////////////////////////////////

Text::~Text() {}

////////////////////////////////////////////////////////////////////////////////

void Text::append( const char *str )
{
    for ( Strings::iterator it = m_strings.begin(); it != m_strings.end(); it++ )
    {
        it->second += str;
    }
}

////////////////////////////////////////////////////////////////////////////////

void Text::append( const std::string &str )
{
    append( str.c_str() );
}

////////////////////////////////////////////////////////////////////////////////

void Text::append( const Text &text )
{
    if ( m_strings.size() == text.m_strings.size() )
    {
        Strings::iterator it = m_strings.begin();
        Strings::const_iterator it_src = text.m_strings.begin();

        while ( it != m_strings.end() && it_src != text.m_strings.end() )
        {
            it->second += it_src->second;

            it++;
            it_src++;
        }
    }
}

////////////////////////////////////////////////////////////////////////////////

std::string Text::get() const
{
    Strings::const_iterator it = m_strings.find( Languages::instance()->getCurrent() );

    if ( it != m_strings.end() )
    {
        return it->second;
    }

    return std::string();
}

////////////////////////////////////////////////////////////////////////////////

void Text::set( UInt8 index, const std::string &str )
{
    Strings::iterator it = m_strings.find( index );

    if ( it != m_strings.end() )
    {
        it->second = str;
    }
    else
    {
        m_strings.insert( std::pair< UInt8, std::string >( index, str ) );
    }
}
