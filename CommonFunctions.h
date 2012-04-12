/***************************************************************************
                          CommonFunctions.h  -  description
                             -------------------
    begin                : lun gen 27 2003
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

#define DEBUG

#ifdef DEBUG
#include <QtDebug>
#define HITPOINT    { qDebug() << __FUNCTION__ << ":" << __FILE__ << "(" << __LINE__ << ")" ; }
#else
#define HITPOINT
#endif

#ifdef WIN32
#include <windows.h>
#endif

#ifdef __cplusplus
extern "C" {
#endif

//---------------------------------------------------------------------------
#ifndef CommonFunctionsH
#define CommonFunctionsH
//---------------------------------------------------------------------------
#include <stdlib.h>
#include <stdio.h>

/*!
*
*/
#define arnDebug(msg...) do { \
    qDebug("file : %s; function : %s; line : %d - ",__FILE__,__FUNCTION__,__LINE__); \
    qDebug(msg); \
    } while(0)

/*!
*
*/
#define arnCriticalExit() do { \
    qCritical("file : %s; function : %s; line : %d - Critical Abort.\n",__FILE__,__FUNCTION__,__LINE__); \
    exit(EXIT_FAILURE); \
    } while(0)

/*!
*
*/
unsigned long lmirror(unsigned long value);

/*!
*
*/
unsigned short smirror(unsigned short value);

/*!
*
*/
unsigned char NToD(char InChr);


/*!
*
*/
char DToN(unsigned char InDigit);

/*!
*
*/
char arnToUP(char InChr);

/*!
*
*/
bool arnHexDigitToBin(unsigned char *dest,int *destlen, const char *src,int srclen);

/*!
*

*/
bool arnBinToHexDigit(char *dest,int *destlen, const unsigned char *src,int srclen);

/*!
*
*/
unsigned long atolh(char* str);

/*!
*
*/
void arnSleep(int mSec);

/*!
*
*/
const char* arnExtactPath(char *outpathname,const char* absfilename);

/*!
*
*/
const char* arnExtactFileName(char *outfilename,const char* absfilename);

/*!
*
*/
int arnFindFile(const char* absdir, const char* filename);

/*!
*
*/
bool copyfile(const char *destination, const char *source);

/*!
*
*/
bool arnCopyFileToBuffer(char *bufdest, size_t buffsize, const char *source);

/*!
*
*/
bool arnCopyBufferToFile(char *bufsrc, size_t buffsize, const char *destination);

#ifdef WIN32
#ifndef strtok_r
char *strtok_r(char *ptr, const char *sep, char **end);
#endif
#endif

#endif

#ifdef __cplusplus
}
#endif
