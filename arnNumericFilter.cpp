/***************************************************************************
                          arnNumericFilter.cpp  -  description
                             -------------------
    begin                : gio mar 6 2003
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
#include <stdio.h> // requirend only by toRawxxxx functions; better check needed
#include <math.h> // requirend only by toRawxxxx functions; better check needed
#include "CommonFunctions.h"
#include "arnNumericFilter.h"

arnNumericFilter::arnNumericFilter(void)
{
}

arnNumericFilter::~arnNumericFilter(void)
{
}

double arnNumericFilter::linear(unsigned char val, double min, double max)
{
    return (double) ((((max - min) / 255.0) * val) + min);
}

double arnNumericFilter::linear(unsigned short val, double min, double max)
{
    return (double) ((((max - min) / 65535.0) * val) + min);
}

double arnNumericFilter::linear(unsigned long val, double min, double max)
{
    return (double) ((((max - min) / (2147483647.0 + 2147483648.0)) * val) + min);
}

double arnNumericFilter::linear(signed char val, double min, double max)
{
    return (double) ((((max - min) / 255.0) * (val + 128.0)) + min);
}

double arnNumericFilter::linear(signed short val, double min, double max)
{
    return (double) ((((max - min) / 65535.0) * (val + 32768.0)) + min);
}

double arnNumericFilter::linear(signed long val, double min, double max)
{
    return (double) ((((max - min) / (2147483647.0 + 2147483648.0)) * (val + 2147483648.0)) + min);
}

double arnNumericFilter::polinom1(double val, double c0, double c1)
{
    double res = c0;

    res += c1 * val;
    return res;
}

double arnNumericFilter::polinom2(double val, double c0, double c1, double c2)
{
    double res = c0;

    res += c1 * val;
    res += c2 * (val * val);
    return res;
}

double arnNumericFilter::polinom3(double val, double c0, double c1, double c2, double c3)
{
    double res = c0;

    res += c1 * val;
    res += c2 * (val * val);
    res += c3 * (val * val * val);
    return res;
}

unsigned char arnNumericFilter::toRawUnsignedChar(double sclval, double sclmin, double sclmax)
{
    double t1,t2;
    char ln[64];

    t1 = ((double)(sclmax - sclmin));
    t2 = (((sclval * 255.0) / t1) - ((sclmin * 255.0) / t1));
	t2 = round(t2);
	// test test test
	//arnDebug("%g\n",t2);
    sprintf(ln,"%g",t2); // optimization truoble: going deeper.
    //arnDebug("%d\n",atoi(ln));
    return ((unsigned char)atoi(ln));
}

unsigned short arnNumericFilter::toRawUnsignedShort(double sclval, double sclmin, double sclmax)
{
    double t1,t2;
    char ln[64];

    t1 = ((double)(sclmax - sclmin));
    t2 = (((sclval * 65535.0) / t1) - ((sclmin * 65535.0) / t1));
	t2 = round(t2);
//    arnDebug("%g\n",t2);
    sprintf(ln,"%g",t2); // optimization truoble: going deeper.
//    arnDebug("%d\n",atoi(ln));
    return ((unsigned short)atoi(ln));
}

unsigned long arnNumericFilter::toRawUnsignedLong(double sclval, double sclmin, double sclmax)
{
    double t1,t2;
    char ln[64];

    t1 = ((double)(sclmax - sclmin));
    t2 = (((sclval * (2147483647.0 + 2147483648.0)) / t1) - ((sclmin * (2147483647.0 + 2147483648.0)) / t1));
	t2 = round(t2);
    sprintf(ln,"%g",t2); // optimization truoble: going deeper.
    return ((unsigned long)atoi(ln));
}

signed char arnNumericFilter::toRawSignedChar(double sclval, double sclmin, double sclmax)
{
    double t1,t2,t3,x1;
    double res;
    char ln[64];

    x1 = -128.0;
    t1 = ((double)(sclmax - sclmin)); // y2 -y1
    t2 = (255.0); // x2 - x1
    t3 = ((double)(sclval - sclmin));
    res = ((t2 / t1) * t3) + x1;
	res = round(res);
    sprintf(ln,"%g",res); // optimization truoble: going deeper.
    return ((signed char)atoi(ln));
}

signed short arnNumericFilter::toRawSignedShort(double sclval, double sclmin, double sclmax)
{
    double t1,t2,t3,x1;
    double res;
    char ln[64];

    x1 = -32768.0;
    t1 = ((double)(sclmax - sclmin)); // y2 -y1
    t2 = (65535.0); // x2 - x1
    t3 = ((double)(sclval - sclmin)); // y - y1
    res = ((t2 / t1) * t3) + x1;
	res = round(res);
    sprintf(ln,"%g",res); // optimization truoble: going deeper.
    return ((signed short)atoi(ln));
}

signed long arnNumericFilter::toRawSignedLong(double sclval, double sclmin, double sclmax)
{
    double t1,t2,t3,x1;
    double res;
    char ln[64];

    x1 = -2147483648.0;
    t1 = ((double)(sclmax - sclmin)); // y2 -y1
    t2 = (2147483647.0 + 2147483648.0); // x2 - x1
    t3 = ((double)(sclval - sclmin)); // y - y1
    res = ((t2 / t1) * t3) + x1;
	res = round(res);
    sprintf(ln,"%g",res); // optimization truoble: going deeper.
    return ((signed long)atoi(ln));
}
