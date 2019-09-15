#ifndef SIM_FONTS_H
#define SIM_FONTS_H

////////////////////////////////////////////////////////////////////////////////

#include <osgText/Font>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Fonts container class. */
class Fonts : public Singleton< Fonts >
{
    friend class Singleton< Fonts >;

public:

    typedef std::vector< osg::ref_ptr<osgText::Font> > List;

    /** */
    static osgText::Font* get( const std::string &fontFile );

    /** Resets fonts list. */
    static void reset();

private:

    /**
     * You should use static function getInstance() due to get refernce
     * to Fonts class instance.
     */
    Fonts();

    /** Using this constructor is forbidden. */
    Fonts( const Fonts & ) : Singleton< Fonts >() {}

public:

    /** Destructor. */
    virtual ~Fonts();

private:

    List m_fonts;                           ///<
    std::vector< std::string > m_fileNames; ///<
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FONTS_H
