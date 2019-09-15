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
