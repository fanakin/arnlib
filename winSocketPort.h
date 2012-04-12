#ifndef WinSocketPortH
#define WinSocketPortH

#include <windows.h>
#include <winsock2.h>
#include "arnSerialInterface.h"


struct sockdef {
	char hostname[512];		/*!< hostname value: ex. pippo.pluto.com or ip address. */
	unsigned short port;		/*!< tcp port: ex. 23, for tlenet connection */
	int  timeout;			/*!< Timeout : in ms */
};

#define		COMBUFF		4096
#define		RXBFSIZE	1024

class arnSocketPort : public arnSerialInterface {
	private:
	protected:
		int rc;
		struct sockaddr_in localAddr, servAddr;
		//CSADDR_INFO h;
		hostent *h;
		int  timeout;			/*!< Timeout : in ms */

		static bool socketInitialized;
	public:
		/*! \brief constructor using portdef parameter
		*
                * With this constructor we build the arnSocketPort\n
                * using the sockdef description.\n
		*/
		arnSocketPort(sockdef aport);

		/*! \brief default destructor
		*
		*/
		~arnSocketPort();

		/*! \brief It sends a buffer outside
		*
		* @param Buff : pointer to the sending buffer
		* @param Dim : length of the sending buffer
		* @return false if there is a problem in sending, true otherwise.
		*
		* It sends the data stored in Buff and flush the tx buffer\n
		* so we know the trasmission is complete.
		*/
		virtual bool SendData(char *Buff,int Dim);

		/*! \brief It Receive a buffer inside
		*
		* @param Buff : pointer to the receiving buffer
		* @param Dim : number of bytes to receive
		* @return true if we receive Dim bytes on Buff, flase otherwise.
		*
		* It tries to receive Dim bytes and stores them on Buff. It returns\n
		* false if for some reason this target is not reached.
		*/
		virtual bool ReceiveData(char *Buff,int Dim);

		/*! \brief It purges the Tx buffer
		*
		* @return true on Tx buffer purge success, false otherwise.
		*
		* It uses the tcflush for linux implementation (termios.h).
		*/
		virtual bool PurgeTx(void);

		/*! \brief It purges the Rx buffer
		*
		* @return true on Rx buffer purge success, false otherwise.
		*
		* It uses the tcflush for linux implementation (termios.h).
		*/
		virtual bool PurgeRx(void);
		
		/*! \brief It set the timeout value for Rx and Tx flow at the same value
		*
		* @param to is the timeout value (ms)
		* @return true if ssetting timeout has been successfull, false otherwise.
		*/
		virtual bool SetTimeout(int to);
};
#endif
