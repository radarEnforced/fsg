#ifndef SIM_TEXTURES_H
#define SIM_TEXTURES_H

////////////////////////////////////////////////////////////////////////////////

#include <osg/Texture2D>

#include <sim/utils/sim_Singleton.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Textures container class. */
class Textures : public Singleton< Textures >
{
    friend class Singleton< Textures >;

public:

    typedef std::vector< osg::ref_ptr<osg::Texture2D> > List;

    /** */
    static osg::Texture2D* get( const std::string &textureFile, float maxAnisotropy = 1.0f,
                                osg::Texture::WrapMode mode = osg::Texture::MIRROR );

private:

    /**
     * You should use static function getInstance() due to get refernce
     * to Textures class instance.
     */
    Textures();

    /** Using this constructor is forbidden. */
    Textures( const Textures & ) : Singleton< Textures >() {}

public:

    /** Destructor. */
    virtual ~Textures();

private:

    List m_textures;                        ///<
    std::vector< std::string > m_fileNames; ///<
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_TEXTURES_H
