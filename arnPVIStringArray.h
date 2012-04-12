/***************************************************************************
                          arnPVIStringArray.h  -  description
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

#ifndef ArnPVIStringArrayH
#define ArnPVIStringArrayH

#include "arnPVIArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIStringArray -------------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIStringArray : public arnPVIArray
{
	Q_OBJECT

	private:
	protected:
		arnPVIStringArray *xAxis;
		virtual void init(void);
		int stringLength;
	public:
		arnPVIStringArray ( QObject * Opar, Q3ListView * parent );
		arnPVIStringArray ( QObject * Opar, Q3ListViewItem *parent );
		arnPVIStringArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
		arnPVIStringArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
		arnPVIStringArray ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIStringArray ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIStringArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIStringArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		virtual inline void setFormat(NumericFixedFormat_t /*ft*/) {elemformat = nff_string;}
		virtual ~arnPVIStringArray(void);
	public slots:
		inline void setStringLength(int l) {stringLength = l;}
		inline int StringLength(void) {return stringLength;}
		inline void setDims(int rows) {if (!xAxis) NRows = rows; else {NRows = xAxis->rows();}}
		inline int Dims(void) {if (!xAxis) return NRows; else return xAxis->rows();}
		inline void setXAxis(arnPVIStringArray *x) {xAxis = x;}
		inline arnPVIStringArray* XAxis(void) {return xAxis;}
		virtual void setValue(int row, const QString& val);
		virtual void setValue(int row, int col);
		QString value(int row);
		QString valueX(int row);
};

#endif
