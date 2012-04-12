/*
*****************************************************************************
*
*   File Name : Protocols.h
*
*   Author : Fabio Giovagnini (Aurion s.r.l)  09/02/2005
*   Contents : Communication Protocols Headers
*
*****************************************************************************
*/
#ifndef PROTOCOLSH
#define PROTOCOLSH

#include "CommonFunctions.h"
#include "arnSerialInterface.h"


// Exception class

//class EProtocol : public Exception {
//    public:
//
//	EProtocol(AnsiString Mess) : Exception(Mess) { }
//};        



//  Abstract protocol (a protocol that send and receive generic packets)

class Protocol {
    protected :
        arnSerialInterface *channel;
        unsigned int tmaxerror;
        unsigned int rmaxerror;
    public :
        Protocol() {channel = 0; tmaxerror = rmaxerror = 1;}
        virtual ~Protocol() {};
        void SetChannel(arnSerialInterface *achannel);
        arnSerialInterface* GetChannel() {return channel;}
        void SetTxMaxErr(unsigned int n) {tmaxerror = n;}
        void SetRxMaxErr(unsigned int n) {rmaxerror = n;}
        virtual unsigned char* GetDataPtr() = 0;
        virtual int MaxDataLen() = 0;
        virtual bool SendPacket(unsigned int len) = 0;
        virtual bool ReceivePacket(unsigned int *len) = 0;
};


class TextMSPPP : public Protocol {
    protected:
    	unsigned int RxLen;
        unsigned int TCmdBffLn;
        char PackType;
        unsigned char Buffer[1024];
        bool Snd(unsigned int Len);
        bool Rcv(unsigned int Len);
        bool RcvPack(unsigned int Len);
        bool SndRes(unsigned int Len);
        bool RcvPackOk;
        unsigned int TCmdPtr;
        char ResetReq;
    public :
        TextMSPPP() {PackType = 0; RcvPackOk = true;}
        ~TextMSPPP() {}
        virtual unsigned char* GetDataPtr(); // !!!!! set correct value!
        virtual int MaxDataLen(){return 100;} // !!!!! set correct value!
        virtual bool SendPacket(unsigned int len);
        virtual bool ReceivePacket(unsigned int *len);
        inline void SetTCmdBffLn(unsigned int TCmdBLn) {TCmdBffLn = TCmdBLn;}
        inline void SetResetReq(char T) {ResetReq = T;}
};
// Text Master Slave Point to Point Protocol for existing GenTab
// code not developed


class TextMSPPPRW16 : public Protocol {
    protected:
        unsigned char Buffer[1024];
        unsigned char *pBff;
        bool Rcv(unsigned int Len);
    public :
        TextMSPPPRW16() {pBff = (Buffer + 1);}
        ~TextMSPPPRW16() {}
        virtual unsigned char* GetDataPtr(); // !!!!! set correct value!
        virtual int MaxDataLen(){return 100;} // !!!!! set correct value!
        virtual bool SendPacket(unsigned int len);
        virtual bool ReceivePacket(unsigned int *len);
};
// Text Master Slave Point to Point Protocol for existing arnSys
// RW16 means : Read and Write commands: chks on 16 bit

class TextMSTCPIPRW : public Protocol {
    protected:
        unsigned char Buffer[2048];
        unsigned char *pBff;
        bool Rcv(unsigned int Len);
    public :
        TextMSTCPIPRW() {memset(Buffer,0,sizeof(Buffer)); pBff = (Buffer + 1);}
        ~TextMSTCPIPRW() {}
        virtual unsigned char* GetDataPtr(); // !!!!! set correct value!
        virtual int MaxDataLen(){return 128;} // !!!!! set correct value!
        virtual bool SendPacket(unsigned int len);
        virtual bool ReceivePacket(unsigned int *len);
};
// Text Master Slave Point to Point Protocol for existing arnSys
// RW means : Read and Write commands: no checksum; tcp/ip is enough

class TextMSPPPZ4 : public Protocol {
    protected:
        unsigned char Buffer[1024];
        unsigned char *pBff;
        bool Rcv(unsigned int Len);
    public :
        TextMSPPPZ4() {pBff = (Buffer + 1);}
        ~TextMSPPPZ4() {}
        virtual unsigned char* GetDataPtr(); // !!!!! set correct value!
        virtual int MaxDataLen(){return 80;} // !!!!! set correct value!
        virtual bool SendPacket(unsigned int len);
        virtual bool ReceivePacket(unsigned int *len);
};
// Text Master Slave Point to Point Protocol for existing z4

class TextMSPPPZ4TCPIP : public Protocol {
    protected:
        unsigned char Buffer[1024];
        unsigned char *pBff;
        bool Rcv(unsigned int Len);
    public :
        TextMSPPPZ4TCPIP() {pBff = (Buffer + 1);}
        ~TextMSPPPZ4TCPIP() {}
        virtual unsigned char* GetDataPtr(); // !!!!! set correct value!
        virtual int MaxDataLen(){return 128;} // !!!!! set correct value!
        virtual bool SendPacket(unsigned int len);
        virtual bool ReceivePacket(unsigned int *len);
};
// Text Master Slave Point to Point Protocol for existing z4

class BinMSArrP : public Protocol {
    protected:
        unsigned char buffer[130];
        unsigned char aux[130];
        unsigned char devaddress;
        bool useaddr;
    public :
        BinMSArrP() {}
        ~BinMSArrP() {}
        void UseAddress(bool val) {useaddr = val;}
        void SetAddress(unsigned char addr) {devaddress = addr;}
        virtual unsigned char* GetDataPtr(){return (buffer+4);}
        virtual int MaxDataLen(){return 120;}
        virtual bool SendPacket(unsigned int len);
        virtual bool ReceivePacket(unsigned int *len);
};
// Binary Master Slave Array Protocol for Dataloggers


#endif
