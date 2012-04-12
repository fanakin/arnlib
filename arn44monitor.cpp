/***************************************************************************
                          arn44monitor.cpp  -  description
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
#include "arn44monitor.h"

arn44monitor::arn44monitor(void)
    : arnCarrier()
{
}

arn44monitor::~arn44monitor(void)
{

}

//---------------------------------------------------------------------------
unsigned char* arn44monitor::GetMemorySeg(unsigned char* Dest,unsigned int* LenDest,unsigned char* Add,unsigned int Num)
{
    unsigned int txlen,rxlen;
    char ts[32] = "";

	SetCommand((char*)"RD");
    sprintf(ts,"%8.8x",(int) Add);
    SetADDRSp(ts);
    sprintf(ts,"%4.4x",(int) Num);
    SetNBTSSp(ts);
//    SetADDRSp(AnsiString(IntToHex((int) Add,8)).c_str());
//    SetNBTSSp(AnsiString(IntToHex((int) Num,4)).c_str());
    txlen = 15;
    bool res = this->TxRxMess(txlen,&rxlen,0);
    if (!res) {(*LenDest) = 0;return NULL;}
    else {
        (*LenDest) = rxlen;
        strncpy((char*) Dest,(char*) this->GetMessPtr() + 2,rxlen);
        return Dest;
        }
}
//---------------------------------------------------------------------------
bool arn44monitor::SetMemorySeg(unsigned char* Add,unsigned int Num,unsigned char* ArrToW)
{
    unsigned int txlen,rxlen;
    char ts[32] = "";

	SetCommand((char*)"WR");
    sprintf(ts,"%8.8x",(int) Add);
    SetADDRSp(ts);
    sprintf(ts,"%4.4x",(int) Num);
    SetNBTSSp(ts);
//    SetADDRSp(AnsiString(IntToHex((int) Add,8)).c_str());
//    SetNBTSSp(AnsiString(IntToHex((int) Num,4)).c_str());
    SetBYTETOWSp((char*) ArrToW,(unsigned int) (2 * Num));
    txlen = 15 + (2 * Num);
    bool res = this->TxRxMess(txlen,&rxlen,0);
    if (!res) {return false;}
    return true;
}
//---------------------------------------------------------------------------
bool arn44monitor::SendReset(void)
{
    qDebug() << __FUNCTION__;

    unsigned int txlen,rxlen;

	SetCommand((char*)"##");
    txlen = 3;
    bool res = this->TxRxMess(txlen,&rxlen,0);
    if (!res) {return false;}
    return true;
}
//---------------------------------------------------------------------------
bool arn44monitor::ReceiveConfiguration(unsigned char* bff, int len)
{
    unsigned int txlen,rxlen;
    char ts[32] = "";

	SetCommand((char*)"CF");
    sprintf(ts,"%8.8x",(int) 0);
    SetADDRSp(ts);
    sprintf(ts,"%4.4x",len);
    SetNBTSSp(ts);
    txlen = 15;
    bool res = this->TxRxMess(txlen,&rxlen,0);
    if (!res) {arnDebug("passo1\n");return false;}
    else {
        int rlen = 0;
        char* p = ((char*) (this->GetMessPtr()));
        p += 2;// skip "DT"
        if (!arnHexDigitToBin(bff,&rlen,p, 2 * len)) {arnDebug("passo2\n");return false;}
    if (rlen != len) {arnDebug("passo3\n");return false;}
        return true;
        }
}
