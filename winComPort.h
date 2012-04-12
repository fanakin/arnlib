#ifndef WinComPortH
#define WinComPortH

#include <windows.h>
#include "arnSerialInterface.h"


struct portdef {
	char portname[15];	/*!< Port name string: ex. COM1, ttyS0 : allowed name: ttyS0,COM1; ttyS1,COM2; ttyUSB0,COM3; ttyUSB1,COM4*/
	int  baudrate;		/*!< Baud rate value: ex. 9600 */
	int  databits;		/*!< Bits of data: ex. 8 or 7*/
	int  parity;		/*!< Parity bit: ex. 0 disabled, otherwise enabled*/
	int  stopbits;		/*!< Number of stop bits: 1 or 2*/
	bool xon_xoff;		/*!< XON / XOFF enabled : ex 0 disabled, otherwise enabled*/
	bool rts_cts;		/*!< RTS / CTS enabled: ex 0 disabled, otherwise enabled*/
	int  timeout;		/*!< Timeout : in ms */
};

#define		COMBUFF		4096
#define		RXBFSIZE	1024

class arnComPort : public arnSerialInterface {
    private:
        int getLock(HANDLE fd);
        int getUnlock(HANDLE fd);
	protected:
		char portname[15];
		int  baudrate;
		int  databits;
		int  parity;
		int  stopbits;
		bool xon_xoff;
		bool rts_cts;

		HANDLE hPort;
		DCB    m_state, m_oldstate;

	public:
		/*! \brief constructor using portdef parameter
		*
                * With this constructor we build the arnComPort\n
                * using the portdef description.\n
		*/
		arnComPort(portdef aport);

		/*! \brief default destructor
		*
		*/
		~arnComPort();

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
