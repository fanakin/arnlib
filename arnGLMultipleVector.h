/***************************************************************************
                          arnGLMultipleVector.h  -  description
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

#ifndef ArnGLMultipleVectorH
#define ArnGLMultipleVectorH

#include <qstring.h>
#include <qgl.h>
#include "CommonFunctions.h"
// questa classe descrive un insieme di vettori, in cui
// l'asse x e' semper los tesso
class arnGLMultipleVector {
    private:
    protected:
    public:
        int nCols; // lunghezza di ogni singolo vettore e quindi anche dell'asse X
		int nRows; // numero di vettori
        GLfloat *pCols;
        GLfloat **Table;
        GLfloat *pRows;
//        GLfloat ** VisTable;
        arnGLMultipleVector(void);
        arnGLMultipleVector(int row, int col, GLfloat val);
        arnGLMultipleVector(const arnGLMultipleVector& aMat);
        ~arnGLMultipleVector(void);
        arnGLMultipleVector& operator=(const arnGLMultipleVector& aMat);
        bool operator==(const arnGLMultipleVector& aMat);
        GLfloat minCol(void);
        GLfloat maxCol(void);
        GLfloat minTable(void);
        GLfloat maxTable(void);
    };

#endif
