/***************************************************************************
                          arnPVI8BitValueMatrix.cpp  -  description
                             -------------------
    begin                : lun mag 26 2008
    copyright            : (C) 2008 by Aurion s.r.l.
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

#include "arnPVI8BitValueMatrix.h"
#include <math.h>

// ---------------------------------------------------
// ***************************************************
// --------- arnPVIMiscMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView * parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after )
{
    this->init();

}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after)
{
    this->init();

}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVI8BitValueMatrix::arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVI8BitValueMatrix::~arnPVI8BitValueMatrix(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVI8BitValueMatrix::init(void)
{
    tpe = apt_8BitValueMatrix;
	yAxis = 0;
	numFormatVal = nrf_dec;
}

void arnPVI8BitValueMatrix::setDims(int rows, int cols)
{
	if (!cols || cols > 8) arnCriticalExit();
	NCols = cols;
    if (!yAxis) NRows = rows;
    else NRows = yAxis->rows();
}


void arnPVI8BitValueMatrix::setValue(int row, int col, double val)
{
	if (!plowDevice) arnCriticalExit();
	if (elemformat == nff_none) arnCriticalExit();
	if (!sze || sze < ((unsigned long)(typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
	val = checkValue(val);
	switch (elemformat) {
		case nff_8bit:
			switch (col) {
				case 0:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B0 = ((val == 0) ? 0 : 1);
					break;
				case 1:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B1 = ((val == 0) ? 0 : 1);
					break;
				case 2:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B2 = ((val == 0) ? 0 : 1);
					break;
				case 3:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B3 = ((val == 0) ? 0 : 1);
					break;
				case 4:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B4 = ((val == 0) ? 0 : 1);
					break;
				case 5:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B5 = ((val == 0) ? 0 : 1);
					break;
				case 6:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B6 = ((val == 0) ? 0 : 1);
					break;
				case 7:
					((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B7 = ((val == 0) ? 0 : 1);
					break;
				default :
					arnCriticalExit();
					break;
				}
			break;
		default:
			arnCriticalExit();
			break;
		}
}

void arnPVI8BitValueMatrix::setValue(int row, int col, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row, col, tNum);
}

void arnPVI8BitValueMatrix::setValue(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    bool ok;
	double tNum;
	switch (numFormatVal) {
		case nrf_hex:
			tNum = pViewer->text(row,col).toInt(&ok,16);
			if (!ok) return;
			break;
		case nrf_bin:
			tNum = pViewer->text(row,col).toInt(&ok,2);
			if (!ok) return;
			break;
		case nrf_dec:
		default:
			tNum = pViewer->text(row,col).toDouble(&ok);
			if (!ok) return;
			break;
	}
	setValue(row, col ,tNum);
}

double arnPVI8BitValueMatrix::value(int row, int col)
{
	if (!plowDevice) arnCriticalExit();
	if (elemformat == nff_none) arnCriticalExit();
	if (!sze || sze < ((unsigned long) (typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
	switch (elemformat) {
		case nff_8bit:
			switch (col) {
				case 0:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B0;
				case 1:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B1;
				case 2:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B2;
				case 3:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B3;
				case 4:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B4;
				case 5:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B5;
				case 6:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B6;
				case 7:
					return ((union _BITFIELD*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))->BIT.B7;
				default :
					arnCriticalExit();
					break;
				}
			break;
		default:
			arnCriticalExit();
			break;
		}
}

double arnPVI8BitValueMatrix::valueX(int cols)
{
	return cols;
}

double arnPVI8BitValueMatrix::valueY(int rows)
{
	if (!yAxis) {
/*		double res = (((mxY - mnY) * rows) / (NRows - 1)) + mnY;*/
		return rows;
		}
    return yAxis->value(rows);
}

