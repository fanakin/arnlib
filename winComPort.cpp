//---------------------------------------------------------------------------
#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
//#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* File control definitions */
#include <errno.h> /* Error number definitions */

#include <windows.h>
#include <malloc.h>

#include <QtDebug>

//------------------------------------------------------------------------------
//		Serial Port
//------------------------------------------------------------------------------
#include "winComPort.h"
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define __DEBUG__
#ifdef __DEBUG__
#define __CNS_OUT(arg...) do {fprintf(stderr,arg); fflush(stdout);} while (0)
#else
#define __CNS_OUT(arg...)
#endif

#define 	UMAXERR 	5

static int convbrvaltospeed_tval(int val);
static int convbitsizevaltotcflag_tval(int val);

//------------------------------------------------------------------------------

int arnComPort::getLock(HANDLE fd)
{
	/*
    int stat;
    struct flock lock;
    lock.l_type = F_WRLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    if ((stat = fcntl(fd,F_SETLK,&lock)) == -1) __CNS_OUT("failed locking\n");
    else __CNS_OUT("successfully locked\n");
    return stat;
	*/
	return 0;
}
int arnComPort::getUnlock(HANDLE fd)
{
	/*
    int stat;
    struct flock lock;
    lock.l_type = F_UNLCK;
    lock.l_whence = SEEK_SET;
    lock.l_start = 0;
    lock.l_len = 0;
    lock.l_pid = getpid();
    if ((stat = fcntl(fd,F_SETLK,&lock)) == -1) __CNS_OUT("failed unlocking\n");
    else __CNS_OUT("successfully unlocked\n");
    return stat;
	*/
	return 0;
}
//------------------------------------------------------------------------------
arnComPort::arnComPort(portdef aport) : arnSerialInterface() {
	unsigned int lIndex;

	rx = NULL;
	status = 0;

	strcpy (portname, aport.portname);

	//strcpy (portname, "COM5");

	/*
	if (!strcmp(aport.portname,"COM1")) strcpy(portname,"COM1");
	else if (!strcmp(aport.portname,"COM2")) strcpy(portname,"COM2");
	else if (!strcmp(aport.portname,"ttyS0")) strcpy(portname,"COM1");
	else if (!strcmp(aport.portname,"ttyS1")) strcpy(portname,"COM2");
	else if (!strcmp(aport.portname,"COM3")) strcpy(portname,"COM3");
	else if (!strcmp(aport.portname,"COM4")) strcpy(portname,"COM4");
	else if (!strcmp(aport.portname,"ttyUSB0")) strcpy(portname,"COM1");
	else if (!strcmp(aport.portname,"ttyUSB1")) strcpy(portname,"COM2");
	else strcpy(portname,"COM1:");
	*/

	baudrate = aport.baudrate;
	databits = aport.databits;
	parity = aport.parity;
	stopbits = aport.stopbits;
	xon_xoff = aport.xon_xoff;
	rts_cts = aport.rts_cts;

	/*
    HPort = open(portname,O_RDWR | O_NOCTTY | O_NDELAY);
    if(HPort == -1) {
        status = 1 ;						// invald handle
        return;
        }
    else {
        if (fcntl(HPort,F_SETFL,0) ==  -1) { // non so precisamente 0 come e'definito ; penso O_RONLY
            status = 2;
            return;
            }
        if (getLock(HPort) == -1) {
            status = 3;
            return;
            }
        }

	*/

#ifdef UNICODE
	wchar_t *wportname = (wchar_t *)alloca (strlen(portname)*2 + 2);
	mbstowcs (wportname, portname, strlen(portname)*2+2);
#else
	char *wportname = portname;
#endif

	hPort = CreateFile (wportname, GENERIC_READ | GENERIC_WRITE,
		0 /*NOSHARE*/ , 0 /*SEC_ATTR*/ , OPEN_EXISTING ,
		0, 0);
	if (hPort == INVALID_HANDLE_VALUE) {
		status =1;
		return;
	}

	GetCommState (hPort, &m_oldstate);

	memset (&m_state, 0, sizeof(m_state));
	m_state.DCBlength= sizeof(m_state);
	m_state.BaudRate = convbrvaltospeed_tval (baudrate);
	m_state.fBinary = TRUE;
	m_state.fParity = parity;
	m_state.fOutxCtsFlow = rts_cts;
	m_state.fOutxDsrFlow = rts_cts;
	m_state.fOutxDsrFlow = DTR_CONTROL_DISABLE; // checkit
	m_state.fDsrSensitivity = FALSE;
	m_state.fTXContinueOnXoff  = TRUE; //xon_xoff;
	m_state.fOutX  = FALSE; //xon_xoff;
	m_state.fInX  = FALSE; //xon_xoff;
	m_state.fErrorChar = FALSE; //parity; // ???
	m_state.fNull = FALSE; // ???
	m_state.fRtsControl  = RTS_CONTROL_DISABLE; // ???
	m_state.fAbortOnError = FALSE;
	m_state.XonLim = 16; // CHECK
	m_state.XoffLim = 16; // CHECK
	m_state.ByteSize = convbitsizevaltotcflag_tval(databits);
	m_state.Parity = NOPARITY;
	if (stopbits == 1) 
		m_state.StopBits = ONESTOPBIT;
	else if (stopbits == 2)
		m_state.StopBits = TWOSTOPBITS;
	else
		m_state.StopBits = ONE5STOPBITS;
	m_state.XonChar = 0x11; // CTRL+Q
	m_state.XoffChar = 0x13; // CTRL+S
	m_state.ErrorChar = 0;
	m_state.EofChar = 0x1a; // CTRL+Z
	m_state.EvtChar = 0;

	if (!SetCommState (hPort, &m_state)) {
		status=1;
		qDebug() << "SetCommState failed.";
		return	;
	}

	/*
    if (tcgetattr(HPort,&oldterm) == -1) {
		if (errno == EBADF) {status = 4; return;}
		if (errno == ENOTTY) {status = 5; return;}
		}

	for (lIndex = 0; lIndex < sizeof(term); lIndex++) ((unsigned char*) (&term))[lIndex] = 0;

	cfsetispeed(&term,convbrvaltospeed_tval(baudrate));
	cfsetospeed(&term,convbrvaltospeed_tval(baudrate));
	//
       // parity
	if (!parity) term.c_cflag &= ~PARENB;
	else term.c_cflag |= PARENB;
       // bit stop
	if (stopbits ==1) term.c_cflag &= ~CSTOPB;
	else if (stopbits == 2) term.c_cflag |= CSTOPB;
       // bit size
	term.c_cflag &= ~CSIZE;
	term.c_cflag |= convbitsizevaltotcflag_tval(databits);
	// rts cts
	if (rts_cts) term.c_cflag |= CRTSCTS;
	else term.c_cflag &= ~CRTSCTS;

	// local option
	// raw mode process data
	term.c_lflag &= ~(ICANON | ECHO | ECHOE | ISIG);

	// input option
	// xon xoff
	if (xon_xoff) term.c_iflag |= (IXON | IXOFF | IXANY);
	else  term.c_iflag &= ~(IXON | IXOFF | IXANY);

	// output option
	// raw mode
	term.c_oflag &= ~(OPOST);

	term.c_cflag |= (CLOCAL | CREAD);
*/

	COMMTIMEOUTS cto;
	memset (&cto, 0, sizeof(cto));

	cto.ReadIntervalTimeout = 100L;
    cto.ReadTotalTimeoutMultiplier = 10L;
    cto.ReadTotalTimeoutConstant = aport.timeout*50;
    cto.WriteTotalTimeoutMultiplier = 10L;
    cto.WriteTotalTimeoutConstant = aport.timeout*50;

	if (!SetCommTimeouts (hPort, &cto)) {
		status=1;
		qDebug() << "SetCommTimeout failed.";
		return ;
	}

/*
	term.c_cc[VMIN] = 0;
	term.c_cc[VTIME] = aport.timeout;  // due secondi

	if (tcdrain(HPort) == -1) {status = 6; return;}
	tcflush(HPort, TCIFLUSH);
	if (tcsetattr(HPort, TCSAFLUSH/, &term) ==  -1) {status = 7; return;}
*/
	rx = new unsigned char[RXBFSIZE];
}
//------------------------------------------------------------------------------
arnComPort::~arnComPort() {
	if (rx) delete [] rx;					  // deallocate rx buffer
	if (status == 0) {
		SetCommState (hPort, &m_oldstate);
		//tcsetattr(HPort, TCSAFLUSH/*TCSANOW*/, &oldterm);
		getUnlock(hPort);
		}
	CloseHandle(hPort);             // close port
}
//------------------------------------------------------------------------------
bool arnComPort::SendData(char *Buff,int Dim)
{
	DWORD b_tx;
	int cer;
	bool unrevorablerror;
	int lIndex;
	cer = 0;
	unrevorablerror = false;
	// test test test
	//char tstB[1024];
	//bzero(tstB,sizeof(tstB));
	//strncpy(tstB,Buff,Dim);
	//__CNS_OUT("%s\n",tstB);
	for (lIndex = 0; lIndex < Dim; lIndex++) {
		do {
			if (!WriteFile (hPort, (void *)(Buff + lIndex), 1, &b_tx, NULL) || b_tx != 1) {
				cer++;
				continue;
			}
	//		b_tx = write(HPort,(const void*) (Buff + lIndex),(size_t) 1/*Dim*/);
			//if ((b_tx != 1) || (b_tx == -1)) {cer++; continue;}
			else 
				break;
			} while (cer < UMAXERR);
		}


		if ((cer == UMAXERR) || unrevorablerror) {
			__CNS_OUT("Send Data - cer = UMAXERR.\n");
			return false;
		}
	/*
	if (tcdrain(HPort) == -1) {
		__CNS_OUT("Send Data - tcdrain(HPort) failed.\n");
		return false;
		}
		*/
	return true;
}
//------------------------------------------------------------------------------
bool arnComPort::ReceiveData(char *Buff,int Dim)
{
	DWORD b_rx;
	int cer;
	int lIndex;
	cer = 0;
	for (lIndex = 0; lIndex < Dim; lIndex++) {
		do {
			if (!ReadFile (hPort, (void *)(Buff + lIndex), 1, &b_rx, 0)) {
				cer++;
				continue;
			}

			//b_rx = read(HPort,(void*) (Buff + lIndex),(size_t) 1/*Dim*/);
			if (1 != b_rx) {
				cer++;
				continue;
			}
			else 
				break;
		} while (cer < UMAXERR);
		if (cer == UMAXERR) {
			__CNS_OUT("Receive Data - cer = UMAXERR.\n");
			return false;
		}
	}
	// test test test
	//char tstB[1024];
	//bzero(tstB,sizeof(tstB));
	//if (lIndex) {
	//	strncpy(tstB,Buff,Dim);
	//	__CNS_OUT("%s\n",tstB);
	//	}
	//else __CNS_OUT("%s\n","No Char recv.");
	return true;
}
//------------------------------------------------------------------------------
bool arnComPort::PurgeRx(void)
{
    return PurgeComm(hPort,PURGE_RXCLEAR);
	/*
	if (!tcflush(HPort,TCIFLUSH)) return true;
     __CNS_OUT("Purge Rx - failed.\n");
	return false;
	*/
}
//------------------------------------------------------------------------------
bool arnComPort::PurgeTx(void)
{
    return PurgeComm(hPort,PURGE_TXCLEAR);
	/*
	if (!tcflush(HPort,TCOFLUSH)) return true;
     __CNS_OUT("Purge Tx - failed.\n");
	return false;
	*/
}
//------------------------------------------------------------------------------
bool arnComPort::SetTimeout(int to)
{
	COMMTIMEOUTS cto;
	memset (&cto, 0, sizeof(cto));
	cto.ReadTotalTimeoutConstant = to;
	cto.WriteTotalTimeoutConstant = to;

	SetCommTimeouts (hPort, &cto);

	/*
	term.c_cc[VTIME] = to;
	if (tcdrain(HPort) == -1) {return false;}
	tcflush(HPort, TCIFLUSH);
	if (tcsetattr(HPort, TCSAFLUSH, &term) ==  -1) {return false;}
	*/
	return true;
}

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
static int convbrvaltospeed_tval(int val)
{
	switch (val) {
		case 2400:
			return CBR_2400;
		case 4800:
			return CBR_4800;
		case 9600:
			return CBR_9600;
		case 19200:
			return CBR_19200;
		case 38400:
			return CBR_38400;
		case 57600:
			return CBR_57600;
		case 115200:
			return CBR_115200;
		default:
			return CBR_9600;
		}
}

static int convbitsizevaltotcflag_tval(int val)
{
	return val;
	/*
	switch (val) {
		case 5: return CS5;
		case 6: return CS5;
		case 7: return CS7;
		case 8: return CS8;
		default: return CS8;
		}
		*/
}


// da ottimizzare secondo ASCII
/*
static unsigned char convert(unsigned long n) {
	switch (n) {
    	case 0 : return '0';
        case 1 : return '1';
        case 2 : return '2';
        case 3 : return '3';
        case 4 : return '4';
        case 5 : return '5';
        case 6 : return '6';
        case 7 : return '7';
        case 8 : return '8';
        case 9 : return '9';
        case 10 : return 'A';
        case 11 : return 'B';
        case 12 : return 'C';
        case 13 : return 'D';
        case 14 : return 'E';
        case 15 : return 'F';
        default : return '?';
    }
}
//------------------------------------------------------------------------------
static int deconv(unsigned char c) {
	switch (c) {
    	case '0' : return 0;
        case '1' : return 1;
        case '2' : return 2;
        case '3' : return 3;
        case '4' : return 4;
        case '5' : return 5;
        case '6' : return 6;
        case '7' : return 7;
        case '8' : return 8;
        case '9' : return 9;
        case 'A' : return 10;
        case 'B' : return 11;
        case 'C' : return 12;
        case 'D' : return 13;
        case 'E' : return 14;
        case 'F' : return 15;
        default : return 1000;
    }
}
*/
