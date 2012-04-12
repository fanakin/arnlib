/***************************************************************************
                          arnPVIMiscArray.cpp  -  description
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
#include "arnPVIMiscArray.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnPVIMiscArray ----------------------
// ***************************************************
// ---------------------------------------------------
arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListView * parent )
    : arnPVIArray( Opar, parent)
{
    this->init();
}

arnPVIMiscArray::arnPVIMiscArray( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIArray( Opar, parent)
{
    this->init();
}

arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIArray( Opar, parent, after )
{
    this->init();

}

arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIArray( Opar, parent, after)
{
    this->init();

}

arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIArray( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIArray( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIArray( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIMiscArray::arnPVIMiscArray ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIArray( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIMiscArray::~arnPVIMiscArray(void)
{

}

void arnPVIMiscArray::init(void)
{
    tpe = apt_NumericArray;
    xAxis = 0;
    NRows = 5;
    prcX = 0;
    mnX = 0;
    mxX = NRows - 1;
}

void arnPVIMiscArray::setValue(int row, double val)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long)(typeTonbytes() * row))) arnCriticalExit();
	val = checkValue(val);
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))) = arnNumericFilter::toRawUnsignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
                    (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))) = (unsigned char) val;
                    break;
                }
            break;
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
                    (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)]))) = smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * row)]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * row)]))) = lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))) = arnNumericFilter::toRawSignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
		            (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))) = (signed char) val;
                    break;
                }
            break;
        case nff_s16:
            switch (filterT) {
                case np_linear:
                    (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)]))) = smirror((signed short)arnNumericFilter::toRawSignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)]))) = (signed short) smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * row)]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * row)]))) = (signed long) lmirror((unsigned long) val);
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
            (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]))) = (unsigned char) val;
            break;
        }
}

void arnPVIMiscArray::setValue(int row, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row,tNum);
}

void arnPVIMiscArray::setValue(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    if (col != 0) return;
    bool ok;
    double tNum = pViewer->text(row,col).toDouble(&ok);
    if (!ok) return;
    setValue(row,tNum);
}

double arnPVIMiscArray::valueX(int row)
{
	if (!xAxis) {
		double res = (((mxX - mnX) * row) / (NRows - 1)) + mnX;
		return res;
		}
	return xAxis->value(row);
}

double arnPVIMiscArray::value(int row)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long) (typeTonbytes() * row))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
//                    arnDebug("%g\n",arnNumericFilter::linear((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]),mn,mx));
                    return arnNumericFilter::linear((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]),mn,mx);
                case np_none:
                default:
                    return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((unsigned short) smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)])))),mn,mx);
                case np_none:
                default:
                    return ((unsigned short) smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)])))));
                }
        case nff_u32:
            return ((unsigned long) lmirror((*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * row)])))));
        case nff_s8:
            return ((signed char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]));
        case nff_s16:
            return ((signed short) smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (2 * row)])))));
        case nff_s32:
            return ((signed long) lmirror((*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + (4 * row)])))));
        case nff_float:
            arnCriticalExit();
            return -1;
        case nff_double:
            arnCriticalExit();
            return -1;
        default:
            return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst + row]));
        }
}
