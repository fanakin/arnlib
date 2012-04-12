/***************************************************************************
                          arnSStringArray.h  -  description
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

#ifndef ArnSStringArrayH
#define ArnSStringArrayH

#include "arnSArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSStringArray -------------------------
// ***************************************************
// ---------------------------------------------------
class arnSStringArray : public arnSArray
{
	Q_OBJECT
	private:
	protected:
		arnSStringArray *xAxis;
		virtual void init(void);
		int stringLength;
	public:
		arnSStringArray ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSStringArray(void);
		virtual inline void setFormat(NumericFixedFormat_t /*ft*/) {elemformat = nff_string;}
	public slots:
		inline void setStringLength(int l) {stringLength = l;}
		inline int StringLength(void) {return stringLength;}
		inline void setDims(int rows) {if (!xAxis) NRows = rows; else {NRows = xAxis->rows();}}
		inline int Dims(void) {if (!xAxis) return NRows; else return xAxis->rows();}
		inline void setXAxis(arnSStringArray *x) {xAxis = x;}
		inline arnSStringArray* XAxis(void) {return xAxis;}
		virtual void setValue(int row, const QString& val);
		virtual void setValue(int row, int col);
		QString value(int row);
		QString valueX(int row);
};

#endif
