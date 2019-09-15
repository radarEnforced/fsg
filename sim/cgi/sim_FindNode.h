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
#ifndef SIM_FINDNODE_H
#define SIM_FINDNODE_H

////////////////////////////////////////////////////////////////////////////////

#include <string>
#include <vector>

#include <osg/NodeVisitor>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Finding node visitor class. */
class FindNode : public osg::NodeVisitor
{
public:

    typedef std::vector< osg::ref_ptr<osg::Node> > Nodes;

    /** */
    static osg::Node* findFirst( osg::Node* node, const std::string &name );

    /** */
    static Nodes findNodes( osg::Node* node, const std::string &name );

    /** Constructor. */
    FindNode();

    /** Constructor. */
    FindNode( const std::string &name, bool findAll = false );

    /** */
    virtual void apply( osg::Node &searchNode );

    /** Returns first found node. */
    osg::ref_ptr<osg::Node> getFirst();

    /** Returns list of found nodes. */
    Nodes getNodes();

private:

    bool m_findAll;     ///< specifies if search should be continued after finding first matching node
    std::string m_name; ///< name of the nodes to be looking for
    Nodes m_nodes;      ///< found nodes list
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_FINDNODE_H
