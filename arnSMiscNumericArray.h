/***************************************************************************
                          arnSMiscNumericArray.h  -  description
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

#ifndef ArnSMiscNumericArrayH
#define ArnSMiscNumericArrayH

#include "arnSArray.h"
#include "arnPVINumericArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscNumericArray ----------------------
// ***************************************************
// ---------------------------------------------------
class arnSMiscNumericArray : public arnSArray
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		unsigned char prcX;
		arnPVINumericArray *xAxis;
		double mnX, mxX;
	public:
		arnSMiscNumericArray ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSMiscNumericArray(void);
    public slots:
		virtual inline void setDims(int rows) {if (!xAxis) NRows = rows; else NRows = xAxis->rows();mnX = 0; mxX = NRows - 1;}
		virtual inline int Dims(void) {if (!xAxis) return NRows; else return xAxis->rows();}
		inline void setXAxis(arnPVINumericArray *x) {xAxis = x; mnX = xAxis->min(); mxX = xAxis->max();}
		inline arnPVINumericArray *XAxis(void) {return xAxis;}
		inline void setPrecX(unsigned char pc) {if (!xAxis) prcX = pc;}
		inline unsigned char precX(void) {if (xAxis) return xAxis->prec(); return prcX;}
		inline void setMinX(double v) {mnX = v; xAxis = 0;}
		inline void setMaxX(double v) {mxX = v; xAxis = 0;}
		inline double minX(void) {return mnX;}
		inline double maxX(void) {return mxX;}
		virtual void setValue(int row, double val);
		virtual void setValue(int row, const QString& val);
		virtual void setValue(int row,int col);
		double valueX(int row);
		double value(int row);
		double rawvalue(int row);
		virtual inline QString XAxisCaption(void) {if (xAxis) {return QString(xAxis->name());} else {return xAxisCaption;}}
        
};

#endif
