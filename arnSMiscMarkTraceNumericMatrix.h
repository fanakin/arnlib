/***************************************************************************
                          arnSMiscMarkTraceNumericMatrix.h  -  description
                             -------------------
    begin                : lun gui 27 2005
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

#ifndef ArnSMiscMarkTraceNumericMatrixH
#define ArnSMiscMarkTraceNumericMatrixH

#include "arnSMiscMarkNumericMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscTraceNumericMatrix ---------------------
// ***************************************************
// ---------------------------------------------------

class arnSMiscMarkTraceNumericMatrix : public arnSMiscMarkNumericMatrix
{
	Q_OBJECT
	private:
	private slots:
	protected:
		virtual void init(void);
/*		struct trace_info {
			int row;
			int col;
			double value;
			trace_info(void) {row = 0; col = 0; value = 0;}
			};
		struct trace_info itrace;*/
	protected slots:
		virtual void updateMark(int row, int col);
		virtual void updateValue(int row, int col, double value);
	signals:
		void TraceChanged(int row, int col, const QColor& c);
		void MarkChanged(int row, int col, const QColor& c);
		void ValueChanged(int row, int col, double val);
	public:
		arnSMiscMarkTraceNumericMatrix ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSMiscMarkTraceNumericMatrix(void);
	public slots:
		virtual void setValueAndMark(int row, int col, double val);
		virtual void setValueAndMark(int row, int col, const QString& val);
		virtual void setValueAndMark(int row, int col);
		virtual void updateTrace(int row, int col);
};


#endif
