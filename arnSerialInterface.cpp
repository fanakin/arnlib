/***************************************************************************
                          arnSerialInterface.cpp  -  description
                             -------------------
    begin                : mer nov 20 2002
    copyright            : (C) 2002 by fabio giovagnini
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

#include "arnSerialInterface.h"

arnSerialInterface::arnSerialInterface(void)
{
	status = 0;
	rx = 0;
	HPort = -1;
}
