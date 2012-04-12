/***************************************************************************
                          arnParViewItem.cpp  -  description
                             -------------------
    begin                : mer apr 16 2003
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

#include <QPainter>
#include "CommonFunctions.h"
#include "arnParViewItem.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnParViewItem --------------------------
// ***************************************************
// ---------------------------------------------------
arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListView * parent )
    : QObject(Opar), Q3ListViewItem(parent)
{
    this->init();
}

arnParViewItem::arnParViewItem( QObject * Opar , Q3ListViewItem *parent )
    : QObject(Opar), Q3ListViewItem(parent)
{
    this->init();
}
     
arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListView *parent, Q3ListViewItem *after )
    : QObject(Opar), Q3ListViewItem( parent, after )
{
    this->init();

}

arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListViewItem *parent, Q3ListViewItem *after )
    : QObject(Opar), Q3ListViewItem(parent, after)
{
    this->init();

}

arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : QObject(Opar), Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : QObject(Opar), Q3ListViewItem( parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : QObject(Opar), Q3ListViewItem(parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnParViewItem::arnParViewItem ( QObject * Opar , Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : QObject(Opar), Q3ListViewItem(parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnParViewItem::~arnParViewItem(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnParViewItem::init(void)
{
	tpe = apt_None;
	currcolor = QColor(0,0,0);
}

void arnParViewItem::paintCell(QPainter * p,const QColorGroup &cg,int column, int width, int align)
{
	QColorGroup colorGroup(cg);
	QColor color = colorGroup.text();
	colorGroup.setColor(QColorGroup::Text, currcolor);
	Q3ListViewItem::paintCell(p, colorGroup, column, width, align);
	colorGroup.setColor(QColorGroup::Text, color);
}
