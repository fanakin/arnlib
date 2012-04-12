/***************************************************************************
                          arnSStringVariable.cpp  -  description
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
#include "arnSStringVariable.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSStringVariable --------------------
// ***************************************************
// ---------------------------------------------------
arnSStringVariable::arnSStringVariable ( QObject * parent, const char * name )
    : arnSVariable( parent, name)
{
    this->init();
}

arnSStringVariable::~arnSStringVariable(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnSStringVariable::init(void)
{
    tpe = sot_StringVariable;
    elemformat = nff_none;
}

          
void arnSStringVariable::setValue(const QString& val)
{
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (elemformat != nff_string) arnCriticalExit();
    if (!sze) arnCriticalExit();
    char* pT = (char*)(&(pDataFrame[offst]));
    memset(pT,0,sze);
    memcpy(pT,val.latin1(),((((unsigned long)val.length()) < sze) ? val.length() : sze));
}


QString arnSStringVariable::value(void)
{
    QString res;
    if (!pDataFrame) arnCriticalExit();
    if (elemformat == nff_none) arnCriticalExit();
    if (elemformat != nff_string) arnCriticalExit();
    if (!sze) arnCriticalExit();
    char* pT = (char*)(&(pDataFrame[offst]));
    res = QString(pT);
    if (((unsigned long)res.length()) >= sze) res.truncate(sze);
    return res;  
}
