#include <iostream>

#include <QApplication>
#include <QDir>
#include <QMetaType>

#include <defs.h>

#include <gui/MainWindow.h>

////////////////////////////////////////////////////////////////////////////////

/** This is application main function. */
int main( int argc, char *argv[] )
{
    setlocale( LC_ALL, "C" );

#   ifdef _LINUX_
    setenv( "LC_NUMERIC", "en_US", 1 );
#   endif

    QApplication *app = new QApplication( argc, argv );

    app->setApplicationName( SIM_APP_NAME   );
    app->setApplicationVersion( SIM_APP_VER    );
    app->setOrganizationDomain( SIM_ORG_DOMAIN );
    app->setOrganizationName( SIM_ORG_NAME   );

    MainWindow *win = new MainWindow();

    win->show();
    win->init();

    int result = app->exec();

    delete win; win = 0;
    delete app; app = 0;

    return result;
}
