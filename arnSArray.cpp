/***************************************************************************
                          arnSArray.cpp  -  description
                             -------------------
    begin                : mar apr 26 2005
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

#include "arnNumericFilter.h"
#include "arnSArray.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSArray ----------------------
// ***************************************************
// ---------------------------------------------------
arnSArray::arnSArray ( QObject * parent, const char * name )
    : arnSObjectContainer( parent, name)
{
	this->init();
}


arnSArray::~arnSArray(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnSArray::init(void)
{
	tpe = sot_Array;
	xAxisCaption = "X";
	NRows = 5;
}

int arnSArray::typeTonbytes(void)
{
    switch (elemformat) {
        case nff_u8:
        case nff_s8:
            return 1;
        case nff_u16:
        case nff_s16:
            return 2;
        case nff_u32:
        case nff_s32:
            return 4;
        case nff_float:
        case nff_double:
            arnCriticalExit();
            return -1;
        default :
            arnCriticalExit();
            return -1;
        }
}

