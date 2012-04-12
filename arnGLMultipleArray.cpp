/***************************************************************************
                          arnGLArray.cpp  -  description
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
#include <QMouseEvent>

#include "arnGLMultipleArray.h"

#define __ABS__(x) (x > 0 ? x : -x)
#define __MAX__(x,y) (x >= y ? x : y)
#define __MIN__(x,y) (x <= y ? x : y)
#define WINDOWS_X	-0.65
#define WINDOWS_Y	0.65
#define WINDOWS_W	(2 * __ABS__(WINDOWS_X))
#define WINDOWS_H	(2 * __ABS__(WINDOWS_Y))

#define DRAWING_AREA_X	-0.5
#define DRAWING_AREA_Y	-0.5
#define DRAWING_AREA_W	(2 * __ABS__(DRAWING_AREA_X))
#define DRAWING_AREA_H	(2 * __ABS__(DRAWING_AREA_Y))

#define BUFSIZE 512

#define BLU_POINTS_SIZE		5.0
#define RED_POINTS_SIZE		10.0
#define LINE_WITH			2.0

arnGLMultipleArray::arnGLMultipleArray(arnGLArrayPaintingMode_t md, QWidget* parent, const char * name, const QGLWidget* shareWidget, Qt::WFlags f)
     : QGLWidget(parent, name,  shareWidget, f)
{
	pDataVector = new arnGLMatrix(5,5,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLMatrix(5,5,0);
	if (!pVisVector) arnCriticalExit();
	isRowVisible = new bool[5];
	if (!isRowVisible) arnCriticalExit();
	isColVisible = new bool[5];
	if (!isColVisible) arnCriticalExit();
	mde = md;
	for (int rndx = 0; rndx < 5; rndx++) isRowVisible[rndx] = false;
	for (int cndx = 0; cndx < 5; cndx++) isColVisible[cndx] = false;
	pColColor = new QColor[5];
	if (!pColColor) arnCriticalExit();
	pRowColor = new QColor[5];
	if (!pRowColor) arnCriticalExit();
	initDefaultParamsForVis();
}

arnGLMultipleArray:: arnGLMultipleArray (const QGLFormat& format, arnGLArrayPaintingMode_t md,QWidget* parent, const char* name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(format, parent, name,  shareWidget, f)
{
	pDataVector = new arnGLMatrix(5,5,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLMatrix(5,5,0);
	if (!pVisVector) arnCriticalExit();
	isRowVisible = new bool[5];
	if (!isRowVisible) arnCriticalExit();
	isColVisible = new bool[5];
	if (!isColVisible) arnCriticalExit();
	mde = md;
	for (int rndx = 0; rndx < 5; rndx++) isRowVisible[rndx] = false;
	for (int cndx = 0; cndx < 5; cndx++) isColVisible[cndx] = false;
	pColColor = new QColor[5];
	if (!pColColor) arnCriticalExit();
	pRowColor = new QColor[5];
	if (!pRowColor) arnCriticalExit();
	initDefaultParamsForVis();
}

arnGLMultipleArray::arnGLMultipleArray(int Rows, int Cols, arnGLArrayPaintingMode_t md, QWidget* parent, const char * name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(parent, name,  shareWidget, f)
{
	pDataVector = new arnGLMatrix(Rows,Cols,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLMatrix(Rows,Cols,0);
	if (!pVisVector) arnCriticalExit();
	isRowVisible = new bool[Rows];
	if (!isRowVisible) arnCriticalExit();
	isColVisible = new bool[Cols];
	if (!isColVisible) arnCriticalExit();
	mde = md;
	for (int rndx = 0; rndx < Rows; rndx++) isRowVisible[rndx] = false;
	for (int cndx = 0; cndx < Cols; cndx++) isColVisible[cndx] = false;
	pColColor = new QColor[Cols];
	if (!pColColor) arnCriticalExit();
	pRowColor = new QColor[Rows];
	if (!pRowColor) arnCriticalExit();
	initDefaultParamsForVis();
}

arnGLMultipleArray:: arnGLMultipleArray (const QGLFormat& format, int Rows, int Cols, arnGLArrayPaintingMode_t md, QWidget* parent, const char* name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(format, parent, name,  shareWidget, f)
{
	pDataVector = new arnGLMatrix(Rows,Cols,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLMatrix(Rows,Cols,0);
	if (!pVisVector) arnCriticalExit();
	isRowVisible = new bool[Rows];
	if (!isRowVisible) arnCriticalExit();
	isColVisible = new bool[Cols];
	if (!isColVisible) arnCriticalExit();
	mde = md;
	for (int rndx = 0; rndx < Rows; rndx++) isRowVisible[rndx] = false;
	for (int cndx = 0; cndx < Cols; cndx++) isColVisible[cndx] = false;
	pColColor = new QColor[Cols];
	if (!pColColor) arnCriticalExit();
	pRowColor = new QColor[Rows];
	if (!pRowColor) arnCriticalExit();
	initDefaultParamsForVis();
}


arnGLMultipleArray::~arnGLMultipleArray(void)
{
	makeCurrent();
	glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
	if (isRowVisible) {delete [] isRowVisible; isRowVisible = 0;}
	if (isColVisible) {delete [] isColVisible; isColVisible = 0;}
/*	if (pColColor) {delete [] pColColor; pColColor = 0;} qt libera bene
	if (pRowColor) {delete [] pRowColor; pRowColor = 0;}*/
	if (pDataVector) {delete pDataVector; pDataVector = 0;}
	if (pVisVector) {delete pVisVector; pVisVector = 0;}
}

GLuint arnGLMultipleArray::makeObject(void)
{
	GLuint list = 0;
	// inizializzazione del  VisVector
	switch (mde) {
		case arn_glAPM_VERTICAL_LINES: // per un multiple array questa rappresentazione non ha senso
			break;
		case arn_glAPM_MASHED_LINES: {
			GLfloat minRw,maxRw,minCl,maxCl,minTb,maxTb;
			GLfloat x0,z0;
			GLfloat minX,maxX,minZ,maxZ;
			(minRow.set == true) ? minRw = minRow.value  : minRw = pDataVector->minRow();
			(maxRow.set == true) ? maxRw = maxRow.value  : maxRw = pDataVector->maxRow();
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataVector->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataVector->maxCol();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataVector->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataVector->maxTable();
			if (showRows) {
				minX = minCl;
				maxX = maxCl;
				}
			else if (showCols) {
				minX = minRw;
				maxX = maxRw;
				}
			else return list;
			minZ = minTb;
			maxZ = maxTb;
			x0 = (-minX / (maxX - minX)) - 0.5;
			z0 = (-minZ / (maxZ - minZ)) - 0.5;
/*			arnDebug("%s = %f\n","minRw", minRw);
			arnDebug("%s = %f\n","maxRw", maxRw);
			arnDebug("%s = %f\n","minCl", minCl);
			arnDebug("%s = %f\n","maxCl", maxCl);
			arnDebug("%s = %f\n","minTb", minTb);
			arnDebug("%s = %f\n","maxTb", maxTb);
			arnDebug("%s = %f\n","minX", minX);
			arnDebug("%s = %f\n","maxX", maxX);
			arnDebug("%s = %f\n","minZ", minZ);
			arnDebug("%s = %f\n","maxZ", maxZ);
			arnDebug("%s = %f\n","x0", x0);
			arnDebug("%s = %f\n","z0", z0);*/
/*			arnDebug("pDataVector->nRows %d\n",pDataVector->nRows);
			arnDebug("pDataVector->nCols %d\n",pDataVector->nCols);*/
			for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
				if ((maxRw- minRw) == 0)   pVisVector->pRows[rndx] = 1;
				else pVisVector->pRows[rndx] = (1.0 * ( pDataVector->pRows[rndx]  - minRw) / (maxRw- minRw)) - 0.5;
//				arnDebug("%s[%d] = %f\n","pVisVector->pRows",rndx, pVisVector->pRows[rndx] );
				}
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisVector->pCols[cndx] = 1;
				else pVisVector->pCols[cndx] = (1.0 * ( pDataVector->pCols[cndx]  - minCl) / (maxCl- minCl)) - 0.5;
//				arnDebug("%s[%d] = %f\n","pVisVector->pCols",cndx, pVisVector->pCols[cndx] );
				}
			for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
				for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
					if ((maxTb- minTb) == 0) pVisVector->Table[rndx][cndx] = 1;
					else pVisVector->Table[rndx][cndx] =  (1.0 * ( pDataVector->Table[rndx][cndx]  - minTb) / (maxTb- minTb)) - 0.5;
//					arnDebug("%s[%d]  = %f\n","pVisVector->Table",cndx, pVisVector->Table[cndx]  );
					}
				}
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glLineWidth( LINE_WITH );
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			if (showRows) {
				glBegin(GL_LINES);
				glVertex2f(pVisVector->pCols[0], z0);
				glVertex2f(pVisVector->pCols[pVisVector->nCols - 1], z0);
				glEnd();
				}
			else if (showCols) {
				glBegin(GL_LINES);
				glVertex2f(pVisVector->pRows[0], z0);
				glVertex2f(pVisVector->pRows[pVisVector->nRows - 1], z0);
				glEnd();
				}
			else {;}
			glBegin(GL_LINES);
			glVertex2f(x0,__MIN__(z0,pVisVector->minTable()));
			glVertex2f(x0,__MAX__(z0,pVisVector->maxTable()));
			glEnd();
			if (showRows) {
				for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
					if (isRowVisible[rndx]) {
						setRowColor(true,rndx);
						glBegin(GL_LINE_STRIP);
						for (int cndx = 1; cndx < pVisVector->nCols; cndx++)  {
							glVertex2f(pVisVector->pCols[cndx - 1],pVisVector->Table[rndx][cndx - 1]);
							glVertex2f(pVisVector->pCols[cndx],pVisVector->Table[rndx][cndx]);
							}
						glEnd();
						}
					}
				}
			else if (showCols) {
				for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
					if (isColVisible[cndx]) {
						setRowColor(false,cndx);
						glBegin(GL_LINE_STRIP);
						for (int rndx = 1; rndx < pVisVector->nRows; rndx++)  {
							glVertex2f(pVisVector->pRows[rndx - 1],pVisVector->Table[rndx - 1][cndx]);
							glVertex2f(pVisVector->pRows[rndx],pVisVector->Table[rndx][cndx]);
							}
						glEnd();
						}
					}
				}
			else {;}
			glPointSize( BLU_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::blue );		      // Shorthand for glColor3f or glIndex
			if (showRows) {
				for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
					if (isRowVisible[rndx]) {
						for (int cndx = 0; cndx < pVisVector->nCols; cndx++)  {
							glBegin(GL_POINTS);
								glVertex2f(pVisVector->pCols[cndx],pVisVector->Table[rndx][cndx]);
							glEnd();
							}
						}
					}
				}
			else if (showCols) {
				for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
					if (isColVisible[cndx]) {
						for (int rndx = 0; rndx < pVisVector->nRows; rndx++)  {
							glBegin(GL_POINTS);
								glVertex2f(pVisVector->pRows[rndx],pVisVector->Table[rndx][cndx]);
							glEnd();
							}
						}
					}
				}
			else {;}
			glPointSize( 1.0 );
			glDisable(GL_POINT_SMOOTH);
			glEndList();
			}
			break;
		case arn_glAPM_NONE:
		default:
		list = 0;
		break;
		}
	return list;
}

GLuint arnGLMultipleArray::makeSelection(int srow, int scol, int erow, int ecol)
{
    GLuint list = 0;
    int tmp;
	// inizializzazione della  VisTable
	if (srow > erow) {tmp = srow; srow = erow; erow = tmp;}
	if (scol > ecol) {tmp = scol; scol = ecol; ecol = tmp;}
    switch (mde) {
        case arn_glAPM_VERTICAL_LINES:// questa modalita' non ha senso in questo componente
            break;
        case arn_glAPM_MASHED_LINES: {
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glPointSize( RED_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			if (showRows) {
				for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
					if (((srow <= rndx) && (rndx <= erow)) && isRowVisible[rndx]) {
						for (int cndx = 0; cndx < pVisVector->nCols; cndx++)  {
							if ((scol <= cndx) && (cndx <= ecol)) {
								glBegin(GL_POINTS);
									glVertex2f(pVisVector->pCols[cndx],pVisVector->Table[rndx][cndx]);
								glEnd();
								}
							}
						}
					}
				}
			else if (showCols) {
				for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
					if (((scol <= cndx) && (cndx <= ecol)) && isColVisible[cndx]) {
						for (int rndx = 0; rndx < pVisVector->nRows; rndx++)  {
							if ((srow <= rndx) && (rndx <= erow)) {
								glBegin(GL_POINTS);
									glVertex2f(pVisVector->pRows[rndx],pVisVector->Table[rndx][cndx]);
								glEnd();
								}
							}
						}
					}
				}
			else {;}
			glPointSize( 1.0 );
			glDisable(GL_POINT_SMOOTH);
			glEndList();
            }
            break;
        case arn_glAPM_NONE:
        default:
            list = 0;
            break;
        }
    return list;
}

GLint arnGLMultipleArray::makeObjectforselection(GLint x, GLint y,int* row, int* col)
{
	GLuint hits = 0;
	GLint viewport[4];
	GLuint selectBuf[BUFSIZE];
	// inizializzazione del  VisVector
	switch (mde) {
		case arn_glAPM_VERTICAL_LINES: // non ha senso questa modalita' nel multiple array
			break;
		case arn_glAPM_MASHED_LINES: {
			GLfloat minRw,maxRw,minCl,maxCl,minTb,maxTb;
			GLfloat x0,z0;
			GLfloat minX,maxX,minZ,maxZ;
			(minRow.set == true) ? minRw = minRow.value  : minRw = pDataVector->minRow();
			(maxRow.set == true) ? maxRw = maxRow.value  : maxRw = pDataVector->maxRow();
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataVector->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataVector->maxCol();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataVector->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataVector->maxTable();
			if (showRows) {
				minX = minCl;
				maxX = maxCl;
				}
			else if (showCols) {
				minX = minRw;
				maxX = maxRw;
				}
			else  {return (hits = (GLuint)-1);}
			minZ = minTb;
			maxZ = maxTb;
			x0 = (-minX / (maxX - minX)) - 0.5;
			z0 = (-minZ / (maxZ - minZ)) - 0.5;
/*			arnDebug("%s = %f\n","minRw", minRw);
			arnDebug("%s = %f\n","maxRw", maxRw);
			arnDebug("%s = %f\n","minCl", minCl);
			arnDebug("%s = %f\n","maxCl", maxCl);
			arnDebug("%s = %f\n","minTb", minTb);
			arnDebug("%s = %f\n","maxTb", maxTb);
			arnDebug("%s = %f\n","minX", minX);
			arnDebug("%s = %f\n","maxX", maxX);
			arnDebug("%s = %f\n","minZ", minZ);
			arnDebug("%s = %f\n","maxZ", maxZ);
			arnDebug("%s = %f\n","x0", x0);
			arnDebug("%s = %f\n","z0", z0);*/
/*			arnDebug("pDataVector->nRows %d\n",pDataVector->nRows);
			arnDebug("pDataVector->nCols %d\n",pDataVector->nCols);*/
			for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
				if ((maxRw- minRw) == 0)   pVisVector->pRows[rndx] = 1;
				else pVisVector->pRows[rndx] = (1.0 * ( pDataVector->pRows[rndx]  - minRw) / (maxRw- minRw)) - 0.5;
//				arnDebug("%s[%d] = %f\n","pVisVector->pRows",rndx, pVisVector->pRows[rndx] );
				}
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisVector->pCols[cndx] = 1;
				else pVisVector->pCols[cndx] = (1.0 * ( pDataVector->pCols[cndx]  - minCl) / (maxCl- minCl)) - 0.5;
//				arnDebug("%s[%d] = %f\n","pVisVector->pCols",cndx, pVisVector->pCols[cndx] );
				}
			for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
				for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
					if ((maxTb- minTb) == 0) pVisVector->Table[rndx][cndx] = 1;
					else pVisVector->Table[rndx][cndx] =  (1.0 * ( pDataVector->Table[rndx][cndx]  - minTb) / (maxTb- minTb)) - 0.5;
//					arnDebug("%s[%d]  = %f\n","pVisVector->Table",cndx, pVisVector->Table[cndx]  );
					}
				}
			glGetIntegerv (GL_VIEWPORT, viewport);
			glSelectBuffer (BUFSIZE, selectBuf);
			(void) glRenderMode (GL_SELECT);
			glInitNames();
			glPushName((GLuint)-1);
			glMatrixMode (GL_PROJECTION);
			glPushMatrix ();
				glLoadIdentity ();
				/* create 5x5 pixel picking region near cursor location */
				gluPickMatrix ((GLdouble) x, (GLdouble) (viewport[3] - y), 5.0, 5.0, viewport);
				glOrtho(WINDOWS_X, WINDOWS_Y, WINDOWS_X, WINDOWS_Y, -1, 1);// la stessa dlla resize
				glLineWidth( LINE_WITH );
				qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
				if (showRows) {
					glLoadName((GLuint)-1); // nome asse x
					glBegin(GL_LINES);
					glVertex2f(pVisVector->pCols[0], z0);
					glVertex2f(pVisVector->pCols[pVisVector->nCols - 1], z0);
					glEnd();
					}
				else if (showCols) {
					glLoadName((GLuint)-1); // nome asse x
					glBegin(GL_LINES);
					glVertex2f(pVisVector->pRows[0], z0);
					glVertex2f(pVisVector->pRows[pVisVector->nRows - 1], z0);
					glEnd();
					}
				else {;}
				glLoadName((GLuint)-2); // nome asse y
				glBegin(GL_LINES);
				glVertex2f(x0,__MIN__(z0,pVisVector->minTable()));
				glVertex2f(x0,__MAX__(z0,pVisVector->maxTable()));
				glEnd();
				if (showRows) {
					for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
						if (isRowVisible[rndx]) {
							setRowColor(true,rndx);
							glBegin(GL_LINE_STRIP);
							for (int cndx = 1; cndx < pVisVector->nCols; cndx++)  {
								glVertex2f(pVisVector->pCols[cndx - 1],pVisVector->Table[rndx][cndx - 1]);
								glVertex2f(pVisVector->pCols[cndx],pVisVector->Table[rndx][cndx]);
								}
							glEnd();
							}
						}
					}
				else if (showCols) {
					for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
						if (isColVisible[cndx]) {
							setRowColor(false,cndx);
							glBegin(GL_LINE_STRIP);
							for (int rndx = 1; rndx < pVisVector->nRows; rndx++)  {
								glVertex2f(pVisVector->pRows[rndx - 1],pVisVector->Table[rndx - 1][cndx]);
								glVertex2f(pVisVector->pRows[rndx],pVisVector->Table[rndx][cndx]);
								}
							glEnd();
							}
						}
					}
				else {;}
				glPointSize( BLU_POINTS_SIZE );
				glEnable(GL_POINT_SMOOTH);
				qglColor( Qt::blue );		      // Shorthand for glColor3f or glIndex
				if (showRows) {
					for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
						if (isRowVisible[rndx]) {
							for (int cndx = 0; cndx < pVisVector->nCols; cndx++)  {
								glLoadName((GLuint)(cndx << 16) + rndx); // punto disegnato
								glBegin(GL_POINTS);
									glVertex2f(pVisVector->pCols[cndx],pVisVector->Table[rndx][cndx]);
								glEnd();
								}
							}
						}
					}
				else if (showCols) {
					for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
						if (isColVisible[cndx]) {
							for (int rndx = 0; rndx < pVisVector->nRows; rndx++)  {
								glLoadName((GLuint)(cndx << 16) + rndx); // punto disegnato
								glBegin(GL_POINTS);
									glVertex2f(pVisVector->pRows[rndx],pVisVector->Table[rndx][cndx]);
								glEnd();
								}
							}
						}
					}
				else {;}
				glPointSize( 1.0 );
				glDisable(GL_POINT_SMOOTH);
			glPopMatrix ();
			glFlush ();
			hits = glRenderMode (GL_RENDER);
			processHits (hits, selectBuf,row,col);
			glMatrixMode( GL_MODELVIEW );
			}
			break;
		case arn_glAPM_NONE:
		default:
			hits = (GLuint)-1;
			break;
		}
	return hits;
}

void arnGLMultipleArray::processHits (GLint hits, GLuint buffer[],int* row,int* col)
{
	unsigned int i,j;
	*row = -1;
	*col = -1;
	switch (mde) {
		case arn_glAPM_VERTICAL_LINES: // questomodo non ha senso in questo componente
			break;
		case arn_glAPM_MASHED_LINES: {
			GLuint names, *ptr;
			ptr = (GLuint *) buffer;
			for (i = 0; i < (unsigned int)hits; i++) {
				names = *ptr; ptr++;
				for (j = 0; j < names; j++) {
					/*printf ("z1 is %u;", *ptr);*/ ptr++;
					/*printf (" z2 is %u\n", *ptr);*/ ptr++;
					if ((*ptr) == (GLuint)-1); // asse x
					else if ((*ptr) == (GLuint)-2); // asse y 
					else {
						*row = (int)(*ptr & 0x0000ffff);
						*col = ((int)(*ptr) >> 16);
						}
					ptr++;
					}
				}
			}
			break;
		case arn_glAPM_NONE:
		default:
			*row = -1;
			*col = -1;
			break;
		}
}

void arnGLMultipleArray::initializeGL()
{
    qglClearColor( Qt::white ); // Let OpenGL clear to black
    object = makeObject(); // Generate an OpenGL display list
    glShadeModel( GL_FLAT );
}


void arnGLMultipleArray::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();

    glOrtho(WINDOWS_X, WINDOWS_Y, WINDOWS_X, WINDOWS_Y, -1, 1);

    glMatrixMode( GL_MODELVIEW );
}

void arnGLMultipleArray::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glLoadIdentity();
//    glTranslatef(0.0, 0.0, -1.0 );
//    glScalef( scle, scle, scle );

//    glRotatef( xRot, 1.0, 0.0, 0.0 );
//    glRotatef( yRot, 0.0, 1.0, 0.0 );
//    glRotatef( zRot, 0.0, 0.0, 1.0 );

    drawText();
    drawLabels();
    glCallList( object );
    if (selection) {glCallList( selection );}
}



void arnGLMultipleArray::setColValue(int col, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (col < pDataVector->nCols) {
        if (ok) pDataVector->pCols[col] = vl;
		return;
        }
	arnCriticalExit();
}

void arnGLMultipleArray::setColValue(int col, double val)
{
    GLfloat vl = (GLfloat) val;
    if (col < pDataVector->nCols) {
		pDataVector->pCols[col] = vl;
		return;
		}
	arnCriticalExit();
}

void arnGLMultipleArray::setRowValue(int row, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (row < pDataVector->nRows) {
        if (ok) pDataVector->pRows[row] = vl;
		return;
        }
	arnCriticalExit();
}

void arnGLMultipleArray::setRowValue(int row, double val)
{
    GLfloat vl = (GLfloat) val;
    if (row < pDataVector->nRows) {
		pDataVector->pRows[row] = vl;
		return;
		}
	arnCriticalExit();
}


void arnGLMultipleArray::setValue(int row, int col, QString& val)
{
	bool ok;
	GLfloat vl = (GLfloat) val.toDouble(&ok);
	if ((row < pDataVector->nRows) && (col < pDataVector->nCols)) {
		if (ok) pDataVector->Table[row][col] = vl;
		//arnDebug("row %d, col %d\n",row,col);
		}
}

void arnGLMultipleArray::setValue(int row, int col, double val)
{
	GLfloat vl = (GLfloat) val;
	if ((row < pDataVector->nRows) && (col < pDataVector->nCols)) {
		pDataVector->Table[row][col] = vl;
		//arnDebug("row %d, col %d\n",row,col);
		}
}

double arnGLMultipleArray::value(int row, int col)
{
	if ((row < pDataVector->nRows) && (col < pDataVector->nCols))
		return (double)(pDataVector->Table[row][col]);
	arnCriticalExit();
}

QString arnGLMultipleArray::text(int row, int col)
{
	QString vl("");
	if ((row < pDataVector->nRows) && col < (pDataVector->nCols)) {
		vl.setNum((double)(pDataVector->Table[row][col]));
		return vl;
		}
	arnCriticalExit();
}

double arnGLMultipleArray::colValue(int col)
{
	if (col < pDataVector->nCols) {
		return pDataVector->pCols[col];
		}
	arnCriticalExit();
}

QString arnGLMultipleArray::colText(int col)
{
	QString vl("");
	if (col < pDataVector->nCols) {
	vl.setNum((double)(pDataVector->pCols[col]));
	return vl;
	}
	arnCriticalExit();
}

double arnGLMultipleArray::rowValue(int row)
{
	if (row < pDataVector->nRows) {
		return pDataVector->pRows[row];
		}
	arnCriticalExit();
}

QString arnGLMultipleArray::rowText(int row)
{
	QString vl("");
	if (row < pDataVector->nRows) {
	vl.setNum((double)(pDataVector->pRows[row]));
	return vl;
	}
	arnCriticalExit();
}

//void arnGLTable::setXRotation( int degrees )
//{
//    xRot = (GLfloat)(((int)sxRot + degrees) % 360);
//    updateGL();
//}

//void arnGLTable::setYRotation( int degrees )
//{
//    yRot = (GLfloat)(((int)syRot + degrees) % 360);
//    updateGL();
//}

//void arnGLTable::setZRotation( int degrees )
//{
//    zRot = (GLfloat)(((int)szRot + degrees) % 360);
//    updateGL();
//}



void arnGLMultipleArray::initDefaultParamsForVis(void)
{
    //mde = arn_glTPM_VERTICAL_LINES;

//    sxRot = 290.0; // default object rotation -  XAxis
//    xRot = sxRot;
//    syRot = 0.0; // default object rotation -  YAxis
//    yRot = syRot;
//    szRot = -35.0;  // default object rotation -  ZAxis
//    zRot = szRot;
	
	sSelRow = eSelRow = sSelCol = eSelCol = -1;
	showRows = false;
	showCols = false;

    scle = 1.00; // default object scale

    object = 0;

	minRow.set = false;
    minRow.value = 0;
	maxRow.set = false;
    maxRow.value = 0;
	minCol.set = false;
    minCol.value = 0;
    maxCol.set = false;
    maxCol.value = 0;
    minTab.set = false;
    minTab.value = 0;
    maxTab.set = false;
    maxTab.value = 0;

    labels.xAxis = "X";
    labels.yAxis = "Y";
    labels.caption = "2DArrayViewer";
    sSelRow = eSelRow = -1;
    selection = 0;
	for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
		QColor q;
		q.setRgb(0,255 - (cndx * 15) % 255, (cndx * 15) % 255);
		pColColor[cndx] = q;
		}
	for (int rndx = 0; rndx < pDataVector->nRows; rndx++) {
		QColor q;
		q.setRgb(0, 255 - (rndx * 15) % 255, 255 - (rndx * 15) % 255);
		pRowColor[rndx] = q;
		}
}




void arnGLMultipleArray::setColMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minCol.value = vl;
        minCol.set = true;
        }
}

void arnGLMultipleArray::setColMinScale(double val)
{
    minCol.value = (GLfloat)val;
    minCol.set = true;
}

void arnGLMultipleArray::setColMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxCol.value = vl;
        maxCol.set = true;
        }
}

void arnGLMultipleArray::setColMaxScale(double val)
{
    maxCol.value = (GLfloat)val;
    maxCol.set = true;
}

void arnGLMultipleArray::setRowMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minRow.value = vl;
        minRow.set = true;
        }
}

void arnGLMultipleArray::setRowMinScale(double val)
{
    minRow.value = (GLfloat)val;
    minRow.set = true;
}

void arnGLMultipleArray::setRowMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxRow.value = vl;
        maxRow.set = true;
        }
}

void arnGLMultipleArray::setRowMaxScale(double val)
{
    maxRow.value = (GLfloat)val;
    maxRow.set = true;
}

void arnGLMultipleArray::setTableMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minTab.value = vl;
        minTab.set = true;
        }
}

void arnGLMultipleArray::setTableMinScale(double val)
{
    minTab.value = (GLfloat)val;
    minTab.set = true;
}

void arnGLMultipleArray::setTableMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxTab.value = vl;
        maxTab.set = true;
        }
}

void arnGLMultipleArray::setTableMaxScale(double val)
{
    maxTab.value = (GLfloat)val;
    maxTab.set = true;
}

void arnGLMultipleArray::drawText(void)
{
    glPushAttrib( GL_LIGHTING_BIT | GL_TEXTURE_BIT );
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    qglColor( QColor("skyblue") );
    QString str( labels.caption);
    QFontMetrics fm( QApplication::font() );
    QFont f = QApplication::font();
    f.setStyleStrategy(QFont::PreferBitmap);
    renderText( (width() - fm.width( str )) / 2, 15, str,f );
    qglColor( QColor("skyblue") );
    str.sprintf( "minY: %g - maxY: %g",minTab.value,maxTab.value);
    renderText( (width() - fm.width( str )) / 2, height() - 15, str, f );
    glPopAttrib();
}

void arnGLMultipleArray::drawLabels(void)
{
    glPushAttrib( GL_LIGHTING_BIT | GL_TEXTURE_BIT );
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    qglColor( Qt::green );
    QFont f = QApplication::font();
    f.setStyleStrategy(QFont::PreferBitmap);
    renderText( pVisVector->pCols[pVisVector->nCols - 1], pVisVector->pCols[0] - 0.05, 0.0, labels.xAxis, f);
    renderText( pVisVector->pCols[0] - 0.05, pVisVector->pCols[pVisVector->nCols - 1], 0.0, labels.yAxis, f);
    glPopAttrib();
}

void arnGLMultipleArray::setMode (arnGLArrayPaintingMode_t md)
{
    mde = md;

    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
    initializeGL();
}

void arnGLMultipleArray::invalidate(void)
{
    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
    initializeGL();
}

void arnGLMultipleArray::mousePressEvent ( QMouseEvent *e )
{
	int xP,yP;
	
	if (e->button() == Qt::RightButton) return QGLWidget::mousePressEvent(e);
	setFocus();
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&sSelRow,&sSelCol);
	updateGL();
//	eR = sR;
//	emit selectionChanged(sR,eR);
}

void arnGLMultipleArray::mouseMoveEvent ( QMouseEvent *e )
{
	int xP,yP;
	int selRow,selCol = -1;
	if (e->button() == Qt::RightButton) return QGLWidget::mouseMoveEvent(e);
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&selRow, &selCol);
	if (((selRow != -1) && (selCol != -1)) &&
		((sSelRow != -1) && (sSelCol != -1)) &&
/*		((selRow != sSelRow) && (selCol != sSelCol)) &&*/
		((sSelRow < pDataVector->nRows) && (sSelCol < pDataVector->nCols)) &&
		((selRow < pDataVector->nRows) && (selCol < pDataVector->nCols))
		) {
/*		arnDebug("selRow % d, selCol %d\n",selRow,selCol);*/
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		selection = makeSelection(sSelRow,sSelCol,selRow,selCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,selRow,selCol);
		updateGL();
		return;
		}
	else return QGLWidget::mousePressEvent(e);
}

void arnGLMultipleArray::mouseReleaseEvent ( QMouseEvent *e )
{
	int xP,yP;
	if (e->button() == Qt::RightButton) return QGLWidget::mouseReleaseEvent(e);
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&eSelRow,&eSelCol);
/*	arnDebug("eSelRow % d, eSelCol %d\n",eSelRow,eSelCol);*/
	if (((eSelRow != -1) && (eSelCol != -1)) &&
		((sSelRow != -1) && (sSelCol != -1)) &&
		((sSelRow < pDataVector->nRows) && (sSelCol < pDataVector->nCols)) &&
		((eSelRow < pDataVector->nRows) && (eSelCol < pDataVector->nCols))
		) {
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		}
	else return QGLWidget::mouseReleaseEvent(e);
}

void arnGLMultipleArray::keyReleaseEvent (  QKeyEvent *e )
{
	if (e->key() == Qt::Key_Left) {  // freccia sinistra
		e->accept();
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		if (showRows) {
			((sSelCol -= 1) < 0) ? sSelCol = 0 : sSelCol = sSelCol;
			eSelCol = sSelCol;
			}
		else if (showCols) {
			((sSelRow -= 1) < 0) ? sSelRow = 0 : sSelRow = sSelRow;
			eSelRow = sSelRow;
			}
		selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		}
	else if (e->key() == Qt::Key_Up) { // freccia alta
		e->accept();
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		if (showRows) {
			((sSelRow += 1) > (pDataVector->nRows -1)) ? sSelRow = (pDataVector->nRows - 1) : sSelRow = sSelRow;
			if (!isRowVisible[sSelRow]) {sSelRow -= 1; return;}
			eSelRow = sSelRow;
			}
		else if (showCols) {
			((sSelCol += 1) > (pDataVector->nCols -1)) ? sSelCol = (pDataVector->nCols - 1) : sSelCol = sSelCol;
			if (!isColVisible[sSelCol]) {sSelCol -= 1; return;}
			eSelCol = sSelCol;
			}
		selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		}
	else if (e->key() == Qt::Key_Right) { // freccia destra
		e->accept();
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		if (showRows) {
			((sSelCol += 1) > (pDataVector->nCols -1)) ? sSelCol = (pDataVector->nCols - 1) : sSelCol = sSelCol;
			eSelCol = sSelCol;
			}
		else if (showCols) {
			((sSelRow += 1) > (pDataVector->nRows -1)) ? sSelRow = (pDataVector->nRows - 1) : sSelRow = sSelRow;
			eSelRow = sSelRow;
			}
		selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		}
	else if (e->key() == Qt::Key_Down) { // freccia bassa
		e->accept();
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		if (showRows) {
			((sSelRow -= 1) < 0) ? sSelRow = 0 : sSelRow = sSelRow;
			if (!isRowVisible[sSelRow]) {sSelRow += 1; return;}
			eSelRow = sSelRow;
			}
		else if (showCols) {
			((sSelCol -= 1) < 0) ? sSelCol = 0 : sSelCol = sSelCol;
			if (!isColVisible[sSelCol]) {sSelCol += 1; return;}
			eSelCol = sSelCol;
			}
		selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
		updateGL();
		}
	else {
		e->ignore();
		QGLWidget::keyReleaseEvent(e);
		}
}

void arnGLMultipleArray::setRowColor(bool RowNotCol,int indx) {
	if (RowNotCol) { // righe
		qglColor(pRowColor[indx]); // Shorthand for glColor3f or glIndex
		}
	else { // colonne
		qglColor(pColColor[indx]); // Shorthand for glColor3f or glIndex
		}
	}

void arnGLMultipleArray::setColVisible(int col, bool v)
{
	if (col >=0 && col < pDataVector->nCols) isColVisible[col] = v;
}

void arnGLMultipleArray::setRowVisible(int row, bool v)
{
	if (row >= 0 && row < pDataVector->nRows) isRowVisible[row] = v;
}

void arnGLMultipleArray::HideAllRows(void)
{
	for (int rndx = 0; rndx < pDataVector->nRows; rndx++)
		isRowVisible[rndx] = false;
}

void arnGLMultipleArray::HideAllCols(void)
{
	for (int cndx = 0; cndx < pDataVector->nCols; cndx++)
		isColVisible[cndx] = false;
}

void arnGLMultipleArray::ShowAllRows(void)
{
	for (int rndx = 0; rndx < pDataVector->nRows; rndx++)
		isRowVisible[rndx] = true;
}

void arnGLMultipleArray::ShowAllCols(void)
{
	for (int cndx = 0; cndx < pDataVector->nCols; cndx++)
		isColVisible[cndx] = true;
}


/*double arnGLMultipleArray::ColMinScale(void)
{
	GLfloat lmx = pDataVector[0]->minCol();
	for (int cIndx = 1; cIndx < numRows; cIndx++) {
		if (pDataVector[cIndx]->minCol() > lmx) lmx = pDataVector[cIndx]->minCol();
		}
	return lmx;
}
*/
// double arnGLMultipleArray::ColMaxScale(void)
// {
// 	GLfloat lmx = pDataVector[0]->maxCol();
// 	for (int cIndx = 1; cIndx < numRows; cIndx++) {
// 		if (pDataVector[cIndx]->maxCol() > lmx) lmx = pDataVector[cIndx]->maxCol();
// 		}
// 	return lmx;
// }
// 
// double arnGLMultipleArray::TableMinScale(void)
// {
// 	GLfloat lmx = pDataVector[0]->minTable();
// 	for (int cIndx = 1; cIndx < numRows; cIndx++) {
// 		if (pDataVector[cIndx]->minTable() > lmx) lmx = pDataVector[cIndx]->minTable();
// 		}
// 	return lmx;
// }
// 
// double arnGLMultipleArray::TableMaxScale(void)
// {
// 	GLfloat lmx = pDataVector[0]->maxTable();
// 	for (int cIndx = 1; cIndx < numRows; cIndx++) {
// 		if (pDataVector[cIndx]->maxTable() > lmx) lmx = pDataVector[cIndx]->maxTable();
// 		}
// 	return lmx;
// }

//QFont f = QApplication::font();
// f.setStyleStrategy(QFont::PreferBitmap);
// renderText(x, y, "Text", f);

