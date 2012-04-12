/***************************************************************************
                          arnGLTable.cpp  -  description
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
#include <QMouseEvent>
#include "arnGLTable.h"

#define BUFSIZE 512

#define RED_POINTS_SIZE		5.0
#define LINE_WIDTH			1.2

arnGLTable::arnGLTable(arnGLTablePaintingMode_t md, QWidget* parent, const char * name, const QGLWidget* shareWidget, Qt::WFlags f)
     : QGLWidget(parent, name,  shareWidget, f)
{
    pDataMatrix = new arnGLMatrix(5,5,0);
    if (!pDataMatrix) arnCriticalExit();
    pVisMatrix = new arnGLMatrix(5,5,0);
    if (!pVisMatrix) arnCriticalExit();
    mde = md;
	sSelRow = eSelRow = sSelCol = eSelCol = -1;
    initDefaultParamsForVis();
}

arnGLTable:: arnGLTable (const QGLFormat& format, arnGLTablePaintingMode_t md,QWidget* parent, const char* name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(format, parent, name,  shareWidget, f)
{
    pDataMatrix = new arnGLMatrix(5,5,0);
    if (!pDataMatrix) arnCriticalExit();
    pVisMatrix = new arnGLMatrix(5,5,0);
    if (!pVisMatrix) arnCriticalExit();
    mde = md;
	sSelRow = eSelRow = sSelCol = eSelCol = -1;
    initDefaultParamsForVis();
}

 arnGLTable::arnGLTable(int Rows, int Cols, arnGLTablePaintingMode_t md, QWidget* parent, const char * name, const QGLWidget* shareWidget, Qt::WFlags f)
     : QGLWidget(parent, name,  shareWidget, f)
{
    pDataMatrix = new arnGLMatrix(Rows,Cols,0);
    if (!pDataMatrix) arnCriticalExit();
    pVisMatrix = new arnGLMatrix(Rows,Cols,0);
    if (!pVisMatrix) arnCriticalExit();
    mde = md;
	sSelRow = eSelRow = sSelCol = eSelCol = -1;
    initDefaultParamsForVis();
}

arnGLTable:: arnGLTable (const QGLFormat& format,int Rows, int Cols, arnGLTablePaintingMode_t md, QWidget* parent, const char* name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(format, parent, name,  shareWidget, f)
{
    pDataMatrix = new arnGLMatrix(Rows,Cols,0);
    if (!pDataMatrix) arnCriticalExit();
    pVisMatrix = new arnGLMatrix(Rows,Cols,0);
    if (!pVisMatrix) arnCriticalExit();
    mde = md;
	sSelRow = eSelRow = sSelCol = eSelCol = -1;
    initDefaultParamsForVis();
}


arnGLTable::~arnGLTable(void)
{
    if (pDataMatrix) {delete pDataMatrix; pDataMatrix = 0;}
    if (pVisMatrix) {delete pVisMatrix; pVisMatrix = 0;}

    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
}

GLuint arnGLTable::makeObject(void)
{
    GLuint list = 0;

    // inizializzazione della  VisTable
        
    switch (mde) {
        case arn_glTPM_VERTICAL_LINES: {
            GLfloat minCl,maxCl,minRw,maxRw,minTb,maxTb;
            (minCol.set == true) ? minCl = minCol.value  : minCl = pDataMatrix->minCol();
            (maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataMatrix->maxCol();
            (minRow.set == true) ? minRw = minRow.value  : minRw = pDataMatrix->minRow();
            (maxRow.set == true) ? maxRw = maxRow.value  : maxRw = pDataMatrix->maxRow();
            (minTab.set == true) ? minTb = minTab.value  : minTb = pDataMatrix->minTable();
            (maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataMatrix->maxTable();
//            arnDebug("%s = %d\n","minCl", (int)minCl);
//            arnDebug("%s = %d\n","maxCl", (int)maxCl);
//            arnDebug("%s = %d\n","minRw", (int)minRw);
//            arnDebug("%s = %d\n","maxRw", (int)maxRw);
//            arnDebug("%s = %d\n","minTb", (int)minTb);
//            arnDebug("%s = %d\n","maxTb", (int)maxTb);
            for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)  {
                if ((maxRw - minRw) == 0)  pVisMatrix->pRows[rndx] = 1;
                else pVisMatrix->pRows[rndx] = (1.0 * ( pDataMatrix->pRows[rndx]  - minRw) / (maxRw - minRw)) - 0.5;
//                arnDebug("%s[%d] = %f\n","pVisMatrix->pRows",rndx, pVisMatrix->pRows[rndx] );
                }
            for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
                if ((maxCl- minCl) == 0)   pVisMatrix->pCols[cndx] = 1;
                else pVisMatrix->pCols[cndx] = (1.0 * ( pDataMatrix->pCols[cndx]  - minCl) / (maxCl- minCl))  - 0.5;
//                arnDebug("%s[%d] = %f\n","pVisMatrix->pCols",cndx, pVisMatrix->pCols[cndx] );
                }

            for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)
                for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
                    if ((maxTb- minTb) == 0) pVisMatrix->Table[rndx][cndx] = 1;
                    else pVisMatrix->Table[rndx][cndx] =  (1.0 * ( pDataMatrix->Table[rndx][cndx]  - minTb) / (maxTb- minTb));
//                    arnDebug("%s[%d][%d]  = %f\n","pVisMatrix->Table",rndx,cndx, pVisMatrix->Table[rndx][cndx]  );
                    }

            list = glGenLists( 1 );
            glNewList( list, GL_COMPILE );
            glLineWidth( LINE_WIDTH );
            qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
            glBegin(GL_LINES);
                glVertex3f(pVisMatrix->pCols[0] - 0.1, pVisMatrix->pRows[0] - 0.1,0.0);
                glVertex3f( pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[pVisMatrix->nRows - 1] +  0.1,0.0);
                glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1 ,0.0);
                glVertex3f( pVisMatrix->pCols[pVisMatrix->nCols - 1] + 0.1, pVisMatrix->pRows[0]  - 0.1,0.0);
                glVertex3f(pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[0] - 0.1, 0.0);
                glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1,1.0 + 0.1);
            glEnd();
            qglColor( Qt::black );		      // Shorthand for glColor3f or glIndex
            glBegin(GL_LINES);
                for (int i = 0; i < pVisMatrix->nRows; i++)
                    for (int j = 0; j <pVisMatrix->nCols; j++)  {
                        glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],0.0);
                        glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
                        }
            glEnd();
            glEndList();
            }
            break;
        case arn_glTPM_MASHED_SURFACE: {
            GLfloat minCl,maxCl,minRw,maxRw,minTb,maxTb;
            (minCol.set == true) ? minCl = minCol.value  : minCl = pDataMatrix->minCol();
            (maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataMatrix->maxCol();
            (minRow.set == true) ? minRw = minRow.value  : minRw = pDataMatrix->minRow();
            (maxRow.set == true) ? maxRw = maxRow.value  : maxRw = pDataMatrix->maxRow();
            (minTab.set == true) ? minTb = minTab.value  : minTb = pDataMatrix->minTable();
            (maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataMatrix->maxTable();
//            arnDebug("%s = %d\n","minCl", (int)minCl);
//            arnDebug("%s = %d\n","maxCl", (int)maxCl);
//            arnDebug("%s = %d\n","minRw", (int)minRw);
//            arnDebug("%s = %d\n","maxRw", (int)maxRw);
//            arnDebug("%s = %d\n","minTb", (int)minTb);
//            arnDebug("%s = %d\n","maxTb", (int)maxTb);
            for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)  {
                if ((maxRw - minRw) == 0)  pVisMatrix->pRows[rndx] = 1;
                else pVisMatrix->pRows[rndx] = (1.0 * ( pDataMatrix->pRows[rndx]  - minRw) / (maxRw - minRw)) - 0.5;
//                arnDebug("%s[%d] = %f\n","pVisMatrix->pRows",rndx, pVisMatrix->pRows[rndx] );
                }
            for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
                if ((maxCl- minCl) == 0)   pVisMatrix->pCols[cndx] = 1;
                else pVisMatrix->pCols[cndx] = (1.0 * ( pDataMatrix->pCols[cndx]  - minCl) / (maxCl- minCl))  - 0.5;
//                arnDebug("%s[%d] = %f\n","pVisMatrix->pCols",cndx, pVisMatrix->pCols[cndx] );
                }

            for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)
                for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
                    if ((maxTb- minTb) == 0) pVisMatrix->Table[rndx][cndx] = 1;
                    else pVisMatrix->Table[rndx][cndx] =  (1.0 * ( pDataMatrix->Table[rndx][cndx]  - minTb) / (maxTb- minTb));
//                    arnDebug("%s[%d][%d]  = %f\n","pVisMatrix->Table",rndx,cndx, pVisMatrix->Table[rndx][cndx]  );
                    }

            list = glGenLists( 1 );
            glNewList( list, GL_COMPILE );
            glLineWidth( LINE_WIDTH );
            qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
            glBegin(GL_LINES);
                glVertex3f(pVisMatrix->pCols[0] - 0.1, pVisMatrix->pRows[0] - 0.1,0.0);
                glVertex3f( pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[pVisMatrix->nRows - 1] +  0.1,0.0);
                glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1 ,0.0);
                glVertex3f( pVisMatrix->pCols[pVisMatrix->nCols - 1] + 0.1, pVisMatrix->pRows[0]  - 0.1,0.0);
                glVertex3f(pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[0] - 0.1, 0.0);
                glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1,1.0 + 0.1);
            glEnd();
            qglColor( Qt::black );      // Shorthand for glColor3f or glIndex
            for (int j = 0; j <pVisMatrix->nCols; j++) {  
                glBegin(GL_LINE_STRIP);
                for (int i =1; i < pVisMatrix->nRows; i++) {
                    glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i - 1],pVisMatrix->Table[i - 1][j]);
                    glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
                    }
                glEnd();
                }
            for (int i = 0; i <pVisMatrix->nRows; i++) {
                glBegin(GL_LINE_STRIP);
                for (int j =1; j < pVisMatrix->nCols; j++) {
                    glVertex3f(pVisMatrix->pCols[j - 1],pVisMatrix->pRows[i],pVisMatrix->Table[i ][j - 1]);
                    glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
                    }
                glEnd();
                }
            glEndList();
            }
            break;
        case arn_glTPM_NONE:
        default:
            list = 0;
            break;
        }
    return list;
}

GLuint arnGLTable::makeSelection(int srow, int scol,int erow, int ecol)
{
	GLuint list = 0;
	int tmp;
	// inizializzazione della  VisTable
	if (srow > erow) {tmp = srow; srow = erow; erow = tmp;}
	if (scol > ecol) {tmp = scol; scol = ecol; ecol = tmp;}
//arnDebug("srow = %d, scol = %d, erow = %d, ecol = %d\n",srow, scol, erow, ecol);
	switch (mde) {
		case arn_glTPM_VERTICAL_LINES: {
			// ToDo same as follow
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glPointSize( RED_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			for (int i = srow; i < erow + 1; i++)
				for (int j = scol; j < ecol + 1; j++)  {
					glBegin(GL_POINTS);
						glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
					glEnd();
					}
			glPointSize( 1.0 );
			glDisable(GL_POINT_SMOOTH);
			glEndList();
			}
			break;
		case arn_glTPM_MASHED_SURFACE:
			if ((srow == erow) && (scol == ecol)){
				// ToDo same as follow
				list = glGenLists( 1 );
				glNewList( list, GL_COMPILE );
				glPointSize( RED_POINTS_SIZE );
				glEnable(GL_POINT_SMOOTH);
				qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
				for (int i = srow; i < erow + 1; i++)
					for (int j = scol; j < ecol + 1; j++)  {
						glBegin(GL_POINTS);
							glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
						glEnd();
						}
				glPointSize( 1.0 );
				glDisable(GL_POINT_SMOOTH);
				glEndList();
				}
			else {
				list = glGenLists( 1 );
				//arnDebug("list = %u\n",list);
				glNewList( list, GL_COMPILE );
				glLineWidth( LINE_WIDTH );
				qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
				for (int j = scol; j < ecol + 1; j++) {
					glBegin(GL_LINE_STRIP);
						for (int i = srow + 1; i < erow + 1; i++) {
							glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i - 1],pVisMatrix->Table[i - 1][j]);
							glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
							}
					glEnd();
					}
				for (int i = srow; i < erow + 1; i++) {
					glBegin(GL_LINE_STRIP);
						for (int j = scol + 1; j < ecol + 1; j++) {
							glVertex3f(pVisMatrix->pCols[j - 1],pVisMatrix->pRows[i],pVisMatrix->Table[i ][j - 1]);
							glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
							}
					glEnd();
					}
				glEndList();
				}
			break;
		case arn_glTPM_NONE:
		default:
			list = 0;
			break;
		}
	return list;
}

GLint arnGLTable::makeObjectforselection(GLint x, GLint y,int* row, int* col)
{
	GLint hits = 0;
	GLint viewport[4];
	GLuint selectBuf[BUFSIZE];
	// inizializzazione della  VisTable
	switch (mde) {
		case arn_glTPM_VERTICAL_LINES: {
			GLfloat minCl,maxCl,minRw,maxRw,minTb,maxTb;
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataMatrix->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataMatrix->maxCol();
			(minRow.set == true) ? minRw = minRow.value  : minRw = pDataMatrix->minRow();
			(maxRow.set == true) ? maxRw = maxRow.value  : maxRw = pDataMatrix->maxRow();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataMatrix->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataMatrix->maxTable();
			for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)  {
				if ((maxRw - minRw) == 0)  pVisMatrix->pRows[rndx] = 1;
				else pVisMatrix->pRows[rndx] = (1.0 * ( pDataMatrix->pRows[rndx]  - minRw) / (maxRw - minRw)) - 0.5;
				}
			for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisMatrix->pCols[cndx] = 1;
				else pVisMatrix->pCols[cndx] = (1.0 * ( pDataMatrix->pCols[cndx]  - minCl) / (maxCl- minCl))  - 0.5;
				}
			for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)
				for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
					if ((maxTb- minTb) == 0) pVisMatrix->Table[rndx][cndx] = 1;
					else pVisMatrix->Table[rndx][cndx] =  (1.0 * ( pDataMatrix->Table[rndx][cndx]  - minTb) / (maxTb- minTb));
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
				glFrustum(-0.7,0.7, -0.7, 0.7, 2.0 ,300.0); // la stessa dlla resize
				glLineWidth( LINE_WIDTH );
				qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
				glLoadName((GLuint)-1); // nome degli assi
				glBegin(GL_LINES);
					glVertex3f(pVisMatrix->pCols[0] - 0.1, pVisMatrix->pRows[0] - 0.1,0.0);
					glVertex3f( pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[pVisMatrix->nRows - 1] +  0.1,0.0);
					glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1 ,0.0);
					glVertex3f( pVisMatrix->pCols[pVisMatrix->nCols - 1] + 0.1, pVisMatrix->pRows[0]  - 0.1,0.0);
					glVertex3f(pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[0] - 0.1, 0.0);
					glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1,1.0 + 0.1);
				glEnd();
				qglColor( Qt::black );		      // Shorthand for glColor3f or glIndex
				for (int i = 0; i < pVisMatrix->nRows; i++)
					for (int j = 0; j <pVisMatrix->nCols; j++)  {
						glLoadName ((GLint)i);
						glPushName ((GLint)j);
						glBegin(GL_LINES);
							glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],0.0);
							glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
						glEnd();
						glPopName();
						}
			glPopMatrix ();
			glFlush ();
			hits = glRenderMode (GL_RENDER);
			processHits (hits, selectBuf,row,col);
			glMatrixMode( GL_MODELVIEW );
			}
			break;
		case arn_glTPM_MASHED_SURFACE: {
			GLfloat minCl,maxCl,minRw,maxRw,minTb,maxTb;
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataMatrix->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataMatrix->maxCol();
			(minRow.set == true) ? minRw = minRow.value  : minRw = pDataMatrix->minRow();
			(maxRow.set == true) ? maxRw = maxRow.value  : maxRw = pDataMatrix->maxRow();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataMatrix->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataMatrix->maxTable();
			for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)  {
				if ((maxRw - minRw) == 0)  pVisMatrix->pRows[rndx] = 1;
				else pVisMatrix->pRows[rndx] = (1.0 * ( pDataMatrix->pRows[rndx]  - minRw) / (maxRw - minRw)) - 0.5;
				}
			for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisMatrix->pCols[cndx] = 1;
				else pVisMatrix->pCols[cndx] = (1.0 * ( pDataMatrix->pCols[cndx]  - minCl) / (maxCl- minCl))  - 0.5;
				}
			
			for (int  rndx = 0; rndx < pDataMatrix->nRows; rndx++)
				for (int cndx = 0; cndx < pDataMatrix->nCols; cndx++) {
					if ((maxTb- minTb) == 0) pVisMatrix->Table[rndx][cndx] = 1;
					else pVisMatrix->Table[rndx][cndx] =  (1.0 * ( pDataMatrix->Table[rndx][cndx]  - minTb) / (maxTb- minTb));
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
				glFrustum(-0.7,0.7, -0.7, 0.7, 2.0 ,300.0); // la stessa dlla resize
				glLineWidth( LINE_WIDTH );
				qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
				glLoadName((GLuint)-1); // nome degli assi
				glBegin(GL_LINES);
					glVertex3f(pVisMatrix->pCols[0] - 0.1, pVisMatrix->pRows[0] - 0.1,0.0);
					glVertex3f( pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[pVisMatrix->nRows - 1] +  0.1,0.0);
					glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1 ,0.0);
					glVertex3f( pVisMatrix->pCols[pVisMatrix->nCols - 1] + 0.1, pVisMatrix->pRows[0]  - 0.1,0.0);
					glVertex3f(pVisMatrix->pCols[0] - 0.1,pVisMatrix->pRows[0] - 0.1, 0.0);
					glVertex3f(pVisMatrix->pCols[0]  - 0.1, pVisMatrix->pRows[0] - 0.1,1.0 + 0.1);
				glEnd();
				qglColor( Qt::black );      // Shorthand for glColor3f or glIndex
				for (int j = 0; j <pVisMatrix->nCols; j++) {
					glLoadName ((GLint)j);
					glBegin(GL_LINE_STRIP);
					for (int i =1; i < pVisMatrix->nRows; i++) {
						glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i - 1],pVisMatrix->Table[i - 1][j]);
						glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
						}
					glEnd();
					}
				for (int i = 0; i <pVisMatrix->nRows; i++) {
					glLoadName ((GLint)(i << 16));
					glBegin(GL_LINE_STRIP);
					for (int j =1; j < pVisMatrix->nCols; j++) {
						glVertex3f(pVisMatrix->pCols[j - 1],pVisMatrix->pRows[i],pVisMatrix->Table[i ][j - 1]);
						glVertex3f(pVisMatrix->pCols[j],pVisMatrix->pRows[i],pVisMatrix->Table[i][j]);
						}
					glEnd();
					}
			glPopMatrix ();
			glFlush ();
			hits = glRenderMode (GL_RENDER);
			processHits (hits, selectBuf,row,col);
			glMatrixMode( GL_MODELVIEW );
			}
			break;
		case arn_glTPM_NONE:
		default:
			hits = -1;
			break;
			}
		return hits;
}

void arnGLTable::processHits (GLint hits, GLuint buffer[],int* row, int* col)
{
	unsigned int i,j;
	*row = *col = -1;
	switch (mde) {
		case arn_glTPM_VERTICAL_LINES: {
			GLuint names, *ptr;
			if (hits != 1) return;
			ptr = (GLuint *) buffer;
			for (i = 0; i < (unsigned int)hits; i++) {
				/* for each hit */
				names = *ptr; ptr++;
				/*printf ("z1 is %u;", *ptr);*/ ptr++;
				/*printf (" z2 is %u\n", *ptr);*/ ptr++;
				/*printf ("names are ");*/
				if ((GLint)names != 2) return;
				for (j = 0; j < names; j++) {
					/*printf ("%d ", *ptr);*/
					if (j == 0) *row = (int)(*ptr);
					else if (j == 1) *col = (int)(*ptr);
					ptr++;
					}
				/*printf ("\n");*/
				}
			}
			break;
		case arn_glTPM_MASHED_SURFACE: {
			GLuint names, *ptr;
			ptr = (GLuint *) buffer;
			for (i = 0; i < (unsigned int)hits; i++) {
				names = *ptr; ptr++;
				for (j = 0; j < names; j++) {
					/*printf ("z1 is %u;", *ptr);*/ ptr++;
					/*printf (" z2 is %u\n", *ptr);*/ ptr++;
					if ((*ptr) == (GLuint)-1); // gli assi
					else if (!(*ptr)) {
						if (i == 0) *col = (int)(*ptr);
						else if (i == 1) *row = (int)(*ptr) >> 16;
						}
					else if ((*ptr) & 0x0000ffff) { // le colonne
						*col = (int)(*ptr);
						}
					else if (((*ptr) >> 16) & 0x0000ffff) { // le righe
						*row = ((int)(*ptr) >> 16);
						}
					ptr++;
					}
				}

			}
			break;
		case arn_glTPM_NONE:
		default:
			*row = *col = -1; 
			break;
		}
}



void arnGLTable::initializeGL()
{
    qglClearColor( Qt::white ); // Let OpenGL clear to black

    object = makeObject(); // Generate an OpenGL display list

    glShadeModel( GL_FLAT );
}


void arnGLTable::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();

    glFrustum(-0.7,0.7, -0.7, 0.7, 2.0 ,300.0);

    glMatrixMode( GL_MODELVIEW );
}

void arnGLTable::paintGL()
{
    glClear( GL_COLOR_BUFFER_BIT );

    glLoadIdentity();
    glTranslatef(0.0, 0.0, -4 );
    glScalef( scle, scle, scle );

    glRotatef( xRot, 1.0, 0.0, 0.0 );
    glRotatef( yRot, 0.0, 1.0, 0.0 );
    glRotatef( zRot, 0.0, 0.0, 1.0 );

    drawText();
    drawLabels();
    glCallList( object );
    if (selection) {glCallList( selection );}
}

void arnGLTable::wheelEvent(QWheelEvent *e)
{
	e->delta() > 0 ? scle += scle*0.1f : scle -= scle*0.1f;
	updateGL();
 }
/*
void arnGLTable::setZoom(int zoomfactor)
{
	int delta = zoomfactor - pervZoomValue;
	pervZoomValue = zoomfactor;
	
	if (delta > 0) scle += 0.01;
	else if (delta < 0) scle -= 0.01;
	else if (zoomfactor == 10000) {
		scle = 1.00;
		glFrustum(-0.7 ,0.7, -0.7, 0.7, 2.0 ,300.0);
		}

arnDebug("%d\n",zoomfactor);
arnDebug("%f\n",scle);

    //glMatrixMode( GL_PROJECTION );

    //glLoadIdentity();

    

    //glMatrixMode( GL_MODELVIEW );
	updateGL();
}*/

void arnGLTable::setRowValue(int row, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (row < pDataMatrix->nRows) {
        if (ok) pDataMatrix->pRows[row] = vl;
        }
}

void arnGLTable::setColValue( int col, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (col < pDataMatrix->nCols) {
        if (ok) pDataMatrix->pCols[col] = vl;
        }
}

void arnGLTable::setRowValue(int row, double val)
{
    GLfloat vl = (GLfloat) val;
    if (row < pDataMatrix->nRows) pDataMatrix->pRows[row] = vl;
}

void arnGLTable::setColValue( int col, double val)
{
    GLfloat vl = (GLfloat) val;
    if (col < pDataMatrix->nCols) pDataMatrix->pCols[col] = vl;
}

void arnGLTable::setValue(int row, int col, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if ((row < pDataMatrix->nRows) && (col <pDataMatrix-> nCols)) {
        if (ok) pDataMatrix->Table[row][col] = vl;
        }
}

void arnGLTable::setValue(int row, int col, double val)
{
    GLfloat vl = (GLfloat) val;
    if ((row < pDataMatrix->nRows) && (col < pDataMatrix->nCols)) pDataMatrix->Table[row][col] = vl;
}

double arnGLTable::value(int row, int col)
{
     if ((row <pDataMatrix-> nRows) && (col < pDataMatrix->nCols))
         return (double)(pDataMatrix->Table[row][col]);
     arnCriticalExit();
}

QString arnGLTable:: text(int row, int col)
{
     QString vl("");
     if ((row < pDataMatrix->nRows) && (col < pDataMatrix->nCols)) {
         vl.setNum((double)(pDataMatrix->Table[row][col]));
         return vl;
         }
     arnCriticalExit();
}

void arnGLTable::setXRotation( int degrees )
{
    xRot = (GLfloat)(((int)sxRot + degrees) % 360);
    updateGL();
}

void arnGLTable::setYRotation( int degrees )
{
    yRot = (GLfloat)(((int)syRot + degrees) % 360);
    updateGL();
}

void arnGLTable::setZRotation( int degrees )
{
    zRot = (GLfloat)(((int)szRot + degrees) % 360);
    updateGL();
}



void arnGLTable::initDefaultParamsForVis(void)
{
    //mde = arn_glTPM_VERTICAL_LINES;
    
    sxRot = 290.0; // default object rotation -  XAxis
    xRot = sxRot;
    syRot = 0.0; // default object rotation -  YAxis
    yRot = syRot;
    szRot = -35.0;  // default object rotation -  ZAxis
    zRot = szRot;

    scle = 1.00; // default object scale

    object = 0;

    minCol.set = false;
    minCol.value = 0;
    maxCol.set = false;
    maxCol.value = 0;
    minRow.set = false;
    minRow.value = 0;
    maxRow.set = false;
    maxRow.value = 0;
    minTab.set = false;
    minTab.value = 0;
    maxTab.set = false;
    maxTab.value = 0;

    labels.xAxis = "X";
    labels.yAxis = "Y";
    labels.zAxis = "Z";
    labels.caption = "3DMatrixViewer";
    sSelRow = sSelCol = eSelRow = eSelCol = -1;
    selection = 0;
	pervZoomValue = 0;
}

void arnGLTable::setRowMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minRow.value = vl;
        minRow.set = true;
        }
}

void arnGLTable::setRowMinScale(double val)
{
    minRow.value = (GLfloat)val;
    minRow.set = true;
}

void arnGLTable::setRowMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxRow.value = vl;
        maxRow.set = true;
        }
}

void arnGLTable::setRowMaxScale(double val)
{
    maxRow.value = (GLfloat)val;
    maxRow.set = true;
}

void arnGLTable::setColMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minCol.value = vl;
        minCol.set = true;
        }
}

void arnGLTable::setColMinScale(double val)
{
    minCol.value = (GLfloat)val;
    minCol.set = true;
}

void arnGLTable::setColMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxCol.value = vl;
        maxCol.set = true;
        }
}

void arnGLTable::setColMaxScale(double val)
{
    maxCol.value = (GLfloat)val;
    maxCol.set = true;
}

void arnGLTable::setTableMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minTab.value = vl;
        minTab.set = true;
        }
}

void arnGLTable::setTableMinScale(double val)
{
    minTab.value = (GLfloat)val;
    minTab.set = true;
}

void arnGLTable::setTableMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxTab.value = vl;
        maxTab.set = true;
        }
}

void arnGLTable::setTableMaxScale(double val)
{
    maxTab.value = (GLfloat)val;
    maxTab.set = true;
}

//double arnGLTable::getTableMinScale(void)
//{
//	return minTab.value;
//}
//
//double arnGLTable::getTableMaxScale(void)
//{
//	return maxTab.value;
//}

void arnGLTable::drawText(void)
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
    int x, y, z;
    x = (xRot >= 0) ? (int) xRot % 360 : 359 - (QABS((int) xRot) % 360);
    y = (yRot >= 0) ? (int) yRot % 360 : 359 - (QABS((int) yRot) % 360);
    z = (zRot >= 0) ? (int) zRot % 360 : 359 - (QABS((int) zRot) % 360);
    str.sprintf( "Rot X: %03d - Rot Y: %03d - Rot Z: %03d", x, y, z );
    renderText( (width() - fm.width( str )) / 2, height() - 30, str, f );
    str.sprintf( "minZ: %g - maxZ: %g", minTab.value,maxTab.value);
    renderText( (width() - fm.width( str )) / 2, height() - 15, str, f );
    glPopAttrib();
}

void arnGLTable::drawLabels(void)
{
    glPushAttrib( GL_LIGHTING_BIT | GL_TEXTURE_BIT );
    glDisable( GL_LIGHTING );
    glDisable( GL_TEXTURE_2D );
    qglColor( Qt::green );
    QFont f = QApplication::font();
    f.setStyleStrategy(QFont::PreferBitmap);
    renderText( pVisMatrix->pCols[pVisMatrix->nCols - 1] , pVisMatrix->pRows[0]  - 0.2, 0.0, labels.xAxis, f);
    renderText( pVisMatrix->pCols[0] - 0.2 ,pVisMatrix->pRows[pVisMatrix->nRows - 1], 0.0, labels.yAxis, f);
    renderText( pVisMatrix->pCols[0] - 0.2 , pVisMatrix->pRows[0]  - 0.2 , 1.0, labels.zAxis, f);
    glPopAttrib();
}

void arnGLTable::setMode (arnGLTablePaintingMode_t md)
{
    mde = md;

    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
    initializeGL();
} 

void arnGLTable::invalidate(void)
{
    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
    initializeGL();
}

void arnGLTable::mousePressEvent ( QMouseEvent *e )
{
	int xP,yP;
	if (e->button() == Qt::RightButton) return QGLWidget::mousePressEvent(e);
	setFocus();
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&sSelRow,&sSelCol);
//	arnDebug("sSelRow %d, sSelCol %d\n",sSelRow,sSelCol);
	updateGL();
}

void arnGLTable::mouseMoveEvent ( QMouseEvent *e )
{
	int xP,yP;
	int selRow,selCol;
	if (e->button() == Qt::RightButton) return QGLWidget::mouseMoveEvent(e);
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&selRow,&selCol);
//	arnDebug("SelRow %d, SelCol %d\n",selRow,selRow);
	if (((selRow != -1) && (selCol != -1)) &&
		((sSelRow != -1) && (sSelCol != -1)) &&
		((selRow != sSelRow) && (selCol != sSelCol)) &&
		((sSelRow < pDataMatrix->nRows) && (sSelCol < pDataMatrix->nCols)) &&
		((selRow < pDataMatrix->nRows) && (selCol < pDataMatrix->nCols))
		) {
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		selection = makeSelection(sSelRow,sSelCol,selRow,selCol);
		updateGL();
		emit selectionChanged(sSelRow,sSelCol,selRow,selCol);
		updateGL();
		}
	else return QGLWidget::mousePressEvent(e);
}

void arnGLTable::mouseReleaseEvent ( QMouseEvent *e )
{
	int xP,yP;
	if (e->button() == Qt::RightButton) return QGLWidget::mouseReleaseEvent(e);
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&eSelRow,&eSelCol);
//	arnDebug("eSelRow %d, eSelCol %d\n",eSelRow,eSelCol);
	if (((eSelRow != -1) && (eSelCol != -1)) &&
		((sSelRow != -1) && (sSelCol != -1)) &&
		((sSelRow < pDataMatrix->nRows) && (sSelCol < pDataMatrix->nCols)) &&
		((eSelRow < pDataMatrix->nRows) && (eSelCol < pDataMatrix->nCols))
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

void arnGLTable::keyReleaseEvent (  QKeyEvent *e )
{
	if (((sSelRow != -1) && (sSelCol != -1)) &&
		((sSelRow < pDataMatrix->nRows) && (sSelCol < pDataMatrix->nCols)) &&
		((eSelRow != -1) && (eSelCol != -1)) &&
		((eSelRow < pDataMatrix->nRows) && (eSelCol < pDataMatrix->nCols))
		) {
		if (e->key() == Qt::Key_Left) {  // freccia sinistra
			e->accept();
			if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
			//arnDebug("Allocation allowd\n");
			((sSelRow -= 1) < 0) ? sSelRow = 0 : sSelRow = sSelRow;
			eSelRow = sSelRow;
			selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
			updateGL();
			emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
			updateGL();
			}
		else if (e->key() == Qt::Key_Up) { // freccia alta
			e->accept();
			if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
			//arnDebug("Allocation allowd\n");
			((sSelCol += 1) > (pDataMatrix->nCols -1)) ? sSelCol = (pDataMatrix->nCols - 1) : sSelCol = sSelCol;
			eSelCol = sSelCol;
			selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
			updateGL();
			emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
			updateGL();
			}
		else if (e->key() == Qt::Key_Right) { // freccia destra
			e->accept();
			if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
			//arnDebug("Allocation allowd\n");
			((sSelRow += 1) > (pDataMatrix->nRows -1)) ? sSelRow = (pDataMatrix->nRows - 1) : sSelRow = sSelRow;
			eSelRow = sSelRow;
			selection = makeSelection(sSelRow,sSelCol,eSelRow,eSelCol);
			updateGL();
			emit selectionChanged(sSelRow,sSelCol,eSelRow,eSelCol);
			updateGL();
			}
		else if (e->key() == Qt::Key_Down) { // freccia bassa
			e->accept();
			if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
			//arnDebug("Allocation allowd\n");
			((sSelCol -= 1) < 0) ? sSelCol = 0 : sSelCol = sSelCol;
			eSelCol = sSelCol;
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
	else {
		e->ignore();
		QGLWidget::keyReleaseEvent(e);
		}
}

void arnGLTable::updateTrace(int row, int col)
{
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
	selection = makeSelection(row ,col,row,col);
	updateGL();
	emit selectionChanged(row ,col,row,col);
	updateGL();
}
//QFont f = QApplication::font();
// f.setStyleStrategy(QFont::PreferBitmap);
// renderText(x, y, "Text", f);

