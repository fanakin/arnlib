/***************************************************************************
                          arnPVINumericVariable.h  -  description
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

#ifndef ArnPVINumericVariableH
#define ArnPVINumericVariableH

#include "arnPVIVariable.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnPVINumericVariable -------------------
// ***************************************************
// ---------------------------------------------------
class arnPVINumericVariable : public arnPVIVariable
{
    Q_OBJECT

    private:
        virtual void init(void);
    protected:
		NumericRepresentationFormat_t numFormatVal;
    public:
		arnPVINumericVariable ( QObject * Opar, Q3ListView * parent );
        arnPVINumericVariable ( QObject * Opar, Q3ListViewItem *parent );
        arnPVINumericVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVINumericVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVINumericVariable ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVINumericVariable ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVINumericVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVINumericVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVINumericVariable(void);
    public slots:
		inline NumericRepresentationFormat_t getNumFormat(void) {return numFormatVal;}
		inline void setNumFormat(NumericRepresentationFormat_t nf = nrf_dec) {numFormatVal = nf;}
		void setValue(double val);
        virtual void setValue(const QString& val);
        double value(void);
		void updateValueColumn(void);
};


#endif
