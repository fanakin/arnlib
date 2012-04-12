/***************************************************************************
                          arnGLMultipleArrayViewer.h  -  description
                             -------------------
    begin                : lun lug 28 2003
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

#ifndef ArnGLMultipleArrayViewerH
#define ArnGLMultipleArrayViewerH

#include <qlayout.h>
#include <qslider.h>
#include <QMenu>
#include <qaction.h>
#include "arnGLMultipleArray.h"
#include "arnObjectViewer.h"


class arnGLMultipleArrayViewer : public arnObjectViewer
{
	Q_OBJECT
	private:
	private slots:
	protected:
		arnGLMultipleArray* pMatrix;
		QVBoxLayout* sldlayout;
		QVBoxLayout* zslayout; // zoom, scaling layout
		QHBoxLayout* layout;
		QGridLayout* gltablelayout;
		// slider per il controllo delle scale
		QSlider* scaleslMax;
		QSlider* scaleslMin;
		// per cambiamento dinamico pilotato da altri widget
		arnObjectViewer *pSender;

		double scaleZMaxValue;
		double scaleZMinValue;
		
	signals:
	protected slots:
		void scaleZMax(int val);
		void scaleZMin(int val);
	public :
		arnGLMultipleArrayViewer(arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
		arnGLMultipleArrayViewer(int NRows = 5, int NCols = 5, arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES ,QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
		~arnGLMultipleArrayViewer(void);
		//virtual bool eventFilter(QObject* watched, QEvent* e);
		
		inline arnGLArrayPaintingMode_t mode (void) {return pMatrix->mode();}
		inline void setMode (arnGLArrayPaintingMode_t md) {pMatrix->setMode(md);}
		inline void setSender(arnObjectViewer *Sender) {pSender = Sender;}
		inline const arnGLMultipleArray* array(void) {return pMatrix;}
	public slots:
		inline void setXMinScale(double val) {pMatrix->setColMinScale(val);}
		inline void setXMaxScale(double val) {pMatrix->setColMaxScale(val);}
		inline void setYMinScale(double val) {pMatrix->setRowMinScale(val);}
		inline void setYMaxScale(double val) {pMatrix->setRowMaxScale(val);}
		void setValueMinScale(double val);
		void setValueMaxScale(double val);
		void setXValue(int indx, double val);
		void setYValue(int indx, double val);
		inline void setXAxisLabel(const QString& str) {pMatrix->setXAxisLabel(str);}
		inline void setYAxisLabel(const QString& str) {pMatrix->setYAxisLabel(str);}
		inline void setCaptionLabel(const QString& str) {pMatrix->setCaptionLabel(str);}
		inline QString XAxisLabel(void) {return pMatrix->XAxisLabel();}
		inline QString YAxisLabel(void) {return pMatrix->YAxisLabel();}
		inline QString CaptionLabel(void) {return pMatrix->CaptionLabel();}
		virtual void setValue(int row, int col, double val); // per connetterlo alle tabelle
		virtual QString text(int row, int col);  // per connetterlo alle tabelle
		void setValue(int row, int col); // per connetterlo alle tabelle
		inline void invalidate(void) {pMatrix->invalidate();pMatrix->updateGL();}
		inline void setColVisible(int col, bool v) {pMatrix->setColVisible(col,v);}
		inline void setRowVisible(int row, bool v) {pMatrix->setRowVisible(row,v);}
		inline void ShowRows(void) {
			pMatrix->ShowRows();
			scaleslMax->setValue(scaleslMax->maxValue());
			scaleslMin->setValue(scaleslMin->minValue());
			}
		inline void ShowCols(void) {
			pMatrix->ShowCols();
			scaleslMax->setValue(scaleslMax->maxValue());
			scaleslMin->setValue(scaleslMin->minValue());
			}
		inline void HideRows(void) {
			pMatrix->HideRows();
			scaleslMax->setValue(scaleslMax->maxValue());
			scaleslMin->setValue(scaleslMin->minValue());
			}
		inline void HideCols(void) {
			pMatrix->HideCols();
			scaleslMax->setValue(scaleslMax->maxValue());
			scaleslMin->setValue(scaleslMin->minValue());
			}
		inline void HideAllRows(void) {pMatrix->HideAllRows();}
		inline void HideAllCols(void) {pMatrix->HideAllCols();}
		inline void ShowAllRows(void) {pMatrix->ShowAllRows();}
		inline void ShowAllCols(void) {pMatrix->ShowAllCols();}
		inline void setRowColor(int row, QColor Color) {pMatrix->setRowColor(row,Color);}
		inline void setColColor(int col, QColor Color) {pMatrix->setColColor(col,Color);}
};

#endif

