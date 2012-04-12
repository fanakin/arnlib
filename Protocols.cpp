/*
*****************************************************************************
*
*   File Name : Protocols.cpp
*
*   Author : Fabio Giovagnini (Aurion s.r.l)  09/02/2005
*   Contents : Communication Protocols
*
*****************************************************************************
*/
                               
#include <stdlib.h>
#include <string.h>

#include "GlbDecl.h"
#include "Protocols.h"
#include <QtDebug>

#undef __DEBUG

#ifdef __DEBUG
#include "CommonFunctions.h"
#define DBG(msg...)		arnDebug(msg)
#else 
#define DBG(msg...)
#endif



void Protocol::SetChannel(arnSerialInterface *achannel)
{
    if (achannel == 0) arnCriticalExit();//throw(EProtocol("Invalid Channel"));
    else channel = achannel;
}

bool BinMSArrP::SendPacket(unsigned int len)
{
    unsigned int i, chk, nerr;
    unsigned char plen;
    bool rxres;

    if (channel == NULL)  arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    if (len > 120) return false;
    buffer[0] = SYNC1;
    buffer[1] = SYNC2;
    if (useaddr) buffer[2] = devaddress;
    else buffer[2] = SYNC3;
    buffer[3] = plen = (unsigned char) (len + 2);
    chk = 0;
    for (i = 0; i < len; i++) chk += buffer[i+4];
    buffer[len+4] = (unsigned char) ((chk & 0x0000FF00) / 256);
    buffer[len+5] = (unsigned char) (chk & 0x000000FF);
    nerr = 0;
    /*channel->PurgeRxBuff();*/
    do {
        channel->PurgeRx();  /* Aggiunta Fabio 26 - 02 - 1999 */
        channel->SendData((char*)buffer,len + 6);
        aux[1] = aux[0] = 0;

        rxres = channel->ReceiveData((char*)aux, 2);
        if (rxres == true &&
            aux[0] == ACK &&
            aux[1] == plen) break;
        else {
            nerr++;
            if (aux[1] != plen) {
                for (i = 0; i < 127; i++) aux[i] = 0;
                channel->SendData((char*)aux, 128);
                arnSleep(20);
                channel->PurgeRx();
            }
        }
    } while (nerr < tmaxerror);
    if (nerr >= tmaxerror) return false;
    return true;
}


bool BinMSArrP::ReceivePacket(unsigned int *len)
{
    unsigned int i, l, chk, nerr;
    bool rxres;

    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    nerr = 0;
    do {
        do {
            aux[1] = aux[0] = 0;

            rxres = channel->ReceiveData((char*)aux, 4);
            l = aux[3];
            if (rxres &&
                l <= 120 &&
                aux[0] == SYNC1 &&
                aux[1] == SYNC2 &&
                ((useaddr && (aux[2] == devaddress)) ||
                 (!useaddr && (aux[2] == SYNC3)))) break;
            else {
                arnSleep(150);
                channel->PurgeRx();

                aux[0] = NAK;
                aux[1] = (unsigned char) l;
                channel->SendData((char*)aux, 2);
                nerr++;
            }
        } while (nerr < rmaxerror);
        if (nerr >= rmaxerror) return false;
        nerr = 0;
        chk = 0;

        rxres = channel->ReceiveData((char*)(buffer+4), l);
        l -= 2;
        for (i = 0; i < l; i++) chk += buffer[i+4];
        if (rxres &&
            (buffer[l+4] == (unsigned char) ((chk & 0x0000FF00) / 256)) &&
            (buffer[l+5] == (unsigned char) (chk & 0x000000FF)))  {
	    *len = l;
	    aux[0] = ACK;
	    aux[1] = (unsigned char) (l+2);
	    channel->SendData((char*)aux, 2);
	    break;
        }
        else {
	    channel->PurgeRx();
	    aux[0] = NAK;
	    aux[1] = (unsigned char) l;
	    channel->SendData((char*)aux, 2);
	    nerr++;
        }
    } while (nerr < rmaxerror);
    if (nerr >= rmaxerror) return false;
    return true;
}

// **************************************************************************
//  --------------   TextMSPPP   --------------------------------------------
// **************************************************************************
//---------------------------------------------------------------------------
bool TextMSPPP::SndRes(unsigned int Len)
{
    unsigned char TBuff[3];
    TBuff[0] = ':';
    TBuff[1] = ResetReq;
    unsigned char chks = 0;
    for (unsigned int i = 0; i < (Len - 1); i++) chks += TBuff[i];
    TBuff[Len - 1] = chks;
    unsigned int nerr = 0;
    do {
    	channel->PurgeRx();
        channel->PurgeTx();
        if (!channel->SendData((char*)TBuff, Len)) {nerr++; continue;}
        else break;
    } while (nerr < tmaxerror);
    if (nerr >= tmaxerror) return false;
    else return true;
}
//---------------------------------------------------------------------------
bool TextMSPPP::Snd(unsigned int Len)
{
    Buffer[0] = ':';
    unsigned char chks = 0;
    for (unsigned int i = 0; i < (Len - 1); i++) chks += Buffer[i];
    Buffer[Len - 1] = chks;
    unsigned int nerr = 0;
    do {
    	channel->PurgeRx();
        channel->PurgeTx();
        if (!channel->SendData((char*)Buffer, Len)) {nerr++; continue;}
        else break;
    } while (nerr < tmaxerror);
    if (nerr >= tmaxerror) return false;
    else return true;
}
//---------------------------------------------------------------------------
bool TextMSPPP::Rcv(unsigned int Len)
{
    unsigned int nerr = 0;
    do {
        if (!channel->ReceiveData((char*)Buffer, Len)) {nerr++; continue;}
        unsigned char chks = 0;
        for (unsigned int i = 0; i < ((unsigned int)(Len - 1)); i++) chks += Buffer[i];
        if (chks != Buffer[Len - 1]) {nerr++; continue;}
        else break;
    } while ((nerr < rmaxerror) && (nerr < tmaxerror));
    if (nerr >= rmaxerror) return false;
    else return true;

}
//---------------------------------------------------------------------------
bool TextMSPPP::RcvPack(unsigned int Len)
{
    unsigned int nerr = 0;
    do {
        if (RcvPackOk) {
	    if (!channel->ReceiveData((char*)Buffer, (2 * Len) + 7)) {nerr++; continue;}
            if ((Buffer[0] != ':') ||
            	(Buffer[1] != 'O') ||
                (Buffer[2] != 'K') ||
                (Buffer[3] != '!') ||
                (Buffer[4] != 245)) {RcvPackOk = false; nerr++; continue;}

            else {
		unsigned char chks = 0;
                unsigned int LocPtr = 5;
                while ((Buffer[LocPtr] != ':') && ((LocPtr++) < ((2 * Len) + 7)));
                if (LocPtr == ((2 * Len) + 7)) {RcvPackOk = false; nerr++; continue;}
                TCmdPtr = LocPtr;
		for (unsigned int i = 0; i < ((unsigned int)((2 * Len) + 1)); i++) chks += Buffer[i + LocPtr];
		if (chks != Buffer[(2 * Len) + 6]) {RcvPackOk = false; nerr++; continue;}
		else {RcvPackOk = false; nerr++; continue;}
	    }
	}
	else {
	    if (!channel->ReceiveData((char*)Buffer, (2 * Len) + 2 + (((2 * Len) + 2) / 2))) {nerr++; continue;}
    	    unsigned char chks = 0;
            unsigned int LocPtr = 0;
            while ((Buffer[LocPtr] != ':') && ((LocPtr++) < ((2 * Len) + 2 + (((2 * Len) + 2) / 2))));
            if (LocPtr == ((2 * Len) + 2 + (((2 * Len) + 2) / 2))) {nerr++; continue;}
            TCmdPtr = LocPtr;
	    for (unsigned int i = 0; i < ((unsigned int)((2 * Len) + 1)); i++) chks += Buffer[i + LocPtr];
	    if (chks != Buffer[(2 * Len) + 1 + LocPtr]) {nerr++; continue;}
	    else break;
	}
    } while ((nerr < rmaxerror) && (nerr < tmaxerror));
    if (nerr >= rmaxerror) return false;
    else return true;
}
//---------------------------------------------------------------------------
unsigned char* TextMSPPP::GetDataPtr()
{
    if (PackType != 'T') return Buffer;
    else return (Buffer + TCmdPtr);


}
//---------------------------------------------------------------------------
bool TextMSPPP::SendPacket(unsigned int len)
{
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    if ((PackType == 'T') && (ResetReq != '?')) return true;
    unsigned int LLen = 2 + len;
    if (ResetReq == '?') PackType = ResetReq;
    else PackType = Buffer[1];
    switch (PackType) {
	case 'W': RxLen = 5; return Snd(LLen);
	case 'R':
	    RxLen = (int)(5 +  2 * ((NToD(Buffer[10]) * 16) + NToD(Buffer[11])));
	    if (((int)RxLen) > MaxDataLen()) arnCriticalExit();//EProtocol("RxBuffer Mismatched.");
	    return Snd(LLen);
	case 'A': RxLen = 5; return Snd(LLen);
	case '?': RxLen = 5; RcvPackOk = false; return SndRes(LLen);
	case 'D': RxLen = 13; return Snd(LLen);
	case 'Q': RxLen = 13; return Snd(LLen);
	case 'V': RxLen = 13; return Snd(LLen);
	case 'T': RxLen = TCmdBffLn; return Snd(LLen);
	case 'C': RxLen = 0; return Snd(LLen);
	case 'E': RxLen = 0; return Snd(LLen);
	default : RxLen = 0; return false;
    }
}
//---------------------------------------------------------------------------
bool TextMSPPP::ReceivePacket(unsigned int *len)
{
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    switch (PackType) {
	case 'W': (*len) = 4; return Rcv(5);
	case 'R':
	    (*len) = (int)(2 * ((NToD(Buffer[10]) * 16) + NToD(Buffer[11])));
	    if (((int) (*len)) > MaxDataLen()) arnCriticalExit();//EProtocol("RxBuffer Mismatched.");
	    return Rcv((*len) + 5);
	case 'A': (*len) = 0; return Rcv(5);
	case '?': (*len) = 4; return Rcv(5);
	case 'D': (*len) = 8; return Rcv(13);
	case 'Q': (*len) = 8; return Rcv(13);
	case 'V': (*len) = 8;return Rcv(13);
	case 'T': (*len) = (2 * TCmdBffLn); return RcvPack(TCmdBffLn);

	case 'C': (*len) = 0; return true;
	case 'E': (*len) = 0; return true;
	default : return false;
    }
}
//---------------------------------------------------------------------------










// **************************************************************************
//  --------------   TextMSPPPRW16   ----------------------------------------
// **************************************************************************
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
unsigned char* TextMSPPPRW16::GetDataPtr()
{
    return pBff;
}
//---------------------------------------------------------------------------
bool TextMSPPPRW16::SendPacket(unsigned int len)
{
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    Buffer[0] = ':';
    unsigned char chks = 0;
    for (unsigned int i = 0; i < len; i++) chks += Buffer[i];
    if ((len + 1) > sizeof(Buffer)) return false;
    Buffer[len] = chks;
    unsigned int nerr = 0;
    do {
    	channel->PurgeRx();
        channel->PurgeTx();
        if (!channel->SendData((char*)Buffer, len + 1)) {nerr++; continue;}
        else break;
    } while (nerr < tmaxerror);
    if (nerr >= tmaxerror) return false;
    else return true;
}
//---------------------------------------------------------------------------
bool TextMSPPPRW16::ReceivePacket(unsigned int *len)
{
    //qDebug() << __FUNCTION__ << "command:" << (char *)pBff;

    unsigned int LLen;
    unsigned int BytesToReceive = 0;
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    if (!strncmp((const char*)pBff,"RD",2)) {
        BytesToReceive = (unsigned int) (
	    ((unsigned short) (NToD(*(pBff + 10)) * 4096)) +
	    ((unsigned short) (NToD(*(pBff + 11)) * 256)) +
	    ((unsigned short) (NToD(*(pBff + 12)) * 16)) +
	    ((unsigned short) (NToD(*(pBff + 13)) * 1))
	    );
        LLen = 5;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        LLen = 4 + (2 * BytesToReceive);
        if (!Rcv(LLen)) {*len = 0; return false;}
        *len = (LLen - 4);
        return true;
    }
    else if (!strncmp((const char*)pBff,"WR",2)) {
        LLen = 5;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        return true;
    }
    // controllare al test
    else if (!strncmp((const char*)pBff,"##",2)) {

		//qDebug() << __FUNCTION__ << "RESET";

        LLen = 5;
        if (!Rcv(LLen)) {*len = 0; return false;}

        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}

        return true;
    }
    // controllare al test
    else if (!strncmp((const char*)pBff,"CF",2)) {
        BytesToReceive = (unsigned int) (
	    ((unsigned short) (NToD(*(pBff + 10)) * 4096)) +
	    ((unsigned short) (NToD(*(pBff + 11)) * 256)) +
	    ((unsigned short) (NToD(*(pBff + 12)) * 16)) +
	    ((unsigned short) (NToD(*(pBff + 13)) * 1))
	    );
        LLen = 5;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}

//	qDebug() << " Got ok. now read " << BytesToReceive;

        LLen = 4 + (2 * BytesToReceive);
        if (!Rcv(LLen)) {*len = 0; return false;}
//	qDebug() << "here";
        *len = (LLen - 4);
        return true;
    } else {
		qDebug() << __FUNCTION__ << "Unknown command.";
		*len = 0; 
		return false;
    }
}
//---------------------------------------------------------------------------
bool TextMSPPPRW16::Rcv(unsigned int Len)
{
	unsigned int nerr = 0;
	do {
		if (!channel->ReceiveData((char*)Buffer, Len)) {
			nerr++; 
			continue;
			}
		unsigned char chks = 0;
		for (unsigned int i = 0; i < ((unsigned int)(Len - 1)); i++)  {
			chks += Buffer[i];
			//qDebug() << i << ((char*)Buffer)[i];
			}
		if (chks != Buffer[Len - 1]) {
			qDebug() << "Checksum error: " << Buffer[Len-1] << " expected " << chks;
			nerr++; 
			continue;
			}
		else break;
	} while ((nerr < rmaxerror) && (nerr < tmaxerror));
	if (nerr >= rmaxerror)  return false;
	else return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


// **************************************************************************
//  --------------   TextMSTCPIPRW   ----------------------------------------
// **************************************************************************
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
unsigned char* TextMSTCPIPRW::GetDataPtr()
{
    return pBff;
}
//---------------------------------------------------------------------------
bool TextMSTCPIPRW::SendPacket(unsigned int len)
{
	if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
	Buffer[0] = ':';
	if ((len ) > sizeof(Buffer)) return false;
	unsigned int nerr = 0;
	do {
		channel->PurgeRx();
		channel->PurgeTx();
		//qDebug() << __FUNCTION__ << "send length:" << len;
		//qDebug() << __FUNCTION__ << "send Buffer:" << (char *)Buffer;
		if (!channel->SendData((char*)Buffer, len)) {nerr++; continue;}
		else break;
		} while (nerr < tmaxerror);
	if (nerr >= tmaxerror) return false;
	else return true;
}
//---------------------------------------------------------------------------
bool TextMSTCPIPRW::ReceivePacket(unsigned int *len)
{
    unsigned int LLen;
    unsigned int BytesToReceive = 0;
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));

    //qDebug() << __FUNCTION__ << "command:" << (char *)pBff;

    if (!strncmp((const char*)pBff,"RD",2)) {
        BytesToReceive = (unsigned int) (
	    ((unsigned short) (NToD(*(pBff + 10)) * 4096)) +
	    ((unsigned short) (NToD(*(pBff + 11)) * 256)) +
	    ((unsigned short) (NToD(*(pBff + 12)) * 16)) +
	    ((unsigned short) (NToD(*(pBff + 13)) * 1))
	    );
        LLen = 4;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        LLen = 3 + (2 * BytesToReceive);
        if (!Rcv(LLen)) {*len = 0; return false;}
        *len = (LLen - 3);
        return true;
    }
    else if (!strncmp((const char*)pBff,"WR",2)) {
        LLen = 4;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        //arnSleep(200);
        return true;
    }
    // controllare al test
    else if (!strncmp((const char*)pBff,"##",2)) {
        LLen = 4;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        return true;
    }
    // controllare al test
    else if (!strncmp((const char*)pBff,"CF",2)) {
        BytesToReceive = (unsigned int) (
	    ((unsigned short) (NToD(*(pBff + 10)) * 4096)) +
	    ((unsigned short) (NToD(*(pBff + 11)) * 256)) +
	    ((unsigned short) (NToD(*(pBff + 12)) * 16)) +
	    ((unsigned short) (NToD(*(pBff + 13)) * 1))
	    );
        LLen = 4;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        LLen = 3 + (2 * BytesToReceive);
        if (!Rcv(LLen)) {*len = 0; return false;}
        *len = (LLen - 3);
        return true;
    }
    else {*len =0; return false;}
}
//---------------------------------------------------------------------------
bool TextMSTCPIPRW::Rcv(unsigned int Len)
{
	unsigned int nerr = 0;
	do {
		if (!channel->ReceiveData((char*)Buffer, Len)) {DBG("%s\n",Buffer);nerr++; continue;}
/*		for (unsigned int i = 0; i < ((unsigned int)(Len)); i++) {
			qDebug() << i << ((char*)Buffer)[i];
			}*/
		break;
		} while ((nerr < rmaxerror) && (nerr < tmaxerror));
	if (nerr >= rmaxerror) {return false;}
	else {return true;}
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------
unsigned char* TextMSPPPZ4::GetDataPtr()
{
    return pBff;
}
//---------------------------------------------------------------------------
bool TextMSPPPZ4::SendPacket(unsigned int len)

{
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    Buffer[0] = ':';
    unsigned char chks = 0;
    for (unsigned int i = 0; i < len; i++) chks += Buffer[i];
    if ((len + 1) > sizeof(Buffer)) return false;
    Buffer[len] = chks;
    unsigned int nerr = 0;
    if (!strncmp((const char*)pBff,"##",2)) { // reset command
        channel->PurgeRx();
        channel->PurgeTx();
	// invio di caratteri errati per avere in risposta ":NOT+"
	for (int i = 0; i < 10; i++) {
	    if (!channel->SendData("\n", 1)) arnCriticalExit();
	    char tpB[8] = {0,0,0,0,0,0,0,0};
	    for (int j = 0; j < 5; j++) {
		if (!channel->ReceiveData(tpB + j, 1)) break;
	    }
	    if (!strncmp(tpB,":NOT+",5)) {
// test test test
//arnDebug("index = %d, NOT, received.\n",i);
		break;
	    }
	    if (i == 9) return false;
	}
	nerr = 0;
	do {
            channel->PurgeRx();
            channel->PurgeTx();
            if (!channel->SendData((char*)Buffer, len /*+ 1*/)) {nerr++; continue;}
            else break;
	} while (nerr < tmaxerror);
	//for (int i = 0; i < 3; i++) {
        //    nerr = 0;
        //    do {
        //        char tp;
        //        if (!channel->SendData((char*)(Buffer + i), 1)) {nerr++; continue;}
        //        if (i < 2) {
        //            if (channel->ReceiveData(&tp, 1)) {
        //                channel->PurgeRx();
        //                channel->PurgeTx();
        //                return false;
        //                }
        //            else {break;}
        //            }
        //        else {break;}
        //        } while (nerr < tmaxerror);
        //    if (nerr >= tmaxerror) break;
        //    }
    }
    else {
        do {
            channel->PurgeRx();
            channel->PurgeTx();
            if (!channel->SendData((char*)Buffer, len + 1)) {nerr++; continue;}
            else break;
	} while (nerr < tmaxerror);
    }
    if (nerr >= tmaxerror) return false;
    else return true;
}
//---------------------------------------------------------------------------
bool TextMSPPPZ4::ReceivePacket(unsigned int *len)
{
    unsigned int LLen;
    unsigned int BytesToReceive = 0;
    if (channel == NULL) arnCriticalExit();//throw(EProtocol("Channel Not Assigned"));
    if (!strncmp((const char*)pBff,"RD",2)) {
        BytesToReceive = (unsigned int) (
	    ((unsigned short) (NToD(*(pBff + 10)) * 4096)) +
	    ((unsigned short) (NToD(*(pBff + 11)) * 256)) +
	    ((unsigned short) (NToD(*(pBff + 12)) * 16)) +
	    ((unsigned short) (NToD(*(pBff + 13)) * 1))
	    );

        LLen = 4 + (2 * BytesToReceive);
        if (!Rcv(LLen)) {*len = 0; return false;}
        *len = (LLen - 4);
        return true;
    }
    else if (!strncmp((const char*)pBff,"WR",2)) {
        LLen = 5;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
        return true;
    }
    else if (!strncmp((const char*)pBff,"##",2)) {
        LLen = 5;
        if (!Rcv(LLen)) {*len = 0; return false;}
        if (strncmp((const char*)pBff,"OK!",3)) {*len = 0; return false;}
// test test test
	arnDebug("ResetBuffer done.\n");
        return true;
    }
    else if (!strncmp((const char*)pBff,"CF",2)) {
        BytesToReceive = (unsigned int) (
	    ((unsigned short) (NToD(*(pBff + 10)) * 4096)) +
	    ((unsigned short) (NToD(*(pBff + 11)) * 256)) +
	    ((unsigned short) (NToD(*(pBff + 12)) * 16)) +
	    ((unsigned short) (NToD(*(pBff + 13)) * 1))
	    );
        LLen = 4 + (2 * BytesToReceive);
        if (!Rcv(LLen)) {*len = 0; return false;}
        *len = (LLen - 4);
        return true;
    }
    else {*len =0; return false;}
}

//---------------------------------------------------------------------------
bool TextMSPPPZ4::Rcv(unsigned int Len)
{
    unsigned int nerr = 0;
    do {
        if (!channel->ReceiveData((char*)Buffer, Len)) {nerr++; continue;}
        unsigned char chks = 0;
        for (unsigned int i = 0; i < ((unsigned int)(Len - 1)); i++) chks += Buffer[i];
        if (chks != Buffer[Len - 1]) {nerr++; continue;}
        else break;
    } while ((nerr < rmaxerror) && (nerr < tmaxerror));
    if (nerr >= rmaxerror) return false;
    else return true;
}
//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
