/***************************************************************************
                          arnMulVectorPlot.cpp  -  description
                             -------------------
    begin                : lun lug 25 2011
    copyright            : (C) 2011 by fabio giovagnini
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

#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qcolor.h>
#include <qpainter.h>
#include "CommonFunctions.h"
#include "arnMulVectorPlot.h"

arnMulVectorPlot::arnMulVectorPlot(int NumOfP,QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    NumOfPlot = NumOfP;
    if (NumOfPlot <= 0) arnCriticalExit();
    Size = new int[NumOfPlot];
    if (!Size) arnCriticalExit();
    xval = new double*[NumOfPlot];
    if (!xval) arnCriticalExit();
    yval = new double*[NumOfPlot];
    if (!yval) arnCriticalExit();
    d_curves = new QwtPlotCurve[NumOfPlot];
    if (!d_curves) arnCriticalExit();
    xMap = new QwtScaleMap[NumOfPlot];
    if (!xMap) arnCriticalExit();
    yMap = new QwtScaleMap[NumOfPlot];
    if (!yMap) arnCriticalExit();

    qwtSym = new QwtSymbol(QwtSymbol::Ellipse, Qt::yellow, QPen(Qt::blue), QSize(5, 5));
    //
    //  Frame style
    //
    setFrameStyle(QFrame::Box|QFrame::Raised);
    setLineWidth(2);
    setMidLineWidth(3);

    for (int i = 0; i < NumOfPlot; i++) {
        Size[i] = 0;
        xval[i] = 0;
        yval[i] = 0;
        d_curves[i].setSymbol(qwtSym);
        d_curves[i].setPen(QColor(Qt::red));
        d_curves[i].setStyle(QwtPlotCurve::Sticks);
        }


}

arnMulVectorPlot::~arnMulVectorPlot(void)
{
    for (int i = 0; i < NumOfPlot; i++) {
        if (xval[i]) {delete [] xval[i]; xval[i] = 0;}
        if (yval[i]) {delete [] yval[i]; yval[i] = 0;}
        }
    delete [] xval; xval = 0;
    delete [] yval; yval = 0;
    delete [] xMap; xMap = 0;
    delete [] yMap; yMap = 0;
    delete [] d_curves; d_curves = 0;
    if (qwtSym) {delete qwtSym; qwtSym = 0;}
}

void arnMulVectorPlot::setSize(int indx,int sz)
{
    if ((indx <= 0) || (indx > NumOfPlot)) return;
    Size[indx] = sz;
    if (Size[indx] <= 0) arnCriticalExit();
    xval[indx] = new double[Size[indx]];
    if (!xval[indx]) arnCriticalExit();
    yval[indx] = new double[Size[indx]];
    if (!yval[indx]) arnCriticalExit();
    for (int i = 0; i < Size[indx]; i++) {yval[indx][i] = 0; xval[indx][i] = i;}
}

void arnMulVectorPlot::setX(int indx,double* x)
{
    if ((indx <= 0) || (indx > NumOfPlot)) return;
    if (!xval[indx]) return;
    for (int i = 0; i < Size[indx]; i++) xval[indx][i] = x[i];
}

void arnMulVectorPlot::setY(int indx,double* y)
{
    if ((indx <= 0) || (indx > NumOfPlot)) return;
    if (!yval[indx]) return;
    for (int i = 0; i < Size[indx]; i++) yval[indx][i] = y[i];
}

void arnMulVectorPlot::plotCurve(void)
{
    for (int i = 0; i < NumOfPlot; i++) {
        d_curves[i].setRawSamples(xval[i], yval[i], Size[i]);
        }
    update();
}

void arnMulVectorPlot::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setClipRect(contentsRect());
    drawContents(&painter);
}

void arnMulVectorPlot::shiftDown(QRect &rect, int offset) const
{
    rect.translate(0, offset);
}


//
//  REDRAW CONTENTS
//
void arnMulVectorPlot::drawContents(QPainter *painter)
{
    int deltay;

    QRect r = contentsRect();

    deltay = r.height() / NumOfPlot -1;

    r.setHeight(deltay);

    //
    //  draw curve
    //
    for (int i = 0; i < NumOfPlot; i++) {
        xMap[i].setPaintInterval(r.left(), r.right());
        yMap[i].setPaintInterval(r.bottom(),r.top());

        painter->setRenderHint(QPainter::Antialiasing,d_curves[i].testRenderHint(QwtPlotItem::RenderAntialiased) );
        d_curves[i].draw(painter, xMap[i], yMap[i], r);

        shiftDown(r, deltay);
        }

}
