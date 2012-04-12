/***************************************************************************
                          arnVectorPlot.cpp  -  description
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

#include <qcolor.h>
#include <qpainter.h>
#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qwt_plot_canvas.h>
#include <qwt_picker_machine.h>
#include "CommonFunctions.h"
#include "arnVectorPlot.h"


class Zoomer: public QwtPlotZoomer
{
public:
    Zoomer(int xAxis, int yAxis, QwtPlotCanvas *canvas):
        QwtPlotZoomer(xAxis, yAxis, canvas)
    {
        setTrackerMode(QwtPicker::AlwaysOff);
        setRubberBand(QwtPicker::NoRubberBand);

        // RightButton: zoom out by 1
        // Ctrl+RightButton: zoom out to full size

        setMousePattern(QwtEventPattern::MouseSelect2,
            Qt::RightButton, Qt::ControlModifier);
        setMousePattern(QwtEventPattern::MouseSelect3,
            Qt::RightButton);
    }
};

arnVectorPlot::arnVectorPlot(QWidget *parent, Qt::WindowFlags f)
    : QFrame(parent,f)
{
    d_directPainter = new QwtPlotDirectPainter();
    if (!d_directPainter) arnCriticalExit();
    d_grid = new QwtPlotGrid();
    if (!d_grid) arnCriticalExit();
    d_origin = new QwtPlotMarker();
    if (!d_origin) arnCriticalExit();
    d_curve = new QwtPlotCurve();
    if (!d_curve) arnCriticalExit();
    d_plot = new QwtPlot(this);
    if (!d_plot) arnCriticalExit();
    pLayout = new QGridLayout(this,1, 1, 0, 0);
    pSplitter = new QSplitter (Qt::Horizontal, this);
    if (!pSplitter) arnCriticalExit();
    pOptionGroup = new QGroupBox("Options");
    if (!pOptionGroup) arnCriticalExit();
    pAutoScaleChkBx = new QCheckBox("AutoScale");
    if (!pAutoScaleChkBx) arnCriticalExit();
    pZoonerChkBx = new QCheckBox("Zoom");
    if (!pZoonerChkBx) arnCriticalExit();
    vbox = new QVBoxLayout();
    if (!vbox) arnCriticalExit();

    init();
}

void arnVectorPlot::init(void) {
    Size = 0;
    xval = 0;
    yval = 0;
    memallocaced = false;
    const QwtSymbol* qwtSym = new QwtSymbol(QwtSymbol::Ellipse, Qt::yellow, QPen(Qt::blue), QSize(5, 5));
    //
    //  Frame style
    //
    d_plot->setFrameStyle(QFrame::Box|QFrame::Raised);
    d_plot->setLineWidth(2);
    d_plot->setMidLineWidth(3);

    d_plot->setAxisTitle(QwtPlot::xBottom, "Time [s]");
    d_plot->setAxisScale(QwtPlot::xBottom,0, 10);
    d_plot->setAxisScale(QwtPlot::yLeft, -20.0, 20.0);

    d_grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    d_grid->enableX(true);
    d_grid->enableXMin(true);
    d_grid->enableY(true);
    d_grid->enableYMin(false);
    d_grid->attach(d_plot);

    d_origin = new QwtPlotMarker();
    d_origin->setLineStyle(QwtPlotMarker::Cross);
    d_origin->setValue(5, 0.0);
    d_origin->setLinePen(QPen(Qt::gray, 0.0, Qt::DashLine));
    d_origin->attach(d_plot);

    d_curve->setSymbol(qwtSym);
    d_curve->setPen(QColor(Qt::red));
    d_curve->setStyle(QwtPlotCurve::Sticks);
    d_curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
    d_curve->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
    d_curve->attach(d_plot);

    d_zoomer[0] = 0;
    d_zoomer[1] = 0;
    d_panner = 0;

    pLayout->addWidget(pSplitter);
    pSplitter->addWidget(d_plot);
    pSplitter->addWidget(pOptionGroup);

    pAutoScaleChkBx->setCheckable(true);
    pZoonerChkBx->setCheckable(true);

    vbox->addWidget(pAutoScaleChkBx);
    vbox->addWidget(pZoonerChkBx);
    vbox->addStretch(1);
    pOptionGroup->setLayout(vbox);

    connect(pZoonerChkBx, SIGNAL(toggled(bool)), SLOT(enableZoomMode(bool)));
    connect(pAutoScaleChkBx, SIGNAL(toggled(bool)), SLOT(enableAutoScale(bool)));
    enableZoomMode(false);
    //TEST TEST TEST
    pSplitter->setStretchFactor (pSplitter->indexOf(d_plot), 9 );
    pSplitter->setStretchFactor (pSplitter->indexOf(pOptionGroup), 1 );
    //END TEST TEST TEST
}

arnVectorPlot::~arnVectorPlot(void)
{
    if (memallocaced) {
        if (xval) {delete [] xval; xval = 0;}
        if (yval) {delete [] yval; yval = 0;}
    }
}

void arnVectorPlot::setSize(int sz,bool allocmem)
{
    Size = sz;
    if (Size <= 0) arnCriticalExit();
    if (allocmem) {
        xval = new double[Size];
        if (!xval) arnCriticalExit();
        yval = new double[Size];
        if (!yval) arnCriticalExit();
        for (int i = 0; i < Size; i++) {yval[i] = 0; xval[i] = i;}
        memallocaced = true;
        }
    else {
        xval = 0;
        yval = 0;
        }
}

void arnVectorPlot::setX(double* x)
{
    if (!xval) {xval = x;}
    else {for (int i = 0; i < Size; i++) xval[i] = x[i];}
}

void arnVectorPlot::setY(double* y)
{
    if (!yval) {yval  = y;}
    else {for (int i = 0; i < Size; i++) yval[i] = y[i];}
}

void arnVectorPlot::replot (void)
{
    d_curve->setRawSamples(xval, yval, Size);
    d_plot->replot();
}

void arnVectorPlot::showEvent(QShowEvent *)
{
    replot();
}

void arnVectorPlot::resizeEvent(QResizeEvent *event)
{
    d_directPainter->reset();
    QFrame::resizeEvent(event);
}

void arnVectorPlot::enableZoomMode(bool on)
{
    if (on) {
        OriginalIntervalYLeft = d_plot->axisInterval(QwtPlot::yLeft);
        OriginalIntervalXBottom = d_plot->axisInterval(QwtPlot::xBottom);

        d_zoomer[0] = new Zoomer( QwtPlot::xBottom, QwtPlot::yLeft,
            d_plot->canvas());
        d_zoomer[0]->setRubberBand(QwtPicker::RectRubberBand);
        d_zoomer[0]->setRubberBandPen(QColor(Qt::green));
        d_zoomer[0]->setTrackerMode(QwtPicker::ActiveOnly);
        d_zoomer[0]->setTrackerPen(QColor(Qt::white));

        d_zoomer[1] = new Zoomer(QwtPlot::xTop, QwtPlot::yRight,
             d_plot->canvas());

        d_panner = new QwtPlotPanner(d_plot->canvas());
        d_panner->setMouseButton(Qt::MidButton);


        d_panner->setEnabled(on);

        d_zoomer[0]->setEnabled(on);
        d_zoomer[0]->zoom(0);
        d_zoomer[1]->setEnabled(on);
        d_zoomer[1]->zoom(0);

        if (d_picker) {delete d_picker; d_picker = 0;}
    }
    else {
        d_plot->setAxisScale(QwtPlot::yLeft,OriginalIntervalYLeft.minValue(),OriginalIntervalYLeft.maxValue());
        d_plot->setAxisScale(QwtPlot::xBottom,OriginalIntervalXBottom.minValue(),OriginalIntervalXBottom.maxValue());

        if (d_zoomer[0]) {delete d_zoomer[0]; d_zoomer[0] = 0;}
        if (d_zoomer[1]) {delete d_zoomer[1]; d_zoomer[1] = 0;}
        if (d_panner) {delete d_panner; d_panner = 0;}

        d_picker = new QwtPlotPicker(QwtPlot::xBottom, QwtPlot::yLeft,
            QwtPlotPicker::CrossRubberBand, QwtPicker::AlwaysOn,
           d_plot->canvas());
        d_picker->setStateMachine(new QwtPickerDragPointMachine());
        d_picker->setRubberBandPen(QColor(Qt::green));
        d_picker->setRubberBand(QwtPicker::CrossRubberBand);
        d_picker->setTrackerPen(QColor(Qt::white));

        d_picker->setEnabled(!on);
    }

}

void arnVectorPlot::enableAutoScale(bool on)
{
    d_plot->setAxisAutoScale(QwtPlot::yLeft,on);
    //d_plot->setAxisAutoScale(QwtPlot::xBottom,on);
}
