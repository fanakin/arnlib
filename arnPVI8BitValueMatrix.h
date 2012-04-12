/***************************************************************************
                          arnPVI8BitValueMatrix.h  -  description
                             -------------------
    begin                : lun mag 26 2008
    copyright            : (C) 2008 by Aurion s.r.l.
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

#ifndef ArnPVI8BitValueMatrixH
#define ArnPVI8BitValueMatrixH
#include "arnPVINumericArray.h"
#include "arnPVIMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVI8BitValueMatrix ---------------------
// ***************************************************
// ---------------------------------------------------

class arnPVI8BitValueMatrix : public arnPVIMatrix
{
	Q_OBJECT

	private:
		void init(void);
	protected:
		union _BITFIELD {
			unsigned char BYTE;
			struct {
				unsigned char B7 : 1;
				unsigned char B6 : 1;
				unsigned char B5 : 1;
				unsigned char B4 : 1;
				unsigned char B3 : 1;
				unsigned char B2 : 1;
				unsigned char B1 : 1;
				unsigned char B0 : 1;
				} BIT;
			};
		arnPVINumericArray *yAxis;
		unsigned char prcY;
		double mnY, mxY;
		NumericRepresentationFormat_t numFormatVal;
	public:
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView * parent );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVI8BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		virtual ~arnPVI8BitValueMatrix(void);
	public slots:
		virtual inline int cols(void) {return NCols;}
		virtual inline int rows(void) {return NRows;}
		virtual void setDims(int rows, int cols);
		virtual void setValue(int row, int col, double val);
		virtual void setValue(int row, int col, const QString& val);
		virtual void setValue(int row, int col);
		virtual double value(int row, int col);
		inline void setYAxis(arnPVINumericArray *y) {yAxis = y; NRows = yAxis->rows();}
		inline arnPVINumericArray *YAxis(void) {return yAxis;}
		inline void setPrecY(unsigned char pc) {if (!yAxis) prcY = pc;}
		inline unsigned char precY(void) {if (yAxis) return yAxis->prec(); return prcY;}
		inline void setMinY(double v) {mnY = v; yAxis = 0;}
		inline void setMaxY(double v) {mxY = v; yAxis = 0;}
		inline double minY(void) {return mnY;}
		inline double maxY(void) {return mxY;}
		double valueX(int cols);
		double valueY(int rows);
		virtual inline QString XAxisCaption(void) {return xAxisCaption;}
		virtual inline QString YAxisCaption(void) {if (yAxis) {return yAxis->text(0);} else {return yAxisCaption;}}
		inline NumericRepresentationFormat_t getNumFormat(void) {return numFormatVal;}
		inline void setNumFormat(NumericRepresentationFormat_t nf = nrf_dec) {numFormatVal = nf;}
		inline NumericRepresentationFormat_t getYNumFormat(void) {
			if (yAxis) return yAxis->getNumFormat();
			else return nrf_dec;
		}
};


#endif
