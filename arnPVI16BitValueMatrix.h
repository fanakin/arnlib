/***************************************************************************
                          arnPVI16BitValueMatrix.h  -  description
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

#ifndef ArnPVI16BitValueMatrixH
#define ArnPVI16BitValueMatrixH
#include "arnPVINumericArray.h"
#include "arnPVIMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVI16BitValueMatrix ---------------------
// ***************************************************
// ---------------------------------------------------

class arnPVI16BitValueMatrix : public arnPVIMatrix
{
	Q_OBJECT

	private:
		void init(void);
	protected:
		union _BITFIELD {
			unsigned short BYTE;
			struct {
				unsigned short B15 : 1;
				unsigned short B14 : 1;
				unsigned short B13 : 1;
				unsigned short B12 : 1;
				unsigned short B11 : 1;
				unsigned short B10 : 1;
				unsigned short B9 : 1;
				unsigned short B8 : 1;
				unsigned short B7 : 1;
				unsigned short B6 : 1;
				unsigned short B5 : 1;
				unsigned short B4 : 1;
				unsigned short B3 : 1;
				unsigned short B2 : 1;
				unsigned short B1 : 1;
				unsigned short B0 : 1;
				} BIT;
			};
		arnPVINumericArray *yAxis;
		unsigned char prcY;
		double mnY, mxY;
		NumericRepresentationFormat_t numFormatVal;
	public:
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListView * parent );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		arnPVI16BitValueMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
		virtual ~arnPVI16BitValueMatrix(void);
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
