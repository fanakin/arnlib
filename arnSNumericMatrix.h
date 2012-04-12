/***************************************************************************
                          arnSNumericMatrix.h  -  description
                             -------------------
    begin                : mar apr 26 2005
    copyright            : (C) 2005 by fabio giovagnini
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

#ifndef ArnSNumericMatrixH
#define ArnSNumericMatrixH

#include "arnSMatrix.h"
#include "arnSNumericArray.h"
#include "arnPVINumericArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSNumericMatrix ---------------------
// ***************************************************
// ---------------------------------------------------
class arnSNumericMatrix : public arnSMatrix
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		unsigned char prcX,prcY;
		arnSNumericArray *xAxis,*yAxis;
		double mnX, mxX;
		double mnY, mxY;
	public:
		arnSNumericMatrix ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSNumericMatrix(void);
	public slots:
		virtual int rows(void) {if (!yAxis) return NRows; else return yAxis->rows();}
		virtual int cols(void) {if (!xAxis) return NCols; else return xAxis->rows();}
		virtual void setDims(int rows, int cols);
		virtual void setValue(int row, int col, double val);
		virtual void setValue(int row, int col, const QString& val);
		virtual void setValue(int row, int col);
		inline void setXAxis(arnSNumericArray *x) {xAxis = x; NCols = xAxis->rows();}
		inline arnSNumericArray *XAxis(void) {return xAxis;}
		inline void setYAxis(arnSNumericArray *y) {yAxis = y; NRows = yAxis->rows();}
		inline arnSNumericArray *YAxis(void) {return yAxis;}
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
		double value(int row, int col);
		double valueX(int cols);
		double valueY(int rows);
		virtual inline QString XAxisCaption(void) {if (xAxis) {return QString(xAxis->name());} else {return xAxisCaption;}}
		virtual inline QString YAxisCaption(void) {if (yAxis) {return QString(yAxis->name());} else {return yAxisCaption;}}
};


#endif
