/*
 *  Copyright (C) 2002 Roberto Raggi (roberto@kdevelop.org)
 *
 *  This program is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; see the file COPYING.  If not, write to
 *  the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 *  Boston, MA 02111-1307, USA.
 *
 */

/**********************************************************************
** Copyright (C) 2000 Trolltech AS.  All rights reserved.
**
** This file is part of Qt Designer.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file COPYING included in the
** packaging of this file.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#ifndef __markerwidget_h
#define __markerwidget_h

#include <Qt3Support>
#include <QtGui>
#include <QtCore>

namespace qrs {

class QEditor;

class Mark {
public:
    int line;
    int type;
};

class MarkerWidget: public QWidget
{
    Q_OBJECT

public:
    MarkerWidget( QEditor*, QWidget* =0, const char* =0 );
    virtual ~MarkerWidget();

    virtual void setPixmap(int, const QPixmap &);
    virtual void setDescription(int, const QString &);
    virtual void setMarksUserChangable(uint markMask);

public slots:
    void doRepaint() { repaint( FALSE ); }

protected:
    virtual void resizeEvent( QResizeEvent* );
    virtual void paintEvent( QPaintEvent* );
    virtual void contextMenuEvent( QContextMenuEvent* );
    virtual void mousePressEvent ( QMouseEvent * e );

signals:
    void marksChanged();

private:
    QEditor*                m_editor;
    QPixmap                 m_buffer;
    QMap<int,QPixmap>       m_pixmapMap;
    bool                    m_clickChangesBPs;
    bool                    m_changeBookmarksAllowed;
    bool                    m_changeBreakpointsAllowed;
    QString                 m_bookmarkDescr;
    QString                 m_breakpointDescr;
};
}
#endif // __markerwidget_h
