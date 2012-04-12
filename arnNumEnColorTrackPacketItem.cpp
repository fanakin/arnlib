/***************************************************************************
                          arnNumEnColorTrackPacketItem.cpp  -  description
                             -------------------
    begin                : mar luglio 26 2003
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
#include <qcolordialog.h>
#include "CommonFunctions.h"
#include "arnNumEnColorTrackPacketItem.h"

arnNumEnColorTrackPacketItem::arnNumEnColorTrackPacketItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumEnPacketItem(parent,name,f)
{
	this->init();
}

arnNumEnColorTrackPacketItem::arnNumEnColorTrackPacketItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumEnPacketItem(label,parent,name,f)
{
	this->init();
}


arnNumEnColorTrackPacketItem::arnNumEnColorTrackPacketItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumEnPacketItem(label,value,parent,name,f)
{
	this->init();
}

arnNumEnColorTrackPacketItem::arnNumEnColorTrackPacketItem(const QString& label, int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumEnPacketItem(label,value,parent,name,f)
{
	this->init();
}

arnNumEnColorTrackPacketItem::arnNumEnColorTrackPacketItem(const QString& label, double value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumEnPacketItem(label,value,parent,name,f)
{
	this->init();
}

arnNumEnColorTrackPacketItem::~arnNumEnColorTrackPacketItem(void)
{

}

void arnNumEnColorTrackPacketItem::init(void)
{
	tpe = apit_NumEnColorTrackPacketItem;
	clr = QColor("blue");
	defaultColor = Name->palette().color(QPalette::Active,QPalette::WindowText);
	enTrackColor = new QAction( this, "enTrackColor");
	if (!enTrackColor) arnCriticalExit();
	enTrackColor->setToggleAction(true);
	enTrackColor->setText( trUtf8("Track Color"));
	enTrackColor->setMenuText( trUtf8("Track Color"));
	enTrackColor->setToolTip( trUtf8("Mostra in background il colore della traccia nella finestra di real time"));

	selTrackColor = new QAction( this, "selTrackColor");
	if (!selTrackColor) arnCriticalExit();
	selTrackColor->setText( trUtf8("Select Color"));
	selTrackColor->setMenuText( trUtf8("Select Color"));
	selTrackColor->setToolTip( trUtf8("Seleziona in background il colore della traccia nella finestra di real time"));

	connect( enTrackColor,SIGNAL( toggled(bool) ), this, SLOT( enTrackColor_Hndl(bool) ) );
	connect( selTrackColor,SIGNAL( activated(void) ), this, SLOT( selTrackColor_Hndl(void) ) );
	enTrackColor->addTo(pPopUp);
	selTrackColor->addTo(pPopUp);
}

void arnNumEnColorTrackPacketItem::setTrackColor(const QColor& c)
{
	clr = QColor(c);
/*	enTrackColor->setOn(true);
	QPixmap xpm = QPixmap();
	xpm.resize(Name->width(),Name->height());
	xpm.fill(clr);
	Name->setPaletteBackgroundPixmap(xpm);*/
}

void arnNumEnColorTrackPacketItem::showTrackColor(void)
{
	QPalette pal = Name->palette ();
	pal.setColor(QPalette::Normal,QPalette::WindowText,clr);
	Name->setPalette (pal);
/*	QPixmap xpm = QPixmap();
	enTrackColor->setOn(true);
	xpm.resize(Name->width(),Name->height());
	xpm.fill(clr);
	Name->setPaletteBackgroundPixmap(xpm);
*/
}

void arnNumEnColorTrackPacketItem::enTrackColor_Hndl(bool tg)
{
	if (!tg) {
		QPalette pal = Name->palette ();
		pal.setColor(QPalette::Normal,QPalette::WindowText,defaultColor);
		Name->setPalette (pal);
		}
	else {
		QPalette pal = Name->palette ();
		pal.setColor(QPalette::Normal,QPalette::WindowText,clr);
		Name->setPalette (pal);
		}
}

void arnNumEnColorTrackPacketItem::selTrackColor_Hndl(void)
{
	QColor Clr = QColorDialog::getColor ();
	if (Clr.isValid()) {
		setTrackColor(Clr);
		}
	else arnDebug("Track Color not valid.");
}

//
// ---- uso quello definito in arnNumPacketItem
//
// void arnPacketItem::mousePressEvent(QMouseEvent *e)
// {
// 	if (e->button () == Qt::LeftButton) {
// 		QFrame::mousePressEvent(e);
// 		}
// 	else if (e->button () == Qt::RightButton) {
// 		if (pPopUp) pPopUp->exec(QCursor::pos());
// 		QFrame::mousePressEvent(e);
// 		}
// 	else QFrame::mousePressEvent(e);
// }

