/***************************************************************************
                          arnPVIStringVariable.h  -  description
                             -------------------
    begin                : mer set 24 2003
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
#ifndef ArnPVIStringVariableH
#define ArnPVIStringVariableH

#include "arnPVIVariable.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnPVIStringVariable --------------------
// ***************************************************
// ---------------------------------------------------
class arnPVIStringVariable : public arnPVIVariable
{
    Q_OBJECT

    private:
        void init(void);
    protected:
    public:
		arnPVIStringVariable ( QObject * Opar, Q3ListView * parent );
        arnPVIStringVariable ( QObject * Opar, Q3ListViewItem *parent );
        arnPVIStringVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem *after );
        arnPVIStringVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after );
        arnPVIStringVariable ( QObject * Opar, Q3ListView *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIStringVariable ( QObject * Opar, Q3ListViewItem *parent,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIStringVariable ( QObject * Opar, Q3ListView *parent, Q3ListViewItem * after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        arnPVIStringVariable ( QObject * Opar, Q3ListViewItem *parent, Q3ListViewItem *after,
			QString label1, QString label2 = QString::null, QString label3 = QString::null,
			QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null,
			QString label7 = QString::null, QString label8 = QString::null );
        virtual ~arnPVIStringVariable(void);

    public slots:
        virtual void setValue(const QString& val);
        QString value(void);
};

#endif
