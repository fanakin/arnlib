/***************************************************************************
                          arnSArray.h  -  description
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

#ifndef ArnSArrayH
#define ArnSArrayH

#include "arnSObjectContainer.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSArray ----------------------
// ***************************************************
// ---------------------------------------------------
class arnSArray : public arnSObjectContainer
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		int NRows;
		int typeTonbytes(void);
		QString xAxisCaption;
	public:
		arnSArray ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSArray(void);
	public slots:
		inline int rows(void) {return NRows;}
		virtual void setDims(int rows) = 0;
		virtual int Dims(void) = 0;
		virtual void setValue(int row, double val)  = 0;
		virtual void setValue(int row, const QString& val)  = 0;
		virtual void setValue(int row,int col) = 0;
		virtual inline void setXAxisCaption(const QString& xc) {xAxisCaption = xc;}
		virtual inline QString XAxisCaption(void) {return xAxisCaption;}
		virtual inline QString YAxisCaption(void) {return QString(this->name());}

};

#endif
