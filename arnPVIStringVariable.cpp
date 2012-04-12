/***************************************************************************
                          arnPVIStringVariable.cpp  -  description
                             -------------------
    begin                : mer set 24 2003
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
#include "arnPVIStringVariable.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnPVIStringVariable --------------------
// ***************************************************
// ---------------------------------------------------
arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListView * parent )
    : arnPVIVariable( Opar, parent)
{
    this->init();
}

arnPVIStringVariable::arnPVIStringVariable( QObject * Opar, Q3ListViewItem *parent )
    : arnPVIVariable( Opar, parent)
{
    this->init();
}

arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after )
    : arnPVIVariable( Opar, parent, after )
{
    this->init();

}

arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after )
    : arnPVIVariable( Opar, parent, after)
{
    this->init();

}

arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListView *parent, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListViewItem * parent, QString label1, QString label2, QString label3 , QString label4, QString label5 , QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, label1, label2, label3, label4, label5, label6, label7, label8 )
{
    this->init();

}

arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringVariable::arnPVIStringVariable ( QObject * Opar, Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2, QString label3, QString label4, QString label5, QString label6, QString label7, QString label8)
    : arnPVIVariable( Opar, parent, after, label1, label2, label3, label4, label5, label6, label7, label8)
{
    this->init();

}

arnPVIStringVariable::~arnPVIStringVariable(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnPVIStringVariable::init(void)
{
    tpe = apt_StringVariable;
    elemformat = nff_none;
}

          
void arnPVIStringVariable::setValue(const QString& val)
{
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (elemformat != nff_string) arnCriticalExit();
    if (!sze) arnCriticalExit();
    char* pT = (char*)(&(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]));
    memset(pT,0,sze);
    memcpy(pT,val.latin1(),((val.length() < ((int)sze)) ? val.length() : sze));
}


QString arnPVIStringVariable::value(void)
{
    QString res;
    if (!plowDevice) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (elemformat != nff_string) arnCriticalExit();
    if (!sze) arnCriticalExit();
    char* pT = (char*)(&(plowDevice->getParContainer().getmemWrapper()->memoryImg.arr[offst]));
    res = QString(pT);
    if (res.length() >= (int)sze) res.truncate(sze);
    return res;  
}
