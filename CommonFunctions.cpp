/***************************************************************************
                          CommonFunctions.cpp  -  description
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

//---------------------------------------------------------------------------
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/param.h>
#include <dirent.h>
#include <errno.h>
#include <QString>
#include <string.h>

#include "CommonFunctions.h"

//---------------------------------------------------------------------------
//---------------------------------------------------------------------------
//////////////////////////////////// Common Functions //////////////////////////
unsigned long lmirror(unsigned long value)
{
    unsigned long  r;
    unsigned char *v = (((unsigned char*) &value) + 3);
    unsigned char *x = (unsigned char*) &r;
    *(x++) = *(v--);
    *(x++) = *(v--);
    *(x++) = *(v--);
    *x = *v;
    return r;
}
//---------------------------------------------------------------------------
unsigned short smirror(unsigned short value)
{
    unsigned short  r;
    unsigned char *v = (((unsigned char*) &value) + 1);
    unsigned char *x = (unsigned char*) &r;
    *(x++) = *(v--);
    *x = *v;
    return r;
}
//---------------------------------------------------------------------------

//***** TODO: Verificare tutte queste funzioni che seguono *****************//

unsigned char NToD(char InChr)
{
    switch (InChr) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'a': return 10;
        case 'b': return 11;
        case 'c': return 12;
        case 'd': return 13;
        case 'e': return 14;
        case 'f': return 15;
        case 'A': return 10;
        case 'B': return 11;
        case 'C': return 12;
        case 'D': return 13;
        case 'E': return 14;
        case 'F': return 15;
        default : return 0;
        }
}
char DToN(unsigned char InDigit)
{
    switch (InDigit) {
        case 0: return '0';
        case 1: return '1';




        case 2: return '2';
        case 3: return '3';
        case 4: return '4';
        case 5: return '5';
        case 6: return '6';
        case 7: return '7';
        case 8: return '8';
        case 9: return '9';
        case 10: return 'A';
        case 11: return 'B';
        case 12: return 'C';
        case 13: return 'D';
        case 14: return 'E';
        case 15: return 'F';
        default : return '0';
        }
}
//---------------------------------------------------------------------------
char arnToUP(char InChr)
{
    switch (InChr) {
        case 'a': return 'A';
        case 'b': return 'B';
        case 'c': return 'C';
        case 'd': return 'D';
        case 'e': return 'E';
        case 'f': return 'F';
        default : return InChr;
        }
}
//---------------------------------------------------------------------------

//** TODO: Correggere, possibile buffer overflow in queste due funzioni!!!

bool arnHexDigitToBin(unsigned char *dest,int *destlen, const char *src,int srclen)
{
    if ((srclen % 2)) return false;
    if (!dest || !src) return  false;
    for (int i = 0; i < srclen;) {
        *dest++ = (unsigned char) ((0x10 * NToD(src[i++])) + NToD(src[i++]));
        }
    *destlen = srclen / 2;
    return true;
}
//---------------------------------------------------------------------------
bool arnBinToHexDigit(char *dest,int *destlen, const unsigned char *src,int srclen)
{
    for (int i = 0; i < srclen;) {
        *dest++ = DToN((src[i] & 0xF0) >> 4);
        *dest++ = DToN(src[i++]  & 0x0F);
        }
    *destlen =  2 * srclen;
    return true;
}
//---------------------------------------------------------------------------
unsigned long atolh(char* str)
{
    unsigned char l = 0;
    char* strc = str;
    while (*strc++) l++;
    l /= ((unsigned char) 2);
    union _Res {
    	unsigned long ul;
        unsigned char uc[4];
        } Res;
    Res.ul = 0;    
    unsigned char BytesC = 1;
    strc = str;
	while (*strc) {
        unsigned char t = ((unsigned char) (NToD(*strc++) * 16 + NToD(*strc++)));
        Res.uc[l - BytesC] = t;
        BytesC++;
    	}
	return Res.ul;
}
//---------------------------------------------------------------------------
#include <limits.h>
#include <sys/time.h>

#ifdef WIN32

void arnSleep (int mSec)
{
	Sleep(mSec);
}

#else

void arnSleep(int mSec)
{

	// TODO:  E' possibile cambiare questa funzione utilizzando semplicemente la usleep() ?
	struct timeval tv;
	long tm1,tm2;
	unsigned long uSec;
	unsigned long delta = 0;
	uSec = (unsigned long) (mSec * 1000);
	if (!gettimeofday(&tv,0)) {
		tm1 = tv.tv_usec;
		do {
                        if (gettimeofday(&tv,0) == -1) break;
			tm2 = tv.tv_usec;
                        if (tm2 >= tm1) delta = tm2 -tm1;
                        else delta = tm2 + (LONG_MAX - tm1);
			} while (delta <= uSec);
		}
}

#endif

//---------------------------------------------------------------------------
//int fabioerrno;
int arnFindFile(const char* absdir, const char* filename)
{
    DIR* dID;
    dirent* dp;
    char oldwpath[MAXPATHLEN];

    if (!absdir) return 0;
    dID = opendir(absdir);
    if (!dID) return 0;
    if (!getcwd(oldwpath, sizeof(oldwpath))) {
        closedir(dID);
        return 0;
        }

    if (chdir(absdir) == -1) {
        closedir(dID);
        return 0;
        }

    while ((dp = readdir(dID)) != NULL) {
        DIR* test;
        char tempfilename[MAXPATHLEN];
        memset(tempfilename,0, sizeof(tempfilename));
        char* tests;
        tests = (char*)arnExtactFileName(tempfilename,filename);
        if (!strcmp(tests,dp->d_name)) {
            if ((test = opendir(tests)) == NULL) {
//                fabioerrno = errno;
                switch (errno) {
                    case ENOTDIR:
                        chdir(oldwpath);
                        closedir(dID);
                        return 1;
                    case EACCES:
                    case ENAMETOOLONG:
                    case EMFILE:
                    case ENFILE:
                    case ENOENT:
                    case ENOMEM:
                    default :
                        break;
                    }
                }
            }
        }
    chdir(oldwpath);
    closedir(dID);
    return 0;
}
//---------------------------------------------------------------------------
// not fully debugged

#ifdef WIN32
#define PATHSEPARATOR '\\'
#define PATHSEPARATOR_STR "\\"
#else
#define PATHSEPARATOR  '/'
#define PATHSEPARATOR_STR "/"
#endif

const char* arnExtactPath(char *outpathname,const char* absfilename)
{
    char *ret;

	outpathname[0] = 0;
	if (absfilename[0] != PATHSEPARATOR) {
#ifdef WIN32
		if (absfilename[1] != ':') {	
			strcpy (outpathname, ".");
			strcat (outpathname, PATHSEPARATOR_STR);
		}
#else
		strcpy (outpathname, ".");
		strcat (outpathname, PATHSEPARATOR_STR);
#endif
	}

    strcat(outpathname, absfilename);
    ret = outpathname;
    ret += strlen(outpathname);

    while ((*ret != PATHSEPARATOR) && (ret != outpathname)) ret--;
    if (ret > outpathname) *ret = 0;
    return  outpathname;
}
//---------------------------------------------------------------------------
const char* arnExtactFileName(char *outfilename,const char* absfilename)
{
    char *ret;

    strcpy(outfilename,"");
    ret = (char*)absfilename;
    ret += strlen(absfilename);
    while ((*ret != PATHSEPARATOR) && (ret != absfilename)) ret--;
    if (ret == absfilename) strcpy(outfilename, ret);
    else {ret++; strcpy(outfilename, ret);}

    return  outfilename;
}
//---------------------------------------------------------------------------
bool copyfile(const char *destination, const char *source)
{
    FILE *in, *out;
    int c;

    in = fopen(source,"rb");
    if (in == NULL) return false;
    out = fopen(destination,"wb");
    if (out == NULL) return false;

    for(;;) {
       if ((c = fgetc(in)) == EOF) break;
       fputc(c,out);
    }

    fclose(in);
    fclose(out);
    return true;
}
//---------------------------------------------------------------------------
bool arnCopyFileToBuffer(char *bufdest, size_t buffsize, const char *source)
{
	FILE *in;
	int c;
	size_t byteCnt = 0;

	in = fopen(source,"rb");
	if (in == NULL) return false;
	for(;;) {
		if ((c = fgetc(in)) == EOF) break;
		bufdest[byteCnt++] = (char)c;
		if (byteCnt == buffsize) {fclose(in); return false;}
		}
	bufdest[byteCnt] = 0;
	fclose(in);
	return true;
}
//---------------------------------------------------------------------------
bool arnCopyBufferToFile(char *bufsrc, size_t buffsize, const char *destination)
{
	FILE *out;
	int c;
	size_t byteCnt = 0;

	out = fopen(destination,"wb");
	if (out == NULL) return false;

	for(;;) {
		c = bufsrc[byteCnt++];
		fputc(c,out);
		if (byteCnt == buffsize) break;
		}
	fclose(out);
	return true;
}

#ifdef WIN32
#ifndef strtok_r
char *strtok_r(char *ptr, const char *sep, char **end)
{
	if (!ptr)
		/* we got NULL input so then we get our last position instead */
		ptr = *end;

	/* pass all letters that are including in the separator string */
	while (*ptr && strchr(sep, *ptr))
		++ptr;

	if (*ptr) {
		/* so this is where the next piece of string starts */
		char *start = ptr;

		/* set the end pointer to the first byte after the start */
		*end = start + 1;

		/* scan through the string to find where it ends, it ends on a
		null byte or a character that exists in the separator string */
		while (**end && !strchr(sep, **end))
			++*end;

		if (**end) {
			/* the end is not a null byte */
			**end = '\0';  /* zero terminate it! */
			++*end;        /* advance the last pointer to beyond the null byte */
		}

		return start; /* return the position where the string starts */
	}

	/* we ended up on a null byte, there are no more strings to find! */
	return NULL;
}
#endif
#endif
