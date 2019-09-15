#include <sim/cgi/sim_ManipulatorShift.h>

////////////////////////////////////////////////////////////////////////////////

using namespace sim;

////////////////////////////////////////////////////////////////////////////////

ManipulatorShift::ManipulatorShift() :
    inherited()
{}

////////////////////////////////////////////////////////////////////////////////

ManipulatorShift::ManipulatorShift( const ManipulatorShift &cmi, const osg::CopyOp &copyOp ) :
    osg::Object( cmi, copyOp ),
    inherited( cmi, copyOp ),
    m_matrix( cmi.m_matrix )
{}

////////////////////////////////////////////////////////////////////////////////

void ManipulatorShift::setByMatrix( const osg::Matrixd &matrix )
{
    m_matrix = matrix;
}

////////////////////////////////////////////////////////////////////////////////

void ManipulatorShift::setByInverseMatrix( const osg::Matrixd &matrix )
{
    setByMatrix( osg::Matrixd::inverse( matrix ) );
}

////////////////////////////////////////////////////////////////////////////////

osg::Matrixd ManipulatorShift::getMatrix() const
{
    return m_matrix;
}

////////////////////////////////////////////////////////////////////////////////

osg::Matrixd ManipulatorShift::getInverseMatrix() const
{
    return osg::Matrixd::inverse( m_matrix );
}

////////////////////////////////////////////////////////////////////////////////

bool ManipulatorShift::handle( const osgGA::GUIEventAdapter &ea,
                               osgGA::GUIActionAdapter &/*us*/ )
{
    switch ( ea.getEventType() )
    {
    case osgGA::GUIEventAdapter::FRAME:
        updateMatrix();
        return false;
        break;
    default:
        break;
    }

    return false;
}

////////////////////////////////////////////////////////////////////////////////

void ManipulatorShift::updateMatrix() {}
