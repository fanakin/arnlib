/***************************************************************************
                          arn44monitor.h  -  description
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

#ifndef Arn44MonitorH
#define Arn44MonitorH

#include "arnlibtypes.h"
#include "arnCarrier.h"


class arn44monitor : public arnCarrier  {
    private:
    protected:
        //Z4Comm_t Z4Cfg;
    public:
    arn44monitor(void);
    virtual ~arn44monitor(void);
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
    * and storing them into an external buffer.\n
    * the user needs to know what is the structure matching the configuration\n
    * of the device. So wee give the application the capability to parse the configuration structure.
    *
    * Ex:\n
    * ...\n
    */
    virtual bool ReceiveConfiguration(unsigned char* bff, int len);

};


#endif
