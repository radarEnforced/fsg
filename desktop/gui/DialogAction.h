#ifndef DIALOGACTION_H
#define DIALOGACTION_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include <hid/hid_Manager.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogAction;
}

////////////////////////////////////////////////////////////////////////////////

/** */
class DialogAction : public QDialog
{
    Q_OBJECT

public:

    static hid::Assignment getJoyAxisAssignment( QWidget *parent = 0, hid::Assignment assignment = hid::Assignment(), short joystickId = 0 );
    static hid::Assignment getJoyButtAssignment( QWidget *parent = 0, hid::Assignment assignment = hid::Assignment(), short joystickId = 0 );
    static hid::Assignment getKeyAssignment( QWidget *parent = 0, hid::Assignment assignment = hid::Assignment() );

    explicit DialogAction( QWidget *parent = 0, short joystickId = -1 );

    ~DialogAction();

protected:

    void timerEvent( QTimerEvent *event );

private:

    Ui::DialogAction *m_ui;

    int m_timerId;

    short m_keyId;

    short m_axisCount;
    short m_buttCount;
    short m_povsCount;

    short m_joystickId;
    short m_axisId;
    short m_buttonId;
    short m_povId;
    hid::Assignment::POVs m_povDir;
    bool  m_inverted;

private slots:

    void on_comboAxis_currentIndexChanged( int index );
    void on_comboButt_currentIndexChanged( int index );
    void on_comboKeys_currentIndexChanged( int index );
    void on_checkAxisInverted_toggled( bool checked );
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGACTION_H
