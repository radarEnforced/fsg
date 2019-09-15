#ifndef SIM_MANIPULATORSHIFT_H
#define SIM_MANIPULATORSHIFT_H

////////////////////////////////////////////////////////////////////////////////

#include <osgGA/CameraManipulator>

////////////////////////////////////////////////////////////////////////////////

namespace sim
{

/** Shift view camera manipulator class. */
class ManipulatorShift : public osgGA::CameraManipulator
{
    typedef CameraManipulator inherited;

public:

    /** Constructor. */
    ManipulatorShift();

    /** Constructor. */
    ManipulatorShift( const ManipulatorShift &cmi,
                      const osg::CopyOp &copyOp = osg::CopyOp::SHALLOW_COPY );

    void setByMatrix( const osg::Matrixd &matrix );
    void setByInverseMatrix( const osg::Matrixd &matrix );
    osg::Matrixd getMatrix() const;
    osg::Matrixd getInverseMatrix() const;

    bool handle( const osgGA::GUIEventAdapter &ea,
                 osgGA::GUIActionAdapter &us );

private:

    osg::Matrixd m_matrix;

    /** */
    void updateMatrix();
};

} // end of sim namespace

////////////////////////////////////////////////////////////////////////////////

#endif // SIM_MANIPULATORSHIFT_H
