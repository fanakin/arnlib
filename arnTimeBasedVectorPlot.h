/***************************************************************************
                          arnTimeBasedVectorPlot.h  -  description
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

#ifndef ArnTimeBasedVectorPlotH
#define ArnTimeBasedVectorPlotH

#include <qframe.h>
#include "qwt_plot.h"
#include "qwt_plot_grid.h"
#include "qwt_plot_marker.h"
#include "qwt_scale_map.h"
#include "qwt_plot_directpainter.h"
#include "qwt_plot_curve.h"
#include "qwt_system_clock.h"

//BEGIN Class Signal data
class SignalData
{
public:
    static SignalData &instance();

    void append(const QPointF &pos);
    void clearStaleValues(double min);

    int size() const;
    QPointF value(int index) const;

    QRectF boundingRect() const;

    void lock();
    void unlock();

private:
    SignalData();
    SignalData(const SignalData &);
    SignalData &operator=( const SignalData & );

    virtual ~SignalData();

    class PrivateData;
    PrivateData *d_data;
};
//END Class Signal data

//BEGIN Class Curve data
class CurveData: public QwtSeriesData<QPointF>
{
public:
    const SignalData &values() const;
    SignalData &values();

    virtual QPointF sample(size_t i) const;
    virtual size_t size() const;

    virtual QRectF boundingRect() const;
};
//END Class Curve data





class arnTimeBasedVectorPlot : public QwtPlot
{
    Q_OBJECT

public:
    arnTimeBasedVectorPlot(QWidget * = NULL);
    virtual ~arnTimeBasedVectorPlot(void);
    virtual void replot(void);
    void start(void);
    //void stop(void);

    void append(double x, double y);
    //inline void setAutoScale(int axisid, bool on) {setAxisAutoScale(axisid,on);}
    inline void setCurveColor(QColor c) {d_curve->setPen(QPen(c));}
    inline void setCurveStyle(QwtPlotCurve::CurveStyle st) {d_curve->setStyle(st);}
    inline void setMarkerOrigin(double xOrig, double yOrig) {
        double xO;
        if (xOrig < d_interval.minValue()) xO = d_interval.minValue();
        else if (xOrig > d_interval.minValue() + d_interval.width()) xOrig = d_interval.minValue() + d_interval.width();
        else xO = xOrig;
        d_origin->setValue(xO, yOrig);
    }
    void setGradient(QColor startColor,QColor finalColor);
public Q_SLOTS:
    void setIntervalLength(double);
    inline double elapsedTime(void) {return (d_clock.elapsed() / 1000.0);}

protected:
    virtual void showEvent(QShowEvent *);
    virtual void resizeEvent(QResizeEvent *);
    virtual void timerEvent(QTimerEvent *);

private:
    void initGradient();

    void updateCurve();
    void incrementInterval();
    void initCanvas(void);

    QwtPlotGrid *grid;
    QwtPlotMarker *d_origin;
    QwtPlotCurve *d_curve;
    int d_paintedPoints;

    QwtPlotDirectPainter *d_directPainter;

    QwtInterval d_interval;

    int d_timerId;
    QwtSystemClock d_clock;

    //int CanvasInitialized;
};
#endif
