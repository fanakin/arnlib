/*
*****************************************************************************
*
*   File Name : Dispatchers.cpp
*
*   Author : Fabio Giovagnini (Aurion s.r.l.)  10/02/2005
*   Contents : Dispatchers 
*
*****************************************************************************
*/
#include <stdlib.h>
#include "Protocols.h"
#include "Dispatchers.h"

#ifdef __DEBUG
#endif


void Dispatcher::SetProtocol(Protocol *aprotocol)
{
    if (aprotocol == 0) arnCriticalExit();//throw(EDispatcher("Invalid Protocol"));
    usedprotocol = aprotocol;
}

unsigned char* PlainDispatcher::GetMessPtr()
{
    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));
    return usedprotocol->GetDataPtr();
}

unsigned int PlainDispatcher::MaxMessLen()
{
    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));
    return usedprotocol->MaxDataLen();
}

bool PlainDispatcher::TxMess(unsigned int txlen)
{
    bool txr;

    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));

    txr = usedprotocol->SendPacket(txlen);
    
	return(txr);
}

bool PlainDispatcher::RxMess(unsigned int *rxlen)
{
    bool rxr;
    unsigned int l = 0;

    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));

    rxr = usedprotocol->ReceivePacket(&l);

    *rxlen = (unsigned char) l;
    return(rxr);
}

bool PlainDispatcher::TxRxMess(unsigned int txlen, unsigned int *rxlen, unsigned int wfa)
{
    bool txr, rxr;
    unsigned int l = 0;

    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));
    txr = usedprotocol->SendPacket(txlen);
    if (wfa > 0) arnSleep(wfa);
    rxr = usedprotocol->ReceivePacket(&l);
    *rxlen = (unsigned int) l;
    return (txr && rxr);
}


unsigned char* AddrDispatcher8::GetMessPtr()
{
    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));
    return (usedprotocol->GetDataPtr() + 2);
}

unsigned int AddrDispatcher8::MaxMessLen()
{
    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));
    return (usedprotocol->MaxDataLen() - 2);
}

bool AddrDispatcher8::TxMess(unsigned int tlen)
{
    bool txr;

    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));

    usedprotocol->GetDataPtr()[0] = txdestination;
    usedprotocol->GetDataPtr()[1] = txsource;

    txr = usedprotocol->SendPacket(tlen + 2);

    return(txr);
}

bool AddrDispatcher8::RxMess(unsigned int *rlen)
{
    bool rxr;
    unsigned int l = 0;

    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));

    rxr = usedprotocol->ReceivePacket(&l);

    rxdestination = usedprotocol->GetDataPtr()[0];


    rxsource = usedprotocol->GetDataPtr()[1];

    *rlen =  l - 2;
    return(rxr);
}

bool AddrDispatcher8::TxRxMess(unsigned int tlen, unsigned int *rlen, unsigned int wfa)
{
    bool txr, rxr;
    unsigned int l = 0;

    if (usedprotocol == NULL) arnCriticalExit();//throw(EDispatcher("Protocol Not Assigned"));

    usedprotocol->GetDataPtr()[0] = txdestination;
    usedprotocol->GetDataPtr()[1] = txsource;

    txr = usedprotocol->SendPacket(tlen+2);

    if (wfa > 0) arnSleep(wfa);

    rxr = usedprotocol->ReceivePacket(&l);

    rxdestination = usedprotocol->GetDataPtr()[0];
    rxsource = usedprotocol->GetDataPtr()[1];

    *rlen = l - 2;
    return (txr && rxr);
}

