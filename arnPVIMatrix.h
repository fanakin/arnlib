/***************************************************************************
                          arnPVIMatrix.h  -  description
                             -------------------
    begin                : ven mar 18 20035
    copyright            : (C) 2003 by Aurion s.r.l.
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

#ifndef ArnPVIMatrixH
#define ArnPVIMatrixH

#include "arnPVIArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIMatrix ---------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIMatrix : public arnPVIObjectContainer
{
    Q_OBJECT

    private:
		void init(void);
    protected:
        int NRows,NCols;
        int typeTonbytes(void);
        QString yAxisCaption,xAxisCaption;
    public:
		arnPVIMatrix ( QObject * Opar, Q3ListView * parent );
		arnPVIMatrix ( QObject * Opar, Q3ListViewItem *parent );
        arnPVIMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVIMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVIMatrix ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMatrix ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVIMatrix(void);

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
		virtual inline QString ZAxisCaption(void) {return this->text(0);}
};


#endif
