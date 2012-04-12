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

#include "arnGLArray.h"

#define __ABS__(x) (x > 0 ? x : -x)
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

arnGLArray::arnGLArray(arnGLArrayPaintingMode_t md, QWidget* parent, const char * name, const QGLWidget* shareWidget, Qt::WFlags f)
     : QGLWidget(parent, name,  shareWidget, f)
{
	pDataVector = new arnGLVector(5,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLVector(5,0);
	if (!pVisVector) arnCriticalExit();
	mde = md;
	sSelRow = eSelRow = -1;
	initDefaultParamsForVis();
}

arnGLArray:: arnGLArray (const QGLFormat& format, arnGLArrayPaintingMode_t md,QWidget* parent, const char* name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(format, parent, name,  shareWidget, f)
{
	pDataVector = new arnGLVector(5,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLVector(5,0);
	if (!pVisVector) arnCriticalExit();
	mde = md;
	sSelRow = eSelRow = -1;
	initDefaultParamsForVis();
}

arnGLArray::arnGLArray(int Cols, arnGLArrayPaintingMode_t md, QWidget* parent, const char * name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(parent, name,  shareWidget, f)
{
	pDataVector = new arnGLVector(Cols,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLVector(Cols,0);
	if (!pVisVector) arnCriticalExit();
	mde = md;
	sSelRow = eSelRow = -1;
	initDefaultParamsForVis();
}

arnGLArray:: arnGLArray (const QGLFormat& format, int Cols, arnGLArrayPaintingMode_t md, QWidget* parent, const char* name, const QGLWidget* shareWidget,Qt::WFlags f)
     : QGLWidget(format, parent, name,  shareWidget, f)
{
	pDataVector = new arnGLVector(Cols,0);
	if (!pDataVector) arnCriticalExit();
	pVisVector = new arnGLVector(Cols,0);
	if (!pVisVector) arnCriticalExit();
	mde = md;
	sSelRow = eSelRow = -1;
	initDefaultParamsForVis();
}


arnGLArray::~arnGLArray(void)
{
	if (pDataVector) {delete pDataVector; pDataVector = 0;}
	if (pVisVector) {delete pVisVector; pVisVector = 0;}
	makeCurrent();
	glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}

}

GLuint arnGLArray::makeObject(void)
{
	GLuint list = 0;
	// inizializzazione del  VisVector
	switch (mde) {
		case arn_glAPM_VERTICAL_LINES: {
			GLfloat minCl,maxCl,minTb,maxTb;
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataVector->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataVector->maxCol();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataVector->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataVector->maxTable();
//			arnDebug("%s = %d\n","minCl", (int)minCl);
//			arnDebug("%s = %d\n","maxCl", (int)maxCl);
//			arnDebug("%s = %d\n","minTb", (int)minTb);
//			arnDebug("%s = %d\n","maxTb", (int)maxTb);
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisVector->pCols[cndx] = 1;
				else pVisVector->pCols[cndx] = (1.0 * ( pDataVector->pCols[cndx]  - minCl) / (maxCl- minCl)) - 0.5;
//				arnDebug("%s[%d] = %f\n","pVisVector->pCols",cndx, pVisVector->pCols[cndx] );
				}
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxTb- minTb) == 0) pVisVector->Table[cndx] = 1;
				else pVisVector->Table[cndx] =  (1.0 * ( pDataVector->Table[cndx]  - minTb) / (maxTb- minTb)) - 0.5;
//				arnDebug("%s[%d]  = %f\n","pVisVector->Table",cndx, pVisVector->Table[cndx]  );
				}
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glLineWidth( LINE_WITH );
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			glBegin(GL_LINES);
			glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
			glVertex2f(pVisVector->pCols[pVisVector->nCols - 1] + 0.1,pVisVector->pCols[0]);
			glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
			glVertex2f(pVisVector->pCols[0], pVisVector->pCols[pVisVector->nCols - 1] + 0.1);
			glEnd();
			qglColor( Qt::black );		      // Shorthand for glColor3f or glIndex
			for (int j = 0; j < pVisVector->nCols; j++)  {
				glBegin(GL_LINES);
					glVertex2f(pVisVector->pCols[j],- 0.5);
					glVertex2f(pVisVector->pCols[j], pVisVector->Table[j]);
				glEnd();
				}
			glPointSize( BLU_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::blue );		      // Shorthand for glColor3f or glIndex
			for (int j = 0; j < pVisVector->nCols; j++)  {
				glBegin(GL_POINTS);
					glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
				glEnd();
				}
			glPointSize( 1.0 );
			glDisable(GL_POINT_SMOOTH);
			glEndList();
			}
			break;
		case arn_glAPM_MASHED_LINES: {
			GLfloat minCl,maxCl,minTb,maxTb;
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataVector->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataVector->maxCol();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataVector->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataVector->maxTable();
//			arnDebug("%s = %d\n","minCl", (int)minCl);
//			arnDebug("%s = %d\n","maxCl", (int)maxCl);
//			arnDebug("%s = %d\n","minTb", (int)minTb);
//			arnDebug("%s = %d\n","maxTb", (int)maxTb);
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisVector->pCols[cndx] = 1;
				else pVisVector->pCols[cndx] = (1.0 * ( pDataVector->pCols[cndx]  - minCl) / (maxCl- minCl)) - 0.5;
//				arnDebug("%s[%d] = %f\n","pVisVector->pCols",cndx, pVisVector->pCols[cndx] );
				}
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxTb- minTb) == 0) pVisVector->Table[cndx] = 1;
				else pVisVector->Table[cndx] =  (1.0 * ( pDataVector->Table[cndx]  - minTb) / (maxTb- minTb)) - 0.5;
//				arnDebug("%s[%d]  = %f\n","pVisVector->Table",cndx, pVisVector->Table[cndx]  );
				}
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glLineWidth( LINE_WITH );
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			glBegin(GL_LINES);
			glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
			glVertex2f(pVisVector->pCols[pVisVector->nCols - 1] /*+ 0.1*/,pVisVector->pCols[0]);
			glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
			glVertex2f(pVisVector->pCols[0], pVisVector->pCols[pVisVector->nCols - 1] /*+ 0.1*/);
			glEnd();
			qglColor( Qt::black );		      // Shorthand for glColor3f or glIndex
			glBegin(GL_LINE_STRIP);
			for (int j = 1; j < pVisVector->nCols; j++)  {
				glVertex2f(pVisVector->pCols[j - 1],pVisVector->Table[j -1]);
				glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
				}
			glEnd();
			glPointSize( BLU_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::blue );		      // Shorthand for glColor3f or glIndex
			for (int j = 0; j < pVisVector->nCols; j++)  {
				glBegin(GL_POINTS);
					glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
				glEnd();
				}
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

GLuint arnGLArray::makeSelection(int srow, int erow)
{
    GLuint list = 0;
    int tmp;
    // inizializzazione della  VisTable
    if (srow > erow) {tmp = srow; srow = erow; erow = tmp;}
    //arnDebug("srow = %d, scol = %d, erow = %d, ecol = %d\n",srow, scol, erow, ecol);
    switch (mde) {
        case arn_glAPM_VERTICAL_LINES: {
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glPointSize( RED_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			for (int j = srow ; j < erow + 1; j++)  {
				glBegin(GL_POINTS);
					glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
				glEnd();
				}
			glPointSize( 1.0 );
			glDisable(GL_POINT_SMOOTH);
			glEndList();
            }
            break;
        case arn_glAPM_MASHED_LINES: {
			list = glGenLists( 1 );
			glNewList( list, GL_COMPILE );
			glPointSize( RED_POINTS_SIZE );
			glEnable(GL_POINT_SMOOTH);
			qglColor( Qt::red );		      // Shorthand for glColor3f or glIndex
			for (int j = srow ; j < erow + 1; j++)  {
				glBegin(GL_POINTS);
					glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
				glEnd();
				}
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

GLint arnGLArray::makeObjectforselection(GLint x, GLint y,int* row)
{
	GLuint hits = 0;
	GLint viewport[4];
	GLuint selectBuf[BUFSIZE];
	// inizializzazione del  VisVector
	switch (mde) {
		case arn_glAPM_VERTICAL_LINES: {
			GLfloat minCl,maxCl,minTb,maxTb;
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataVector->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataVector->maxCol();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataVector->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataVector->maxTable();
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisVector->pCols[cndx] = 1;
				else pVisVector->pCols[cndx] = (1.0 * ( pDataVector->pCols[cndx]  - minCl) / (maxCl- minCl)) - 0.5;
				}
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxTb- minTb) == 0) pVisVector->Table[cndx] = 1;
				else pVisVector->Table[cndx] =  (1.0 * ( pDataVector->Table[cndx]  - minTb) / (maxTb- minTb)) - 0.5;
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
				glLoadName((GLuint)-1); // nome degli assi
				glBegin(GL_LINES);
					glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
					glVertex2f(pVisVector->pCols[pVisVector->nCols - 1] + 0.1,pVisVector->pCols[0]);
					glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
					glVertex2f(pVisVector->pCols[0], pVisVector->pCols[pVisVector->nCols - 1] + 0.1);
				glEnd();
				qglColor( Qt::black );		      // Shorthand for glColor3f or glIndex
				for (int j = 0; j < pVisVector->nCols; j++)  {
					glLoadName ((GLint)j);
					glBegin(GL_LINES);
						glVertex2f(pVisVector->pCols[j],- 0.5);
						glVertex2f(pVisVector->pCols[j], pVisVector->Table[j]);
					glEnd();
					}
				glPointSize( BLU_POINTS_SIZE );
				glEnable(GL_POINT_SMOOTH);
				qglColor( Qt::blue );		      // Shorthand for glColor3f or glIndex
				for (int j = 0; j < pVisVector->nCols; j++)  {
					glLoadName ((GLint)((j) << 16));
					glBegin(GL_POINTS);
						glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
					glEnd();
					}
				glPointSize( 1.0 );
				glDisable(GL_POINT_SMOOTH);
			glPopMatrix ();
			glFlush ();
			hits = glRenderMode (GL_RENDER);
			processHits (hits, selectBuf,row);
			glMatrixMode( GL_MODELVIEW );
			}
			break;
		case arn_glAPM_MASHED_LINES: {
			GLfloat minCl,maxCl,minTb,maxTb;
			(minCol.set == true) ? minCl = minCol.value  : minCl = pDataVector->minCol();
			(maxCol.set == true) ? maxCl = maxCol.value  : maxCl = pDataVector->maxCol();
			(minTab.set == true) ? minTb = minTab.value  : minTb = pDataVector->minTable();
			(maxTab.set == true) ? maxTb = maxTab.value  : maxTb = pDataVector->maxTable();
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxCl- minCl) == 0)   pVisVector->pCols[cndx] = 1;
				else pVisVector->pCols[cndx] = (1.0 * ( pDataVector->pCols[cndx]  - minCl) / (maxCl- minCl)) - 0.5;
				}
			for (int cndx = 0; cndx < pDataVector->nCols; cndx++) {
				if ((maxTb- minTb) == 0) pVisVector->Table[cndx] = 1;
				else pVisVector->Table[cndx] =  (1.0 * ( pDataVector->Table[cndx]  - minTb) / (maxTb- minTb)) - 0.5;
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
				glLoadName((GLuint)-1); // nome degli assi
				glBegin(GL_LINES);
					glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
					glVertex2f(pVisVector->pCols[pVisVector->nCols - 1] /*+ 0.1*/,pVisVector->pCols[0]);
					glVertex2f(pVisVector->pCols[0], pVisVector->pCols[0]);
					glVertex2f(pVisVector->pCols[0], pVisVector->pCols[pVisVector->nCols - 1] /*+ 0.1*/);
				glEnd();
				qglColor( Qt::black );		      // Shorthand for glColor3f or glIndex
				glBegin(GL_LINE_STRIP);
					for (int j = 1; j < pVisVector->nCols; j++)  {
						glVertex2f(pVisVector->pCols[j - 1],pVisVector->Table[j -1]);
						glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
						}
				glEnd();
				glPointSize( BLU_POINTS_SIZE );
				glEnable(GL_POINT_SMOOTH);
				qglColor( Qt::blue );		      // Shorthand for glColor3f or glIndex
				for (int j = 0; j < pVisVector->nCols; j++)  {
					glLoadName ((GLint)(j << 16));
					glBegin(GL_POINTS);
						glVertex2f(pVisVector->pCols[j],pVisVector->Table[j]);
					glEnd();
					}
				glPointSize( 1.0 );
				glDisable(GL_POINT_SMOOTH);
			glPopMatrix ();
			glFlush ();
			hits = glRenderMode (GL_RENDER);
			processHits (hits, selectBuf,row);
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

void arnGLArray::processHits (GLint hits, GLuint buffer[],int* row)
{
	unsigned int i,j;
	*row = -1;
	switch (mde) {
		case arn_glAPM_VERTICAL_LINES: {
			GLuint names, *ptr;
			ptr = (GLuint *) buffer;
			for (i = 0; i < (unsigned int)hits; i++) {
				names = *ptr; ptr++;
				for (j = 0; j < names; j++) {
					/*printf ("z1 is %u;", *ptr);*/ ptr++;
					/*printf (" z2 is %u\n", *ptr);*/ ptr++;
					if ((*ptr) == (GLuint)-1); // gli assi
					else if (!(*ptr)) *row = (int)(*ptr);
					else if ((*ptr) & 0x0000ffff) { // le linee
						*row = (int)(*ptr);
						}
					else if (((*ptr) >> 16) & 0x0000ffff) { // il pallino
						*row = ((int)(*ptr) >> 16);
						}
					ptr++;
					}
				}
			}
			break;
		case arn_glAPM_MASHED_LINES: {
			GLuint names, *ptr;
			ptr = (GLuint *) buffer;
			for (i = 0; i < (unsigned int)hits; i++) {
				names = *ptr; ptr++;
				for (j = 0; j < names; j++) {
					/*printf ("z1 is %u;", *ptr);*/ ptr++;
					/*printf (" z2 is %u\n", *ptr);*/ ptr++;
					if ((*ptr) == (GLuint)-1); // gli assi
					else if (!(*ptr)) *row = (int)(*ptr);
					else if (((*ptr) >> 16) & 0x0000ffff) { // il pallino
						*row = ((int)(*ptr) >> 16);
						}
					ptr++;
					}
				}
			}
			break;
		case arn_glAPM_NONE:
		default:
			*row = -1;
			break;
		}
}

void arnGLArray::initializeGL()
{
    qglClearColor( Qt::white ); // Let OpenGL clear to black

    object = makeObject(); // Generate an OpenGL display list

    glShadeModel( GL_FLAT );
}


void arnGLArray::resizeGL(int width, int height)
{
    glViewport( 0, 0, (GLint)width, (GLint)height );
    glMatrixMode( GL_PROJECTION );

    glLoadIdentity();

    glOrtho(WINDOWS_X, WINDOWS_Y, WINDOWS_X, WINDOWS_Y, -1, 1);

    glMatrixMode( GL_MODELVIEW );
}

void arnGLArray::paintGL()
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



void arnGLArray::setColValue( int col, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (col < pDataVector->nCols) {
        if (ok) pDataVector->pCols[col] = vl;
        }
}

void arnGLArray::setColValue( int col, double val)
{
    GLfloat vl = (GLfloat) val;
    if (col < pDataVector->nCols) pDataVector->pCols[col] = vl;
}

void arnGLArray::setValue(int col, QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (col < pDataVector-> nCols) {
        if (ok) pDataVector->Table[col] = vl;
        }
}

void arnGLArray::setValue(int col, double val)
{
    GLfloat vl = (GLfloat) val;
    if (col < pDataVector->nCols) pDataVector->Table[col] = vl;
}

double arnGLArray::value(int col)
{
     if (col < pDataVector->nCols)
         return (double)(pDataVector->Table[col]);
     arnCriticalExit();
}

QString arnGLArray:: text(int col)
{
     QString vl("");
     if (col < pDataVector->nCols) {
         vl.setNum((double)(pDataVector->Table[col]));
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



void arnGLArray::initDefaultParamsForVis(void)
{
    //mde = arn_glTPM_VERTICAL_LINES;

//    sxRot = 290.0; // default object rotation -  XAxis
//    xRot = sxRot;
//    syRot = 0.0; // default object rotation -  YAxis
//    yRot = syRot;
//    szRot = -35.0;  // default object rotation -  ZAxis
//    zRot = szRot;

    scle = 1.00; // default object scale

    object = 0;

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
}




void arnGLArray::setColMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minCol.value = vl;
        minCol.set = true;
        }
}

void arnGLArray::setColMinScale(double val)
{
    minCol.value = (GLfloat)val;
    minCol.set = true;
}

void arnGLArray::setColMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxCol.value = vl;
        maxCol.set = true;
        }
}

void arnGLArray::setColMaxScale(double val)
{
    maxCol.value = (GLfloat)val;
    maxCol.set = true;
}

void arnGLArray::setTableMinScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        minTab.value = vl;
        minTab.set = true;
        }
}

void arnGLArray::setTableMinScale(double val)
{
    minTab.value = (GLfloat)val;
    minTab.set = true;
}

void arnGLArray::setTableMaxScale(QString& val)
{
    bool ok;
    GLfloat vl = (GLfloat) val.toDouble(&ok);
    if (ok) {
        maxTab.value = vl;
        maxTab.set = true;
        }
}

void arnGLArray::setTableMaxScale(double val)
{
    maxTab.value = (GLfloat)val;
    maxTab.set = true;
}

void arnGLArray::drawText(void)
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

void arnGLArray::drawLabels(void)
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

void arnGLArray::setMode (arnGLArrayPaintingMode_t md)
{
    mde = md;

    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
    initializeGL();
}

void arnGLArray::invalidate(void)
{
    makeCurrent();
    glDeleteLists( object, 1 );
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
    initializeGL();
}

void arnGLArray::mousePressEvent ( QMouseEvent *e )
{
	int xP,yP;
	
	if (e->button() == Qt::RightButton) return QGLWidget::mousePressEvent(e);
	setFocus();
	if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&sSelRow);
	//arnDebug("sSelRow %d\n",sSelRow);
	updateGL();
//	eR = sR;
//	emit selectionChanged(sR,eR);
}

void arnGLArray::mouseMoveEvent ( QMouseEvent *e )
{
	int xP,yP;
	int selRow;
	if (e->button() == Qt::RightButton) return QGLWidget::mouseMoveEvent(e);
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&selRow);
	if ((selRow != -1) &&
		(sSelRow != -1) &&
		(selRow != sSelRow) &&
		(sSelRow < pDataVector->nCols) &&
		(selRow < pDataVector->nCols)
		) {
		//arnDebug("selRow % d, selCol %d\n",selRow,selCol);
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		selection = makeSelection(sSelRow,selRow);
		updateGL();
		emit selectionChanged(sSelRow,selRow);
		updateGL();
		}
	else return QGLWidget::mousePressEvent(e);
}

void arnGLArray::mouseReleaseEvent ( QMouseEvent *e )
{
	int xP,yP;
	
	if (e->button() == Qt::RightButton) return QGLWidget::mouseReleaseEvent(e);
	
	e->accept();
	xP = e->x();
	yP = e->y();
	makeObjectforselection(xP,yP,&eSelRow);
	//arnDebug("eSelRow %d\n",eSelRow);
	if ((eSelRow != -1) &&
		(eSelRow < pDataVector->nCols)
		) {
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		selection = makeSelection(sSelRow,eSelRow);
		updateGL();
		emit selectionChanged(sSelRow,eSelRow);
		updateGL();
		}
	else return QGLWidget::mouseReleaseEvent(e);
}

void arnGLArray::keyReleaseEvent (  QKeyEvent *e )
{
	if (e->key() == Qt::Key_Left) {  // freccia sinistra
		e->accept();
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		((sSelRow -= 1) < 0) ? sSelRow = 0 : sSelRow = sSelRow;
		eSelRow = sSelRow;
		updateGL();
		selection = makeSelection(sSelRow,eSelRow);
		updateGL();
		emit selectionChanged(sSelRow,eSelRow);
		updateGL();
		}
	else if (e->key() == Qt::Key_Right) { // freccia destra
		e->accept();
		if (selection) {glDeleteLists( selection, 1 ); selection = 0;}
		//arnDebug("Allocation allowd\n");
		((sSelRow += 1) > (pDataVector->nCols -1)) ? sSelRow = (pDataVector->nCols - 1) : sSelRow = sSelRow;
		eSelRow = sSelRow;
		updateGL();
		selection = makeSelection(sSelRow,eSelRow);
		updateGL();
		emit selectionChanged(sSelRow,eSelRow);
		updateGL();
		}
	else {
		e->ignore();
		QGLWidget::keyReleaseEvent(e);
		}
}



//QFont f = QApplication::font();
// f.setStyleStrategy(QFont::PreferBitmap);
// renderText(x, y, "Text", f);

