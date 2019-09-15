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
#ifndef WIDGETCAMPAIGN_H
#define WIDGETCAMPAIGN_H

////////////////////////////////////////////////////////////////////////////////

#include <QWidget>

#include "Mission.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class WidgetCampaign;
}

////////////////////////////////////////////////////////////////////////////////

/** */
class WidgetCampaign : public QWidget
{
    Q_OBJECT

public:

    typedef QVector< Mission > Missions;

    /** */
    explicit WidgetCampaign( QWidget *parent = 0 );

    /** */
    ~WidgetCampaign();

    /** */
    void reinit();

    inline int getMissionIndex() const { return m_missionIndex; }

signals:

    void changed();

private:

    Ui::WidgetCampaign *m_ui;   ///<

    Missions m_missions;        ///<

    int m_missionIndex;         ///< current mission index

    void initMissions();

private slots:

    void on_listWidgetMissions_currentRowChanged( int currentRow );
};

////////////////////////////////////////////////////////////////////////////////

#endif // WIDGETCAMPAIGN_H
