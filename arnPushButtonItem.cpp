/***************************************************************************
						  arnPushButtonItem.cpp  -  description
                             -------------------
	begin                : sab sett 25 2010
	copyright            : (C) 2003-2010 by fabio giovagnini
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

#include <QPalette>

#include "CommonFunctions.h"
#include "arnPushButtonItem.h"

arnPushButtonItem::arnPushButtonItem(QWidget *parent, const char* name)
	: QPushButton(QString(name),parent)
{
	typ = agit_PushButtonItem;
	setName(name);
	//connect(this, SIGNAL(clicked(bool)),this,SLOT(clicked_hndl(bool)));
	//connect(this, SIGNAL(pressed(void)),this,SLOT(pressed_hndl(void)));
	//connect(this, SIGNAL(released(void)),this,SLOT(released_hndl(void)));
}
/*
void arnPushButtonItem::clicked_hndl(bool )
{
}

void arnPushButtonItem::pressed_hndl(void)
{
}

void arnPushButtonItem::released_hndl(void)
{
}

*/
