/***************************************************************************
                          arnCycle.cpp  -  description
                             -------------------
    begin                : gio ott 21 2004
    copyright            : (C) 2004 by fabio giovagnini
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
#include <ctype.h> // requirend for isdigit
#include <stdio.h> // requirend only by toRawxxxx functions; better check needed
#include <math.h>
#include "CommonFunctions.h"
#include "arnCycle.h"

static char Separators[] = {',','\t'};

arnCycle::arnCycle(void)
{
	pfile = 0;
	filename = "";
	cyclename = "";
}

arnCycle::arnCycle(const char* fname)
{
	QString ln;
	pfile = 0;

	numoflines = 0;
	pfile = fopen(fname,"rb");
	if (pfile == NULL) arnCriticalExit();
	filename = fname;
	filename = filename.right(filename.length() - filename.findRev('/') - 1);
	arnDebug("filename = %s\n",filename.latin1());
	if (((ln = getLine(pfile)) != filename) || !ln.contains(".cle")) arnCriticalExit();
	numoflines++;
}

arnCycle::~arnCycle(void)
{
	if (pfile) {fclose(pfile); pfile = 0;}
}

bool arnCycle::isSeparator(char c)
{
	for (unsigned int i = 0; i < sizeof(Separators); i++) {
		if (c == Separators[i]) return true;
		}
	return false;
}

QString arnCycle::getLine(FILE *pf)
{
	QString res("");
	int c;
	if (!pf) return res;
	for(;;) {
		if ((c = fgetc(pf)) == EOF) return res;
		else if (c == '\r') ;
		else if (c == '\n') return res;
		else res += (char)c;
		}
}

