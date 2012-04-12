/***************************************************************************
                          arnGLMatrix.cpp  -  description
                             -------------------
    begin                : ven giu 20 2003
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

#include "arnGLMatrix.h"


arnGLMatrix::arnGLMatrix(void)
{
    nRows = 5;
    nCols = 5;
    
    pRows = new GLfloat[nRows];
    if (!pRows) arnCriticalExit();
    pCols = new GLfloat[nCols];
    if (!pCols) arnCriticalExit();

    Table = new GLfloat*[nRows];
//    VisTable = new GLfloat*[nRows];
    if (!Table) arnCriticalExit();
//    if (!VisTable) arnCriticalExit();
    for (int rndx = 0; rndx < nRows; rndx++) {
        Table[rndx] = new GLfloat[nCols];
//        VisTable[rndx] = new GLfloat[nCols];
        if (!Table[rndx]) arnCriticalExit();
//        if (!VisTable[rndx]) arnCriticalExit();
        }
}

arnGLMatrix::arnGLMatrix(int row, int col, GLfloat val)
{
    nRows = row;
    nCols = col;

    pRows = new GLfloat[nRows];
    if (!pRows) arnCriticalExit();
    pCols = new GLfloat[nCols];
    if (!pCols) arnCriticalExit();
    Table = new GLfloat*[nRows];
//    VisTable = new GLfloat*[nRows];
    if (!Table) arnCriticalExit();
//    if (!VisTable) arnCriticalExit();
    for (int rndx = 0; rndx < nRows; rndx++) {
        Table[rndx] = new GLfloat[nCols];
//        VisTable[rndx] = new GLfloat[nCols];
        if (!Table[rndx]) arnCriticalExit();
//        if (!VisTable[rndx]) arnCriticalExit();
        }
    for (int rndx = 0; rndx < nRows; rndx++)
        for (int cndx = 0; cndx < nCols; cndx++) {
            Table[rndx][cndx] = val;
//            VisTable[rndx][cndx] = val;
            }
}

arnGLMatrix::arnGLMatrix(const arnGLMatrix& aMat)
{
    nRows = aMat.nRows;
    nCols = aMat.nCols;

    pRows = new GLfloat[nRows];
    if (!pRows) arnCriticalExit();
    pCols = new GLfloat[nCols];
    if (!pCols) arnCriticalExit();
    Table = new GLfloat*[nRows];
//    VisTable = new GLfloat*[nRows];
    if (!Table) arnCriticalExit();
//    if (!VisTable) arnCriticalExit();
    for (int rndx = 0; rndx < nRows; rndx++) {
        Table[rndx] = new GLfloat[nCols];
//        VisTable[rndx] = new GLfloat[nCols];
        if (!Table[rndx]) arnCriticalExit();
//        if (!VisTable[rndx]) arnCriticalExit();
        }
    for (int rndx = 0; rndx < nRows; rndx++) pRows[rndx] = aMat.pRows[rndx];
    for (int cndx = 0; cndx < nCols; cndx++) pCols[cndx] =   aMat.pCols[cndx];
    for (int rndx = 0; rndx < nRows; rndx++)
        for (int cndx = 0; cndx < nCols; cndx++) {
            Table[rndx][cndx] = aMat.Table[rndx][cndx];
//            VisTable[rndx][cndx] = aMat.VisTable[rndx][cndx];
            }
}

arnGLMatrix::~arnGLMatrix(void)
{
    if (pRows) {delete [] pRows; pRows = 0;}
    if (pCols) {delete [] pCols; pCols = 0;}
    if (Table) {
        for (int rIndx = 0; rIndx < nRows; rIndx++) {
            if (Table[rIndx])  {delete [] Table[rIndx]; Table[rIndx] = 0;}
//            if (VisTable[rIndx])  {delete [] VisTable[rIndx]; VisTable[rIndx] = 0;}
            }
        delete [] Table;
        Table = 0;
//        delete [] VisTable;
//        VisTable = 0;
        }

}

arnGLMatrix& arnGLMatrix::operator=(const arnGLMatrix& aMat)
{
    if (nRows != aMat.nRows) arnCriticalExit();
    if (nCols != aMat.nCols) arnCriticalExit();

    for (int rndx = 0; rndx < nRows; rndx++) pRows[rndx] =   aMat.pRows[rndx];
    for (int cndx = 0; cndx < nCols; cndx++) pCols[cndx] =   aMat.pCols[cndx];

    for (int rndx = 0; rndx < nRows; rndx++)
        for (int cndx = 0; cndx < nCols; cndx++) {
            Table[rndx][cndx] = aMat.Table[rndx][cndx];
//            VisTable[rndx][cndx] = aMat.VisTable[rndx][cndx];
            }
    return *this;
}

bool arnGLMatrix::operator==(const arnGLMatrix& aMat)
{
    for (int rndx = 0; rndx < nRows; rndx++)
        if (pRows[rndx] != aMat.pRows[rndx]) return false;
    for (int cndx = 0; cndx < nCols; cndx++)
        if (pRows[cndx] != aMat.pCols[cndx]) return false;

    for (int rndx = 0; rndx < nRows; rndx++)
        for (int cndx = 0; cndx < nCols; cndx++) {
            if (Table[rndx][cndx] != aMat.Table[rndx][cndx]) return false;
//            if (VisTable[rndx][cndx] != aMat.VisTable[rndx][cndx]) return false;
            }

    return true;    
}

GLfloat arnGLMatrix::minCol(void)
{
    GLfloat lmn = pCols[0];
    for (int cIndx = 1; cIndx < nCols; cIndx++) {
        if (pCols[cIndx] < lmn) lmn = pCols[cIndx];
        }
    return lmn;
}

GLfloat arnGLMatrix::maxCol(void)
{
    GLfloat lmx = pCols[0];
    for (int cIndx = 1; cIndx < nCols; cIndx++) {
        if (pCols[cIndx] > lmx) lmx = pCols[cIndx];
        }
    return lmx;
}

GLfloat arnGLMatrix::minRow(void)
{
    GLfloat lmn = pRows[0];
    for (int rIndx = 1; rIndx < nRows; rIndx++) {
        if (pRows[rIndx] < lmn) lmn = pRows[rIndx];
        }
    return lmn;
}

GLfloat arnGLMatrix::maxRow(void)
{
    GLfloat lmx = pRows[0];
    for (int rIndx = 1; rIndx < nRows; rIndx++) {
        if (pRows[rIndx] > lmx) lmx = pRows[rIndx];
        }
    return lmx;
}

GLfloat arnGLMatrix::minTable(void)
{
    GLfloat lmn = Table[0][0];
    for (int rIndx = 1; rIndx < nRows; rIndx++) {
        for (int cIndx = 1; cIndx < nCols; cIndx++) {
            if (Table[rIndx][cIndx] < lmn) lmn = Table[rIndx][cIndx];
            }
        }
    return lmn;
}

GLfloat arnGLMatrix::maxTable(void)
{
    GLfloat lmx = Table[0][0];
    for (int rIndx = 1; rIndx < nRows; rIndx++) {
        for (int cIndx = 1; cIndx < nCols; cIndx++) {
            if (Table[rIndx][cIndx] > lmx) lmx = Table[rIndx][cIndx];
            }
        }
    return lmx;
}



//QFont f = QApplication::font();
// f.setStyleStrategy(QFont::PreferBitmap);
// renderText(x, y, "Text", f);

