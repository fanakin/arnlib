/***************************************************************************
                          arnWTmonitor.h  -  description
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

#ifndef ArnWtMonitorH
#define ArnWtMonitorH

#include "arnlibtypes.h"
#include "arnCarrier.h"


class arnWTmonitor : public arnCarrier  {
    private:
    protected:
        void SetCommand(char Cmd);
        virtual void SetCommand(char Cmd[2]);  // due caratteri per comando
        virtual void SetADDRSp(char Add[8]); // su 32 bit
        virtual void SetNBTSSp(char NBt[4]); // su 16 nit
        virtual void SetBYTETOWSp(char* BtoW,unsigned int N);
        //Z4Comm_t Z4Cfg;
    public:
    arnWTmonitor(void);// : arnCarrier() {;}
    virtual ~arnWTmonitor(void);// {;}
    virtual unsigned int MaxMessLen();
    //inline Z4Comm_t* GetpCfg(void) {return &Z4Cfg;}
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
    virtual unsigned char* GetMemorySeg(unsigned char* Dest,unsigned int* LenDest,unsigned char* Add,unsigned int Num);

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
    virtual bool SetMemorySeg(unsigned char* Add,unsigned int Num,unsigned char* ArrToW);

    /*! \brief gsend the reset command to the device\n
    *
    *
    *
    * Ex:\n
    * ...\n
    */
    virtual bool SendReset(void);

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
        virtual bool ReceiveConfiguration(void);

        /*! \brief expotrs the configuration of the device the the applocation\n
        *
        *
        * This function allows the application to use the configuration parameters\n
        * for real time interactoion with the system in user mode.\n
        * The first word of the configuration record is the size of\n
        * itself, so we can read in len the dimension of the configuration record.
        *
        * Ex:\n
        * ...\n
        */
        virtual inline void* GetpCfg(void) {return 0;}
};


#endif
