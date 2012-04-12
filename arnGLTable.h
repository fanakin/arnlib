/***************************************************************************
                          arnGLTable.h  -  description
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

#ifndef ArnGLTableH
#define ArnGLTableH

#include <qstring.h>
#include <qgl.h>
#include "arnlibtypes.h"
#include "CommonFunctions.h"
#include "arnGLMatrix.h"

class arnGLTable : public QGLWidget
{
    Q_OBJECT

    private:
        arnGLTablePaintingMode_t mde;

        GLuint object,selection;
        GLfloat sxRot,xRot;
        GLfloat syRot, yRot;
        GLfloat szRot, zRot;
        GLfloat scle;
        struct ScalingExtreme {
            GLfloat value;
            bool set;
            };
        struct ScalingExtreme minCol,maxCol,minRow,maxRow,minTab,maxTab; 

        struct {
            QString xAxis;
            QString yAxis;
            QString zAxis;
            QString caption;
            } labels;
		int pervZoomValue;
        arnGLMatrix *pDataMatrix, *pVisMatrix;
        int sSelRow, eSelRow, sSelCol, eSelCol;
        void initDefaultParamsForVis(void);
        void drawText(void);
        void drawLabels(void);
        void processHits (GLint hits, GLuint buffer[],int* row, int* col);
    private slots:

    protected:

        virtual GLuint makeObject(void);
        virtual GLuint makeSelection(int srow, int scol,int erow, int ecol);
        virtual GLint makeObjectforselection(GLint x, GLint y,int* row, int* col); // return hits
        virtual void initializeGL();
        virtual void resizeGL (int width, int height);
        virtual void paintGL();
        virtual void mousePressEvent ( QMouseEvent *e );
        virtual void mouseMoveEvent ( QMouseEvent *e );
        virtual void mouseReleaseEvent ( QMouseEvent *e );
        virtual void keyReleaseEvent (  QKeyEvent *e );
		virtual void wheelEvent(QWheelEvent *e);
    protected slots:

    signals:
    	void selectionChanged(int start_row, int start_col,int end_row, int end_col);

    public :
        arnGLTable(arnGLTablePaintingMode_t md = arn_glTPM_VERTICAL_LINES, QWidget* parent = 0, const char * name = 0, const QGLWidget* shareWidget = 0, Qt::WFlags f = 0);
        arnGLTable (const QGLFormat& format, arnGLTablePaintingMode_t md = arn_glTPM_VERTICAL_LINES, QWidget* parent = 0, const char* name = 0, const QGLWidget* shareWidget = 0,Qt::WFlags f = 0);
        arnGLTable( int Rows = 5,int Cols = 5, arnGLTablePaintingMode_t md = arn_glTPM_VERTICAL_LINES, QWidget* parent = 0, const char * name = 0, const QGLWidget* shareWidget = 0, Qt::WFlags f = 0);
        arnGLTable (const QGLFormat& format, int Rows = 5,int Cols = 5, arnGLTablePaintingMode_t md = arn_glTPM_VERTICAL_LINES, QWidget* parent = 0, const char* name = 0, const QGLWidget* shareWidget = 0,Qt::WFlags f = 0);
        ~arnGLTable(void);

        void setMode (arnGLTablePaintingMode_t md);
        inline arnGLTablePaintingMode_t mode (void) {return mde;}
//        double getTableMinScale(void);
//        double getTableMaxScale(void);
    public slots:
        void setRowValue(int row, QString& val);
        void setColValue( int col, QString& val);
        void setRowValue(int row, double val);
        void setColValue( int col, double val);
        void setValue(int row, int col, QString& val);
        void setValue(int row, int col, double val);

        void setRowMinScale(QString& val);
        void setRowMinScale(double val);
        void setRowMaxScale(QString& val);
        void setRowMaxScale(double val);
        void setColMinScale(QString& val);
        void setColMinScale(double val);
        void setColMaxScale(QString& val);
        void setColMaxScale(double val);
        void setTableMinScale(QString& val);
        void setTableMinScale(double val);
        void setTableMaxScale(QString& val);
        void setTableMaxScale(double val);

        double value(int row, int col);
        QString text(int row, int col);

        void setXRotation( int degrees );
        void setYRotation( int degrees );
        void setZRotation( int degrees );

        inline void setXAxisLabel(const QString& str) {labels.xAxis = str;}
        inline void setYAxisLabel(const QString& str) {labels.yAxis = str;}
        inline void setZAxisLabel(const QString& str) {labels.zAxis = str;}
        inline void setCaptionLabel(const QString& str) {labels.caption = str;}

        void invalidate(void);

        inline double RowMinScale(void) {return ((minCol.set == true) ? minCol.value  : pDataMatrix->minCol());}
        inline double RowMaxScale(void) {return ((maxCol.set == true) ? maxCol.value  : pDataMatrix->maxCol());}
        inline double ColMinScale(void) {return ((minRow.set == true) ? minRow.value  : pDataMatrix->minRow());}
        inline double ColMaxScale(void) {return ((maxRow.set == true) ? maxRow.value  : pDataMatrix->maxRow());}
        inline double TableMinScale(void) {return ((minTab.set == true) ? minTab.value  : pDataMatrix->minTable());}
        inline double TableMaxScale(void) {return ((maxTab.set == true) ? maxTab.value  : pDataMatrix->maxTable());}
     
		inline QString XAxisLabel(void) {return labels.xAxis;}
        inline QString YAxisLabel(void) {return labels.yAxis;}
        inline QString ZAxisLabel(void) {return labels.zAxis;}
        inline QString CaptionLabel(void) {return labels.caption;}

        void updateTrace(int row, int col);

		///void setZoom(int zoomfactor);
};
#endif

//static float zoomFactor; /* Global, if you want. Modified by user input. Initially 1.0 */ 
/* A routine for setting the projection matrix. May be called from a resize event handler in a typical application. Takes integer width and height dimensions of the drawing area. Creates a projection matrix with correct aspect ratio and zoom factor. */ 
// void setProjectionMatrix (int width, int height) 
// { 
// 	glMatrixMode(GL_PROJECTION); 
// 	glLoadIdentity(); 
// 	gluPerspective (50.0*zoomFactor, (float)width/(float)height, zNear, zFar); 
// 	/* ...Where 'zNear' and 'zFar' are up to you to fill in. */ 
// } 
