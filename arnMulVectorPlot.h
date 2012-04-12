/***************************************************************************
                          arnMulVectorPlot.h  -  description
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

#ifndef ArnMulVectorPlotH
#define ArnMulVectorPlotH

#include <qframe.h>
#include "qwt_scale_map.h"
#include "qwt_plot_curve.h"

class arnMulVectorPlot : public QFrame {

    Q_OBJECT

    private:
        void shiftDown(QRect &rect, int offset) const;

    protected:
        int NumOfPlot;
        int* Size;
        double** xval;
        double** yval;
        QwtScaleMap* xMap;
        QwtScaleMap* yMap;
        QwtPlotCurve* d_curves;
        QwtSymbol *qwtSym;

        virtual void paintEvent(QPaintEvent *);
        void drawContents(QPainter *p);

    public:

        /*! \brief constructor in QT style \n
        *
        */
        arnMulVectorPlot(int NumOfP = 1,QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnMulVectorPlot(void);


        /*! \brief It returns the number of allocated plots\n
        *
        * It returns the number of allocated plots to iterate on them other operations \n
        *
        * @return : number of allocated plots
        * Ex:\n
        * ...\n
        */
        inline int NumberOfPlot(void) {return NumOfPlot;}

        /*! \brief Set the Size of the vector to plot amnd allocate memory for x and y vectors\n
        *
        * It sets the Size of the vector to be plotted.
        *
        * @param indx : index of the specific plot
        * @param sz : lenght of the vector to plot
        * Ex:\n
        * ...\n
        */
        virtual void setSize(int indx, int sz);

        /*! \brief Set the x values vector for plotting\n
        *
        * It sets the x vestor to be shown on x axis
        *
        * @param indx : index of the specific plot
        * @param x : x vector
        * Ex:\n
        * ...\n
        */
        virtual void setX(int indx, double* x);

        /*! \brief Set the y values vector for plotting\n
        *
        * It sets the y vestor to be shown on y axis
        *
        * @param indx : index of the specific plot
        * @param y : y vector
        * Ex:\n
        * ...\n
        */
        virtual void setY(int indx,double* y);

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
        * pl.setXScaleInterval(0, 128);
        * pl.setYScaleInterval(-1.1, 1.1);
        * pl.setX(x);
        * pl.setY(y);
        * pl.plotCurve(x);
        */
        virtual void plotCurve(void);

        /*! \brief Set the x axis scale interval\n
        *
        * It sets the scale interval on x axis
        *
        * @param indx : index of the specific plot
        * @param min : minimum value of the x axis values
        * @param max : maxmum value of the x axis values
        * Ex:\n
        * ...\n
        */
        virtual inline void setXScaleInterval(int indx,double min, double max) {if (indx < NumOfPlot) xMap[indx].setScaleInterval(min, max);}

        /*! \brief Set the y axis scale interval\n
        *
        * It sets the scale interval on y axis
        *
        * @param indx : index of the specific plot
        * @param min : minimum value of the y axis values
        * @param max : maxmum value of the y axis values
        * Ex:\n
        * ...\n
        */
        virtual inline void setYScaleInterval(int indx,double min, double max) {if (indx < NumOfPlot) yMap[indx].setScaleInterval(min, max);}

 };

#endif
