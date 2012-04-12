/*
*****************************************************************************
*
*   File Name : Dispatchers.h
*
*
*****************************************************************************
*/

#include "Protocols.h"

#ifndef DispatchersH
#define DispatchersH


// Exception class

//class EDispatcher : public Exception {
//    public:
//	EDispatcher(AnsiString Mess) : Exception(Mess) { }
//};        


//  Abstract object with messages transport

class Interface {
    public :
        Interface() {}
        virtual ~Interface() {}
        virtual unsigned char* GetMessPtr() = 0;
        virtual unsigned int MaxMessLen() = 0;
        virtual bool TxMess(unsigned int txlen) = 0;
        virtual bool RxMess(unsigned int *rxlen) = 0;
        virtual bool TxRxMess(unsigned int txlen, unsigned int *rxlen, unsigned int wfa) = 0;
};

//  Abstract message dispatcher(a dispatcher that send and receive generic messages)

class Dispatcher : public Interface {
    protected :
        Protocol *usedprotocol;
    public :
        Dispatcher() {usedprotocol = 0;}
        ~Dispatcher() {}
        void SetProtocol(Protocol *aprotocol);
        Protocol* GetProtocol() {return usedprotocol;}
};


class PlainDispatcher : public Dispatcher {
    public :
        PlainDispatcher() {}
        ~PlainDispatcher() {}
        virtual unsigned char* GetMessPtr();
        virtual unsigned int MaxMessLen();
        virtual bool TxMess(unsigned int txlen);
        virtual bool RxMess(unsigned int *rxlen);
        virtual bool TxRxMess(unsigned int txlen, unsigned int *rxlen, unsigned int wfa);
};
// Send message as passed


class AddrDispatcher8 : public Dispatcher {
    protected :
        unsigned char txdestination;
        unsigned char txsource;
        unsigned char rxdestination;
        unsigned char rxsource;
    public :
        AddrDispatcher8() {}
        ~AddrDispatcher8() {}
        virtual unsigned char* GetMessPtr();
        virtual unsigned int MaxMessLen();
        virtual bool TxMess(unsigned int txlen);
        virtual bool RxMess(unsigned int *rxlen);
        virtual bool TxRxMess(unsigned int txlen, unsigned int *rxlen, unsigned int wfa);
        void SetTxDestAddr(unsigned char addr) {txdestination = addr;}
        void SetTxSourceAddr(unsigned char addr){txsource = addr;}
        unsigned char GetRxDestAddr(){return rxdestination;}
        unsigned char GetRxSourceAddr(){return rxsource;}
};
// Send message with destination and source 8 bits address (0-255)

#endif
