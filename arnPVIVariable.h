/***************************************************************************
                          arnPVIVariable.h  -  description
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

#ifndef ArnPVIVariableH
#define ArnPVIVariableH

#include "arnPVIObjectContainer.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnPVIVariable -------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIVariable : public arnPVIObjectContainer
{
    Q_OBJECT

    private:
    protected:
        int typeTonbytes(void);
    public:
		arnPVIVariable ( QObject * Opar, Q3ListView * parent );
		arnPVIVariable ( QObject * Opar, Q3ListViewItem *parent );
		arnPVIVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
		arnPVIVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
		arnPVIVariable ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIVariable ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVIVariable(void);
    public slots:
        virtual void setValue(const QString& val) = 0;
};


#endif
