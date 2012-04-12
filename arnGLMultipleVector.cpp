/***************************************************************************
                          arnGLMultipleVector.cpp  -  description
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

#include "arnGLMultipleVector.h"

arnGLMultipleVector::arnGLMultipleVector(void)
{
	nCols = 5;
	nRows = 1;
	pCols = new GLfloat[nCols];
	if (!pCols) arnCriticalExit();
	pRows = new GLfloat[nRows];
	if (!pRows) arnCriticalExit();
	Table = new GLfloat*[nRows];
	if (!Table) arnCriticalExit();
	for (int rndx = 0; rndx < nRows; rndx++) {
		Table[rndx] = new GLfloat[nCols];
		if (!Table[rndx]) arnCriticalExit();
		}
}

arnGLMultipleVector::arnGLMultipleVector(int row, int col, GLfloat val)
{
	nCols = col;
	nRows = row;
	pCols = new GLfloat[nCols];
	if (!pCols) arnCriticalExit();
	pRows = new GLfloat[nRows];
	if (!pRows) arnCriticalExit();
	Table = new GLfloat*[nRows];
	if (!Table) arnCriticalExit();
	for (int cndx = 0; cndx < nCols; cndx++) {
		pCols[cndx] = cndx;
		}
	for (int rndx = 0; rndx < nRows; rndx++) {
		pRows[rndx] = rndx;
		}
	for (int rndx = 0; rndx < nRows; rndx++) {
		Table[rndx] = new GLfloat[nCols];
		if (!Table[rndx]) arnCriticalExit();
		for (int cndx = 0; cndx < nCols; cndx++) {
			Table[rndx][cndx] = val;
			}
		}
}
                                     
arnGLMultipleVector::arnGLMultipleVector(const arnGLMultipleVector& aMat)
{
	nCols = aMat.nCols;
	nRows = aMat.nRows;
	pCols = new GLfloat[nCols];
	if (!pCols) arnCriticalExit();
	pRows = new GLfloat[nRows];
	if (!pRows) arnCriticalExit();
	Table = new GLfloat*[nRows];
	if (!Table) arnCriticalExit();
	for (int cndx = 0; cndx < nCols; cndx++) {
		pCols[cndx] = aMat.pCols[cndx];
		}
	for (int rndx = 0; rndx < nRows; rndx++) {
		pRows[rndx] = aMat.pRows[rndx];
		}
	for (int rndx = 0; rndx < nRows; rndx++) {
		Table[rndx] = new GLfloat[nCols];
		if (!Table[rndx]) arnCriticalExit();
		for (int cndx = 0; cndx < nCols; cndx++) {
			Table[rndx][cndx] = aMat.Table[rndx][cndx];;
			}
		}
}

arnGLMultipleVector::~arnGLMultipleVector(void)
{
	if (pCols) {delete [] pCols; pCols = 0;}
	if (pRows) {delete [] pRows; pRows = 0;}
	if (Table) {
		for (int rndx = 0; rndx < nRows; rndx++) {
			if  (Table[rndx]) {delete Table[rndx]; Table[rndx] = 0;}
			}
		delete [] Table;Table = 0;
		}
}

arnGLMultipleVector& arnGLMultipleVector::operator=(const arnGLMultipleVector& aMat)
{
	if (nCols != aMat.nCols) arnCriticalExit();
	if (nRows != aMat.nRows) arnCriticalExit();
	for (int cndx = 0; cndx < nCols; cndx++) {
		pCols[cndx] = aMat.pCols[cndx];
		}
	for (int rndx = 0; rndx < nRows; rndx++) {
		pRows[rndx] = aMat.pRows[rndx];
		}
	for (int rndx = 0; rndx < nRows; rndx++) {
		for (int cndx = 0; cndx < nCols; cndx++) {
			Table[rndx][cndx] = aMat.Table[rndx][cndx];
			}
		}
    return *this;
}

bool arnGLMultipleVector::operator==(const arnGLMultipleVector& aMat)
{
	for (int cndx = 0; cndx < nCols; cndx++) if (pCols[cndx] != aMat.pCols[cndx]) return false;
	for (int rndx = 0; rndx < nRows; rndx++) if (pRows[rndx] != aMat.pRows[rndx]) return false;
	for (int rndx = 0; rndx < nRows; rndx++) {
		for (int cndx = 0; cndx < nCols; cndx++) {
			if (Table[rndx][cndx] != aMat.Table[rndx][cndx]) return false;
			}
		}
	return true;
}

GLfloat arnGLMultipleVector::minCol(void)
{
	GLfloat lmn = pCols[0];
	for (int cIndx = 1; cIndx < nCols; cIndx++) {
		if (pCols[cIndx] < lmn) lmn = pCols[cIndx];
		}
	return lmn;
}

GLfloat arnGLMultipleVector::maxCol(void)
{
	GLfloat lmx = pCols[0];
	for (int cIndx = 1; cIndx < nCols; cIndx++) {
		if (pCols[cIndx] > lmx) lmx = pCols[cIndx];
		}
	return lmx;
}

GLfloat arnGLMultipleVector::minTable(void)
{
	GLfloat lmn = Table[0][0];
	for (int rndx = 0; rndx < nRows; rndx++) {
		for (int cndx = 0; cndx < nCols; cndx++) {
			if (Table[rndx][cndx] < lmn) lmn = Table[rndx][cndx];
			}
		}
	return lmn;
}

GLfloat arnGLMultipleVector::maxTable(void)
{
	GLfloat lmx = Table[0][0];
	for (int rndx = 0; rndx < nRows; rndx++) {
		for (int cndx = 0; cndx < nCols; cndx++) {
			if (Table[rndx][cndx] > lmx) lmx = Table[rndx][cndx];
			}
		}
	return lmx;
}

//---------------------------------------------------------------------------------------------------------------
