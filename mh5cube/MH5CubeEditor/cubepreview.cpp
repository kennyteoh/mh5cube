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

#include "cubepreview.h"

CubePreview::CubePreview(QPixmap &preview)
{
    this->previewPicture = new QPixmap(preview);
}

QSize CubePreview::sizeHint() const
{
    return QSize(100, 100);
}


//! draws the pixmap
void CubePreview::paint(QPainter *painter, const QRect &rect, const QPalette &palette, EditMode mode) const
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing, true);
    painter->setPen(Qt::NoPen);

    if (mode == Editable) {
        painter->setBrush(palette.highlight());
    } else {
        painter->setBrush(palette.foreground());
    }

    int yOffset = 0;
    painter->translate(rect.x(), rect.y() + yOffset);

    painter->drawPixmap(0,0, *(this->previewPicture));

    painter->translate(1.0, 0.0);

    painter->restore();
}

//! Returns the previewPicture as a QPixmap on Reference
void CubePreview::getPreviewPicture(QPixmap &preview) {
    preview = *(this->previewPicture); //Return the PreviewPixmap on argument
}

