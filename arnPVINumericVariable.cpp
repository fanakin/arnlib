/***************************************************************************
                          arnPVINumericVariable.cpp  -  description
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
#include "arnPVINumericVariable.h"

 
// ---------------------------------------------------
// ***************************************************
// --------- arnPVINumericVariable -------------------
// ***************************************************
// ---------------------------------------------------
arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListView * parent )
    : arnPVIVariable( Opar, parent)
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIVariable( Opar, parent)
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIVariable( Opar, parent, after )
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIVariable( Opar, parent, after)
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();
}

arnPVINumericVariable::arnPVINumericVariable ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();
}

arnPVINumericVariable::~arnPVINumericVariable(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVINumericVariable::init(void)
{
    tpe = apt_NumericVariable;
    elemformat = nff_none;
	numFormatVal = nrf_dec;
}


void arnPVINumericVariable::setValue(double val)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze > 8) arnCriticalExit();
	val = checkValue(val);
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                  (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = arnNumericFilter::toRawUnsignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
                    (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = (unsigned char) val;
                    break;
                }
            break;
        case nff_u16:
            switch (filterT) {
                case np_linear:
                  (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = smirror((unsigned short)arnNumericFilter::toRawUnsignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_u32:
            switch (filterT) {
                case np_linear:
                  (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = lmirror((unsigned long)arnNumericFilter::toRawUnsignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = lmirror((unsigned long) val);
                    break;
                }
            break;
        case nff_s8:
            switch (filterT) {
                case np_linear:
                  (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = arnNumericFilter::toRawSignedChar(val,mn,mx);
                    break;
                case np_none:
                default:
                  (*((signed char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = (signed char) val;

                    break;
                }
            break;
        case nff_s16:
            switch (filterT) {
                case np_linear:
                  (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = smirror((signed short)arnNumericFilter::toRawSignedShort(val,mn,mx));
                    break;
                case np_none:
                default:
                    (*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = (signed short) smirror((unsigned short) val);
                    break;
                }
            break;
        case nff_s32:
            switch (filterT) {
                case np_linear:
                  (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = lmirror((signed long)arnNumericFilter::toRawSignedLong(val,mn,mx));
                    break;
                case np_none:
                default:
		            (*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = (signed long) lmirror((unsigned long) val);
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
            (*((unsigned char*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))) = (unsigned char) val;
            break;
        }
	updateValueColumn();
}

void arnPVINumericVariable::setValue(const QString& val)
{
    bool ok;
	double tNum;
	switch (numFormatVal) {
		case nrf_hex:
			tNum = val.toInt(&ok,16);
			if (!ok) return;
			break;
		case nrf_bin:
			tNum = val.toInt(&ok,2);
			if (!ok) return;
			break;
		case nrf_dec:
		default:
			tNum = val.toDouble(&ok);
			if (!ok) return;
			break;
	}
	setValue(tNum);
}

double arnPVINumericVariable::value(void)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (!sze || sze > 8) arnCriticalExit();
    switch (elemformat) {
        case nff_u8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]),mn,mx);
                case np_none:
                default:
                    return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]));
                }
        case nff_u16:
            switch (filterT) {
                case np_linear:
		            return arnNumericFilter::linear(((unsigned short) smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((unsigned short) smirror((*((unsigned short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst])))));
                }
        case nff_u32:
            switch (filterT) {
                case np_linear:
		            return arnNumericFilter::linear(((unsigned long) lmirror((*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((unsigned long) lmirror((*((unsigned long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst])))));
                }
        case nff_s8:
            switch (filterT) {
                case np_linear:
                    return arnNumericFilter::linear((signed char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]),mn,mx);
                case np_none:
                default:
                    return ((signed char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]));
                }
        case nff_s16:
            switch (filterT) {
                case np_linear:
		            return arnNumericFilter::linear(((signed short) smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))))),mn,mx);
                case np_none:
                default:
                    return ((signed short) smirror((*((signed short*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst])))));
                }
        case nff_s32:
            switch (filterT) {
                case np_linear:
		            return arnNumericFilter::linear(((signed long) lmirror((*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]))))),mn,mx);
                case np_none:
                default:
		            return ((signed long) lmirror((*((signed long*) &(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst])))));
                }
        case nff_float:
            arnCriticalExit();
            return -1;
        case nff_double:
            arnCriticalExit();
            return -1;
        default:
            return ((unsigned char) (plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]));
        }
}

void arnPVINumericVariable::updateValueColumn(void)
{
	QString t;
	// se della colonna values se c'e'.
	if (!prc) {
		switch (numFormatVal) {
			case nrf_hex:
				t.setNum((int)value(),16);
				break;
			case nrf_bin:
				t.setNum((int)value(),2);
				break;
			case nrf_dec:
			default:
				t.setNum(value());
				break;
		}
	}
	else {
		switch (numFormatVal) {
			case nrf_hex:
				t.setNum((int)value(),16);
				break;
			case nrf_bin:
				t.setNum((int)value(),2);
				break;
			case nrf_dec:
			default:
				t.setNum(value(),'f',prc);
				break;
		}
	}
	setText (1,t);
}
