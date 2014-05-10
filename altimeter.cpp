/*
 *  This file is part of the Altimeter project
 *  Copyright (C) 10/05/2014 -- altimeter.cpp -- bertrand
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * */

#include "altimeter.h"

#define WIDGETSIZE      (200)
#define CIRCLEPENWIDTH  (4)

Altimeter::Altimeter(QWidget *parent) :
    QGraphicsView(parent),
    feets(0)
{
    this->setGeometry(0,0, WIDGETSIZE, WIDGETSIZE);

    // Style Setting
    backgroundBrush = QBrush(QColor(0x53, 0x54, 0x48));
    circlePen       = QPen(Qt::black);
    circlePen.setWidth(CIRCLEPENWIDTH);
    graduationPen   = QPen(Qt::white);
    graduationPen.setWidth(2);
    graduationFont  = QFont("lucida");
    graduationFont.setPointSize(12);
    graduationFont.setBold(true);

    // BACKGROUND PIXMAP
    backgroundPixmap = QPixmap(WIDGETSIZE,WIDGETSIZE);
    QPainter painter;
    painter.begin(&(this->backgroundPixmap));
    painter.setRenderHint(QPainter::Antialiasing);
    // Background
    painter.fillRect(QRect(0,0,WIDGETSIZE,WIDGETSIZE), backgroundBrush);
    // Circle
    painter.translate(WIDGETSIZE/2, WIDGETSIZE/2);
    painter.setBrush(Qt::NoBrush);
    painter.setPen(circlePen);
    painter.drawEllipse(QPoint(0,0),
                        (WIDGETSIZE/2-CIRCLEPENWIDTH),
                        (WIDGETSIZE/2-CIRCLEPENWIDTH)
                        );
    // Graduation
    painter.save();
    painter.setFont(graduationFont);
    for(int i=0 ; i<10 ; ++i)
    {
        graduationPen.setWidth(2);
        painter.setPen(graduationPen);
        painter.drawLine(QPoint(0, -(WIDGETSIZE/2-CIRCLEPENWIDTH)+5),
                         QPoint(0, -(WIDGETSIZE/2-CIRCLEPENWIDTH)+13));

        graduationPen.setWidth(1);
        painter.setPen(graduationPen);
        painter.drawText(QPoint(-5, -(WIDGETSIZE/2-CIRCLEPENWIDTH)+28), QString::number(i));
        for(int j=1 ; j<5 ; ++j)
        {
            painter.rotate(7.2);
            painter.drawLine(QPoint(0, -(WIDGETSIZE/2-CIRCLEPENWIDTH)+5),
                             QPoint(0, -(WIDGETSIZE/2-CIRCLEPENWIDTH)+10));
        }
        painter.rotate(7.2);
    }
    painter.restore();
    painter.end();
}

void Altimeter::setAltitude(double feets)
{
    if(feets>0)
    {
        this->feets = feets;
        this->viewport()->update();
    }
}

void Altimeter::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this->viewport());
    painter.setRenderHint(QPainter::Antialiasing);
    paint(&painter, event);
    painter.end();
}

void Altimeter::paint(QPainter *painter, QPaintEvent *event)
{
    painter->drawPixmap(0,0, backgroundPixmap);
}
