/***************************************************************************
                          arnSNumericVariable.h  -  description
                             -------------------
    begin                : mar apr 26 2005
    copyright            : (C) 2005 by fabio giovagnini
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

#ifndef ArnSNumericVariableH
#define ArnSNumericVariableH

#include "arnSVariable.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSNumericVariable -------------------
// ***************************************************
// ---------------------------------------------------
class arnSNumericVariable : public arnSVariable
{
	Q_OBJECT
	private:
		virtual void init(void);
	protected:
	public:
		arnSNumericVariable ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSNumericVariable(void);
	public slots:
		void setValue(double val);
		virtual void setValue(const QString& val);
		double value(void);
};


#endif
