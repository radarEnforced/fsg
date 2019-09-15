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
#ifndef WIDGETCGI_H
#define WIDGETCGI_H

////////////////////////////////////////////////////////////////////////////////

#include <QDateTime>
#include <QGridLayout>
#include <QWidget>

#include <osgViewer/Viewer>
#include <osgGA/GUIEventHandler>
#include <osgQt/GraphicsWindowQt>

#include <hid/hid_Assignment.h>

////////////////////////////////////////////////////////////////////////////////

/** This is widget wrapper for CGI. */
class WidgetCGI : public QWidget, public osgViewer::Viewer
{
    Q_OBJECT

public:

    static const double m_zNear;
    static const double m_zFar;

    /** */
    class KeyHandler : public osgGA::GUIEventHandler
    {
    public:

        /** */
        KeyHandler( WidgetCGI *widgetCGI );

        /** */
        inline const bool* getKeysState() const { return m_keysState; }

        /** */
        bool handle( const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter & );

    private:

        WidgetCGI *m_widgetCGI;

        bool m_keysState[ HID_MAX_KEYS ];

        bool handleKeyDn( const osgGA::GUIEventAdapter &ea );
        bool handleKeyUp( const osgGA::GUIEventAdapter &ea );
    };

    /** Constructor. */
    WidgetCGI( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~WidgetCGI();

    /** */
    void init();

    /** */
    void stop();

    /** */
    void update();

protected:

    /** */
    void paintEvent( QPaintEvent *event );

    /** */
    void resizeEvent( QResizeEvent *event );

private:

    QGridLayout *m_gridLayout;

    osg::ref_ptr<osgQt::GraphicsWindowQt> m_graphicsWin;
    osg::ref_ptr<KeyHandler> m_keyHandler;

    osg::ref_ptr<osg::Camera> m_cameraOTW;
    osg::ref_ptr<osg::Camera> m_cameraHUD;

    QWidget* addViewWidget();

    void createCameraOTW();
    void createCameraHUD();

    osgQt::GraphicsWindowQt* createGraphicsWindow( int x, int y, int w, int h,
                                                   const std::string &name = "",
                                                   bool windowDecoration = false );

    void removeAllChildren( osg::Camera *camera );
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETCGI_H
