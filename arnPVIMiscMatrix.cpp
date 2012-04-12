/***************************************************************************
                          arnPVIMiscMatrix.cpp  -  description
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
#include "arnPVIMiscMatrix.h"
#include <math.h>

// ---------------------------------------------------
// ***************************************************
// --------- arnPVIMiscMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListView * parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after )
{
    this->init();

}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after)
{
    this->init();

}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIMiscMatrix::arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIMiscMatrix::~arnPVIMiscMatrix(void)
{
//arnDebug("%s\n",text(0).latin1());
	if (mnCol) {delete [] mnCol; mnCol = 0;}
	if (mxCol) {delete [] mxCol; mxCol = 0;}
	if (prcCol) {delete [] prcCol; prcCol = 0;}
}

void arnPVIMiscMatrix::init(void)
{
    tpe = apt_MiscMatrix;
	numFormatVal = nrf_dec;
	prcY = 0;
    mnY = 0;
    mxY = NRows - 1;
	mnCol = new double[NCols];
	if (!mnCol) arnCriticalExit();
	mxCol = new double[NCols];
	if (!mxCol) arnCriticalExit();
	prcCol = new unsigned char[NCols];
	if (!prcCol) arnCriticalExit();
	for (int indx = 0; indx < NCols; indx++) {
		mnCol[indx] = mnY;
		mxCol[indx] = mxY;
		prcCol[indx] = prcY;
		}
}

void arnPVIMiscMatrix::setDims(int rows, int cols)
{
    NCols = cols; 
    NRows = rows;
    mxY = NRows - 1;
	XVals.clear();
	if (mnCol) {delete [] mnCol; mnCol = 0;}
	if (mxCol) {delete [] mxCol; mxCol = 0;}
	if (prcCol) {delete [] prcCol; prcCol = 0;}
	mnCol = new double[NCols];
	if (!mnCol) arnCriticalExit();
	mxCol = new double[NCols];
	if (!mxCol) arnCriticalExit();
	prcCol = new unsigned char[NCols];
	if (!prcCol) arnCriticalExit();
	for (int indx = 0; indx < NCols; indx++) {
		mnCol[indx] = mnY;
		mxCol[indx] = mxY;
		prcCol[indx] = prcY;
		XVals.append("");
		}
}

void arnPVIMiscMatrix::setMinCol(int col, double v)
{
	if (col < NCols) {
		mnCol[col] = v;
		evalPrec(col);
		}
}

void arnPVIMiscMatrix::setMaxCol(int col, double v)
{
	if (col < NCols) {
		mxCol[col] = v;
		evalPrec(col);
		}
}

void arnPVIMiscMatrix::setValue(int row, int col, double val)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long)(typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
	val = checkValue(val);
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = arnNumericFilter::toRawUnsignedChar(val,mnCol[col],mxCol[col]);
                    break;
                case np_none:
                default:
                    (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = (unsigned char) val;
                    break;
                }
            break;
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mnCol[col],mxCol[col]));
                    break;
                case np_none:
                default:
                    (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mnCol[col],mxCol[col]));
                    break;
                case np_none:
                default:
		            (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))) = lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = arnNumericFilter::toRawSignedChar(val,mnCol[col],mxCol[col]);
                    break;
                case np_none:
                default:
		            (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = (signed char) val;
                    break;
                }
            break;
        case nff_s16:
            switch (filterT) {
                case np_linear:
                    (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = smirror((signed short)arnNumericFilter::toRawSignedShort(val,mnCol[col],mxCol[col]));
                    break;
                case np_none:
                default:
		            (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = (signed short) smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mnCol[col],mxCol[col]));
                    break;
                case np_none:
                default:
		            (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))) = (signed long) lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_float:
            arnCriticalExit();
            break;
        case nff_double:
            arnCriticalExit();
            break;
        default:
            (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = (unsigned char) val;
            break;
        }
}

void arnPVIMiscMatrix::setValue(int row, int col, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row, col, tNum);
}

void arnPVIMiscMatrix::setValue(int row, int col)
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

double arnPVIMiscMatrix::value(int row, int col)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long) (typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear(((plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)])),mnCol[col],mxCol[col]);
                case np_none:
                default:
                    return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear((smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))))),mnCol[col],mxCol[col]);
                case np_none:
                default:
                    return ((unsigned short) smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))])))));
                }
        case nff_u32:
            return ((unsigned long) lmirror((*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))])))));
        case nff_s8:
            return ((signed char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]));
        case nff_s16:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear(((signed short) smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))))),mnCol[col],mxCol[col]);
                case np_none:
                default:
                    return ((signed short) smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))])))));
                }
        case nff_s32:
            return ((signed long) lmirror((*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))])))));
        case nff_float:
            arnCriticalExit();
            return -1;
        case nff_double:
            arnCriticalExit();
            return -1;
        default:
            return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]));
		}
}

void arnPVIMiscMatrix::setValueX(int col, QString value)
{
	if (col >= NCols) return;
	XVals[col] = value;
//	QStringList::Iterator it =  XVals.at(col);
//	(*it) = value;
}

QString arnPVIMiscMatrix::valueX(int cols)
{
	
	if (cols >= NCols) return QString("");
//	QStringList::Iterator it =  XVals.at(cols);
//	return (*it);
	return XVals[cols];
}

double arnPVIMiscMatrix::valueY(int rows)
{
	double res = (((mxY - mnY) * rows) / (NRows - 1)) + mnY;
	return res;
}
		
void arnPVIMiscMatrix::evalPrec(int col)
{
    double rawRange;
    double actRange;
	if (col >= NCols) return;
    switch (elemformat) {
        case nff_u8:
        case nff_s8:
            rawRange = 255.0;
            actRange = mxCol[col] - mnCol[col];
            if (actRange == 0) prcCol[col] = 0;
            else if (actRange >= rawRange) prcCol[col] = 0;
            else {
                double logVal = log10(rawRange / actRange);
                if ((logVal / ((int)logVal)) > 1) prcCol[col] = (unsigned char) (1.0 + logVal);
                else prcCol[col] = (unsigned char)logVal;
                }
            break;
        case nff_u16:
        case nff_s16:
            rawRange = 65535.0;
            actRange = mxCol[col] - mnCol[col];
            if (actRange == 0) prcCol[col] = 0;
            else if (actRange >= rawRange) prcCol[col] = 0;
            else {
                double logVal = log10(rawRange / actRange);
                if ((logVal / ((int)logVal)) > 1) prcCol[col] = (unsigned char) (1.0 + logVal);
                else prcCol[col] = (unsigned char)logVal;
                }
            break;
        case nff_u32:
        case nff_s32:
            rawRange = (2147483647.0 + 2147483648.0);
            actRange = mxCol[col] - mnCol[col];
            if (actRange == 0) prcCol[col] = 0;
            else if (actRange >= rawRange) prcCol[col] = 0;
            else {
                double logVal = log10(rawRange / actRange);
                if ((logVal / ((int)logVal)) > 1) prcCol[col] = (unsigned char) (1.0 + logVal);
                else prcCol[col] = (unsigned char)logVal;
                }
            break;
        case nff_none:
        default:
            break;
        }
}
