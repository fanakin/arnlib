/***************************************************************************
                          arnSObjectContainer.cpp  -  description
                             -------------------
    begin                : mar apr 24 2005
    copyright            : (C) 2005 by fabio giovagnini
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
#include "arnSObjectContainer.h"
#include <math.h>


// ---------------------------------------------------
// ***************************************************
// --------- arnPVIObjectContainer -------------------
// ***************************************************
// ---------------------------------------------------
arnSObjectContainer::arnSObjectContainer ( QObject * parent, const char * name )
    : QObject( parent, name)
{
    this->init();
}


arnSObjectContainer::~arnSObjectContainer(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnSObjectContainer::init(void)
{
    tpe = sot_ObjectContainer;
    pDataFrame = 0;
    pViewer = 0;

    mn = 0;
    mx = 0;
    flr = 0;
    cil = 0;
    filterT = np_none;
    Comment="";
    prc = 0;
}

void arnSObjectContainer::setMin(double m)
{
    mn = m;
    flr = mn;
    evalPrec();
}

void arnSObjectContainer::setMax(double m)
{
    mx = m;
    cil = mx;
    evalPrec();
}

void arnSObjectContainer::setFloor(double f)
{
    flr = f;
}

void arnSObjectContainer::setCeil(double c)
{
    cil = c;
}

void arnSObjectContainer::evalPrec(void)
{
    double rawRange;
    double actRange;
    switch (elemformat) {
        case nff_u8:
        case nff_s8:
            rawRange = 255.0;
            actRange = mx - mn;
            if (actRange == 0) prc = 0;
            else if (actRange >= rawRange) prc = 0;
            else {
                double logVal = log10(rawRange / actRange);
                if ((logVal / ((int)logVal)) > 1) prc = (unsigned char) (1.0 + logVal);
                else prc = (unsigned char)logVal;
                }
            break;
        case nff_u16:
        case nff_s16:
            rawRange = 65535.0;
            actRange = mx - mn;
            if (actRange == 0) prc = 0;
            else if (actRange >= rawRange) prc = 0;
            else {
                double logVal = log10(rawRange / actRange);
                if ((logVal / ((int)logVal)) > 1) prc = (unsigned char) (1.0 + logVal);
                else prc = (unsigned char)logVal;
                }
            break;
        case nff_u32:
        case nff_s32:
            rawRange = (2147483647.0 + 2147483648.0);
            actRange = mx - mn;
            if (actRange == 0) prc = 0;
            else if (actRange >= rawRange) prc = 0;
            else {
                double logVal = log10(rawRange / actRange);
                if ((logVal / ((int)logVal)) > 1) prc = (unsigned char) (1.0 + logVal);
                else prc = (unsigned char)logVal;
                }
            break;
        case nff_none:
        default:
            break;
        }
}

double arnSObjectContainer::checkValue(double val)
{
	if (val > cil) return cil;
	else if (val < flr) return flr;
	return val;
}







