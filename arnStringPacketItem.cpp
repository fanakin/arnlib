/***************************************************************************
                          arnStringPacketItem.h  -  description
                             -------------------
    begin                : mar apr 19 2005
    copyright            : (C) 2005 by fabio giovagnini
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
#include "arnStringPacketItem.h"
#include <QMouseEvent>

arnStringPacketItem::arnStringPacketItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(parent,name,f)
{
	this->init();
}

arnStringPacketItem::arnStringPacketItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
}


arnStringPacketItem::arnStringPacketItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->setText(value);
}

arnStringPacketItem::arnStringPacketItem(const QString& label, int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->setText(QString::number(value));
}

arnStringPacketItem::arnStringPacketItem(const QString& label, double value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnPacketItem(label,parent,name,f)
{
	this->init();
	Value->setText(QString::number(value));
}

arnStringPacketItem::~arnStringPacketItem(void)
{

}

void arnStringPacketItem::init(void)
{
	tpe = apit_StringPacketItem;

    Value = new QLabel(this);
    if (!Value) arnCriticalExit();
	QFont font("courier",18);
	Value->setFont(font);
    pHLayout->addWidget(Value);
}

void arnStringPacketItem::mousePressEvent(QMouseEvent *e)
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

void arnStringPacketItem::setValueFontSize(int size)
{
	QFont font("courier",size);
	Value->setFont(font);
}

void arnStringPacketItem::setValueFontColor(QColor color)
{
	QPalette pal = Value->palette ();
	pal.setColor(QPalette::Normal,QPalette::WindowText,color);
	Value->setPalette (pal);
	//Value->setPaletteForegroundColor(color);
}
