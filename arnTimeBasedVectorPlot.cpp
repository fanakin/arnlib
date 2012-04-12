/***************************************************************************
                          arnTimeBasedVectorPlot.cpp  -  description
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

#include <QColor>
#include <QPainter>
#include <QMutex>
#include <QTimerEvent>

#include <qwt_symbol.h>
#include <qwt_math.h>
#include <qreadwritelock.h>
#include <qwt_plot_canvas.h>
#include <qwt_plot_layout.h>
#include <qwt_plot_grid.h>
#include "CommonFunctions.h"
#include "arnTimeBasedVectorPlot.h"

//BEGIN Class Signal data
class SignalData::PrivateData
{
public:
    PrivateData():
        boundingRect(1.0, 1.0, -2.0, -2.0) // invalid
    {
        values.reserve(1000);
    }

    inline void append(const QPointF &sample)
    {
        values.append(sample);

        // adjust the bounding rectangle

        if ( boundingRect.width() < 0 || boundingRect.height() < 0 )
        {
            boundingRect.setRect(sample.x(), sample.y(), 0.0, 0.0);
        }
        else
        {
            boundingRect.setRight(sample.x());

            if ( sample.y() > boundingRect.bottom() )
                boundingRect.setBottom(sample.y());

            if ( sample.y() < boundingRect.top() )
                boundingRect.setTop(sample.y());
        }
    }

    QReadWriteLock lock;

    QVector<QPointF> values;
    QRectF boundingRect;

    QMutex mutex; // protecting pendingValues
    QVector<QPointF> pendingValues;
};

SignalData::SignalData()
{
    d_data = new PrivateData();
}

SignalData::~SignalData()
{
    delete d_data;
}

int SignalData::size() const
{
    return d_data->values.size();
}

QPointF SignalData::value(int index) const
{
    return d_data->values[index];
}

QRectF SignalData::boundingRect() const
{
    return d_data->boundingRect;
}

void SignalData::lock()
{
    d_data->lock.lockForRead();
}

void SignalData::unlock()
{
    d_data->lock.unlock();
}

void SignalData::append(const QPointF &sample)
{
    d_data->mutex.lock();
    d_data->pendingValues += sample;

    const bool isLocked = d_data->lock.tryLockForWrite();
    if ( isLocked )
    {
        const int numValues = d_data->pendingValues.size();
        const QPointF *pendingValues = d_data->pendingValues.data();

        for ( int i = 0; i < numValues; i++ )
            d_data->append(pendingValues[i]);

        d_data->pendingValues.clear();

        d_data->lock.unlock();
    }

    d_data->mutex.unlock();
}

void SignalData::clearStaleValues(double limit)
{
    d_data->lock.lockForWrite();

    d_data->boundingRect = QRectF(1.0, 1.0, -2.0, -2.0); // invalid

    const QVector<QPointF> values = d_data->values;
    d_data->values.clear();
    d_data->values.reserve(values.size());

    int index;
    for ( index = values.size() - 1; index >= 0; index-- )
    {
        if ( values[index].x() < limit )
            break;
    }

    if ( index > 0 )
        d_data->append(values[index++]);

    while ( index < values.size() - 1 )
        d_data->append(values[index++]);

    d_data->lock.unlock();
}

SignalData &SignalData::instance()
{
    static SignalData valueVector;
    return valueVector;
}
//END Class Signal data




//BEGIN Class Curve data
const SignalData &CurveData::values() const
{
    return SignalData::instance();
}

SignalData &CurveData::values()
{
    return SignalData::instance();
}

QPointF CurveData::sample(size_t i) const
{
    return SignalData::instance().value(i);
}

size_t CurveData::size() const
{
    return SignalData::instance().size();
}

QRectF CurveData::boundingRect() const
{
    return SignalData::instance().boundingRect();
}
//END Class Curve data





arnTimeBasedVectorPlot::arnTimeBasedVectorPlot(QWidget *parent):
    QwtPlot(parent),
    d_paintedPoints(0),
    d_interval(0.0, 5.0)
    //CanvasInitialized(0)
{
    d_directPainter = new QwtPlotDirectPainter();
    grid = new QwtPlotGrid();
    d_origin = new QwtPlotMarker();
    d_curve = new QwtPlotCurve();
    initCanvas();
    initGradient();
}

void arnTimeBasedVectorPlot::initCanvas(void)
{
    //if (CanvasInitialized) return;

    d_paintedPoints = 0;
    d_interval.setInterval(0.0,5.0);

    setAutoReplot(false);

    // The backing store is important, when working with widget
    // overlays ( f.e rubberbands for zooming ).
    // Here we don't have them and the internal
    // backing store of QWidget is good enough.

    canvas()->setPaintAttribute(QwtPlotCanvas::BackingStore, false);


#if defined(Q_WS_X11)
    // Even if not recommended by TrollTech, Qt::WA_PaintOutsidePaintEvent
    // works on X11. This has a nice effect on the performance.

    canvas()->setAttribute(Qt::WA_PaintOutsidePaintEvent, true);

    // Disabling the backing store of Qt improves the performance
    // for the direct painter even more, but the canvas becomes
    // a native window of the window system, receiving paint events
    // for resize and expose operations. Those might be expensive
    // when there are many points and the backing store of
    // the canvas is disabled. So in this application
    // we better don't both backing stores.

    if ( canvas()->testPaintAttribute( QwtPlotCanvas::BackingStore ) )
    {
        canvas()->setAttribute(Qt::WA_PaintOnScreen, true);
        canvas()->setAttribute(Qt::WA_NoSystemBackground, true);
    }

#endif

    plotLayout()->setAlignCanvasToScales(true);

    setAxisTitle(QwtPlot::xBottom, "Time [s]");
    setAxisScale(QwtPlot::xBottom, d_interval.minValue(), d_interval.maxValue());
    setAxisScale(QwtPlot::yLeft, -20.0, 20.0);

    grid->setPen(QPen(Qt::gray, 0.0, Qt::DotLine));
    grid->enableX(true);
    grid->enableXMin(true);
    grid->enableY(true);
    grid->enableYMin(false);
    grid->attach(this);

    d_origin = new QwtPlotMarker();
    d_origin->setLineStyle(QwtPlotMarker::Cross);
    d_origin->setValue(d_interval.minValue() + d_interval.width() / 2.0, 0.0);
    d_origin->setLinePen(QPen(Qt::gray, 0.0, Qt::DashLine));
    d_origin->attach(this);

    d_curve = new QwtPlotCurve();
    d_curve->setStyle(QwtPlotCurve::Lines);
    d_curve->setPen(QPen(Qt::green));
#if 1
    d_curve->setRenderHint(QwtPlotItem::RenderAntialiased, true);
#endif
#if 1
    d_curve->setPaintAttribute(QwtPlotCurve::ClipPolygons, false);
#endif
    d_curve->setData(new CurveData());
    d_curve->attach(this);

    //CanvasInitialized = 1;
}

arnTimeBasedVectorPlot::~arnTimeBasedVectorPlot()
{
    delete d_directPainter;
}

void arnTimeBasedVectorPlot::initGradient()
{
    QPalette pal = canvas()->palette();

#if QT_VERSION >= 0x040400
    QLinearGradient gradient( 0.0, 0.0, 1.0, 0.0 );
    gradient.setCoordinateMode( QGradient::StretchToDeviceMode );
    gradient.setColorAt(0.0, QColor( 0, 49, 110 ) );
    gradient.setColorAt(1.0, QColor( 0, 87, 174 ) );

    pal.setBrush(QPalette::Window, QBrush(gradient));
#else
    pal.setBrush(QPalette::Window, QBrush( color ));
#endif

    canvas()->setPalette(pal);
}

void arnTimeBasedVectorPlot::start()
{
    //initCanvas();
    d_clock.start();
    d_timerId = startTimer(10);
}
/*
void arnTimeBasedVectorPlot::stop()
{
    killTimer(d_timerId);
    d_paintedPoints = 0;
    grid->detach();
    d_origin->detach();
    d_curve->detach();
    CanvasInitialized = 0;
}
*/
void arnTimeBasedVectorPlot::timerEvent(QTimerEvent *event)
{
    if ( event->timerId() == d_timerId )
    {
        updateCurve();

        const double elapsed = d_clock.elapsed() / 1000.0;
        if ( elapsed > d_interval.maxValue() )
            incrementInterval();

        return;
    }

    QwtPlot::timerEvent(event);
}

void arnTimeBasedVectorPlot::setGradient(QColor startColor,QColor finalColor)
{
    QPalette pal = canvas()->palette();

#if QT_VERSION >= 0x040400
    QLinearGradient gradient( 0.0, 0.0, 1.0, 0.0 );
    gradient.setCoordinateMode( QGradient::StretchToDeviceMode );
    gradient.setColorAt(0.0,startColor );
    gradient.setColorAt(1.0, finalColor );

    pal.setBrush(QPalette::Window, QBrush(gradient));
#else
    pal.setBrush(QPalette::Window, QBrush( color ));
#endif

    canvas()->setPalette(pal);
}



void arnTimeBasedVectorPlot::replot()
{
    CurveData *data = (CurveData *)d_curve->data();
    data->values().lock();

    QwtPlot::replot();
    d_paintedPoints = data->size();

    data->values().unlock();
}

void arnTimeBasedVectorPlot::setIntervalLength(double interval)
{
    if ( interval > 0.0 && interval != d_interval.width() )
    {
        d_interval.setMaxValue(d_interval.minValue() + interval);
        setAxisScale(QwtPlot::xBottom,
            d_interval.minValue(), d_interval.maxValue());

        replot();
    }
}

void arnTimeBasedVectorPlot::updateCurve()
{
    CurveData *data = (CurveData *)d_curve->data();
    data->values().lock();

    const int numPoints = data->size();
    if ( numPoints > d_paintedPoints )
    {
        const bool doClip = !canvas()->testAttribute( Qt::WA_PaintOnScreen );
        if ( doClip )
        {
            /*
                Depending on the platform setting a clip might be an important
                performance issue. F.e. for Qt Embedded this reduces the
                part of the backing store that has to be copied out - maybe
                to an unaccelerated frame buffer device.
            */

            const QwtScaleMap xMap = canvasMap( d_curve->xAxis() );
            const QwtScaleMap yMap = canvasMap( d_curve->yAxis() );

            QRectF br = qwtBoundingRect( *data,
                d_paintedPoints - 1, numPoints - 1 );

            const QRect clipRect = QwtScaleMap::transform( xMap, yMap, br ).toRect();
            d_directPainter->setClipRegion( clipRect );
        }

        d_directPainter->drawSeries(d_curve,
            d_paintedPoints - 1, numPoints - 1);
        d_paintedPoints = numPoints;
    }

    data->values().unlock();
}

void arnTimeBasedVectorPlot::incrementInterval()
{
    d_interval = QwtInterval(d_interval.maxValue(),
        d_interval.maxValue() + d_interval.width());

    CurveData *data = (CurveData *)d_curve->data();
    data->values().clearStaleValues(d_interval.minValue());

    // To avoid, that the grid is jumping, we disable
    // the autocalculation of the ticks and shift them
    // manually instead.

    QwtScaleDiv scaleDiv = *axisScaleDiv(QwtPlot::xBottom);
    scaleDiv.setInterval(d_interval);

    for ( int i = 0; i < QwtScaleDiv::NTickTypes; i++ )
    {
        QList<double> ticks = scaleDiv.ticks(i);
        for ( int j = 0; j < ticks.size(); j++ )
            ticks[j] += d_interval.width();
        scaleDiv.setTicks(i, ticks);
    }
    setAxisScaleDiv(QwtPlot::xBottom, scaleDiv);

    d_origin->setValue(d_interval.minValue() + d_interval.width() / 2.0, 0.0);

    d_paintedPoints = 0;
    replot();
}

void arnTimeBasedVectorPlot::resizeEvent(QResizeEvent *event)
{
    d_directPainter->reset();
    QwtPlot::resizeEvent(event);
}

void arnTimeBasedVectorPlot::showEvent( QShowEvent * )
{
    replot();
}


void arnTimeBasedVectorPlot::append(double x, double y)
{
    const QPointF s(x, y);
    SignalData::instance().append(s);
}


/*
arnTimeBasedVectorPlot::arnTimeBasedVectorPlot(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    Size = 0;
    xval = 0;
    yval = 0;
    qwtSym = new QwtSymbol(QwtSymbol::Ellipse, Qt::yellow, QPen(Qt::blue), QSize(5, 5));
    if (!qwtSym) arnCriticalExit();
    //
    //  Frame style
    //
    setFrameStyle(QFrame::Box|QFrame::Raised);
    setLineWidth(2);
    setMidLineWidth(3);

    d_curves.setSymbol(qwtSym);
    d_curves.setPen(QColor(Qt::red));
    d_curves.setStyle(QwtPlotCurve::Sticks);
}

arnTimeBasedVectorPlot::~arnTimeBasedVectorPlot(void)
{
    if (xval) {delete [] xval; xval = 0;}
    if (yval) {delete [] yval; yval = 0;}
    if (qwtSym) {delete qwtSym; qwtSym = 0;}
}

void arnTimeBasedVectorPlot::setSize(int sz)
{
    Size = sz;
    if (Size <= 0) arnCriticalExit();
    xval = new double[Size];
    if (!xval) arnCriticalExit();
    yval = new double[Size];
    if (!yval) arnCriticalExit();
    for (int i = 0; i < Size; i++) {yval[i] = 0; xval[i] = i;}
}

void arnTimeBasedVectorPlot::setX(double* x)
{
    if (!xval) return;
    for (int i = 0; i < Size; i++) xval[i] = x[i];
}

void arnTimeBasedVectorPlot::setY(double* y)
{
    if (!yval) return;
    for (int i = 0; i < Size; i++) yval[i] = y[i];
}

void arnTimeBasedVectorPlot::plotCurve(void)
{
    d_curves.setRawSamples(xval, yval, Size);
    update();
}

void arnTimeBasedVectorPlot::paintEvent(QPaintEvent *event)
{
    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setClipRect(contentsRect());
    drawContents(&painter);
}


//
//  REDRAW CONTENTS
//
void arnTimeBasedVectorPlot::drawContents(QPainter *painter)
{
    int deltay;

    QRect r = contentsRect();

    deltay = r.height();

    r.setHeight(deltay);

    //
    //  draw curve
    //
    xMap.setPaintInterval(r.left(), r.right());
    yMap.setPaintInterval(r.bottom(),r.top());

    painter->setRenderHint(QPainter::Antialiasing,
        d_curves.testRenderHint(QwtPlotItem::RenderAntialiased) );
        d_curves.draw(painter, xMap, yMap, r);

}
*/
