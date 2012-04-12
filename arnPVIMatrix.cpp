/***************************************************************************
                          arnPVIMatrix.cpp  -  description
                             -------------------
    begin                : ven mar 18 2005
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
#include "arnPVIMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVINumericMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListView * parent )
    : arnPVIObjectContainer( Opar, parent)
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIObjectContainer( Opar, parent)
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIObjectContainer( Opar, parent, after )
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIObjectContainer( Opar, parent, after)
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIObjectContainer( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIObjectContainer( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIObjectContainer( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
	this->init();
}

arnPVIMatrix::arnPVIMatrix ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIObjectContainer( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
	this->init();
}

arnPVIMatrix::~arnPVIMatrix(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVIMatrix::init(void)
{
	NRows = 5;
	NCols = 5;
	yAxisCaption = "Y";
	xAxisCaption = "X";
}

int arnPVIMatrix::typeTonbytes(void)
{
    switch (elemformat) {
        case nff_8bit:
        case nff_u8:
        case nff_s8:
            return 1;
        case nff_16bit:
        case nff_u16:
        case nff_s16:
            return 2;
        case nff_32bit:
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


