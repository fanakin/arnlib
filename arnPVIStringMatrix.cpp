/***************************************************************************
						  arnPVIStringMatrix.cpp  -  description
                             -------------------
	begin                : ven giu 18 2010
	copyright            : (C) 2003 - 2010 by fabio giovagnini
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
#include "arnPVIStringMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIStringMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListView * parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after )
{
    this->init();

}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after)
{
    this->init();

}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringMatrix::arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringMatrix::~arnPVIStringMatrix(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVIStringMatrix::init(void)
{
	tpe = apt_StringMatrix;
    xAxis = 0;
    yAxis = 0;
    prcX = 0;
    mnX = 0;
    mxX = NCols - 1;
    prcY = 0;
    mnY = 0;
    mxY = NRows - 1;
	valueLen = 1;
}

void arnPVIStringMatrix::setDims(int rows, int cols)
{
    if (!xAxis) NCols = cols;
    else NCols = yAxis->rows(); 
    if (!yAxis) NRows = rows;
    else NRows = xAxis->rows();
}

void arnPVIStringMatrix::setValue(int row, int col, const QString& val)
{
	arnDebug("passo\n");
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
	if (!sze || sze < ((unsigned long)(valueLen * ((row * NCols) + col)))) arnCriticalExit();
	switch (elemformat) {
        case nff_string:
			strncpy((char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (valueLen * ((row * NCols) + col))]),val.toAscii().data(),valueLen);
            break;
        default:
            break;
        }
}

void arnPVIStringMatrix::setValue(int row, int col)
{
	if (!pViewer) arnCriticalExit();
	setValue(row, col ,pViewer->text(row,col));
}


double arnPVIStringMatrix::valueX(int cols)
{
	if (!xAxis) {
		double res = (((mxX - mnX) * cols) / (NCols - 1)) + mnX;
		return res;
		}
    return xAxis->value(cols);
}

double arnPVIStringMatrix::valueY(int rows)
{
	if (!yAxis) {
		double res = (((mxY - mnY) * rows) / (NRows - 1)) + mnY;
		return res;
		}
    return yAxis->value(rows);
}

const QString arnPVIStringMatrix::value(int row, int col)
{
	QString res("");
	char* pBff = new char[valueLen + 1] ;
	if (!pBff) return res;
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
	if (!sze || sze < ((unsigned long)(valueLen * ((row * NCols) + col)))) arnCriticalExit();
	switch (elemformat) {
		case nff_string:
			strncpy(pBff,(char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (valueLen * ((row * NCols) + col))]),valueLen);
			pBff[valueLen] = 0;
			res = QString::fromAscii(pBff);
			delete pBff; pBff = 0;
			return res;
			break;
		default:
			return res;
			break;
		}
}

