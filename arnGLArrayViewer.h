/***************************************************************************
                          arnGLArrayViewer.h  -  description
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

#ifndef ArnGLArrayViewerH
#define ArnGLArrayViewerH

#include <qlayout.h>
#include <qslider.h>
//#include <qpopupmenu.h>
#include <QMenu>
#include <qaction.h>
#include "arnGLArray.h"
#include "arnObjectViewer.h"


class arnGLArrayViewer : public arnObjectViewer
{
	Q_OBJECT
	private:
	private slots:
	protected:
		arnGLArray* pVector;
		QVBoxLayout* sldlayout;
		QVBoxLayout* zslayout; // zoom, scaling layout
		QHBoxLayout* layout;
		QGridLayout* gltablelayout;
		// slider per il controllo delle scale
		QSlider* scaleslMax;
		QSlider* scaleslMin;
		// per cambiamento dinamico pilotato da altri widget
		arnObjectViewer *pSender;

		double scaleYMaxValue;
		double scaleYMinValue;
		
		//QAction *SelezionaTutto;
		
	signals:
	protected slots:
		void scaleYMax(int val);
		void scaleYMin(int val);
	public :
		arnGLArrayViewer(arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
		arnGLArrayViewer(int XAxisSize = 5, arnGLArrayPaintingMode_t md = arn_glAPM_VERTICAL_LINES ,QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
		~arnGLArrayViewer(void);
		//virtual bool eventFilter(QObject* watched, QEvent* e);
		
		inline arnGLArrayPaintingMode_t mode (void) {return pVector->mode();}
		inline void setMode (arnGLArrayPaintingMode_t md) {pVector->setMode(md);}
		inline void setSender(arnObjectViewer *Sender) {pSender = Sender;}
		inline const arnGLArray* array(void) {return pVector;}
	public slots:
		inline void setXMinScale(double val) {pVector->setColMinScale(val);}
		inline void setXMaxScale(double val) {pVector->setColMaxScale(val);}
		void setValueMinScale(double val);
		void setValueMaxScale(double val);
		void setXValue(int indx, double val);
		inline void setXAxisLabel(const QString& str) {pVector->setXAxisLabel(str);}
		inline void setYAxisLabel(const QString& str) {pVector->setYAxisLabel(str);}
		inline void setCaptionLabel(const QString& str) {pVector->setCaptionLabel(str);}
		inline QString XAxisLabel(void) {return pVector->XAxisLabel();}
		inline QString YAxisLabel(void) {return pVector->YAxisLabel();}
		inline QString CaptionLabel(void) {return pVector->CaptionLabel();}
		virtual void setValue(int x, double val);
		virtual void setValue(int x, int y, double val); // per connetterlo alle tabelle
		virtual QString text(int x);
		virtual QString text(int x, int y);  // per connetterlo alle tabelle
		void setValue(int x);
		void setValue(int x, int y); // per connetterlo alle tabelle
		inline void invalidate(void) {pVector->invalidate();pVector->updateGL();}

};

#endif

