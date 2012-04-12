/***************************************************************************
                          arnSMiscMarkTraceNumericMatrix.cpp  -  description
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
#include "arnSMiscMarkTraceNumericMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscNumericMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnSMiscMarkTraceNumericMatrix::arnSMiscMarkTraceNumericMatrix ( QObject * parent, const char * name )
    : arnSMiscMarkNumericMatrix( parent, name)
{
    this->init();
}

arnSMiscMarkTraceNumericMatrix::~arnSMiscMarkTraceNumericMatrix(void)
{
//arnDebug("%s\n",name());
}

void arnSMiscMarkTraceNumericMatrix::init(void)
{
    tpe = sot_MiscMarkTraceNumericMatrix;
    xAxis = 0;
    yAxis = 0;
    prcX = 0;
    mnX = 0;
    mxX = NCols - 1;
    prcY = 0;
    mnY = 0;
    mxY = NRows - 1;
}


void arnSMiscMarkTraceNumericMatrix::setValueAndMark(int row, int col, double val)
{
	arnSMiscMarkNumericMatrix::setValueAndMark(row,col,val);
	updateMark(row,col);
	updateValue(row,col,value(row, col));
}

void arnSMiscMarkTraceNumericMatrix::setValueAndMark(int row, int col, const QString& val)
{
	arnSMiscMarkNumericMatrix::setValueAndMark(row,col,val);
	updateMark(row,col);
	updateValue(row,col,value(row, col));
}

void arnSMiscMarkTraceNumericMatrix::setValueAndMark(int row, int col)
{
	arnSMiscMarkNumericMatrix::setValueAndMark(row,col);
	updateMark(row,col);
	updateValue(row,col,value(row, col));
}

void arnSMiscMarkTraceNumericMatrix::updateTrace(int row, int col/*, double value*/)
{
	//itrace.row = row;
	//itrace.col = col;
	//itrace.value = value;
	emit TraceChanged(row,col,Color(row,col));
}

void arnSMiscMarkTraceNumericMatrix::updateMark(int row, int col)
{
	emit MarkChanged(row,col,Color(row,col));
}

void arnSMiscMarkTraceNumericMatrix::updateValue(int row, int col, double value)
{
	emit ValueChanged(row,col,value);
}
