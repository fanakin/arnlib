/***************************************************************************
                          arnGLVector.cpp  -  description
                             -------------------
    begin                : lun lug 28 2003
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

#include <qapplication.h>

#include "arnGLVector.h"

arnGLVector::arnGLVector(void)
{
	nCols = 5;
	pCols = new GLfloat[nCols];
	if (!pCols) arnCriticalExit();
	Table = new GLfloat[nCols];
	if (!Table) arnCriticalExit();
}

arnGLVector::arnGLVector(int col, GLfloat val)
{
	nCols = col;
	pCols = new GLfloat[nCols];
	if (!pCols) arnCriticalExit();
	Table = new GLfloat[nCols];
	if (!Table) arnCriticalExit();
	for (int cndx = 0; cndx < nCols; cndx++) {
		Table[cndx] = val;
		}
}
                                     
arnGLVector::arnGLVector(const arnGLVector& aMat)
{
	nCols = aMat.nCols;
	pCols = new GLfloat[nCols];
	if (!pCols) arnCriticalExit();
	Table = new GLfloat[nCols];
	if (!Table) arnCriticalExit();
	for (int cndx = 0; cndx < nCols; cndx++) {
		pCols[cndx] = aMat.pCols[cndx];
		Table[cndx] = aMat.Table[cndx];
		}
}

arnGLVector::~arnGLVector(void)
{
	if (pCols) {delete [] pCols; pCols = 0;}
	if (Table) {delete [] Table;Table = 0;}
}

arnGLVector& arnGLVector::operator=(const arnGLVector& aMat)
{
	if (nCols != aMat.nCols) arnCriticalExit();
	for (int cndx = 0; cndx < nCols; cndx++) {
		pCols[cndx] = aMat.pCols[cndx];
		Table[cndx] = aMat.Table[cndx];
		}
    return *this;
}

bool arnGLVector::operator==(const arnGLVector& aMat)
{
	for (int cndx = 0; cndx < nCols; cndx++) if (pCols[cndx] != aMat.pCols[cndx]) return false;
	for (int cndx = 0; cndx < nCols; cndx++) if (Table[cndx] != aMat.Table[cndx]) return false;
	return true;
}

GLfloat arnGLVector::minCol(void)
{
	GLfloat lmn = pCols[0];
	for (int cIndx = 1; cIndx < nCols; cIndx++) {
		if (pCols[cIndx] < lmn) lmn = pCols[cIndx];
		}
	return lmn;
}

GLfloat arnGLVector::maxCol(void)
{
	GLfloat lmx = pCols[0];
	for (int cIndx = 1; cIndx < nCols; cIndx++) {
		if (pCols[cIndx] > lmx) lmx = pCols[cIndx];
		}
	return lmx;
}

GLfloat arnGLVector::minTable(void)
{
	GLfloat lmn = Table[0];
	for (int cIndx = 1; cIndx < nCols; cIndx++) {
		if (Table[cIndx] < lmn) lmn = Table[cIndx];
		}
	return lmn;
}

GLfloat arnGLVector::maxTable(void)
{
	GLfloat lmx = Table[0];
	for (int cIndx = 1; cIndx < nCols; cIndx++) {
		if (Table[cIndx] > lmx) lmx = Table[cIndx];
		}
	return lmx;
}

//---------------------------------------------------------------------------------------------------------------
