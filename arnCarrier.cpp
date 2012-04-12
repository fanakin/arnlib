/***************************************************************************
                          arnCarrier.cpp  -  description
                             -------------------
    begin                : ven mar 7 2003
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

#include <stdlib.h>
#include "arnCarrier.h"

arnCarrier::arnCarrier(void)
    : Interface()
{
    MaxNerr = 2;
}

arnCarrier::~arnCarrier(void)
{
}

void arnCarrier::SetInterface(Interface *intf)
{
    if (intf == 0) arnCriticalExit();
    if (intf == this) arnCriticalExit();
    usedinterface = intf;
}
//---------------------------------------------------------------------------
void arnCarrier::SetADDRSp(char Add[8])
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned char* Buffer = Disp->GetMessPtr();
    for (unsigned int i = 0; i < 8; i++) Buffer[i + 2] =  arnToUP(Add[i]);
}
//---------------------------------------------------------------------------
void arnCarrier::SetNBTSSp(char NBt[4])
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned char* Buffer = Disp->GetMessPtr();
    for (unsigned int i = 0; i < 4; i++) Buffer[i + 2 + 8] =  arnToUP(NBt[i]);
}
//---------------------------------------------------------------------------
void arnCarrier::SetCommand(char Cmd[2])
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned char* Buffer = Disp->GetMessPtr();
    Buffer[0] = Cmd[0];
    Buffer[1] = Cmd[1];
}
//---------------------------------------------------------------------------
void arnCarrier::SetBYTETOWSp(char* BtoW,unsigned int N)
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned char* Buffer = Disp->GetMessPtr();
    for (unsigned int i = 0; i < N; i++) Buffer[i + 4 + 8 + 2] =  arnToUP(BtoW[i]);
}
unsigned char* arnCarrier::GetMessPtr()
{
    unsigned char* Buffer = usedinterface->GetMessPtr();
    return (Buffer);
}

unsigned int arnCarrier::MaxMessLen()
{
    unsigned int maxlen = usedinterface->MaxMessLen();
    return (maxlen - 16); // ex. :RDxxxxxxxxyyyychks
}

bool arnCarrier::TxMess(unsigned int txlen)
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned int nerr = MaxNerr;
    while ((! Disp->TxMess(txlen)) && (--nerr));
    if (nerr) return true;
    else return false;
}

bool arnCarrier::RxMess(unsigned int *rxlen)
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned int nerr = MaxNerr;
    while ((!Disp->RxMess(rxlen)) && (--nerr));
    if (nerr) return true;
    else return false;
}

bool arnCarrier::TxRxMess(unsigned int txlen, unsigned int *rxlen, unsigned int wfa)
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned int nerr = MaxNerr;
    while ((!Disp->TxRxMess(txlen,rxlen,wfa)) && (--nerr));
    if (nerr) return true;
    else return false;
}

