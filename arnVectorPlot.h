/***************************************************************************
                          arnVectorPlot.h  -  description
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

#ifndef ArnVectorPlotH
#define ArnVectorPlotH

#include <QFrame>
#include <QSplitter>
#include <QGridLayout>
#include <QGroupBox>
#include <QCheckBox>

#include "qwt_plot_grid.h"
#include "qwt_plot_marker.h"
#include "qwt_plot_directpainter.h"
#include "qwt_plot.h"
#include "qwt_text.h"
#include "qwt_scale_map.h"
#include "qwt_plot_curve.h"
#include "qwt_plot_picker.h"
#include "qwt_plot_zoomer.h"
#include "qwt_plot_panner.h"

class arnVectorPlot : public QFrame {

    Q_OBJECT

    private:
        QwtInterval OriginalIntervalYLeft;
        QwtInterval OriginalIntervalXBottom;
        void init(void);
    private slots:
        void enableZoomMode(bool);
        void enableAutoScale(bool on);
    protected:
        int Size;
        double* xval;
        double* yval;
        bool memallocaced;

        QwtPlotDirectPainter *d_directPainter;
        QwtPlotGrid *d_grid;
        QwtPlotMarker *d_origin;
        QwtPlotCurve *d_curve;
        QwtPlot* d_plot;
        QwtPlotPicker *d_picker;
        QwtPlotZoomer *d_zoomer[2];
        QwtPlotPanner *d_panner;

        QGridLayout* pLayout;
        QSplitter* pSplitter;

        QVBoxLayout *vbox;
        QGroupBox* pOptionGroup;
        QCheckBox* pAutoScaleChkBx;
        QCheckBox* pZoonerChkBx;

        virtual void showEvent(QShowEvent *);
        virtual void resizeEvent(QResizeEvent *);

    public:

        /*! \brief constructor in QT style \n
        *
        */
        arnVectorPlot ( QWidget * parent = 0, Qt::WindowFlags f = 0 );


        /*! \brief default destructor\n
        *
        */
        ~arnVectorPlot(void);


        /*! \brief Set the Size of the vector to plot and optionally allocate memory for x and y vectors\n
        *
        * It sets the Size of the vector to be plotted.
        *
        * @param sz : lenght of the vector to plot
        * @param allocmem : if it is true, allocates memory for the vector; otherwise it expect to be allocate outside
        * Ex:\n
        * ...\n
        */
        virtual void setSize(int sz,bool allocmem = true);

        /*! \brief Set the x values vector for plotting\n
        *
        * It sets the x vestor to be shown on x axis
        *
        * @param x : x vector
        * Ex:\n
        * ...\n
        */
        virtual void setX(double* x);

        /*! \brief Set the y values vector for plotting\n
        *
        * It sets the y vestor to be shown on y axis
        *
        * @param y : y vector
        * Ex:\n
        * ...\n
        */
        virtual void setY(double* y);

        /*! \brief It allows the access to QwtPlot widget\n
        *
        * It allows the access to QwtPlot widget
        *
        * @return QwtPlot widget
        * Ex:\n
        * ...\n
        */
        inline QwtPlot& plot(void) const {return (*(d_plot));}

        /*! \brief It allows the access to QwtPlotGrid widget\n
        *
        * It allows the access to QwtPlotGrid widget attached to plot
        *
        * @return QwtPlotGrid widget
        * Ex:\n
        * ...\n
        */
        inline QwtPlotGrid& grid(void) const {return (*(d_grid));}

        /*! \brief It allows the access to QwtPlotMarker widget\n
        *
        * It allows the access to QwtPlotMarker widget attached to plot
        *
        * @return QwtPlotMarker widget
        * Ex:\n
        * ...\n
        */
        inline QwtPlotMarker& origin(void) const {return (*(d_origin));}

    public slots:
        /*! \brief It really plots on the screen the set vector\n
        *
        * It really update the screen with the set values
        *
        *
        * Ex:\n
        * arnVectorPlot pl(parent);
        * ...\n
        * ...\n
        * pl.setSize(128);
        * pl.setAxisTitle(QwtPlot::xBottom, "Freq [Hz]");
        * pl.setAxisScale(QwtPlot::xBottom,0, 1000);
        * pl.setAxisScale(QwtPlot::yLeft, -20.0, 20.0);
        * pl.setX(x);
        * pl.setY(y);
        * pl.plotCurve(x);
        */
        virtual void replot (void);
};

#endif
