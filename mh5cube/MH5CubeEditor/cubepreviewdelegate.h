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

#ifndef CUBEPREVIEWDELEGATE_H
#define CUBEPREVIEWDELEGATE_H

#include <QtGui>
#include <QStyledItemDelegate>
#include "cubepreview.h"
//! This is the Delegate used in the MainWindow model
/*!
  This CubePreviewDelegate is derived from QStyledItemDelegate, as it has to reimplement the paint function to be able to draw a pixmap in it.
  For more information about the use of Delegates please see: http://doc.trolltech.com/4.5/qstyleditemdelegate.html#details
  or the delegate example http://doc.trolltech.com/4.5/itemviews-stardelegate.html
*/
class CubePreviewDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    CubePreviewDelegate(QWidget *parent = 0) : QStyledItemDelegate(parent) {}

    void paint(QPainter *painter, const QStyleOptionViewItem &option,
               const QModelIndex &index) const;
    QSize sizeHint(const QStyleOptionViewItem &option,
                   const QModelIndex &index) const;
    QWidget *createEditor(QWidget *parent,  const QStyleOptionViewItem &,  const QModelIndex &) const;

    ~CubePreviewDelegate() { qDebug() << "Gelöscht";}

private slots:

};

#endif // CUBEPREVIEWDELEGATE_H
