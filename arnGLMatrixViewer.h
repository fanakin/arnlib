/***************************************************************************
                          arnGLMatrixViewer.h  -  description
                             -------------------
    begin                : ven giu 20 2003
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

#ifndef ArnGLMatrixViewerH
#define ArnGLMatrixViewerH

#include <qlayout.h>
#include <qslider.h>
#include "arnGLTable.h"
#include "arnObjectViewer.h"


class arnGLMatrixViewer : public arnObjectViewer
{
	Q_OBJECT
	private:
	private slots:
	protected:
		arnGLTable* pMatrix;
		QVBoxLayout* sldlayout;
		QVBoxLayout* zslayout; // zoom, scaling layout
		QHBoxLayout* layout;
		QGridLayout* gltablelayout;
		// slider per il controllo delle 3 dimensioni spaziali
		QSlider* xsl;
		QSlider* ysl;
		QSlider* zsl;
		// sliders per lo zoom e lo scaling
		QSlider* scaleslMax;
		QSlider* scaleslMin;
		// per cambiamento dinamico pilotato da altri widget
		arnObjectViewer *pSender;
		double scaleZMaxValue;
		double scaleZMinValue;
	protected slots:
	public :
		arnGLMatrixViewer(arnGLTablePaintingMode_t md = arn_glTPM_VERTICAL_LINES, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
		arnGLMatrixViewer(int XAxisSize = 5, int YAxisSize = 5, arnGLTablePaintingMode_t md = arn_glTPM_VERTICAL_LINES ,QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
		~arnGLMatrixViewer(void);
		inline arnGLTablePaintingMode_t mode (void) {return pMatrix->mode();}
		inline void setMode (arnGLTablePaintingMode_t md) {pMatrix->setMode(md);}
		inline void setSender(arnObjectViewer *Sender) {pSender = Sender;}
		inline const arnGLTable* matrix(void) {return pMatrix;}
	public slots:
		inline void setYMinScale(double val) {pMatrix->setRowMinScale(val);}
		inline void setYMaxScale(double val) {pMatrix->setRowMaxScale(val);}
		inline void setXMinScale(double val) {pMatrix->setColMinScale(val);}
		inline void setXMaxScale(double val) {pMatrix->setColMaxScale(val);}
		void setValueMinScale(double val);
		void setValueMaxScale(double val);
		void setXValue(int indx, double val);
		void setYValue(int indx, double val);
		inline void setXAxisLabel(const QString& str) {pMatrix->setXAxisLabel(str);}
		inline void setYAxisLabel(const QString& str) {pMatrix->setYAxisLabel(str);}
		inline void setZAxisLabel(const QString& str) {pMatrix->setZAxisLabel(str);}
		inline void setCaptionLabel(const QString& str) {pMatrix->setCaptionLabel(str);}
		inline QString XAxisLabel(void) {return pMatrix->XAxisLabel();}
		inline QString YAxisLabel(void) {return pMatrix->YAxisLabel();}
		inline QString ZAxisLabel(void) {return pMatrix->ZAxisLabel();}
		inline QString CaptionLabel(void) {return pMatrix->CaptionLabel();}
		virtual void setValue(int x, int y, double val);
		virtual QString text(int x, int y);
		void setValue(int x, int y);
		void scaleZMax(int val);
		void scaleZMin(int val);
		inline void invalidate(void) {pMatrix->invalidate();pMatrix->updateGL();}
		inline double YMinScale(void) {return pMatrix->RowMinScale();}
		inline double YMaxScale(void) {return pMatrix->RowMaxScale();}
		inline double XMinScale(void) {return pMatrix->ColMinScale();}
		inline double XMaxScale(void) {return pMatrix->ColMaxScale();}
		inline double ValueMinScale(void) {return pMatrix->TableMinScale();}
		inline double ValueMaxScale(void) {return pMatrix->TableMaxScale();}
		inline void updateTrace(int row, int col) { pMatrix->updateTrace(row, col); }
};

#endif

