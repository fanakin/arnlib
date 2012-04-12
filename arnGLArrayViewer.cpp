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
#include "arnGLArrayViewer.h"

arnGLArrayViewer:: arnGLArrayViewer(arnGLArrayPaintingMode_t md, QWidget *parent, const char *name, Qt::WFlags f)
    :  arnObjectViewer(parent, name, f)
{
    tpy = avt_GLArrayViewer;

    pVector = new arnGLArray(5, md, this, "Vector");
    if (!pVector) arnCriticalExit();

    layout = new QHBoxLayout( this , 2);
    if (!layout) arnCriticalExit();

    sldlayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!sldlayout) arnCriticalExit();

    zslayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!zslayout) arnCriticalExit();

    gltablelayout = new QGridLayout( (QWidget*)0, 1, 1, 2);
    if (!gltablelayout) arnCriticalExit();
    gltablelayout->addWidget( pVector, 0, 0 );

    scaleslMax = new QSlider(0, 100, 10, 100, Qt::Vertical,this,"scaleslMax");
    if (!scaleslMax) arnCriticalExit();
    scaleslMin = new QSlider(0, 100, 10, 0,Qt::Vertical,this,"scaleslMin");
    if (!scaleslMin) arnCriticalExit();
    zslayout->addWidget(scaleslMax);
    zslayout->addWidget(scaleslMin);

    layout->addLayout(sldlayout, 1);
    layout->addLayout(gltablelayout, 8);
    layout->addLayout(zslayout, 1);

//
    QObject::connect( scaleslMax, SIGNAL(valueChanged(int)),this,SLOT(scaleZMax(int)) );
	QObject::connect( scaleslMin, SIGNAL(valueChanged(int)),this,SLOT(scaleZMin(int)) );

}

arnGLArrayViewer::arnGLArrayViewer(int XAxisSize, arnGLArrayPaintingMode_t md,QWidget *parent, const char *name, Qt::WFlags f)
    :  arnObjectViewer(parent, name, f)
{
    tpy = avt_GLArrayViewer;

    pVector = new arnGLArray(XAxisSize, md, this, "Vector"); // col
    if (!pVector) arnCriticalExit();

    layout = new QHBoxLayout( this , 2);
    if (!layout) arnCriticalExit();

    sldlayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!sldlayout) arnCriticalExit();

    zslayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!zslayout) arnCriticalExit();

    gltablelayout = new QGridLayout( (QWidget*)0, 1, 1, 2);
    if (!gltablelayout) arnCriticalExit();
    gltablelayout->addWidget( pVector, 0, 0 );

    scaleslMax = new QSlider(0, 100, 10, 100, Qt::Vertical,this,"scaleslMax");
    if (!scaleslMax) arnCriticalExit();
    scaleslMin = new QSlider(0, 100, 10, 0,Qt::Vertical,this,"scaleslMin");
    if (!scaleslMin) arnCriticalExit();
    zslayout->addWidget(scaleslMax);
    zslayout->addWidget(scaleslMin);

    layout->addLayout(sldlayout, 1);
    layout->addLayout(gltablelayout, 8);
    layout->addLayout(zslayout, 1);

//
    QObject::connect( scaleslMax, SIGNAL(valueChanged(int)),this,SLOT(scaleYMax(int)) );
	QObject::connect( scaleslMin, SIGNAL(valueChanged(int)),this,SLOT(scaleYMin(int)) );

}

arnGLArrayViewer::~arnGLArrayViewer(void)
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

void arnGLArrayViewer::setXValue(int indx, double val)
{
    pVector->setColValue(indx,val);
}

void arnGLArrayViewer::setValue(int x, double val)
{
    pVector->setValue(x,val); // row, col
}

void arnGLArrayViewer::setValue(int x)
{
    if (!pSender) arnCriticalExit();
    bool ok;
    double tNum = pSender->text(x).toDouble(&ok);
    if (!ok) return;
    pVector->setValue(x,tNum);
    pVector->invalidate();
    pVector->updateGL();
}

QString arnGLArrayViewer::text(int x)
{
    return pVector->text(x); // row, col
}

void arnGLArrayViewer::setValue(int x, int y, double val)
{
    if (y > 1) arnCriticalExit();
    pVector->setValue(x,val); //  row
}

void arnGLArrayViewer::setValue(int x, int y)
{
    if (!pSender) arnCriticalExit();
    if (y > 1) arnCriticalExit();
    bool ok;
    double tNum = pSender->text(x).toDouble(&ok);
    if (!ok) return;
    pVector->setValue(x,tNum);
    pVector->invalidate();
    pVector->updateGL();
}

QString arnGLArrayViewer::text(int x, int y)
{
    if (y > 1) arnCriticalExit();
    return pVector->text(x); // row
}

void arnGLArrayViewer::scaleYMax(int val)
{
	//double sclY = val * scaleYMaxValue / scalesl->maxValue();
	double sclY = val;
	pVector->setTableMaxScale(sclY);
	pVector->invalidate();
	pVector->updateGL();
}

void arnGLArrayViewer::scaleYMin(int val)
{
	//double sclY = val * scaleYMaxValue / scalesl->maxValue();
	double sclY = val;
	pVector->setTableMinScale(sclY);
	pVector->invalidate();
	pVector->updateGL();
}

void arnGLArrayViewer::setValueMinScale(double val) 
{
	pVector->setTableMinScale(val);
	scaleYMinValue = val;
	scaleslMax->setMinimum((int)(pVector->TableMinScale()));
	scaleslMax->setMaximum((int)(pVector->TableMaxScale()));
	scaleslMax->setPageStep((int)((pVector->TableMaxScale() - pVector->TableMinScale()) / 20));
	scaleslMax->setValue((int)(pVector->TableMaxScale()));
	scaleslMin->setMinimum((int)(pVector->TableMinScale()));
	scaleslMin->setMaximum((int)(pVector->TableMaxScale()));
	scaleslMin->setPageStep((int)((pVector->TableMaxScale() - pVector->TableMinScale()) / 20));
	scaleslMin->setValue((int)(pVector->TableMinScale()));
}
void arnGLArrayViewer::setValueMaxScale(double val) 
{
	pVector->setTableMaxScale(val);
	scaleYMaxValue = val;
	scaleslMax->setMinimum((int)(pVector->TableMinScale()));
	scaleslMax->setMaximum((int)(pVector->TableMaxScale()));
	scaleslMax->setPageStep((int)((pVector->TableMaxScale() - pVector->TableMinScale()) / 20));
	scaleslMax->setValue((int)(pVector->TableMaxScale()));
	scaleslMin->setMinimum((int)(pVector->TableMinScale()));
	scaleslMin->setMaximum((int)(pVector->TableMaxScale()));
	scaleslMin->setPageStep((int)((pVector->TableMaxScale() - pVector->TableMinScale()) / 20));
	scaleslMin->setValue((int)(pVector->TableMinScale()));
}


