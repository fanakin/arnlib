//---------------------------------------------------------------------------
#include <stdio.h> /* Standard input/output definitions */
#include <string.h> /* String function definitions */
#include <unistd.h> /* UNIX standard function definitions */
#include <fcntl.h> /* file control interface */
#include <sys/types.h> /* UNIX types */
#include <sys/socket.h> /* Barcklay sockets  */
#include <netinet/in.h> /* Barcklay sockets  */
#include <netinet/tcp.h> /* Barcklay sockets  */
#include <arpa/inet.h> /* Barcklay sockets  */
#include <netdb.h> /* Barcklay sockets  */
#include <errno.h> /* Error number definitions */

//------------------------------------------------------------------------------
//		Serial Port
//------------------------------------------------------------------------------
#include "CommonFunctions.h"
#include "arnSocketPort.h"
//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
#define __DEBUG__
#ifdef __DEBUG__
#define __CNS_OUT(arg...) do {fprintf(stderr,arg); fflush(stderr);} while (0)
#else
#define __CNS_OUT(arg...)
#endif

#define 	UMAXERR 	5

//------------------------------------------------------------------------------
//------------------------------------------------------------------------------
arnSocketPort::arnSocketPort(sockdef aport) : arnSerialInterface() {
	char tB[1536];
//	unsigned int lIndex;
	int rc;
	char connMessage[] = "I'm connected\n";
	int tmp;
	bzero(tB,sizeof(tB));
	rx = NULL;
	timeout = aport.timeout;
	status = 0;
//	if (aport.hostname == 0) {
//		status = 4 ;						// invalid hostname and ip address
//		return;
//		}
	h = gethostbyname(aport.hostname);
	if(h==NULL) {
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
	tmp = fcntl(HPort, F_GETFL, 0);
	if ( tmp >= 0 ) tmp = fcntl( HPort, F_SETFL, (tmp | (O_NONBLOCK | O_ASYNC) /*FNDELAY O_NDELAY*/));
	if ( tmp < 0 ) {
		status = 9 ;						// invald binding
		return;
		}
	tmp = 1;
	if (setsockopt(HPort, SOL_TCP, TCP_NODELAY, &tmp, sizeof(tmp)) == -1) {
		perror("TCP_NODELAY");
		status = 10;						// invald connect
		return;
		}
	tmp = 1;
	if (setsockopt(HPort, SOL_TCP, TCP_QUICKACK, &tmp, sizeof(tmp)) == -1) {
		perror("TCP_QUICKACK");
		status = 11;						// invald connect
		return;
		}
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
	usleep(1000);
	arnDebug("%s",tB);
}
//------------------------------------------------------------------------------
arnSocketPort::~arnSocketPort() {
	if (rx) delete [] rx;					  // deallocate rx buffer
	if (status == 0) {;}
	close(HPort);             // close port
}
//------------------------------------------------------------------------------
bool arnSocketPort::SendData(char *Buff,int Dim)
{
	int cer = 0;
// test test test
// char tstB[4096];
// bzero(tstB,sizeof(tstB));
// strncpy(tstB,Buff,Dim);
// qDebug() << __FUNCTION__ << "Buffer:" << (char *)tstB;

	do {
		if (/*write(HPort, Buff, Dim)*/send(HPort, Buff, Dim, MSG_DONTWAIT) <= 0) {__CNS_OUT("%s\n","cerr.");cer++; continue;}
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

	memset (Buff, 0, Dim);

	FD_ZERO(&rfds);
	FD_SET(HPort, &rfds);
	
//	int tmp = 1;
	tv.tv_sec = 0;
	tv.tv_usec = (100000 * timeout);
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
//		    qDebug() << i ;
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
	else if (retval == 0) 
	    return false;
	else 
	    return false;
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
