#ifndef DIALOGCTRL_H
#define DIALOGCTRL_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>
#include <QSettings>

#include <defs.h>

#include <hid/hid_Assignment.h>

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogCtrl;
}

////////////////////////////////////////////////////////////////////////////////

/** This is 'Preferences' dialog class. */
class DialogCtrl : public QDialog
{
    Q_OBJECT

public:

    /** Constructor. */
    explicit DialogCtrl( QWidget *parent = 0 );
    
    /** Destructor. */
    virtual ~DialogCtrl();

    /** */
    void getAssignments( hid::Assignment assignments[] );

    void readData();
    void saveData();

    void updateAssignments();
    
private:

    Ui::DialogCtrl *m_ui;

    bool m_defaultAssignmentsInited;

    bool m_comboDeviceInited;

    std::string     m_actionNames[ HID_MAX_ACTIONS ];
    hid::Assignment m_assignments[ HID_MAX_ACTIONS ];

    bool isButtonAssignmentClearEnabled( int action );
    bool isButtonAssignmentChangeEnabled( int action, int device );

    void changeAssignment( int action );
    void clearAssignment( int action );

    void createTableControls();
    void updateTableControls();

    void setButtonsState( int action, int device );

    void settingsRead();
    void settingsSave();

    void initDefaultAssignments();

    void assignmentsRead( QSettings &settings );
    void assignmentsSave( QSettings &settings );

    void assignmentRead( QSettings &settings, hid::Assignment &assignment, hid::Assignment::Action action );
    void assignmentSave( QSettings &settings, hid::Assignment &assignment, hid::Assignment::Action action );

private slots:

    void on_buttonAssignmentClear_clicked();
    void on_buttonAssignmentChange_clicked();
    void on_comboDevice_currentIndexChanged( int index );
    void on_tableControls_cellDoubleClicked( int row, int );
    void on_tableControls_currentCellChanged( int row, int, int, int );
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGCTRL_H
