#ifndef UNITS_H
#define UNITS_H

////////////////////////////////////////////////////////////////////////////////

#include <QString>
#include <QVector>

////////////////////////////////////////////////////////////////////////////////

class Units
{
public:

    struct UnitData
    {
        unsigned int index;
        bool fighter;
        QString name;
        QVector< QString > liveries;
    };

    Units();

    unsigned int getCountUnitData();
    unsigned int getCountAllyData();
    unsigned int getCountOpponent();
    unsigned int getCountPlayable();

    UnitData getUnitData( unsigned int index );
    UnitData getAllyData( unsigned int index );
    UnitData getOpponent( unsigned int index );
    UnitData getPlayable( unsigned int index );

private:

    QVector< UnitData > m_unitsData;
    QVector< UnitData > m_allyData;
    QVector< UnitData > m_opponents;
    QVector< UnitData > m_playables;

    void readUnits();
};

////////////////////////////////////////////////////////////////////////////////

#endif // UNITS_H
