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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

////////////////////////////////////////////////////////////////////////////////

#include <QDomElement>
#include <QElapsedTimer>
#include <QMainWindow>
#include <QSettings>
#include <QShortcut>
#include <QTime>
//#include <QTimer>

#include <defs.h>

#include "DialogCtrl.h"
#include "DialogData.h"

#include "DialogQuickAction.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class MainWindow;
}

////////////////////////////////////////////////////////////////////////////////

/** This is main window class. */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    typedef QVector< QString > Units;

    /** Constructor. */
    explicit MainWindow( QWidget *parent = 0 );

    /** Destructor. */
    virtual ~MainWindow();

    /** */
    void init();

protected:

    /** */
    void closeEvent( QCloseEvent *event );

    /** */
    void timerEvent( QTimerEvent *event );

private:

    Ui::MainWindow *m_ui;                   ///<

    DialogCtrl *m_dialogCtrl;               ///<
    DialogData *m_dialogData;               ///<

    DialogQuickAction *m_dialogQuickAction; ///<

    QShortcut *m_shortcutPause;             ///<
    QShortcut *m_shortcutAbort;             ///<

    QShortcut *m_shortcutAuto;              ///<

    QShortcut *m_shortcutCtrl;              ///<
    QShortcut *m_shortcutData;              ///<
    QShortcut *m_shortcutExit;              ///<

    QShortcut *m_shortcutViewFull;          ///<
    QShortcut *m_shortcutViewToggle;        ///<

    QShortcut *m_shortcutTimeFaster;        ///<
    QShortcut *m_shortcutTimeSlower;        ///<

    QElapsedTimer *m_timer;                 ///<
    int m_timerId;                          ///< timer ID

    Units m_units;                          ///<

    double m_timeCoef;                      ///<

    bool m_autopilot;                       ///<

    bool m_inited;                          ///<
    bool m_paused;                          ///<

    bool m_throttleInited;                  ///<

    bool m_fullScreen;                      ///<

    bool m_pending;                         ///< specifies if mission is pending

    float m_heading;                        ///< [rad] last valid heading

    void askIfAbort();

    void initUnits();

    void readUnits( QDomElement &node );

    void settingsRead();
    void settingsSave();

    void simulationStart();
    void simulationPause();
    void simulationAbort();

    void toggleAutopilot();

private slots:

    void dialogQuickAction_accepted();
    void dialogQuickAction_rejected();

    void on_actionStart_triggered();
    void on_actionPause_triggered();
    void on_actionAbort_triggered();

    void on_actionAuto_triggered();

    void on_actionCtrl_triggered();
    void on_actionData_triggered();
    void on_actionQuit_triggered();

    void on_actionViewChase_triggered();
    void on_actionViewFlyby_triggered();
    void on_actionViewFront_triggered();
    void on_actionViewOrbit_triggered();
    void on_actionViewPilot_triggered();
    void on_actionViewShift_triggered();
    void on_actionViewWorld_triggered();

    void on_actionViewToggle_triggered();

    void on_actionViewFull_triggered();

    void on_actionTimeFaster_triggered();
    void on_actionTimeSlower_triggered();

    void on_comboBoxLanguage_currentIndexChanged( int index );

    void on_pushButtonStartCampaign_clicked();
    void on_pushButtonStartQuickAction_clicked();
    void on_pushButtonStartUnitView_clicked();

    void on_widgetCampaign_changed();
};

////////////////////////////////////////////////////////////////////////////////

#endif // MAINWINDOW_H
