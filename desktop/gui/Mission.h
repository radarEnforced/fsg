#ifndef MISSION_H
#define MISSION_H

////////////////////////////////////////////////////////////////////////////////

#include <QDomElement>
#include <QFileInfo>
#include <QMap>

////////////////////////////////////////////////////////////////////////////////

class Mission
{
public:

    typedef QMap< int, QString > Text;

    Mission();

    Mission( const Mission &mission );

    Mission( const QFileInfo &fileInfo );

    inline QFileInfo getFileInfo() const { return m_fileInfo; }

    QString getName() const;

    QString getIntroduction() const;

    QString getSummaryFailure() const;
    QString getSummarySuccess() const;

private:

    QFileInfo m_fileInfo;       ///< mission file info

    Text m_name;                ///< mission name
    Text m_introduction;        ///< mission introduction
    Text m_summaryFailure;      ///< mission summary failure
    Text m_summarySuccess;      ///< mission summaru success

    void readText( const QDomElement &node, Text &text );
};

////////////////////////////////////////////////////////////////////////////////

#endif // MISSION_H
