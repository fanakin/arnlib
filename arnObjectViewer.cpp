/***************************************************************************
                          arnObjectViewer.cpp  -  description
                             -------------------
    begin                : mer apr 23 2003
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

#include "arnObjectViewer.h"

arnObjectViewer::arnObjectViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : QFrame(parent, name, f)
{
	tpy = avt_ObjectViewer;
}
arnObjectViewer::~arnObjectViewer(void)
{
;
}
