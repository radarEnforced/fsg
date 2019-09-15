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
