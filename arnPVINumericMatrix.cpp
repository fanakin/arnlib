/***************************************************************************
                          arnPVINumericMatrix.cpp  -  description
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
#include "arnPVINumericMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVINumericMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListView * parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIMatrix( Opar, parent)
{
    this->init();
}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after )
{
    this->init();

}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIMatrix( Opar, parent, after)
{
    this->init();

}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVINumericMatrix::arnPVINumericMatrix ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIMatrix( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVINumericMatrix::~arnPVINumericMatrix(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVINumericMatrix::init(void)
{
    tpe = apt_NumericMatrix;
	numFormatVal = nrf_dec;
    xAxis = 0;
    yAxis = 0;
    prcX = 0;
    mnX = 0;
    mxX = NCols - 1;
    prcY = 0;
    mnY = 0;
    mxY = NRows - 1;
}

void arnPVINumericMatrix::setDims(int rows, int cols)
{
    if (!xAxis) NCols = cols;
    else NCols = yAxis->rows(); 
    if (!yAxis) NRows = rows;
    else NRows = xAxis->rows();
}

void arnPVINumericMatrix::setValue(int row, int col, double val)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long)(typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    //arnDebug("%d\n",arnNumericFilter::toRawUnsignedChar(val,mn,mx));
                    (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = arnNumericFilter::toRawUnsignedChar(val,mn,mx);
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
                    (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
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
                    (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mn,mx));
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
                    //arnDebug("%d\n",arnNumericFilter::toRawSignedChar(val,mn,mx));
                    (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]))) = arnNumericFilter::toRawSignedChar(val,mn,mx);
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
                    (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))) = smirror((signed short)arnNumericFilter::toRawSignedShort(val,mn,mx));
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
                    (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mn,mx));
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

void arnPVINumericMatrix::setValue(int row, int col, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row, col, tNum);
}

void arnPVINumericMatrix::setValue(int row, int col)
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

double arnPVINumericMatrix::valueX(int cols)
{
	if (!xAxis) {
		double res = (((mxX - mnX) * cols) / (NCols - 1)) + mnX;
		return res;
		}
    return xAxis->value(cols);
}

double arnPVINumericMatrix::valueY(int rows)
{
	if (!yAxis) {
		double res = (((mxY - mnY) * rows) / (NRows - 1)) + mnY;
		return res;
		}
    return yAxis->value(rows);
}

double arnPVINumericMatrix::value(int row, int col)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long) (typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear(((plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)])),mn,mx);
                case np_none:
                default:
                    return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear((smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))))),mn,mx);
                case np_none:
                default:
                    return ((unsigned short) smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))])))));
                }
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear((smirror((*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))))),mn,mx);
                case np_none:
                default:
		            return ((unsigned long) lmirror((*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))])))));
                }
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    return (signed char)arnNumericFilter::linear((signed char)((plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)])),mn,mx);
                case np_none:
                default:
                    return ((signed char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + ((row * NCols) + col)]));
                }

        case nff_s16:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear((signed short)(smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))]))))),mn,mx);
                case np_none:
                default:
		            return ((signed short) smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * ((row * NCols) + col))])))));
                }
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear((signed long)(lmirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))]))))),mn,mx);
                case np_none:
                default:
		            return ((signed long) lmirror((*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * ((row * NCols) + col))])))));
                }
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

