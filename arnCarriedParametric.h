/***************************************************************************
                          arnCarriedParametric.h  -  description
                             -------------------
    begin                : dom mar 9 2003
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

#ifndef ArnCarriedParametricH
#define ArnCarriedParametricH

#include "arnParametric.h"

class arnCarriedParametric : public arnParametric
{
    private:
    protected:
    public:
        arnCarriedParametric(unsigned int dim);
        arnCarriedParametric(unsigned int dim,unsigned int nSegs);
        arnCarriedParametric(unsigned int dim, arnCarrier *Mon);
        arnCarriedParametric(const arnCarriedParametric& aPar);
        virtual ~arnCarriedParametric(void);
        arnCarriedParametric& operator = (const arnCarriedParametric& aPar);
        virtual bool send(void);
        virtual bool receive(void);
};

#endif
