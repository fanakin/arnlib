/***************************************************************************
                          arnSNumericMatrix.cpp  -  description
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
#include "arnSNumericMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSNumericMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnSNumericMatrix::arnSNumericMatrix ( QObject * parent, const char * name )
    : arnSMatrix( parent, name)
{
    this->init();
}

arnSNumericMatrix::~arnSNumericMatrix(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnSNumericMatrix::init(void)
{
    tpe = sot_NumericMatrix;
    xAxis = 0;
    yAxis = 0;
    prcX = 0;
    mnX = 0;
    mxX = NCols - 1;
    prcY = 0;
    mnY = 0;
    mxY = NRows - 1;
}

void arnSNumericMatrix::setDims(int rows, int cols)
{
    if (!xAxis) NCols = cols;
    else NCols = yAxis->rows(); 
    if (!yAxis) NRows = rows;
    else NRows = xAxis->rows();
}

void arnSNumericMatrix::setValue(int row, int col, double val)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long)(typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    //arnDebug("%d\n",arnNumericFilter::toRawUnsignedChar(val,mn,mx));
                    (*((unsigned char*) &(pDataFrame[offst + ((row * NCols) + col)]))) = arnNumericFilter::toRawUnsignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
                    (*((unsigned char*) &(pDataFrame[offst + ((row * NCols) + col)]))) = (unsigned char) val;
                    break;
                }
            break;
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    (*((unsigned short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
                    (*((unsigned short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))]))) = smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    (*((unsigned long*) &(pDataFrame[offst + (4 * ((row * NCols) + col))]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned long*) &(pDataFrame[offst + (4 * ((row * NCols) + col))]))) = lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    //arnDebug("%d\n",arnNumericFilter::toRawUnsignedChar(val,mn,mx));
                    (*((signed char*) &(pDataFrame[offst + ((row * NCols) + col)]))) = arnNumericFilter::toRawSignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
		            (*((signed char*) &(pDataFrame[offst + ((row * NCols) + col)]))) = (signed char) val;
                    break;
                }
            break;
        case nff_s16:
            switch (filterT) {
                case np_linear:
                    (*((signed short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))]))) = smirror((signed short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))]))) = (signed short) smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    (*((signed long*) &(pDataFrame[offst + (4 * ((row * NCols) + col))]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed long*) &(pDataFrame[offst + (4 * ((row * NCols) + col))]))) = (signed long) lmirror((unsigned long) val);
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
            (*((unsigned char*) &(pDataFrame[offst + ((row * NCols) + col)]))) = (unsigned char) val;
            break;
        }
}

void arnSNumericMatrix::setValue(int row, int col, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row, col, tNum);
}

void arnSNumericMatrix::setValue(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    bool ok;
    double tNum = pViewer->text(row,col).toDouble(&ok);
    if (!ok) return;
    setValue(row, col ,tNum);
}

double arnSNumericMatrix::valueX(int cols)
{
	if (!xAxis) {
		double res = (((mxX - mnX) * cols) / (NCols - 1)) + mnX;
		return res;
		}
    return xAxis->value(cols);
}

double arnSNumericMatrix::valueY(int rows)
{
	if (!yAxis) {
		double res = (((mxY - mnY) * rows) / (NRows - 1)) + mnY;
		return res;
		}
    return yAxis->value(rows);
}

double arnSNumericMatrix::value(int row, int col)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze < ((unsigned long) (typeTonbytes() * ((row * NCols) + col)))) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear(((pDataFrame[offst + ((row * NCols) + col)])),mn,mx);
                case np_none:
                default:
                    return ((unsigned char) (pDataFrame[offst + ((row * NCols) + col)]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
                    return  arnNumericFilter::linear((smirror((*((unsigned short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))]))))),mn,mx);
                case np_none:
                default:
                    return ((unsigned short) smirror((*((unsigned short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))])))));
                }
        case nff_u32:
            return ((unsigned long) lmirror((*((unsigned long*) &(pDataFrame[offst + (4 * ((row * NCols) + col))])))));
        case nff_s8:
            return ((signed char) (pDataFrame[offst + ((row * NCols) + col)]));
        case nff_s16:
            return ((signed short) smirror((*((signed short*) &(pDataFrame[offst + (2 * ((row * NCols) + col))])))));
        case nff_s32:
            return ((signed long) lmirror((*((signed long*) &(pDataFrame[offst + (4 * ((row * NCols) + col))])))));
        case nff_float:
            arnCriticalExit();
            return -1;
        case nff_double:
            arnCriticalExit();
            return -1;
        default:
            return ((unsigned char) (pDataFrame[offst + ((row * NCols) + col)]));
        }
}

