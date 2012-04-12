/***************************************************************************
                          arnqlabel.cpp  -  description
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

#include "arnqlabel.h"
#include <QtDebug>

arnQLabel::arnQLabel( QWidget *parent, const char* name, Qt::WFlags f )
    : QLabel(parent, name, f)
{
    numericSize = nff_none;
}
arnQLabel::arnQLabel( const QString &text, QWidget *parent, const char* name, Qt::WFlags f)
    : QLabel(text, parent, name, f)
{
    numericSize = nff_none;
}
arnQLabel::arnQLabel( QWidget *buddy, const QString &text,QWidget *parent, const char* name , Qt::WFlags f )
    : QLabel(buddy, text, parent, name, f)
{
    numericSize = nff_none;
}

arnQLabel::~arnQLabel()
{
}

void arnQLabel::setNum( int val)
{
    QString str;
    double scalval;

    switch (numericSize) {
        case nff_u8 :
            scalval = (double) ((((max - min) * ((double)val)) / 255 ) + min);
            str.setNum(scalval,format,prec);
            break;
        case nff_u16 :
            scalval = (double) ((((max - min) * ((double)val)) / 65535 ) + min);
            str.setNum(scalval,format,prec);
            break;
        case nff_u32 :
            scalval = (double) ((((max - min) * ((double)val)) / ((unsigned long)0xffffffff) ) + min);
            str.setNum(scalval,format,prec);
            break;
        case nff_s8 :
            scalval = (double) ((((max - min) * ((double)val + 127)) / 255 ) + min);
            str.setNum(scalval,format,prec);
            break;
        case nff_s16 :
            scalval = (double) ((((max - min) * ((double)val + 32768)) / 65535 ) + min);
            str.setNum(scalval,format,prec);
            break;
        case nff_s32 :
            scalval = (double) ((((max - min) * ((double)val + 2147483648.0)) / ((unsigned long)0xffffffff) ) + min);
            str.setNum(scalval,format,prec);
            break;
        default :
            str.setNum(val);
            break;
        }
    setText(str);
}
