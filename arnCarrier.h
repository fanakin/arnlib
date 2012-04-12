/***************************************************************************
                          arnCarrier.h  -  description
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

#ifndef ArnTypesH
#define ArnTypesH

#include "Dispatchers.h"

class arnCarrier : public Interface {
    private:
    protected:
        unsigned int MaxNerr;
        Interface *usedinterface;
        virtual void SetCommand(char Cmd[2]);  // due caratteri per comando
        virtual void SetADDRSp(char Add[8]); // su 32 bit
        virtual void SetNBTSSp(char NBt[4]); // su 16 nit
        virtual void SetBYTETOWSp(char* BtoW,unsigned int N);
    public:
        arnCarrier(void);
        virtual ~arnCarrier(void);
        virtual void SetInterface(Interface *intf);
        virtual Interface* GetInterface() {return usedinterface;}
        virtual unsigned char* GetMessPtr();
        virtual unsigned int MaxMessLen();
        virtual bool TxMess(unsigned int txlen);
        virtual bool RxMess(unsigned int *rxlen);
        virtual bool TxRxMess(unsigned int txlen, unsigned int *rxlen, unsigned int wfa);
        /*! \brief gets the configuration of the device\n
        *
        *
        * This function allows to read the configuration parameters\n
        * for real time interactoion with the system in user mode.\n
        * The first word of the configuration record is the size of\n
        * itself, so we can read in len the dimension of the configuration record.
        *
        * Ex:\n
        * ...\n
        */
        virtual unsigned char* GetMemorySeg(unsigned char* Dest,unsigned int* LenDest,unsigned char* Add,unsigned int Num) = 0;
        
        /*! \brief gets the configuration of the device\n
        *
        *
        * This function allows to read the configuration parameters\n
        * for real time interactoion with the system in user mode.\n
        * The first word of the configuration record is the size of\n
        * itself, so we can read in len the dimension of the configuration record.
        *
        * Ex:\n
        * ...\n
        */
        virtual bool SetMemorySeg(unsigned char* Add,unsigned int Num,unsigned char* ArrToW) = 0;
        
        /*! \brief gsend the reset command to the device\n
        *
        *
        *
        * Ex:\n
        * ...\n
        */
        virtual bool SendReset(void) = 0;


        /*! \brief gets the configuration of the device\n
        *
        *
        * This function allows to read the configuration parameters\n
        * and storing them into an external buffer.\n
        * the user needs to know what is the structure matching the configuration\n
        * of the device. So wee give the application the capability to parse the configuration structure.
        *
        * Ex:\n
        * ...\n
        */
        inline virtual bool ReceiveConfiguration(unsigned char*, int) {return false;}

};


#endif
