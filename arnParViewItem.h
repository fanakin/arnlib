/***************************************************************************
                          arnParViewItem.h  -  description
                             -------------------
    begin                : mer apr 16 2003
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

#ifndef ArnParViewItemH
#define ArnParViewItemH

//#include "kpartypes.h"
#include <Q3ListViewItem>
//#include "arnParametric.h"
#include "arnlibtypes.h"

typedef enum arnParType {
    apt_ObjectContainer,
    apt_NumericVariable,
    apt_StringVariable,
    apt_NumericArray,
    apt_StringArray,
    apt_MiscArray,
    apt_NumericMatrix,
    apt_MiscMatrix,
    apt_8BitValueMatrix,
    apt_8BitExpandValueMatrix,
    apt_16BitValueMatrix,
	apt_StringMatrix,
    apt_None
    } arnParType_t;

// ---------------------------------------------------
// ***************************************************
// --------- arnParViewItem --------------------------
// ***************************************************
// ---------------------------------------------------
class arnParViewItem : public QObject, public Q3ListViewItem
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		arnParType_t tpe;
		QColor currcolor;
	public:
	arnParViewItem ( QObject * Opar , Q3ListView * parent );
	arnParViewItem ( QObject * Opar , Q3ListViewItem * parent );
	arnParViewItem ( QObject * Opar , Q3ListView * parent, Q3ListViewItem * after );
	arnParViewItem ( QObject * Opar , Q3ListViewItem * parent, Q3ListViewItem * after );
	arnParViewItem ( QObject * Opar ,Q3ListView * parent,
		QString label1, QString label2 = QString::null, QString label3 = QString::null,
		QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
		QString label7 = QString::null, QString label8 = QString::null );
	arnParViewItem ( QObject * Opar , Q3ListViewItem * parent,
		QString label1, QString label2 = QString::null, QString label3 = QString::null,
		QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
		QString label7 = QString::null, QString label8 = QString::null );
	arnParViewItem ( QObject * Opar , Q3ListView * parent, Q3ListViewItem * after,
		QString label1, QString label2 = QString::null, QString label3 = QString::null,
		QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
		QString label7 = QString::null, QString label8 = QString::null );
	arnParViewItem ( QObject * Opar , Q3ListViewItem * parent, Q3ListViewItem * after,
		QString label1, QString label2 = QString::null, QString label3 = QString::null,
		QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
		QString label7 = QString::null, QString label8 = QString::null );
	virtual ~arnParViewItem(void);
    inline arnParType_t type(void) {return tpe;}
	virtual void paintCell( QPainter * p, const QColorGroup &cg, int column, int width, int align);
    //inline void setType(arnParType_t tp) {tpe = tp;}
	inline void setTextColor(const QColor& cl) {currcolor = cl;}
};


#endif
