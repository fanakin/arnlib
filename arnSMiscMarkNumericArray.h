/***************************************************************************
                          arnSMiscMarkNumericArray.h  -  description
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

#ifndef ArnSMiscMarkNumericArrayH
#define ArnSMiscMarkNumericArrayH

#include "arnSMiscNumericArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscMarkNumericArray ----------------------
// ***************************************************
// ---------------------------------------------------
class arnSMiscMarkNumericArray : public arnSMiscNumericArray
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		struct mark_info {
			bool marked;
			QColor color;
			mark_info(void) {marked = false; color = QColor("black");}
			};
		struct mark_info *mark;
		QColor defColor;
	public:
		arnSMiscMarkNumericArray ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSMiscMarkNumericArray(void);
	public slots:
		virtual void setDims(int rows);
		virtual void setValueAndMark(int row, double val);
		virtual void setValueAndMark(int row, const QString& val);
		virtual void setValueAndMark(int row);
		virtual bool isMarked(int row);
		virtual void resetMark(int row);
		virtual void setDefaultColor(const QColor& c);
		virtual void setColor(int row, const QColor& c);
		virtual QColor Color(int row);
	};

#endif
