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
#include "arnThrottleCycle.h"

arnThrottleCycle::arnThrottleCycle(void)
	: arnCycle()
{
	CycleSize = 0;
	pCycle = 0;
}

arnThrottleCycle::arnThrottleCycle(const char* fname)
	: arnCycle(fname)
{
	QString ln;

	if ((cyclename = getLine(pfile)) == "") arnCriticalExit();
	numoflines++;
	arnDebug("cyclename = %s\n",cyclename.latin1());
	ln = getLine(pfile);
	CycleSize = ln.toUInt();
	if (CycleSize == 0) arnCriticalExit();
	numoflines++;
	arnDebug("CycleSize = %d\n",CycleSize);
	pCycle = new struct stepItem[CycleSize];
	if (!pCycle) arnCriticalExit();
	for (unsigned int i = 0; i < CycleSize; i++) {
		ln = getLine(pfile);
		if (ln == "") arnCriticalExit();
		pCycle[i].OpenPerc = getOpenPerc(ln).toInt();
		pCycle[i].DuringTime = getDuringTime(ln).toInt();
		numoflines++;
		arnDebug("Cycle[%d].OpenPerctab = %d\tCycle[%d].DuringTime = %d\n",i,pCycle[i].OpenPerc,i,pCycle[i].DuringTime);
		}
	arnDebug("numoflines = %d\n",numoflines);
	// very very important: this closing get safety over the file
	if (pfile) {fclose(pfile); pfile = 0;}
}

arnThrottleCycle::~arnThrottleCycle(void)
{
	if (pCycle) {delete pCycle; pCycle = 0;}
}


QString arnThrottleCycle::getOpenPerc(QString line)
{
	QString res("");
	if (line.length() == 0) return res;
	for (int i = 0; i < line.length(); i++) {
		if (isSeparator(line.latin1()[i])) return res;
		else if (line.latin1()[i] == '\n') return res;
		else if (isdigit(line.latin1()[i])) res += line.latin1()[i];
		}
	return res;
}

QString arnThrottleCycle::getDuringTime(QString line)
{
	QString res("");
	bool separatorfound = false;
	if (line.length() == 0) return res;
	for (int i = 0; i < line.length(); i++) {
		if (separatorfound) {
			if (line.latin1()[i] == '\n') return res;
			else if (isdigit(line.latin1()[i])) res += line.latin1()[i];
			}
		else {
			if (isSeparator(line.latin1()[i])) separatorfound = true;
			}
		}
	return res;
}

