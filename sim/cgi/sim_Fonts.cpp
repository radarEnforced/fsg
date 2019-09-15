#include <sim/cgi/sim_Fonts.h>

#include <osgDB/ReadFile>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

osgText::Font* Fonts::get( const std::string &fontFile )
{
    for ( unsigned int i = 0; i < instance()->m_fileNames.size(); i++ )
    {
        if ( fontFile == instance()->m_fileNames.at( i ) )
        {
            return instance()->m_fonts.at( i );
        }
    }

    osg::ref_ptr<osgText::Font> font = osgText::readFontFile( fontFile );

    if ( font.valid() )
    {
        instance()->m_fonts.push_back( font.get() );
        instance()->m_fileNames.push_back( fontFile );

        return font.get();
    }
    else
    {
        osg::notify(osg::ALWAYS) << "ERROR! Cannot open font file: " << fontFile << std::endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

void Fonts::reset()
{
    instance()->m_fileNames.clear();
    instance()->m_fonts.clear();
}

////////////////////////////////////////////////////////////////////////////////

Fonts::Fonts()
{
    m_fileNames.clear();
    m_fonts.clear();
}

////////////////////////////////////////////////////////////////////////////////

Fonts::~Fonts()
{
    m_fileNames.clear();
    m_fonts.clear();
}
