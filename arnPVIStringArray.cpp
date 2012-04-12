/***************************************************************************
                          arnPVIStringArray.cpp  -  description
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
#include "arnPVIStringArray.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnPVIStringArray ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListView * parent )
    : arnPVIArray( Opar ,parent)
{
    this->init();
}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIArray( Opar ,parent)
{
    this->init();
}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIArray( Opar ,parent, after )
{
    this->init();

}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIArray( Opar ,parent, after)
{
    this->init();

}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIArray( Opar ,parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIArray( Opar ,parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIArray( Opar ,parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringArray::arnPVIStringArray ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIArray( Opar ,parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringArray::~arnPVIStringArray(void)
{

}

void arnPVIStringArray::init(void)
{
    tpe = apt_StringArray;
    xAxis = 0;
    NRows = 5;
    stringLength = -1;
}

void arnPVIStringArray::setValue(int row, const QString& val)
{
	if (stringLength < 1) return;
	strncpy(((char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (row * stringLength)])),val.latin1(),stringLength);    
}

void arnPVIStringArray::setValue(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    if (col != 0) return;
    QString tVal = pViewer->text(row,col);
    setValue(row,tVal);
}

QString arnPVIStringArray::valueX(int row)
{
	if (!xAxis) return QString ("");
	return xAxis->value(row);
}

QString arnPVIStringArray::value(int row)
{
	if (!plowDevice) arnCriticalExit();
	if (elemformat == nff_none || elemformat != nff_string) arnCriticalExit();
	char* t = new char[stringLength];
	if (!t) arnCriticalExit();
	memset(t,0,stringLength);
	strncpy(t,(const char*)(&(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (row * stringLength)])),stringLength);
	QString res(t);
	delete [] t;
	return res;
}
