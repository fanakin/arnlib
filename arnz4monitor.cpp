/***************************************************************************
                          arnz4monitor.cpp  -  description
                             -------------------
    begin                : mer feb 26 2003
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

#include "stdio.h"
#include "string.h"
#include "arnz4monitor.h"

#define WTO			0
arnZ4monitor::arnZ4monitor(void)
    : arnCarrier()
{
}

arnZ4monitor::~arnZ4monitor(void)
{

}


//---------------------------------------------------------------------------
unsigned char* arnZ4monitor::GetMemorySeg(unsigned char* Dest,unsigned int* LenDest,unsigned char* Add,unsigned int Num)
{
    unsigned int txlen,rxlen;
    char ts[32] = "";

	SetCommand((char*)"RD");
    sprintf(ts,"%8.8x",(int) Add);
    SetADDRSp(ts);
    sprintf(ts,"%4.4x",(int) Num);
    SetNBTSSp(ts);
    txlen = 15;
    bool res = this->TxRxMess(txlen,&rxlen,WTO);
    if (!res) {(*LenDest) = 0;return NULL;}
    else {
        (*LenDest) = rxlen;
        strncpy((char*) Dest,(char*) this->GetMessPtr() + 2,rxlen);
//        if (!arnHexDigitToBin(Dest,(int*)LenDest,(char*) this->GetMessPtr() + 2,rxlen)) return 0;
        return Dest;
        }
}
//---------------------------------------------------------------------------
bool arnZ4monitor::SetMemorySeg(unsigned char* Add,unsigned int Num,unsigned char* ArrToW)
{
    unsigned int txlen,rxlen;
    char ts[32] = "";

	SetCommand((char*)"WR");
    sprintf(ts,"%8.8x",(int) Add);
    SetADDRSp(ts);
    sprintf(ts,"%4.4x",(int) Num);
    SetNBTSSp(ts);
    SetBYTETOWSp((char*) ArrToW,(unsigned int) (2 * Num));
    txlen = 15 + (2 * Num);
    bool res = this->TxRxMess(txlen,&rxlen,WTO);
    if (!res) {return false;}
    return true;
}
//---------------------------------------------------------------------------
bool arnZ4monitor::SendReset(void)
{
    unsigned int txlen,rxlen;

	SetCommand((char*)"##");
    txlen = 3;
    bool res = this->TxRxMess(txlen,&rxlen,WTO);
    if (!res) {return false;}
    return true;
}
//---------------------------------------------------------------------------
//bool arnZ4monitor::ReceiveConfiguration(void)
//{
//    unsigned int txlen,rxlen;
//    char ts[32] = "";
//
//    SetCommand("CF");
//    sprintf(ts,"%8.8x",(int) 0);
//    SetADDRSp(ts);
//    sprintf(ts,"%4.4x",(int) sizeof(Z4Comm_t));
//    SetNBTSSp(ts);
//    txlen = 15;
//    bool res = this->TxRxMess(txlen,&rxlen,5);
//    if (!res) {return false;}
//    else {
//        char tp[32];
//        char* p = ((char*) (this->GetMessPtr()));
//        p += 2;strncpy(tp,p,4);tp[4] = 0;
//        Z4Cfg.Length = (unsigned short)atolh(tp);
//
//        p += 4;strncpy(tp,p,4);tp[4] = 0;
//        Z4Cfg.consPackDim = (unsigned short)atolh(tp);
//
//        p += 4;strncpy(tp,p,8);tp[8] = 0;
//        Z4Cfg.ConsPack = (void*) atolh(tp);
//
//        p += 8;strncpy(tp,p,8);tp[8] = 0;
//        Z4Cfg.Cod = (CodesSTR_t*) atolh(tp);
//
//        p += 8;strncpy(tp,p,8);tp[8] = 0;
//        Z4Cfg.PasswordAddr = (unsigned long*)atolh(tp);
//
//        p += 8;strncpy(tp,p,4);tp[4] = 0;
//        Z4Cfg.free = (unsigned short)atolh(tp);
//
//        p += 4;strncpy(tp,p,4);tp[4] = 0;
//        Z4Cfg.ToolsDef_tDim = (unsigned short)atolh(tp);
//
//        p += 4;strncpy(tp,p,8);tp[8] = 0;
//        Z4Cfg.ToolsPars = (void*) atolh(tp);
//
//        p += 8; // attenzione
//        return true;
//        }
//}

//---------------------------------------------------------------------------
bool arnZ4monitor::ReceiveConfiguration(unsigned char* bff, int len)
{
    unsigned int txlen,rxlen;
    char ts[32] = "";

	SetCommand((char*)"CF");
    sprintf(ts,"%8.8x",(int) 0);
    SetADDRSp(ts);
    sprintf(ts,"%4.4x",len);
    SetNBTSSp(ts);
    txlen = 15;
    bool res = this->TxRxMess(txlen,&rxlen,WTO);
    if (!res) {return false;}
    else {
        int rlen = 0;
        char* p = ((char*) (this->GetMessPtr()));
        p += 2;// skip "DT"
        if (!arnHexDigitToBin(bff,&rlen,p, 2 * len)) return false;
	if (rlen != len) return false;
        return true;
        }
}


