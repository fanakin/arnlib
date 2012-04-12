/***************************************************************************
                          arnGLArray.h  -  description
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

#ifndef ArnGLArrayH
#define ArnGLArrayH

#include <qstring.h>
#include <qgl.h>
#include "CommonFunctions.h"
#include "arnGLVector.h"


class arnGLArray : public QGLWidget
{
    Q_OBJECT

    private:
        arnGLArrayPaintingMode_t mde;

        GLuint object,selection;
//        GLfloat sxRot,xRot;
//        GLfloat syRot, yRot;
//        GLfloat szRot, zRot;
        GLfloat scle;
        struct ScalingExtreme {
            GLfloat value;
            bool set;
            };
        struct ScalingExtreme minCol,maxCol,minTab,maxTab;

        struct {
            QString xAxis;
            QString yAxis;
            QString caption;
            } labels;

        arnGLVector *pDataVector, *pVisVector;
        int sSelRow, eSelRow;
        void initDefaultParamsForVis(void);
        void drawText(void);
        void drawLabels(void);
        void processHits (GLint hits, GLuint buffer[],int* row);
    private slots:

    protected:
    	bool zoomEn;
        virtual GLuint makeObject(void);
        virtual GLint makeObjectforselection(GLint x, GLint y,int* row); // return hits
        virtual GLuint makeSelection(int srow, int erow);
        virtual void initializeGL();
        virtual void resizeGL (int width, int height);
        virtual void paintGL();
        virtual void mousePressEvent ( QMouseEvent *e );
        virtual void mouseMoveEvent ( QMouseEvent *e );
        virtual void mouseReleaseEvent ( QMouseEvent *e );
        virtual void keyReleaseEvent (  QKeyEvent *e );
    protected slots:

    signals:
    //	void valueChanged(int col, double val);
    	void selectionChanged(int start_row, int end_row);
     
    public :
        arnGLArray(arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES, QWidget* parent = 0, const char * name = 0, const QGLWidget* shareWidget = 0, Qt::WFlags f = 0);
        arnGLArray (const QGLFormat& format, arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES, QWidget* parent = 0, const char* name = 0, const QGLWidget* shareWidget = 0,Qt::WFlags f = 0);
        arnGLArray( int Cols = 5, arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES, QWidget* parent = 0, const char * name = 0, const QGLWidget* shareWidget = 0, Qt::WFlags f = 0);
        arnGLArray (const QGLFormat& format, int Cols = 5, arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES, QWidget* parent = 0, const char* name = 0, const QGLWidget* shareWidget = 0,Qt::WFlags f = 0);
        ~arnGLArray(void);

        void setMode (arnGLArrayPaintingMode_t md);
        inline arnGLArrayPaintingMode_t mode (void) {return mde;}
        inline void setZoomEnabled(bool v) {zoomEn = v;}
        inline bool zoomEnabled(void) {return zoomEn;}

    public slots:
        void setColValue( int col, QString& val);
        void setColValue( int col, double val);
        void setValue(int col, QString& val);
        void setValue(int col, double val);

        void setColMinScale(QString& val);
        void setColMinScale(double val);
        void setColMaxScale(QString& val);
        void setColMaxScale(double val);
        void setTableMinScale(QString& val);
        void setTableMinScale(double val);
        void setTableMaxScale(QString& val);
        void setTableMaxScale(double val);

        double value(int col);
        QString text(int col);

//        void setXRotation( int degrees );
//        void setYRotation( int degrees );
//        void setZRotation( int degrees );

        inline void setXAxisLabel(const QString& str) {labels.xAxis = str;}
        inline void setYAxisLabel(const QString& str) {labels.yAxis = str;}
        inline void setCaptionLabel(const QString& str) {labels.caption = str;}
        inline QString XAxisLabel(void) {return labels.xAxis;}
        inline QString YAxisLabel(void) {return labels.yAxis;}
        inline QString CaptionLabel(void) {return labels.caption;}

        void invalidate(void);

        inline double ColMinScale(void) {return ((minCol.set == true) ? minCol.value : pDataVector->minCol());}
        inline double ColMaxScale(void) {return ((maxCol.set == true) ? maxCol.value : pDataVector->maxCol());}
        inline double TableMinScale(void) {return ((minTab.set == true) ? minTab.value : pDataVector->minTable());}
        inline double TableMaxScale(void) {return ((maxTab.set == true) ? maxTab.value : pDataVector->maxTable());}

};


#endif
