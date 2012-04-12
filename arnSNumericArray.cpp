/***************************************************************************
                          arnSNumericArray.cpp  -  description
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
#include "arnSNumericArray.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSNumericArray ----------------------
// ***************************************************
// ---------------------------------------------------
arnSNumericArray::arnSNumericArray ( QObject * parent, const char * name )
    : arnSArray( parent , name)
{
    this->init();
}


arnSNumericArray::~arnSNumericArray(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnSNumericArray::init(void)
{
    tpe = sot_NumericArray;
    xAxis = 0;
    NRows = 5;
    prcX = 0;
    mnX = 0;
    mxX = NRows - 1;
}

void arnSNumericArray::setValue(int row, double val)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long)(typeTonbytes() * row))) arnCriticalExit();
	val = checkValue(val);
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    (*((unsigned char*) &(pDataFrame[offst + row]))) = arnNumericFilter::toRawUnsignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
                    (*((unsigned char*) &(pDataFrame[offst + row]))) = (unsigned char) val;
                    break;
                }
            break;
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    (*((unsigned short*) &(pDataFrame[offst + (2 * row)]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
                    (*((unsigned short*) &(pDataFrame[offst + (2 * row)]))) = smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    (*((unsigned long*) &(pDataFrame[offst + (4 * row)]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned long*) &(pDataFrame[offst + (4 * row)]))) = lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    (*((signed char*) &(pDataFrame[offst + row]))) = arnNumericFilter::toRawSignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
		            (*((signed char*) &(pDataFrame[offst + row]))) = (signed char) val;
                    break;
                }
            break;
        case nff_s16:
            switch (filterT) {
                case np_linear:
                    (*((signed short*) &(pDataFrame[offst + (2 * row)]))) = smirror((signed short)arnNumericFilter::toRawSignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed short*) &(pDataFrame[offst + (2 * row)]))) = (signed short) smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    (*((signed long*) &(pDataFrame[offst + (4 * row)]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed long*) &(pDataFrame[offst + (4 * row)]))) = (signed long) lmirror((unsigned long) val);
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
            (*((unsigned char*) &(pDataFrame[offst + row]))) = (unsigned char) val;
            break;
        }
}

void arnSNumericArray::setValue(int row, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row,tNum);
}

void arnSNumericArray::setValue(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    if (col != 0) return;
    bool ok;
    double tNum = pViewer->text(row,col).toDouble(&ok);
    if (!ok) return;
    setValue(row,tNum);
}

double arnSNumericArray::valueX(int row)
{
	if (!xAxis) {
		double res = (((mxX - mnX) * row) / (NRows - 1)) + mnX;
		return res;
		}
	return xAxis->value(row);
}

double arnSNumericArray::value(int row)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long) (typeTonbytes() * row))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((unsigned char) (pDataFrame[offst + row]),mn,mx);
                case np_none:
                default:
                    return ((unsigned char) (pDataFrame[offst + row]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((unsigned short) smirror((*((unsigned short*) &(pDataFrame[offst + (2 * row)])))),mn,mx);
                case np_none:
                default:
                    return ((unsigned short) smirror((*((unsigned short*) &(pDataFrame[offst + (2 * row)])))));
                }
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((unsigned long) lmirror((*((unsigned long*) &(pDataFrame[offst + (4 * row)])))),mn,mx);
                case np_none:
                default:
		            return ((unsigned long) lmirror((*((unsigned long*) &(pDataFrame[offst + (4 * row)])))));
                }
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((signed char) (pDataFrame[offst + row]),mn,mx);
                case np_none:
                default:
		            return ((signed char) (pDataFrame[offst + row]));
                }
        case nff_s16:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((signed short) smirror((*((unsigned short*) &(pDataFrame[offst + (2 * row)])))),mn,mx);
                case np_none:
                default:
		            return ((signed short) smirror((*((signed short*) &(pDataFrame[offst + (2 * row)])))));
                }
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((signed long) lmirror((*((signed long*) &(pDataFrame[offst + (4 * row)])))),mn,mx);
                case np_none:
                default:
		            return ((signed long) lmirror((*((signed long*) &(pDataFrame[offst + (4 * row)])))));
                }
        case nff_float:
            arnCriticalExit();
            return -1;
        case nff_double:
            arnCriticalExit();
            return -1;
        default:
            return ((unsigned char) (pDataFrame[offst + row]));
        }
}
