/***************************************************************************
                          arnWTmonitor.cpp  -  description
                             -------------------
    begin                : sab mar 8 2003
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

#include <stdio.h>
#include <string.h>
#include "arnWTmonitor.h"

arnWTmonitor::arnWTmonitor(void)
    : arnCarrier()
{
}

arnWTmonitor::~arnWTmonitor(void)
{
}

//---------------------------------------------------------------------------
void arnWTmonitor::SetADDRSp(char Add[8])
{
	PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
	unsigned char* Buffer = Disp->GetMessPtr();
	for (unsigned int i = 0; i < 8; i++) Buffer[i + 2] =  arnToUP(Add[i]);
}
//---------------------------------------------------------------------------
void arnWTmonitor::SetNBTSSp(char NBt[4])
{
	PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
	unsigned char* Buffer = Disp->GetMessPtr();
	for (unsigned int i = 0; i < 2; i++) Buffer[i + 2 + 8] =  arnToUP(NBt[i]);
}
//---------------------------------------------------------------------------
void arnWTmonitor::SetCommand(char Cmd[2])
{
    PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
    unsigned char* Buffer = Disp->GetMessPtr();
    if (Cmd[0] == '?') ((TextMSPPP*) (Disp->GetProtocol()))->SetResetReq(Cmd[0]);
    else {
    	((TextMSPPP*) (Disp->GetProtocol()))->SetResetReq(0);
    	Buffer[1] = Cmd[0];
        }
}
//---------------------------------------------------------------------------
void arnWTmonitor::SetBYTETOWSp(char* BtoW,unsigned int N)
{
	PlainDispatcher* Disp = (PlainDispatcher*) usedinterface;
	unsigned char* Buffer = Disp->GetMessPtr();
	for (unsigned int i = 0; i < N; i++) Buffer[i + 2 + 8 + 2] =  arnToUP(BtoW[i]);
}
//---------------------------------------------------------------------------
unsigned int arnWTmonitor::MaxMessLen()
{
    unsigned int maxlen = usedinterface->MaxMessLen();
    return (maxlen - 13);
}
//---------------------------------------------------------------------------
unsigned char* arnWTmonitor::GetMemorySeg(unsigned char* Dest,unsigned int* LenDest,unsigned char* Add,unsigned int Num)
{
    unsigned int txlen,rxlen;
    char ts[16] = "";

	SetCommand((char*)"R");
    sprintf(ts,"%8.8x",(int) Add);
    SetADDRSp(ts);
    sprintf(ts,"%2.2x",(int) Num);
    SetNBTSSp(ts);
    txlen = 11;

    bool res = this->TxRxMess(txlen,&rxlen,5);
    if (!res) {(*LenDest) = 0;return NULL;}
    else {
        (*LenDest) = rxlen;
        strncpy((char*) Dest,(char*) this->GetMessPtr() + 4,rxlen);
        return Dest;
        }
}
//---------------------------------------------------------------------------
bool arnWTmonitor::SetMemorySeg(unsigned char* Add,unsigned int Num,unsigned char* ArrToW)
{
    unsigned int txlen,rxlen;
    char ts[16] = "";

	SetCommand((char*)"W");
    sprintf(ts,"%8.8x",(int) Add);
    SetADDRSp(ts);
    sprintf(ts,"%2.2x",(int) Num);
    SetNBTSSp(ts);
    SetBYTETOWSp((char*) ArrToW,(unsigned int) (2 * Num));
    txlen = 11 + (2 * Num);
    bool res = this->TxRxMess(txlen,&rxlen,5);
    if (!res) {return false;}
    else {
        if (strncmp((char*) this->GetMessPtr(),":OK!",rxlen) == 0) return true;
        else return false;
        }
}
//---------------------------------------------------------------------------
bool arnWTmonitor::SendReset(void)
{
    return false;
}
//---------------------------------------------------------------------------
bool arnWTmonitor::ReceiveConfiguration(void)
{
    return false;
}
