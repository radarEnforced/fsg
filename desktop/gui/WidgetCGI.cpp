#include <gui/WidgetCGI.h>

#include <osg/PositionAttitudeTransform>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osgViewer/ViewerEventHandlers>

#include <hid/hid_Manager.h>
#include <sim/sim_Manager.h>

////////////////////////////////////////////////////////////////////////////////

const double WidgetCGI::m_zNear = 0.55;
const double WidgetCGI::m_zFar  = SIM_SKYDOME_RAD + 0.1f * SIM_SKYDOME_RAD;

////////////////////////////////////////////////////////////////////////////////

WidgetCGI::WidgetCGI( QWidget *parent ) :
    QWidget ( parent ),

    m_gridLayout ( 0 )
{
#   ifdef SIM_OSGDEBUGINFO
    osg::setNotifyLevel( osg::DEBUG_INFO );
#   else
    osg::setNotifyLevel( osg::WARN );
#   endif

    //setThreadingModel( osgViewer::ViewerBase::SingleThreaded );
    setThreadingModel( osgViewer::ViewerBase::ThreadPerContext );

    m_graphicsWin = createGraphicsWindow( x(), y(), width(), height() );

    QWidget *widget = addViewWidget();

    m_gridLayout = new QGridLayout( this );
    m_gridLayout->setContentsMargins( 1, 1, 1, 1 );
    m_gridLayout->addWidget( widget, 0, 0 );

    m_keyHandler = new KeyHandler( this );
    getEventHandlers().push_front( m_keyHandler.get() );

    setLayout( m_gridLayout );
}

////////////////////////////////////////////////////////////////////////////////

WidgetCGI::~WidgetCGI() {}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::init()
{
    removeAllChildren( m_cameraHUD.get() );
    removeAllChildren( m_cameraOTW.get() );

    osg::ref_ptr<osg::Node> nodeHUD = sim::Manager::instance()->getNodeHUD();
    osg::ref_ptr<osg::Node> nodeOTW = sim::Manager::instance()->getNodeOTW();

    if ( nodeHUD.valid() )
    {
        m_cameraHUD->addChild( nodeHUD.get() );
    }

    if ( nodeOTW.valid() )
    {
        setSceneData( nodeOTW.get() );
    }

    setCameraManipulator( sim::Manager::instance()->getCameraManipulator() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::stop()
{
    removeAllChildren( m_cameraHUD.get() );
    removeAllChildren( m_cameraOTW.get() );

    setCameraManipulator( 0 );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::update()
{
    hid::Manager::instance()->setKeysState( m_keyHandler->getKeysState() );

    //////////////////
    QWidget::update();
    //////////////////
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::paintEvent( QPaintEvent *event )
{
    /////////////////////////////
    QWidget::paintEvent( event );
    /////////////////////////////

    frame();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::resizeEvent( QResizeEvent *event )
{
    //////////////////////////////
    QWidget::resizeEvent( event );
    //////////////////////////////

    sim::Manager::instance()->reload();
}

////////////////////////////////////////////////////////////////////////////////

QWidget* WidgetCGI::addViewWidget()
{
    createCameraOTW();
    createCameraHUD();

    addEventHandler( new osgViewer::StatsHandler );
    setKeyEventSetsDone( 0 );

    return m_graphicsWin->getGLWidget();
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::createCameraOTW()
{
    m_cameraOTW = getCamera();

    m_cameraOTW->setGraphicsContext( m_graphicsWin );

    const osg::GraphicsContext::Traits *traits = m_graphicsWin->getTraits();

    float w = traits->width  / 1.0f;
    float h = traits->height / 1.0f;

    m_cameraOTW->setClearColor( osg::Vec4( 0.0, 0.0, 0.0, 1.0 ) );
    //m_cameraOTW->setClearColor( osg::Vec4( 0.47, 0.71, 1.0, 1.0 ) );
    //m_cameraOTW->setClearColor( osg::Vec4( 0.223529, 0.223529, 0.223529, 1.0 ) );
    m_cameraOTW->setViewport( new osg::Viewport( 0, 0, w, h ) );
    m_cameraOTW->setProjectionMatrixAsPerspective( 30.0f, static_cast<double>(traits->width)/static_cast<double>(traits->height), m_zNear, m_zFar );
    m_cameraOTW->setNearFarRatio( m_zNear / m_zFar );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::createCameraHUD()
{
    m_cameraHUD = new osg::Camera();

    m_cameraHUD->setGraphicsContext( m_graphicsWin );

    const osg::GraphicsContext::Traits *traits = m_graphicsWin->getTraits();

    double size = 100.0;
    double w2h = (double)(traits->width) / (double)(traits->height);

    m_cameraHUD->setProjectionMatrixAsOrtho2D( -size * w2h, size * w2h, -size, size );
    m_cameraHUD->setReferenceFrame( osg::Transform::ABSOLUTE_RF );
    m_cameraHUD->setViewMatrix( osg::Matrix::identity() );
//    m_cameraHUD->setClearMask( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT );
    m_cameraHUD->setClearMask( GL_DEPTH_BUFFER_BIT );
    m_cameraHUD->setRenderOrder( osg::Camera::POST_RENDER );
    m_cameraHUD->setAllowEventFocus( false );
    m_cameraHUD->setProjectionResizePolicy( osg::Camera::HORIZONTAL );
    m_cameraHUD->setViewport( new osg::Viewport( 0, 0, traits->width, traits->height ) );

    addSlave( m_cameraHUD, false );
}

////////////////////////////////////////////////////////////////////////////////

osgQt::GraphicsWindowQt* WidgetCGI::createGraphicsWindow( int x, int y, int w, int h,
                                                          const std::string &name,
                                                          bool windowDecoration )
{
    osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits();

    traits->windowName       = name;
    traits->windowDecoration = windowDecoration;
    traits->x                = x;
    traits->y                = y;
    traits->width            = w;
    traits->height           = h;
    traits->doubleBuffer     = true;
    traits->alpha            = osg::DisplaySettings::instance().get()->getMinimumNumAlphaBits();
    traits->stencil          = osg::DisplaySettings::instance().get()->getMinimumNumStencilBits();
    traits->sampleBuffers    = osg::DisplaySettings::instance().get()->getMultiSamples();
    traits->samples          = 4;
    traits->vsync            = true;

    return new osgQt::GraphicsWindowQt( traits.get() );
}

////////////////////////////////////////////////////////////////////////////////

void WidgetCGI::removeAllChildren( osg::Camera *camera )
{
    if ( camera->getNumChildren() > 0 )
    {
        camera->removeChildren( 0, camera->getNumChildren() );
    }
}
