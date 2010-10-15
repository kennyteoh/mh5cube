/*
# This file is part of the Qube5-Editor.
#
# Qube5-Editor allows you to create figures and animations for the LED-Qube5.
# For more information about the LED-Qube5 and this program, see <http://www.qube-solutions.de>
# Copyright (C) 2009 Christian Strobel
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef CUBEPREVIEW_H
#define CUBEPREVIEW_H

#include <QtGui>
#include <QMetaType>
#include <QPixmap>

//! This class is used as a MetaType for CubePreviewDelegate
class CubePreview
{
public:
    enum EditMode { Editable, ReadOnly };
    CubePreview(QPixmap & preview);
    CubePreview() {}
    void paint(QPainter *painter, const QRect &rect, const QPalette &palette, EditMode mode) const;
    QSize sizeHint() const;
    void getPreviewPicture(QPixmap &preview);
private:
    QPixmap *previewPicture;
};
Q_DECLARE_METATYPE(CubePreview)
#endif // CUBEPREVIEW_H
