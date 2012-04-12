/***************************************************************************
                          arnPVIArray.h  -  description
                             -------------------
    begin                : ven mar 18 2005
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

#ifndef ArnPVIArrayH
#define ArnPVIArrayH

#include "arnPVIObjectContainer.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIArray ----------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIArray : public arnPVIObjectContainer
{
    Q_OBJECT

    private:
		void init(void);
    protected:
        int NRows;
        int typeTonbytes(void);
		QString xAxisCaption;
    public:
		arnPVIArray ( QObject * Opar, Q3ListView * parent );
        arnPVIArray ( QObject * Opar, Q3ListViewItem *parent );
        arnPVIArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVIArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVIArray ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
				QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
				QString label7 = QString::null, QString label8 = QString::null );
        arnPVIArray ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVIArray(void);
    public slots:
		inline int rows(void) {return NRows;}
        virtual void setDims(int rows) = 0;
        virtual int Dims(void) = 0;
        virtual void setValue(int row, double val)  = 0;
        virtual void setValue(int row, const QString& val)  = 0;
        virtual void setValue(int row,int col) = 0;
		virtual inline void setXAxisCaption(const QString& xc) {xAxisCaption = xc;}
		virtual inline QString XAxisCaption(void) {return xAxisCaption;}
		virtual inline QString YAxisCaption(void) {return this->text(0);}

};

#endif
