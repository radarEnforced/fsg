#include <sim/cgi/sim_Textures.h>

#include <osgDB/ReadFile>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

osg::Texture2D* Textures::get( const std::string &textureFile, float maxAnisotropy,
                               osg::Texture::WrapMode mode )
{
    for ( unsigned int i = 0; i < instance()->m_fileNames.size(); i++ )
    {
        if ( textureFile == instance()->m_fileNames.at( i ) )
        {
            instance()->m_textures.at( i )->setMaxAnisotropy( maxAnisotropy );
            return instance()->m_textures.at( i );
        }
    }

    osg::ref_ptr<osg::Image> image = osgDB::readImageFile( textureFile );

    if ( image.valid() )
    {
        osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D();
        texture->setImage( image.get() );

        texture->setWrap( osg::Texture2D::WRAP_S, mode );
        texture->setWrap( osg::Texture2D::WRAP_T, mode );

        texture->setNumMipmapLevels( 4 );
        texture->setMaxAnisotropy( maxAnisotropy );

        texture->setFilter( osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_NEAREST );
        texture->setFilter( osg::Texture::MAG_FILTER, osg::Texture::LINEAR );

        texture->setUnRefImageDataAfterApply( false );

        instance()->m_textures.push_back( texture.get() );
        instance()->m_fileNames.push_back( textureFile );

        return texture.get();
    }
    else
    {
        osg::notify(osg::ALWAYS) << "ERROR! Cannot open texture file: " << textureFile << std::endl;
    }

    return 0;
}

////////////////////////////////////////////////////////////////////////////////

Textures::Textures()
{
    m_fileNames.clear();
    m_textures.clear();
}

////////////////////////////////////////////////////////////////////////////////

Textures::~Textures() {}
