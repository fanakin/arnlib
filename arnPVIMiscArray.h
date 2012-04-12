/***************************************************************************
                          arnPVIMiscArray.h  -  description
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

#ifndef ArnPVIMiscArrayH
#define ArnPVIMiscArrayH

#include "arnPVIArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIMiscArray ----------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIMiscArray : public arnPVIArray
{
    Q_OBJECT

    private:
        void init(void);
    protected:
        unsigned char prcX;
        arnPVIMiscArray *xAxis;
        double mnX, mxX;
    public:
		arnPVIMiscArray ( QObject * Opar, Q3ListView * parent );
        arnPVIMiscArray ( QObject * Opar, Q3ListViewItem *parent );
        arnPVIMiscArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVIMiscArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVIMiscArray ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMiscArray ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMiscArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMiscArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVIMiscArray(void);

    public slots:
        virtual inline void setDims(int rows) {if (!xAxis) NRows = rows; else NRows = xAxis->rows();mnX = 0; mxX = NRows - 1;}
        virtual inline int Dims(void) {if (!xAxis) return NRows; else return xAxis->rows();}
        inline void setXAxis(arnPVIMiscArray *x) {xAxis = x; mnX = xAxis->min(); mxX = xAxis->max();}
        inline arnPVIMiscArray *XAxis(void) {return xAxis;}
        inline void setPrecX(unsigned char pc) {if (!xAxis) prcX = pc;}
        inline unsigned char precX(void) {if (xAxis) return xAxis->prec(); return prcX;}
        inline void setMinX(double v) {mnX = v; xAxis = 0;}
        inline void setMaxX(double v) {mxX = v; xAxis = 0;}
        inline double minX(void) {return mnX;}
        inline double maxX(void) {return mxX;}
        virtual void setValue(int row, double val);
        virtual void setValue(int row, const QString& val);
        virtual void setValue(int row,int col);
        double valueX(int row);
        double value(int row);
        
};

#endif
