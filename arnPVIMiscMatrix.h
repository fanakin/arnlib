/***************************************************************************
                          arnPVIMiscMatrix.h  -  description
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

#ifndef ArnPVIMiscMatrixH
#define ArnPVIMiscMatrixH

#include "arnPVIMatrix.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIMiscMatrix ---------------------
// ***************************************************
// ---------------------------------------------------

class arnPVIMiscMatrix : public arnPVIMatrix
{
	Q_OBJECT

	private:
		void init(void);
	protected:
		unsigned char prcY;
		//arnPVINumericArray *xAxis,*yAxis;
		double mnY, mxY;
		unsigned char *prcCol;
		double *mnCol,*mxCol;
		QStringList XVals;
		void evalPrec(int col);
		NumericRepresentationFormat_t numFormatVal;
	public:
		arnPVIMiscMatrix ( QObject * Opar, Q3ListView * parent );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem *parent );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIMiscMatrix ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVIMiscMatrix(void);

    public slots:
        virtual inline int cols(void) {return NCols;}
        virtual inline int rows(void) {return NRows;}
        virtual void setDims(int rows, int cols);
        virtual void setValue(int row, int col, double val);
        virtual void setValue(int row, int col, const QString& val);
        virtual void setValue(int row, int col);
        inline void setPrecY(unsigned char pc) {prcY = pc;}
        inline unsigned char precY(void) {return prcY;}
        inline void setMinY(double v) {mnY = v;}
        inline void setMaxY(double v) {mxY = v;}
        inline double minY(void) {return mnY;}
        inline double maxY(void) {return mxY;}
        void setMinCol(int col, double v);
        void setMaxCol(int col, double v);
        inline double minCol(int col) {return ((col < NCols) ?  mnCol[col] : (NRows - 1));}
        inline double maxCol(int col) {return ((col < NCols) ? mxCol[col] : (NRows -1));}
        inline void setPrecCol(int col,unsigned char pc) {if (col < NCols) { prcCol[col] = pc;}}
        inline unsigned char PrecCol(int col) {return ((col < NCols) ?  prcCol[col] : (0));}
        double value(int row, int col);
        QString valueX(int cols);
        double valueY(int rows);
		void setValueX(int col, QString value);
		inline NumericRepresentationFormat_t getNumFormat(void) {return numFormatVal;}
		inline void setNumFormat(NumericRepresentationFormat_t nf = nrf_dec) {numFormatVal = nf;}
		inline NumericRepresentationFormat_t getYNumFormat(void) {
			/*if (yAxis) return yAxis->getNumFormat();
			else*/ return nrf_dec;
		}
};


#endif
