/***************************************************************************
                          arnSMiscNumericMatrix.h  -  description
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
#include <qcolor.h>

#ifndef ArnSMiscMarkNumericMatrixH
#define ArnSMiscMarkNumericMatrixH

#include "arnSMiscNumericMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscMarkNumericMatrix ---------------------
// ***************************************************
// ---------------------------------------------------
class arnSMiscMarkNumericMatrix : public arnSMiscNumericMatrix
{
	Q_OBJECT
	
	private:
		void init(void);
	protected:
		struct mark_info {
			bool marked;
			QColor color;
			mark_info(void) {marked = false; color = QColor("white");}
			};
		struct mark_info **mark;
		QColor defColor;
	signals:
		//void MarkChanged(int row, int col/*, double val*/);
	public:
		arnSMiscMarkNumericMatrix ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSMiscMarkNumericMatrix(void);
	public slots:
		virtual void setDims(int rows, int cols);
		virtual void setValueAndMark(int row, int col, double val);
		virtual void setValueAndMark(int row, int col, const QString& val);
		virtual void setValueAndMark(int row, int col);
		virtual bool isMarked(int row, int col);
		virtual void resetMark(int row, int col);
		virtual void setDefaultColor(const QColor& c);
		virtual void setColor(int row, int col, const QColor& c);
		virtual QColor Color(int row, int col);
};


#endif
