/***************************************************************************
                          arnLibversion.cpp  -  description
                             -------------------
    begin                : venerdi ago 15 2003
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

//---------------------------------------------------------------------------
#include "arnLibversion.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
#define __ARNLIB_VERSION__ "0.0.7.2"
static const char version[] = __ARNLIB_VERSION__ " , compiled: "__DATE__ "," __TIME__ "\n";

const char* arnGetVersion(void)
{
	return version;
}
