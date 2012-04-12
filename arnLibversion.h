/***************************************************************************
                          arnLibversion.h  -  description
                             -------------------
    begin                : lun gen 27 2003
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

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
#ifndef ArnLibversionH
#define ArnLibversionH
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>

/*!
* ver 0.0.4.33, data 04/01/2010
* -) Introduce il componente arnPacketVisualizerSelectPanel, per selezionare a run time 
*    i canali di console da visualizzare
* -) Introduce i componente arnEnThermoPacketItem, che aggiunge il valore numerico in calce 
*    alla barra;
*/
const char* arnGetVersion(void);


#endif

#ifdef __cplusplus
}
#endif
