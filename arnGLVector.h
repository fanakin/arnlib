/***************************************************************************
                          arnGLVector.h  -  description
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

#ifndef ArnGLVectorH
#define ArnGLVectorH

#include <qstring.h>
#include <QtOpenGL>
#include "arnlibtypes.h"
#include "CommonFunctions.h"

class arnGLVector {
    private:
    protected:
    public:
        int nCols;
        GLfloat *pCols;
        GLfloat *Table;
//        GLfloat ** VisTable;
        arnGLVector(void);
        arnGLVector(int col, GLfloat val);
        arnGLVector(const arnGLVector& aMat);
        ~arnGLVector(void);
        arnGLVector& operator=(const arnGLVector& aMat);
        bool operator==(const arnGLVector& aMat);
        GLfloat minCol(void);
        GLfloat maxCol(void);
        GLfloat minTable(void);
        GLfloat maxTable(void);
    };


#endif
