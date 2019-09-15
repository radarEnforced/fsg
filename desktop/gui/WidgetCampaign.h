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
