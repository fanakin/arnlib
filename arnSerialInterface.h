/***************************************************************************
                          arnSerialInterface.h  -  description
                             -------------------
    begin                : mer nov 20 2002
    copyright            : (C) 2002 by fabio giovagnini
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
/* *********************************************************************** */
/*! \file arnSerialInterface.h.
    \brief VIRTUAL CLASS. Header file for definition of a general serial interface.

 We define a general serial interface to describe a generic serial communication\n
 interface. So a real serial interface will be derived from\n
 this abstract class.\n

*/
/* *********************************************************************** */

#ifndef ArnSerialInterfaceH
#define ArnSerialInterfaceH

class arnSerialInterface {
	protected:

		int status;
		unsigned char *rx;
		int HPort;
	public:
		/*! \brief generic constructor
		*
		*/
		arnSerialInterface(void);

		/*! \brief Generic destructor
		*
		*/
		virtual ~arnSerialInterface(void) {;}

		/*! \brief return the status of the interface
		*
		* @return an integer not less than 0\n
		* This function returns the interface status,\n
		* if status is 0 then the interface is working good,\n
		* else if status in greater then 0 the interface has a problem\n
		* and doesn't work.\n
		*/
		inline int GetStatus(void) {return status;}

		/*! \brief It sends a buffer outside
		*
		* @param Buff : pointer to the sending buffer
		* @param Dim : length of the sending buffer
		* @return false if there is a problem in sending, true otherwise.
		*/
		virtual bool SendData(char *Buff,int Dim) = 0;

		/*! \brief It Receive a buffer inside
		*
		* @param Buff : pointer to the receiving buffer
		* @param Dim : number of bytes to receive
		* @return true if we receive Dim bytes on Buff, flase otherwise.
		*/
		virtual bool ReceiveData(char *Buff,int Dim) = 0;

		/*! \brief It purges the Tx buffer
		*
		* @return true on Tx buffer purge success, false otherwise.
		*/
		virtual bool PurgeTx(void) = 0;

		/*! \brief It purges the Rx buffer
		*
		* @return true on Rx buffer purge success, false otherwise.
		*/
		virtual bool PurgeRx(void) = 0;
		
		/*! \brief It set the timeout value for Rx and Tx flow at the same value
		*
		* @param to is the timeout value (the units depend on implementation)
		* @return true if ssetting timeout has been successfull, false otherwise.
		*/
		virtual bool SetTimeout(int to) = 0;
};
#endif
