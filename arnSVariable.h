/***************************************************************************
                          arnSVariable.h  -  description
                             -------------------
    begin                : mar apr 26 2005
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

#ifndef ArnSVariableH
#define ArnSVariableH

#include "arnSObjectContainer.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnSVariable -------------------
// ***************************************************
// ---------------------------------------------------
class arnSVariable : public arnSObjectContainer
{
	Q_OBJECT
	private:
		void init(void);
	protected:
		int typeTonbytes(void);
	public:
		arnSVariable ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSVariable(void);
	public slots:
		virtual void setValue(const QString& val) = 0;
};


#endif
