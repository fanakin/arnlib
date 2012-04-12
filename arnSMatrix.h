/***************************************************************************
                          arnSMatrix.h  -  description
                             -------------------
    begin                : mar apr 26 2005
    copyright            : (C) 2005 by Aurion s.r.l.
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

#ifndef ArnSMatrixH
#define ArnSMatrixH

#include "arnSArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMatrix ---------------------
// ***************************************************
// ---------------------------------------------------
class arnSMatrix : public arnSObjectContainer
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		int NRows,NCols;
		int typeTonbytes(void);
		QString yAxisCaption,xAxisCaption;
	public:
		arnSMatrix ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSMatrix(void);
	public slots:
		virtual int rows(void) = 0;
		virtual int cols(void) = 0;
		virtual void setDims(int rows, int cols) = 0;
		virtual void setValue(int row, int col, double val) = 0;
		virtual void setValue(int row, int col, const QString& val) = 0;
		virtual void setValue(int row, int col) = 0;
		virtual inline void setXAxisCaption(const QString& xc) {xAxisCaption = xc;}
		virtual inline void setYAxisCaption(const QString& yc) {yAxisCaption = yc;}
		virtual inline QString XAxisCaption(void) {return xAxisCaption;}
		virtual inline QString YAxisCaption(void) {return yAxisCaption;}
		virtual inline QString ZAxisCaption(void) {return QString(this->name());}
};


#endif
