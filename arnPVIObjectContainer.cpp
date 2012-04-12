/***************************************************************************
                          arnPVIObjectContainer.cpp  -  description
                             -------------------
    begin                : ven apr 18 2003
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

#include "arnNumericFilter.h"
#include "arnPVIObjectContainer.h"
#include <math.h>


// ---------------------------------------------------
// ***************************************************
// --------- arnPVIObjectContainer -------------------
// ***************************************************
// ---------------------------------------------------
arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListView * parent )
    : arnParViewItem( Opar, parent)
{
    this->init();
}

arnPVIObjectContainer::arnPVIObjectContainer( QObject * Opar, Q3ListViewItem *parent )
    : arnParViewItem( Opar, parent)
{
    this->init();
}

arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnParViewItem( Opar, parent, after )
{
    this->init();

}

arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnParViewItem( Opar, parent, after)
{
    this->init();

}

arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnParViewItem( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnParViewItem( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnParViewItem( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIObjectContainer::arnPVIObjectContainer ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnParViewItem( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIObjectContainer::~arnPVIObjectContainer(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVIObjectContainer::init(void)
{
    tpe = apt_ObjectContainer;
    plowDevice = 0;
    pViewer = 0;

    mn = 0;
    mx = 0;
    flr = 0;
    cil = 0;
    filterT = np_none;
    Comment="";
    prc = 0;
}

void arnPVIObjectContainer::setMin(double m)
{
    mn = m;
    flr = mn;
    evalPrec();
}

void arnPVIObjectContainer::setMax(double m)
{
    mx = m;
    cil = mx;
    evalPrec();
}

void arnPVIObjectContainer::setFloor(double f)
{
    flr = f;
}

void arnPVIObjectContainer::setCeil(double c)
{
    cil = c;
}

void arnPVIObjectContainer::evalPrec(void)
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

double arnPVIObjectContainer::checkValue(double val)
{
	if (val > cil) return cil;
	else if (val < flr) return flr;
	return val;
}






