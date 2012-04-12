/***************************************************************************
                          arnNumPacketItem.cpp  -  description
                             -------------------
    begin                : ven lug 4 2003
    copyright            : (C) 2003 by fabio giovagnini
    email                : fabio.giovagnini@aurion-tech.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#include <qcursor.h>
#include "CommonFunctions.h"
#include "arnNumPacketItem.h"
#include <QMouseEvent>

arnNumPacketItem::arnNumPacketItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(parent,name,f)
{
	this->init();
	Value->display(0);
}

arnNumPacketItem::arnNumPacketItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->display(0);
}


arnNumPacketItem::arnNumPacketItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->display(value);
}

arnNumPacketItem::arnNumPacketItem(const QString& label, int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->display(value);
}

arnNumPacketItem::arnNumPacketItem(const QString& label, double value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->display(value);
}

arnNumPacketItem::~arnNumPacketItem(void)
{

}

void arnNumPacketItem::init(void)
{
	tpe = apit_NumPacketItem;
    Value = new QLCDNumber(this);
    if (!Value) arnCriticalExit();;

    pHLayout->addWidget(Value);

	manualBlinkEnabled = false;
	timerManualBlink = new QTimer(this, "timerManualBlink");
	if (!timerManualBlink) arnCriticalExit();
	connect (timerManualBlink,SIGNAL( timeout()), this, SLOT(TimeoutManualBlink_Hndl(void)));
	timerManualBlink->stop();
}

void arnNumPacketItem::mousePressEvent(QMouseEvent *e)
{
	if (e->button () == Qt::LeftButton) {
		QFrame::mousePressEvent(e);
		}
	else if (e->button () == Qt::RightButton) {
		if (pPopUp) pPopUp->exec(QCursor::pos());
		QFrame::mousePressEvent(e);
		}
	else QFrame::mousePressEvent(e);
}

void arnNumPacketItem::setManualBlink(unsigned short blinkShot)
{
	if (!timerManualBlink->isActive()) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(TOHIGHCOLOR));
			Value->setPalette (pal);
			Value->update();
			timerManualBlink->start(blinkShot);
		}
}

void arnNumPacketItem::TimeoutManualBlink_Hndl(void)
{
	QPalette pal = Value->palette();
	pal.setColor(QPalette::Window,QColor(BACKGROUNDCOLOR));
	Value->setPalette (pal);
	Value->update();
	timerManualBlink->stop();
	manualBlinkEnabled = false;
}

