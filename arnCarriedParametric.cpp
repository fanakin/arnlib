/***************************************************************************
                          arnCarriedParametric.cpp  -  description
                             -------------------
    begin                : dom mar 9 2003
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

#include "arnCarriedParametric.h"

#define __UI_OUTPUT(arg...) do {QString uioutbff; \
    uioutbff.sprintf(arg); \
    if (this->outDisplay){ this->outDisplay->showMessage(uioutbff);}\
    } while (0)
#define __PROCESS() do {if (appl) {appl->processEvents();}} while (0)


arnCarriedParametric::arnCarriedParametric(unsigned int dim)
    : arnParametric(dim)
{
	pMon = 0;
}

arnCarriedParametric::arnCarriedParametric(unsigned int dim,unsigned int nSegs)
    : arnParametric(dim,nSegs)
{
	pMon = 0;
}

arnCarriedParametric::arnCarriedParametric(unsigned int dim,arnCarrier *Mon)
    : arnParametric(dim)
{
    pMon = Mon;
}

arnCarriedParametric::arnCarriedParametric(const arnCarriedParametric& aPar)
    : arnParametric(aPar)
{
    pMon = aPar.pMon;
}

arnCarriedParametric::~arnCarriedParametric(void)
{
}

arnCarriedParametric& arnCarriedParametric::operator = (const arnCarriedParametric& aPar)
{
    pMon = aPar.pMon;
    (*pMappa) = (*(aPar.pMappa));
    return (*this);
}

bool arnCarriedParametric::send(void)
{
    if (!pMon) return false;
    unsigned int PackSize = pMon->MaxMessLen() / 2;
    unsigned int numOfPacks = pMappa->getmemWrapper()->memImageDim / PackSize;
    unsigned int TotNumBytesToSend = pMappa->count() * pMappa->getmemWrapper()->memImageDim;
    unsigned int CurNumBytesSent = 0;
    double Perc = 0;
    for (unsigned int indx = 0; indx < pMappa->count(); indx++) {
        unsigned int addr =  pMappa->getmemWrapper(indx)->memImageDisp;
        unsigned int ptr = 0;
        char bff[2048];
        int ltbff;

        memset(bff,0,sizeof(bff));
        for (unsigned int j = 0; j < numOfPacks; j++) {
            if (!arnBinToHexDigit(bff,&ltbff,(unsigned char*)(pMappa->getmemWrapper(indx)->memoryImg.arr + ptr),PackSize)) {
				return false;
				}
            if (ltbff != int(2 * PackSize)) {
				return false;
				}
			ltbff = ((ltbff % 2) == 0) ? (ltbff / 2) : (ltbff / 2 + 1);
            if (!pMon->SetMemorySeg((unsigned char*)(addr + ptr), ltbff, (unsigned char*)bff)) {
                return false;
                }
            ptr += PackSize;
            CurNumBytesSent += PackSize;
            Perc = 100.00 * (((double)CurNumBytesSent) / TotNumBytesToSend);
            __UI_OUTPUT("Trasferimento in corso... %d %s ricevuto.\n",int(Perc),"%");
            __PROCESS();
            }
        if (!arnBinToHexDigit(bff,&ltbff,(unsigned char*)(pMappa->getmemWrapper(indx)->memoryImg.arr + ptr),pMappa->getmemWrapper(indx)->memImageDim - ptr)) {
			return false;
			}
        if (ltbff != int(2 * (pMappa->getmemWrapper(indx)->memImageDim - ptr))) {
			return false;
			}
		ltbff = ((ltbff % 2) == 0) ? (ltbff / 2) : (ltbff / 2 + 1);
        if (!pMon->SetMemorySeg((unsigned char*)(addr + ptr),ltbff,(unsigned char*)bff)) {
            return false;
            }
        ptr += PackSize;
        CurNumBytesSent += PackSize;
        Perc = 100.00 * (((double)CurNumBytesSent) / TotNumBytesToSend);
        __UI_OUTPUT("Trasferimento in corso... %d %s ricevuto.\n",int(Perc),"%");
        __PROCESS();
        }
    __UI_OUTPUT("Trasferimento terminato con successo.\n");
    __PROCESS();
    return true;
}

bool arnCarriedParametric::receive(void)
{
    if (!pMon) return false;
    unsigned int PackSize = pMon->MaxMessLen() / 2;
    unsigned int numOfPacks = pMappa->getmemWrapper()->memImageDim / PackSize;
    unsigned int TotNumBytesToSend = pMappa->count() * pMappa->getmemWrapper()->memImageDim;
    unsigned int CurNumBytesSent = 0;
    double Perc = 0;
    for (unsigned int indx = 0; indx < pMappa->count(); indx++) {
        unsigned int addr =  pMappa->getmemWrapper(indx)->memImageDisp;
        unsigned int ptr = 0;
        char bff[2048];
        unsigned int lbff;
        int ltbff;

        memset(bff,0,sizeof(bff));
        for (unsigned int j = 0; j < numOfPacks; j++) {
            if (!pMon->GetMemorySeg((unsigned char*)bff, &lbff, (unsigned char*)(addr + ptr), PackSize)) {
                return false;
                }
            if (lbff != (2 * PackSize)) {
				return false;
				}
            arnHexDigitToBin((unsigned char*)(pMappa->getmemWrapper(indx)->memoryImg.arr + ptr),&ltbff,(char*) bff,lbff);
            if ((2 * ((unsigned int)ltbff)) != lbff) {
				return false;
				}
            ptr += PackSize;
            CurNumBytesSent += PackSize;
            Perc = 100.00 * (((double)CurNumBytesSent) / TotNumBytesToSend);
            __UI_OUTPUT("Trasferimento in corso... %d %s ricevuto.\n",int(Perc),"%");
            __PROCESS();
            }
        if (!pMon->GetMemorySeg((unsigned char*)bff, &lbff, (unsigned char*)(addr + ptr),pMappa->getmemWrapper(indx)->memImageDim - ptr)) {
            return false;
            }
        if (lbff != (2 * (pMappa->getmemWrapper(indx)->memImageDim - ptr))) {
			return false;
			}
        arnHexDigitToBin((unsigned char*)(pMappa->getmemWrapper(indx)->memoryImg.arr + ptr),&ltbff,(char*) bff,lbff);
        if ((2 * ((unsigned int)ltbff)) != lbff) {
			return false;
			}
        CurNumBytesSent += (pMappa->getmemWrapper(indx)->memImageDim - ptr);
        Perc = 100.00 * (((double)CurNumBytesSent) / TotNumBytesToSend);
        __UI_OUTPUT("Trasferimento in corso... %d %s ricevuto.\n",int(Perc),"%");
        __PROCESS();
        }
    __UI_OUTPUT("Trasferimento terminato con successo.\n");
    __PROCESS();
    return true;
}
