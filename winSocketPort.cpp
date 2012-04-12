//---------------------------------------------------------------------------
#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <errno.h> /* Error number definitions */

//------------------------------------------------------------------------------
//		Serial Port
//------------------------------------------------------------------------------
#include "CommonFunctions.h"
#include "winSocketPort.h"
#include <unistd.h>
#include <fcntl.h>

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define __DEBUG__
#ifdef __DEBUG__
#define __CNS_OUT(arg...) do {fprintf(stderr,arg); fflush(stderr);} while (0)
#else
#define __CNS_OUT(arg...)
#endif

#define 	UMAXERR 	5

bool arnSocketPort::socketInitialized = false;

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
arnSocketPort::arnSocketPort(sockdef aport) : arnSerialInterface() 
{
	WSADATA wsaData;
        socketInitialized = false;
	if (!socketInitialized) {
		if (WSAStartup (MAKEWORD(2,0), &wsaData)) {
			qWarning ("Cannot initialize WinSocks: %d", WSAGetLastError());
			status = 1;
			return;
		}
		socketInitialized = true;
	}

	char tB[1536];
	int rc;
	char connMessage[] = "I'm connected\n";
	u_long tmp;
	memset(tB,0,sizeof(tB));
        memset(&localAddr,0,sizeof(localAddr));
        memset(&servAddr,0,sizeof(servAddr));
        rx = NULL;
	timeout = aport.timeout;
	status = 0;


	h = gethostbyname(aport.hostname);
	if(h==NULL) {
		qDebug() << "gethostbyname returned error " << WSAGetLastError();
		status = 5 ;						// unknown host
		return;
	}

	servAddr.sin_family = h->h_addrtype;
	memcpy((char *) &servAddr.sin_addr.s_addr, h->h_addr_list[0], h->h_length);
	servAddr.sin_port = htons(aport.port);
	/* create socket */
	if ((HPort = socket(PF_INET, SOCK_STREAM,IPPROTO_TCP)/*socket(AF_INET,SOCK_STREAM,0)*/) < 0) {
		status = 1 ;						// invald handle
		return;
	}

        /* bind any port number */
	localAddr.sin_family = AF_INET;
	localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
	localAddr.sin_port = htons(0);
	rc = bind(HPort, (struct sockaddr *) &localAddr, sizeof(localAddr));
	if(rc < 0) {
		status = 2 ;						// invald binding
		return;
		}

        /* connect to server */
	rc = connect(HPort, (struct sockaddr *) &servAddr, sizeof(servAddr));
	if(rc < 0) {
		status = 3 ;						// invald connect
		return;
		}

	tmp = 1;
	ioctlsocket (HPort, FIONBIO, &tmp);

	// TCP_NODELAY will disable the Nagle algorithm.
	tmp = 1;
	if (setsockopt(HPort, IPPROTO_TCP, TCP_NODELAY, (char *)&tmp, sizeof(tmp)) == -1) {
		perror("TCP_NODELAY");
		status = 10;						// invald connect
		return;
		}

#if 0
	tmp = 1;
	if (setsockopt(HPort, IPPROTO_TCP, TCP_QUICKACK, &tmp, sizeof(tmp)) == -1) {
		perror("TCP_QUICKACK");
		status = 11;						// invald connect
		return;
		}
#endif

	rx = new unsigned char[RXBFSIZE];
	if (!rx) {
		status = 6 ;						// rx not allocated
		return;
		}

	if (!ReceiveData(tB,strlen(connMessage))) {
		status = 7 ;						// no host answers
		return;
		}

	if (strcmp(tB,connMessage)) {
		status = 8 ;						// wrong endpoint
		return;
		}
	arnDebug("%s",tB);
}
//------------------------------------------------------------------------------
arnSocketPort::~arnSocketPort() {
	if (rx) delete [] rx;					  // deallocate rx buffer
	if (status == 0) {;}
	shutdown(HPort, SD_BOTH);
	closesocket(HPort);             // close port
	if (socketInitialized == true) {WSACleanup();socketInitialized = false;}
}
//------------------------------------------------------------------------------
bool arnSocketPort::SendData(char *Buff,int Dim)
{
	int cer = 0;
// test test test
//char tstB[4096];
//bzero(tstB,sizeof(tstB));
//strncpy(tstB,Buff,Dim);
//__CNS_OUT("%s\n",tstB);
	do {
		// HAVES: MSG_DONTWAIT
		if (send(HPort, Buff, Dim, 0) <= 0) {__CNS_OUT("%s\n","cerr.");cer++; continue;}
		else {break;}
		} while (cer < UMAXERR);
	if (cer == UMAXERR) {__CNS_OUT("Send Data - cer = UMAXERR.\n"); return false;}
	return true;
}
//------------------------------------------------------------------------------
bool arnSocketPort::ReceiveData(char *Buff,int Dim)
{
	fd_set rfds;
	struct timeval tv;
	int retval;
// test test test
//__CNS_OUT("Dim=%d\n",Dim);

        FD_ZERO(&rfds);
        FD_SET((unsigned int)HPort, &rfds);
	
//	int tmp = 1;
	tv.tv_sec = 0;
	tv.tv_usec = 100000 * timeout;
	retval = select(HPort + 1, &rfds, NULL, NULL, &tv);
	if (retval > 0) {
		if (FD_ISSET(HPort, &rfds)) {
			int i;
			for (i = 0; i < Dim; i++) {
				char c;
				int  r = recv(HPort,&c,1,0);
				if (r == -1) {arnDebug("exit 1\n"); return false;}
				if (r == 0) {arnDebug("exit 2\n");return true;}
				Buff[i] = c;
				}
// test test test
//char tstB[4096];
//bzero(tstB,sizeof(tstB));
//strncpy(tstB,Buff,Dim);
//__CNS_OUT("%s\n",tstB);
			return true;
			}
// test test test
//__CNS_OUT("%s\n","No Char recv.");
		return false;
		}
	else if (retval == 0) return false;
	else return false;
}
//------------------------------------------------------------------------------
bool arnSocketPort::PurgeRx(void)
{
	return true;
}
//------------------------------------------------------------------------------
bool arnSocketPort::PurgeTx(void)
{
	return true;
}
//------------------------------------------------------------------------------
bool arnSocketPort::SetTimeout(int to)
{
	timeout = to;
	return true;
}
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
