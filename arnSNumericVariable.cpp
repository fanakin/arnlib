/***************************************************************************
                          arnSNumericVariable.cpp  -  description
                             -------------------
    begin                : amr apr 26 2005
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
#include "arnSNumericVariable.h"

 
// ---------------------------------------------------
// ***************************************************
// --------- arnSNumericVariable -------------------
// ***************************************************
// ---------------------------------------------------
arnSNumericVariable::arnSNumericVariable ( QObject * parent, const char * name )
    : arnSVariable( parent, name)
{
    this->init();
}

arnSNumericVariable::~arnSNumericVariable(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnSNumericVariable::init(void)
{
    tpe = sot_NumericVariable;
    elemformat = nff_none;
}


void arnSNumericVariable::setValue(double val)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze > 8) arnCriticalExit();
    val = checkValue(val);
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                  (*((unsigned char*) &(pDataFrame[offst]))) = arnNumericFilter::toRawUnsignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
                    (*((unsigned char*) &(pDataFrame[offst]))) = (unsigned char) val;
                    break;
                }
            break;
        case nff_u16:
            switch (filterT) {
                case np_linear:
                  (*((unsigned short*) &(pDataFrame[offst]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned short*) &(pDataFrame[offst]))) = smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_u32:
            switch (filterT) {
                case np_linear:
                  (*((unsigned long*) &(pDataFrame[offst]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned long*) &(pDataFrame[offst]))) = lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_s8:
            switch (filterT) {
                case np_linear:
                  (*((signed char*) &(pDataFrame[offst]))) = arnNumericFilter::toRawSignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
		            (*((signed char*) &(pDataFrame[offst]))) = (signed char) val;
                    break;
                }
            break;
        case nff_s16:
            switch (filterT) {
                case np_linear:
                  (*((signed short*) &(pDataFrame[offst]))) = smirror((signed short)arnNumericFilter::toRawSignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed short*) &(pDataFrame[offst]))) = (signed short) smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_s32:
            switch (filterT) {
                case np_linear:
                  (*((signed long*) &(pDataFrame[offst]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed long*) &(pDataFrame[offst]))) = (signed long) lmirror((unsigned long) val);
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
            (*((unsigned char*) &(pDataFrame[offst]))) = (unsigned char) val;
            break;
        }
}

void arnSNumericVariable::setValue(const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(tNum);
}

double arnSNumericVariable::value(void)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze > 8) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((unsigned char) (pDataFrame[offst]),mn,mx);
                case np_none:
                default:
                    return ((unsigned char) (pDataFrame[offst]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
		            return arnNumericFilter::linear(((unsigned short) smirror((*((unsigned short*) &(pDataFrame[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((unsigned short) smirror((*((unsigned short*) &(pDataFrame[offst])))));
                }
        case nff_u32:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear(((unsigned long) lmirror((*((unsigned long*) &(pDataFrame[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((unsigned long) lmirror((*((unsigned long*) &(pDataFrame[offst])))));
                }
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((signed char) (pDataFrame[offst]),mn,mx);
                case np_none:
                default:
		            return ((signed char) (pDataFrame[offst]));
                }
        case nff_s16:
            switch (filterT) {
                case np_linear:
		            return arnNumericFilter::linear(((signed short) smirror((*((signed short*) &(pDataFrame[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((signed short) smirror((*((signed short*) &(pDataFrame[offst])))));
                }
        case nff_s32:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear(((signed long) lmirror((*((signed long*) &(pDataFrame[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((signed long) lmirror((*((signed long*) &(pDataFrame[offst])))));
                }
        case nff_float:
            arnCriticalExit();
            return -1;
        case nff_double:
            arnCriticalExit();
            return -1;
        default:
            return ((unsigned char) (pDataFrame[offst]));
        }
}
