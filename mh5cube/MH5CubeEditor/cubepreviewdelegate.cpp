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

#include "cubepreviewdelegate.h"

void CubePreviewDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option,
                         const QModelIndex &index) const
{
    if (qVariantCanConvert<CubePreview>(index.data())) {
        CubePreview cubePreview = qVariantValue<CubePreview>(index.data());

        if (option.state & QStyle::State_Selected)
            painter->fillRect(option.rect, option.palette.highlight());

        cubePreview.paint(painter, option.rect, option.palette,
                         CubePreview::ReadOnly);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }

}

QSize CubePreviewDelegate::sizeHint(const QStyleOptionViewItem &option,
                             const QModelIndex &index) const
{
    if (qVariantCanConvert<CubePreview>(index.data())) {
        CubePreview cubePreview = qVariantValue<CubePreview>(index.data());
        return cubePreview.sizeHint();
    } else {
        return QStyledItemDelegate::sizeHint(option, index);
    }
}

QWidget *CubePreviewDelegate::createEditor(QWidget *parent,
                                     const QStyleOptionViewItem &option,
                                     const QModelIndex &index) const
{
    if (qVariantCanConvert<CubePreview>(index.data())) { //Preview
         return NULL; //Don't create editor for the Preview
    }
    else {
        if(index.column() == 2) { //Description
            return QStyledItemDelegate::createEditor(parent, option, index);
        }
        else if (index.column() == 3) { //Time
            QWidget *editor = QStyledItemDelegate::createEditor(parent, option, index);
            QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
            spinBox->setMinimum(1);
            spinBox->setMaximum(20);
            return editor;
        }
     }
    return NULL;
}
