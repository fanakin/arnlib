/***************************************************************************
                          arnqslider.h  -  description
                             -------------------
    begin                : mar feb 7 2006
    copyright            : (C) 2006 by Aurion s.r.l.
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

#include "CommonFunctions.h"
#include "arnqslider.h"

arnQSlider::arnQSlider( QWidget * parent, const char * name )
    : QSlider(parent, name)
{
	init();
}
arnQSlider::arnQSlider( Qt::Orientation orientation, QWidget * parent, const char * name )
    : QSlider(orientation, parent, name)
{
	init();
}
arnQSlider::arnQSlider( int minValue, int maxValue, int pageStep, int value, Qt::Orientation orientation, QWidget * parent, const char * name)
    : QSlider(minValue,maxValue,pageStep,value,orientation, parent,name)
{
	init();
}

arnQSlider::~arnQSlider()
{
}

void arnQSlider::init (void)
{
	MulSelKeyUp = Qt::Key_Escape;
	MulSelKeyDown = Qt::Key_Escape;
}

// void arnQSlider::keyPressEvent ( QKeyEvent * e )
// {
// 	if ((MulSelKeyUp == Qt::Key_Escape) || (MulSelKeyDown == Qt::Key_Escape)) {
// 		e->accept();
// 		}
// 	else {
// 		if (e->key() == MulSelKeyUp) setValue(value() + lineStep());
// 		else if (e->key() == MulSelKeyDown)  setValue(value() - lineStep());
// 		e->accept();
// 		}
// }

// void arnQSlider::focusInEvent ( QFocusEvent * )
// {
// 	parentWidget()->setFocus();
// }
