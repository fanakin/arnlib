/***************************************************************************
                          arnPVINumericArray.h  -  description
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

#ifndef ArnPVINumericArrayH
#define ArnPVINumericArrayH

#include "arnPVIArray.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVINumericArray ----------------------
// ***************************************************
// ---------------------------------------------------
class arnPVINumericArray : public arnPVIArray
{
    Q_OBJECT

    private:
        void init(void);
    protected:
        unsigned char prcX;
        arnPVINumericArray *xAxis;
        double mnX, mxX;
		NumericRepresentationFormat_t numFormatVal;
		//NumericRepresentationFormat_t numFormatX;
   public:
		arnPVINumericArray ( QObject * Opar, Q3ListView * parent );
        arnPVINumericArray ( QObject * Opar, Q3ListViewItem *parent );
        arnPVINumericArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVINumericArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVINumericArray ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVINumericArray ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVINumericArray ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVINumericArray ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVINumericArray(void);

    public slots:
		inline NumericRepresentationFormat_t getNumFormat(void) {return numFormatVal;}
		inline void setNumFormat(NumericRepresentationFormat_t nf = nrf_dec) {numFormatVal = nf;}
		inline NumericRepresentationFormat_t getXNumFormat(void) {
			if (xAxis) return xAxis->getNumFormat();
			else return nrf_dec;
		}
		//inline void setXNumFormat(NumericRepresentationFormat_t nf = nrf_dec) {numFormatX = nf;}
		virtual inline void setDims(int rows) {if (!xAxis) NRows = rows; else NRows = xAxis->rows();mnX = 0; mxX = NRows - 1;}
        virtual inline int Dims(void) {if (!xAxis) return NRows; else return xAxis->rows();}
        inline void setXAxis(arnPVINumericArray *x) {xAxis = x; mnX = xAxis->min(); mxX = xAxis->max();}
        inline arnPVINumericArray *XAxis(void) {return xAxis;}
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
		virtual inline QString XAxisCaption(void) {if (xAxis) {return xAxis->text(0);} else {return xAxisCaption;}}
        
};

#endif
