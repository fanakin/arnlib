/***************************************************************************
                          arnGraphDataStream.cpp  -  description
                             -------------------
    begin                : mar giu 14 2005
    copyright            : (C) 2005 by Aurion s.r.l.
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

#include "arnGraphDataStream.h"

arnGraphDataStream::arnGraphDataStream(QObject * parent, const char * name)
	: QObject(parent, name)
{
	this->init();
}

arnGraphDataStream::~arnGraphDataStream(void)
{
}

void arnGraphDataStream::init(void)
{
	color = QColor( "blue");
	timebase = 200000; // 200 ms
	visibleWinSize = 50; // 10 s
	visibleStartPoint = 0; // from  the beginning
	min = -32768;
	max = 32768;
	visible = true;
	lineformat = LINESTYLE_SOLID;
}
