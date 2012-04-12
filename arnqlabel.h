/***************************************************************************
                          arnqlabel.h  -  description
                             -------------------
    begin                : mar mar 4 2003
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

#ifndef ArnQLabelH
#define ArnQLabelH

#include "arnlibtypes.h"
#include <qlabel.h>


class arnQLabel : public QLabel
{
    Q_OBJECT;
    public:
        arnQLabel( QWidget *parent, const char* name=0, Qt::WFlags f=0 );
        arnQLabel( const QString &text, QWidget *parent, const char* name=0,Qt::WFlags f=0 );
        arnQLabel( QWidget *buddy, const QString &,QWidget *parent, const char* name=0, Qt::WFlags f=0 );
        ~arnQLabel();
        inline void setSize(NumericFixedFormat_t sz, char f = 'f' ,int pr = 3) {numericSize = sz; format = f; prec = pr;}
        inline void setMin(double mn) {min = mn;}
        inline void setMax(double mx) {max = mx;}
        inline double Min(void) {return min;}
        inline double Max(void) {return max;}
		inline NumericFixedFormat_t Size(void) {return numericSize;}
		inline int Prec(void) {return prec;}
    public slots:
        virtual void setNum( int );
    protected:
    private:
        NumericFixedFormat_t numericSize;
        char format;
        int prec;
        double max;
        double min;
};

#endif // ArnQLabelH
