/*
*****************************************************************************
*
*   File Name : GlobalDecl.h
*
*    Author : Fabio Giovagnini (Aurion s.r.l.)  09/02/2005
*   Contents : DataLogger Common Values Header File
*
*****************************************************************************
*/

#ifndef _GLOBALDECL_H
#define _GLOBALDECL_H

#define SYNC1 0xDD
#define SYNC2 0xA5
#define SYNC3 0xFF   /* address */
/* 0xFF is an universal code used for point to point access , all devices recognize
this address but you can mask it at run time.
Do not use it with bus or broadcast communications
*/

#define ACK 0x06
#define NAK 0x15

#define   DLDCHNDAT    0
#define   READCHAN     1
#define   READBLK      2
#define   WRITEBLK     3
#define   GETDEVID     4
#define   GETSTATUS    5
#define   CARRIER      6
#define   RUNLOGGER    7
#define   STOPLOGGER   8
#define   CLRBUFFER    9
#define   SETNCHAN     10
#define   GETNCHAN     11
#define   SETCHANPAR   12
#define   GETCHANPAR   13
#define   GETDEVCNF    14
#define   RESERRORS    15
#define   HWTEST       16
#define   SETDEVMODE   17
#define   DLDCHNMAP    18
#define   DLOGIN        19       /* aggiunta Fabio 12-02-1999 */
#define   DLOGOUT       20       /* aggiunta Fabio 12-02-1999 */
#define   NODEST       253       /* aggiunta Fabio 12-2-1999 */
#define   SETADDR      254      // used by comm protocol, reserved for all devices
#define   SETPROTOCOL  255      // used by comm protocol, reserved for all devices

#define   USERMODE     'U'      // device mode
#define   CFGMODE      'C'

// do not change this values !!
#define   ALL_ADDR          0x00      // pass allcode and address except setprotocol
#define   NOALL_ADDR        0x01      // pass address except setprotocol
#define   ALL_NOADDR        0x02      // pass allcode except setprotocol
#define   NOALL_NOADDR      0x03      // no pass except setprotocol

#define   ENABLETEST      0     // enable test (whithout this step the test do not run)
#define   RUNRAMTEST      1     // run the ram test
#define   RUNHWTEST       2     // run the flash & HW test
#define   DEALLOCTEST     3     // reboot device after reading result

#define     FAILALLOCATION      0x00000001      // heap allocation fail
#define     BADSTATUS           0x00000002      // at bootstrap unknown state in save area
#define     FAILWRITEFLASH      0x00000004      // write on flash memory failed
#define     BADCHANNEL          0x00000008      // access to unallocated channel
#define     BADPOINTER          0x00000010      // databuff pointer out of area
#define     BADSTARTPTR         0x00000020      // start pointer out of area
#define     BADLASTPTR          0x00000040      // last pointer out of area
#define     CHANNELSIZE         0x00000080      // bad channel size param found
#define     CHANNELFLAG         0x00000100      // unused
#define     BADDLDCHAN          0x00000200      // unallocated chan found in data area
#define     BADMAPPING          0x00000400      // pointer jump startptr back in download
#define     INTQUEUE            0x00000800      // detected an interrupt queue in IntAcq()
#define     MAINSLOW            0x00001000      // detected a main cycle too slow
#define     TESTENABLED         0x00002000      // detected test enabled at bootstrap
#define     BADOVERLAP          0x00004000      // detected bad overlap at bootstrap
#define     FAILCLEARFLASH      0x00008000      // clear flash segment fail

/* channel's Number for the several devices MINJ400 based */
#define MAXLOGTIMEOUT 2

#define ENDFRAMEMARK   	0xFF  			// marca di fine frame
#define GOODPACKMARK    0xFE			// marca di pacchetto buono
#define CLEARREQUEST	0xFC                    // marca di richesta di reset
#define NOTGOODPACKMARK     0xF8                // marca di pacchetto non buono

#endif
