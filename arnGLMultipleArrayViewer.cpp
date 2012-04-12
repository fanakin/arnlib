/***************************************************************************
                          arnGLArrayViewer.cpp  -  description
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

#include <qcursor.h>
#include "arnGLMultipleArrayViewer.h"

arnGLMultipleArrayViewer:: arnGLMultipleArrayViewer(arnGLArrayPaintingMode_t md, QWidget *parent, const char *name, Qt::WFlags f)
    :  arnObjectViewer(parent, name, f)
{
    tpy = avt_GLMultipleArrayViewer;

    pMatrix = new arnGLMultipleArray(5, 5, md, this, "Vector"); /** supposed to be that **/
    if (!pMatrix) arnCriticalExit();

    layout = new QHBoxLayout( this , 2);
    if (!layout) arnCriticalExit();

    sldlayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!sldlayout) arnCriticalExit();

    zslayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!zslayout) arnCriticalExit();

    gltablelayout = new QGridLayout( (QWidget*)0, 1, 1, 2);
    if (!gltablelayout) arnCriticalExit();
    gltablelayout->addWidget( pMatrix, 0, 0 );

    scaleslMax = new QSlider(0, 100, 10, 100, Qt::Vertical,this,"scaleslMax");
    if (!scaleslMax) arnCriticalExit();
    scaleslMin = new QSlider(0, 100, 10, 0,Qt::Vertical,this,"scaleslMin");
    if (!scaleslMin) arnCriticalExit();
    zslayout->addWidget(scaleslMax);
    zslayout->addWidget(scaleslMin);

    layout->addLayout(sldlayout, 1);
    layout->addLayout(gltablelayout, 8);
    layout->addLayout(zslayout, 1);

    QObject::connect( scaleslMax, SIGNAL(valueChanged(int)),this,SLOT(scaleZMax(int)) );
    QObject::connect( scaleslMin, SIGNAL(valueChanged(int)),this,SLOT(scaleZMin(int)) );

}

arnGLMultipleArrayViewer::arnGLMultipleArrayViewer(int NRows, int NCols, arnGLArrayPaintingMode_t md,QWidget *parent, const char *name, Qt::WFlags f)
    :  arnObjectViewer(parent, name, f)
{
    tpy = avt_GLMultipleArrayViewer;

    pMatrix = new arnGLMultipleArray(NRows,NCols, md, this, "Vector"); // col
    if (!pMatrix) arnCriticalExit();

    layout = new QHBoxLayout( this , 2);
    if (!layout) arnCriticalExit();

    sldlayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!sldlayout) arnCriticalExit();

    zslayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!zslayout) arnCriticalExit();

    gltablelayout = new QGridLayout( (QWidget*)0, 1, 1, 2);
    if (!gltablelayout) arnCriticalExit();
    gltablelayout->addWidget( pMatrix, 0, 0 );

    scaleslMax = new QSlider(0, 100, 10, 100, Qt::Vertical,this,"scalesl");
    if (!scaleslMax) arnCriticalExit();
    scaleslMin = new QSlider(0, 100, 10, 0,Qt::Vertical,this,"zoomsl");
    if (!scaleslMin) arnCriticalExit();
    zslayout->addWidget(scaleslMax);
    zslayout->addWidget(scaleslMin);

    layout->addLayout(sldlayout, 1);
    layout->addLayout(gltablelayout, 8);
    layout->addLayout(zslayout, 1);

    QObject::connect( scaleslMax, SIGNAL(valueChanged(int)),this,SLOT(scaleZMax(int)) );
    QObject::connect( scaleslMin, SIGNAL(valueChanged(int)),this,SLOT(scaleZMin(int)) );

}

arnGLMultipleArrayViewer::~arnGLMultipleArrayViewer(void)
{
}

//bool arnGLArrayViewer::eventFilter(QObject* watched, QEvent* e)
//{
//	if (e->type() == QEvent::ContextMenu) {
//		pPopUp->exec(QCursor::pos());
//		return true;
//		}
//	return arnObjectViewer::eventFilter(watched, e);
//}

void arnGLMultipleArrayViewer::setXValue(int indx, double val)
{
	pMatrix->setColValue(indx,val);
}

void arnGLMultipleArrayViewer::setYValue(int indx, double val)
{
	pMatrix->setRowValue(indx,val);
}


void arnGLMultipleArrayViewer::setValue(int row, int col, double val)
{
	pMatrix->setValue(row, col, val); // row, col
}


void arnGLMultipleArrayViewer::setValue(int row, int col)
{
    if (!pSender) arnCriticalExit();
    bool ok;
    double tNum = pSender->text(row,col).toDouble(&ok);
    if (!ok) return;
    pMatrix->setValue(row,col,tNum);
}

QString arnGLMultipleArrayViewer::text(int row, int col)
{
	return pMatrix->text(row,col);
}

void arnGLMultipleArrayViewer::scaleZMax(int val)
{
	double scl = val/* * scaleZMaxValue / scalesl->maxValue()*/;
	pMatrix->setTableMaxScale(scl);
	pMatrix->invalidate();
	pMatrix->updateGL();
}

void arnGLMultipleArrayViewer::scaleZMin(int val)
{
	double scl = val/* * scaleZMaxValue / scalesl->maxValue()*/;
	pMatrix->setTableMinScale(scl);
	pMatrix->invalidate();
	pMatrix->updateGL();
}

void arnGLMultipleArrayViewer::setValueMinScale(double val) 
{
	pMatrix->setTableMinScale(val);
	scaleZMinValue = val;
	scaleslMax->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMax->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMax->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMax->setValue((int)(pMatrix->TableMaxScale()));
	scaleslMin->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMin->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMin->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMin->setValue((int)(pMatrix->TableMinScale()));
}
void arnGLMultipleArrayViewer::setValueMaxScale(double val) 
{
	pMatrix->setTableMaxScale(val);
	scaleZMaxValue = val;
	scaleslMax->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMax->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMax->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMax->setValue((int)(pMatrix->TableMaxScale()));
	scaleslMin->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMin->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMin->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMin->setValue((int)(pMatrix->TableMinScale()));
}
