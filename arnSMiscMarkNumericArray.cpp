/***************************************************************************
                          arnSMiscMarkNumericArray.cpp  -  description
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
#include "arnSMiscMarkNumericArray.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscMarkNumericArray ----------------------
// ***************************************************
// ---------------------------------------------------
arnSMiscMarkNumericArray::arnSMiscMarkNumericArray ( QObject * parent, const char * name )
    : arnSMiscNumericArray( parent , name)
{
    this->init();
}


arnSMiscMarkNumericArray::~arnSMiscMarkNumericArray(void)
{
	if (mark) {delete [] mark; mark = 0;}
}

void arnSMiscMarkNumericArray::init(void)
{
    tpe = sot_MiscMarkNumericArray;
	defColor = QColor("red");
    xAxis = 0;
    NRows = 5;
    prcX = 0;
    mnX = 0;
    mxX = NRows - 1;
	mark = new struct mark_info[NRows];
	if (!mark) arnCriticalExit();
}

void arnSMiscMarkNumericArray::setDims(int rows)
{
	if (mark) {delete [] mark; mark = 0;}
	if (!xAxis) NRows = rows;
	else NRows = xAxis->rows();
	mark = new struct mark_info[NRows];
	if (!mark) arnCriticalExit();
}

void arnSMiscMarkNumericArray::setValueAndMark(int row, double val)
{
	arnSMiscNumericArray::setValue(row,val);
	if (mark && row < NRows) {
		mark[row].marked = true;
		mark[row].color = defColor;
		}
}

void arnSMiscMarkNumericArray::setValueAndMark(int row, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row,tNum);
	if (mark && row < NRows) {
		mark[row].marked = true;
		mark[row].color = defColor;
		}
}

void arnSMiscMarkNumericArray::setValueAndMark(int row)
{
    if (!pViewer) arnCriticalExit();
    bool ok;
    double tNum = pViewer->text(row).toDouble(&ok);
    if (!ok) return;
    setValue(row, tNum);
	if (mark && row < NRows) {
		mark[row].marked = true;
		mark[row].color = defColor;
		}
}

bool arnSMiscMarkNumericArray::isMarked(int row)
{
	if (mark && row < NRows) return mark[row].marked;
	return false;
}

void arnSMiscMarkNumericArray::resetMark(int row)
{
	if (mark && row < NRows) mark[row].marked = false;
}

void arnSMiscMarkNumericArray::setDefaultColor(const QColor& c)
{
	defColor = c;
}

void arnSMiscMarkNumericArray::setColor(int row, const QColor& c)
{
	if (mark && row < NRows) mark[row].color = c;
}

QColor arnSMiscMarkNumericArray::Color(int row)
{
	if (mark && row < NRows) return mark[row].color;
	return defColor;
}
