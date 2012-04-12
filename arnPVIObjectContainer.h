/***************************************************************************
                          arnPVIObjectContainer.h  -  description
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

#ifndef ArnPVIObjectContainerH
#define ArnPVIObjectContainerH

#include <arnObjectViewer.h>
#include "arnParametric.h"
#include "arnParViewItem.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIObjectContainer -------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIObjectContainer : public arnParViewItem
{
	Q_OBJECT

	private:
		void init(void);
	protected:
		NumericFixedFormat_t elemformat;
		NumericProcess_t filterT;
		unsigned char prc;
		unsigned long offst;
		unsigned long sze;
		double mn;
		double mx;
		double flr;
		double cil;
		arnParametric *plowDevice;
		arnObjectViewer *pViewer;
		QString Comment;

		virtual void evalPrec(void);
		virtual double checkValue(double val);
	public:
		arnPVIObjectContainer ( QObject * Opar , Q3ListView * parent );
		arnPVIObjectContainer ( QObject * Opar , Q3ListViewItem *parent );
		arnPVIObjectContainer ( QObject * Opar , Q3ListView *parent, Q3ListViewItem *after );
		arnPVIObjectContainer ( QObject * Opar , Q3ListViewItem *parent, Q3ListViewItem *after );
		arnPVIObjectContainer ( QObject * Opar , Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIObjectContainer ( QObject * Opar , Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIObjectContainer ( QObject * Opar , Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVIObjectContainer ( QObject * Opar , Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		virtual ~arnPVIObjectContainer(void);
		virtual inline void setViewer(arnObjectViewer *pV) {pViewer = pV;}
		virtual inline void setFilterType(NumericProcess_t f) {filterT = f;}
		virtual inline void setComment(const QString& cm) {Comment = cm;}
		virtual inline void setFormat(NumericFixedFormat_t ft) {elemformat = ft;}
		inline void setOffset(unsigned long offs) {offst = offs;}
		inline unsigned long offset(void) {return offst;}
		inline void setSize(unsigned long sz) {sze = sz;}
		inline unsigned long size(void) {return sze;}
		inline double min(void) {return mn;}
		inline double max(void) {return mx;}
		inline double floor(void) {return flr;}
		inline double ceil(void) {return cil;}
		inline NumericProcess_t filterType(void) {return filterT;}
		inline void setLowDevice(arnParametric *plD) {plowDevice = plD;}
		inline const arnParametric* LowDevice(void) {return plowDevice;}
		inline const QString& comment(void) {return Comment;}
		inline NumericFixedFormat_t format(void) {return elemformat;}
		inline unsigned char prec(void) {return prc;}
		inline void setPrec(unsigned char pc) {prc = pc;}
		void setMin(double m);
		void setMax(double m);
		void setFloor(double f);
		void setCeil(double c);
};

#endif

// Q3ListViewItem ( Q3ListView * parent )
// Q3ListViewItem ( Q3ListViewItem * parent )
// Q3ListViewItem ( Q3ListView * parent, Q3ListViewItem * after )
// Q3ListViewItem ( Q3ListViewItem * parent, Q3ListViewItem * after )
// Q3ListViewItem ( Q3ListView * parent, QString label1, QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null )
// Q3ListViewItem ( Q3ListViewItem * parent, QString label1, QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null )
// Q3ListViewItem ( Q3ListView * parent, Q3ListViewItem * after, QString label1, QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null )
// Q3ListViewItem ( Q3ListViewItem * parent, Q3ListViewItem * after, QString label1, QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null )
