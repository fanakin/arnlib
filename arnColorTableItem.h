/***************************************************************************
                          arnColorTableItem.h  -  description
                             -------------------
    begin                : mar giu 28 2005
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

#ifndef ArnColorTableItemH
#define ArnColorTableItemH

#include <Q3Table>

class arnColorTableItem : public Q3TableItem
{
	private:
	protected:
		QColor color_;
		virtual void paint ( QPainter * p, const QColorGroup & cg, const QRect & cr, bool selected ) {
			QColorGroup g(cg);
			g.setColor( QColorGroup::Base, color_ );
			Q3TableItem::paint(p,g,cr,selected);
			}
	public:
		arnColorTableItem ( Q3Table * table, EditType et, const QColor & c = QColor("white") ) :
			Q3TableItem (table, et, "") {color_ = c;}
		arnColorTableItem ( Q3Table * table, EditType et, const QString & text, const QColor & c = QColor("white")) :
			Q3TableItem (table, et, text) {color_ = c;}
		arnColorTableItem ( Q3Table * table, EditType et, const QString & text, const QPixmap & p,const QColor & c = QColor("white")):
			Q3TableItem (table, et, text, p) {color_ = c;}
		virtual ~arnColorTableItem(void) {}
		virtual inline void setColor(const QColor& c) {color_ = c;}
		virtual inline QColor Color(void) {return color_;}
};

#endif
