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
#ifndef DIALOGQUICKACTION_H
#define DIALOGQUICKACTION_H

////////////////////////////////////////////////////////////////////////////////

#include <QDialog>

#include "Scenery.h"
#include "Units.h"

////////////////////////////////////////////////////////////////////////////////

namespace Ui
{
    class DialogQuickAction;
}

////////////////////////////////////////////////////////////////////////////////

class DialogQuickAction : public QDialog
{
    Q_OBJECT

public:

    explicit DialogQuickAction( QWidget *parent = 0 );

    virtual ~DialogQuickAction();

    inline int getIndexScenery() const { return m_index_scenery; }
    inline int getIndexOwnship() const { return m_index_ownship; }
    inline int getIndexWingman() const { return m_index_wingman; }
    inline int getIndexAlly1() const { return m_index_ally_1; }
    inline int getIndexAlly2() const { return m_index_ally_2; }
    inline int getIndexOpponent1() const { return m_index_opponent_1; }
    inline int getIndexOpponent2() const { return m_index_opponent_2; }
    inline int getIndexOpponent3() const { return m_index_opponent_3; }
    inline int getIndexOpponent4() const { return m_index_opponent_4; }

    inline int getIndexLiveryOwnship() const { return m_index_livery_ownship; }
    inline int getIndexLiveryWingman() const { return m_index_livery_wingman; }
    inline int getIndexLiveryAlly1() const { return m_index_livery_ally_1; }
    inline int getIndexLiveryAlly2() const { return m_index_livery_ally_2; }
    inline int getIndexLiveryOpponent1() const { return m_index_livery_opponent_1; }
    inline int getIndexLiveryOpponent2() const { return m_index_livery_opponent_2; }
    inline int getIndexLiveryOpponent3() const { return m_index_livery_opponent_3; }
    inline int getIndexLiveryOpponent4() const { return m_index_livery_opponent_4; }

private:

    Ui::DialogQuickAction *m_ui;

    Scenery *m_scenery;
    Units *m_units;

    int m_index_scenery;
    int m_index_ownship;
    int m_index_wingman;
    int m_index_ally_1;
    int m_index_ally_2;
    int m_index_opponent_1;
    int m_index_opponent_2;
    int m_index_opponent_3;
    int m_index_opponent_4;

    int m_index_livery_ownship;
    int m_index_livery_wingman;
    int m_index_livery_ally_1;
    int m_index_livery_ally_2;
    int m_index_livery_opponent_1;
    int m_index_livery_opponent_2;
    int m_index_livery_opponent_3;
    int m_index_livery_opponent_4;

    void init();

private slots:

    void on_comboBoxScenery_currentIndexChanged( int index );

    void on_comboBoxTypeOwnship_currentIndexChanged( int index );
    void on_comboBoxLiveryOwnship_currentIndexChanged( int index );

    void on_comboBoxTypeWingman_currentIndexChanged( int index );
    void on_comboBoxLiveryWingman_currentIndexChanged( int index );

    void on_comboBoxTypeAlly_1_currentIndexChanged( int index );
    void on_comboBoxLiveryAlly_1_currentIndexChanged( int index );

    void on_comboBoxTypeAlly_2_currentIndexChanged( int index );
    void on_comboBoxLiveryAlly_2_currentIndexChanged( int index );

    void on_comboBoxTypeOpponent_1_currentIndexChanged( int index );
    void on_comboBoxLiveryOpponent_1_currentIndexChanged( int index );

    void on_comboBoxTypeOpponent_2_currentIndexChanged( int index );
    void on_comboBoxLiveryOpponent_2_currentIndexChanged( int index );

    void on_comboBoxTypeOpponent_3_currentIndexChanged( int index );
    void on_comboBoxLiveryOpponent_3_currentIndexChanged( int index );

    void on_comboBoxTypeOpponent_4_currentIndexChanged( int index );
    void on_comboBoxLiveryOpponent_4_currentIndexChanged( int index );
};

////////////////////////////////////////////////////////////////////////////////

#endif // DIALOGQUICKACTION_H
