/***************************************************************************
                          arnGLMatrix.h  -  description
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

#ifndef ArnGLMatrixH
#define ArnGLMatrixH

#include <qstring.h>
#include <qgl.h>
#include "arnlibtypes.h"
#include "CommonFunctions.h"

class arnGLMatrix {
    private:
    protected:
    public:
        int nRows,nCols;
        GLfloat *pRows,*pCols;
        GLfloat **Table;
//        GLfloat ** VisTable;
        arnGLMatrix(void);
        arnGLMatrix(int row, int col, GLfloat val);
        arnGLMatrix(const arnGLMatrix& aMat);
        ~arnGLMatrix(void);
        arnGLMatrix& operator=(const arnGLMatrix& aMat);
        bool operator==(const arnGLMatrix& aMat);
        GLfloat minCol(void);
        GLfloat maxCol(void);
        GLfloat minRow(void);
        GLfloat maxRow(void);
        GLfloat minTable(void);
        GLfloat maxTable(void);
    };

#endif
