/***************************************************************************
                          arnSStringArray.cpp  -  description
                             -------------------
    begin                : mar apr 26 2005
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
#include "arnSStringArray.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSStringArray ----------------------
// ***************************************************
// ---------------------------------------------------
arnSStringArray::arnSStringArray ( QObject * parent, const char * name )
    : arnSArray( parent ,name)
{
    this->init();
}

arnSStringArray::~arnSStringArray(void)
{

}

void arnSStringArray::init(void)
{
    tpe = sot_StringArray;
    xAxis = 0;
    NRows = 5;
    stringLength = -1;
}

void arnSStringArray::setValue(int row, const QString& val)
{
	if (stringLength < 1) return;
	strncpy(((char*) &(pDataFrame[offst + (row * stringLength)])),val.latin1(),stringLength);    
}

void arnSStringArray::setValue(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    if (col != 0) return;
    QString tVal = pViewer->text(row,col);
    setValue(row,tVal);
}

QString arnSStringArray::valueX(int row)
{
	if (!xAxis) return QString ("");
	return xAxis->value(row);
}

QString arnSStringArray::value(int row)
{
	if (!pDataFrame) arnCriticalExit();
	if (elemformat == nff_none || elemformat != nff_string) arnCriticalExit();
	char* t = new char[stringLength];
	if (!t) arnCriticalExit();
	memset(t,0,stringLength);
	strncpy(t,(const char*)(&(pDataFrame[offst + (row * stringLength)])),stringLength);
	QString res(t);
	delete [] t;
	return res;
}
