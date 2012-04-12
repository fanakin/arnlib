/***************************************************************************
						  arnPVIStringMatrix.h  -  description
                             -------------------
    begin                : ven apr 18 2003
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

#ifndef ArnPVIStringMatrixH
#define ArnPVIStringMatrixH

#include "arnPVIMatrix.h"
#include "arnPVINumericArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIStringMatrix ---------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIStringMatrix : public arnPVIMatrix
{
    Q_OBJECT

    private:
        void init(void);
    protected:
        unsigned char prcX,prcY;
        arnPVINumericArray *xAxis,*yAxis;
        double mnX, mxX;
		double mnY, mxY;
		unsigned char valueLen;
    public:
		arnPVIStringMatrix ( QObject * Opar, Q3ListView * parent );
		arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem *parent );
		arnPVIStringMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
		arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
		arnPVIStringMatrix ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIStringMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIStringMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		virtual ~arnPVIStringMatrix(void);

    public slots:
        virtual int rows(void) {if (!yAxis) return NRows; else return yAxis->rows();}
        virtual int cols(void) {if (!xAxis) return NCols; else return xAxis->rows();}
        virtual void setDims(int rows, int cols);
        virtual void setValue(int row, int col, const QString& val);
		virtual inline void setValue(int , int , double ) {;}
		virtual void setValue(int row, int col);
		inline void setValueLen(unsigned char len) {valueLen = len;}
		inline unsigned char ValueLen(void) {return valueLen;}
		inline void setXAxis(arnPVINumericArray *x) {xAxis = x; NCols = xAxis->rows();}
        inline arnPVINumericArray *XAxis(void) {return xAxis;}
        inline void setYAxis(arnPVINumericArray *y) {yAxis = y; NRows = yAxis->rows();}
        inline arnPVINumericArray *YAxis(void) {return yAxis;}
        inline void setPrecX(unsigned char pc) {if (!xAxis) prcX = pc;}
        inline void setPrecY(unsigned char pc) {if (!yAxis) prcY = pc;}
        inline unsigned char precX(void) {if (xAxis) return xAxis->prec(); return prcX;}
        inline unsigned char precY(void) {if (yAxis) return yAxis->prec(); return prcY;}
        inline void setMinX(double v) {mnX = v; xAxis = 0;}
        inline void setMaxX(double v) {mxX = v; xAxis = 0;}
        inline double minX(void) {return mnX;}
        inline double maxX(void) {return mxX;}
        inline void setMinY(double v) {mnY = v; yAxis = 0;}
        inline void setMaxY(double v) {mxY = v; yAxis = 0;}
        inline double minY(void) {return mnY;}
        inline double maxY(void) {return mxY;}
		const QString value(int row, int col);
        double valueX(int cols);
        double valueY(int rows);
		virtual inline QString XAxisCaption(void) {if (xAxis) {return xAxis->text(0);} else {return xAxisCaption;}}
		virtual inline QString YAxisCaption(void) {if (yAxis) {return yAxis->text(0);} else {return yAxisCaption;}}

		inline NumericRepresentationFormat_t getXNumFormat(void) {
			if (xAxis) return xAxis->getNumFormat();
			else return nrf_dec;
		}
		inline NumericRepresentationFormat_t getYNumFormat(void) {
			if (yAxis) return yAxis->getNumFormat();
			else return nrf_dec;
		}
};


#endif
