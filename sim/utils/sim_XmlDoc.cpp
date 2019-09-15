#include <sim/utils/sim_XmlDoc.h>

#include <sim/sim_Defs.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

XmlDoc::XmlDoc( const std::string &fileName ) :
    m_doc  ( 0 ),
    m_open ( false ),
    m_root ( 0 )
{
    readFile( fileName );
}

////////////////////////////////////////////////////////////////////////////////

XmlDoc::~XmlDoc()
{
    if ( m_root ) delete m_root;
    m_root = 0;

    xmlFreeDoc( m_doc );
}

////////////////////////////////////////////////////////////////////////////////

int XmlDoc::readFile( const std::string &fileName )
{
    m_doc = xmlParseFile( fileName.c_str() );

    if ( m_doc == 0 )
    {
        xmlFreeDoc( m_doc );
        return SIM_FAILURE;
    }

    xmlNodePtr root = xmlDocGetRootElement( m_doc );

    if ( root == 0 )
    {
        xmlFreeNode( root );
        xmlFreeDoc( m_doc );
        return SIM_FAILURE;
    }

    m_root = new XmlNode( root, fileName );

    m_open = true;

    return SIM_SUCCESS;
}
