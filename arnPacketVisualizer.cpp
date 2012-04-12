/***************************************************************************
                          arnPacketVisualizer.cpp  -  description
                             -------------------
    begin                : sab feb 22 2003
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

#include <stdlib.h>
#include <QObjectList>
#include "CommonFunctions.h"
#include "arnPacketVisualizer.h"

arnPacketVisualizer::arnPacketVisualizer(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    pHLayout = 0;
    pVLayout1 = 0;
    pVLayout2 = 0;
}

arnPacketVisualizer::~arnPacketVisualizer(void)
{
}

