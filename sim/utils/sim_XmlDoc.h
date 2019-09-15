#ifndef SIM_XMLDOC_H
#define SIM_XMLDOC_H

////////////////////////////////////////////////////////////////////////////////

#include <string>

#include <libxml/tree.h>

#include <sim/utils/sim_XmlNode.h>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** XML document class. */
class XmlDoc
{
public:

    /** Constrcutor. */
    XmlDoc( const std::string &fileName );

    /** Destrcutor. */
    virtual ~XmlDoc();

    /** Returns XML document root element. */
    inline XmlNode getRootNode()
    {
        return XmlNode( *m_root );
    }

    /** Returns true if XML document is open. */
    inline bool isOpen() const
    {
        return m_open;
    }

    /** @return SIM_SUCCESS on success, SIM_FAILURE on failure. */
    int readFile( const std::string &fileName );

private:

    xmlDocPtr m_doc;    ///< libxml document pointer

    bool m_open;        ///< specifies if document is open

    XmlNode *m_root;    ///< XML document root element pointer
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_XMLDOC_H
