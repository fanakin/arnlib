/***************************************************************************
                          arnGLMatrixViewer.cpp  -  description
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


#include "arnGLMatrixViewer.h"

arnGLMatrixViewer:: arnGLMatrixViewer(arnGLTablePaintingMode_t md, QWidget *parent, const char *name, Qt::WFlags f)
    :  arnObjectViewer(parent, name, f)
{
    tpy = avt_GLMatrixViewer;

    pMatrix = new arnGLTable(5, 5, md, this, "Matrix");
    if (!pMatrix) arnCriticalExit();
}

arnGLMatrixViewer::arnGLMatrixViewer(int XAxisSize, int YAxisSize, arnGLTablePaintingMode_t md,QWidget *parent, const char *name, Qt::WFlags f)
    :  arnObjectViewer(parent, name, f)
{
    tpy = avt_GLMatrixViewer;

    pMatrix = new arnGLTable(YAxisSize, XAxisSize, md, this, "Matrix"); // row, col
    if (!pMatrix) arnCriticalExit();

    layout = new QHBoxLayout( this/* , 2*/);
    if (!layout) arnCriticalExit();

    sldlayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!sldlayout) arnCriticalExit();

    zslayout = new QVBoxLayout( (QWidget*)0, 2) ;
    if (!zslayout) arnCriticalExit();
    
    gltablelayout = new QGridLayout( (QWidget*)0, 1, 1, 2);
    if (!gltablelayout) arnCriticalExit();
    gltablelayout->addWidget( pMatrix, 0, 0 );

    xsl = new QSlider(0, 360,36, 0, Qt::Vertical,this,"xsl");
    if (!xsl) arnCriticalExit();
    ysl = new QSlider(0, 360,36, 0,Qt::Vertical,this,"ysl");
    if (!ysl) arnCriticalExit();
    zsl = new QSlider(0, 360,36, 0,Qt::Vertical,this,"zsl");
    if (!zsl) arnCriticalExit();
    sldlayout->addWidget(xsl);
    sldlayout->addWidget(ysl);
    sldlayout->addWidget(zsl);

    scaleslMax = new QSlider(0, 100, 10, 100, Qt::Vertical,this,"scaleslMax");
	//scaleslMax = new QSlider((int)(pMatrix->TableMinScale()), (int)(pMatrix->TableMaxScale()),
	//	(int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20),(int)(pMatrix->TableMaxScale()), Qt::Vertical,this,"scaleslMax");
    if (!scaleslMax) arnCriticalExit();
    scaleslMin = new QSlider(0, 100, 10, 0,Qt::Vertical,this,"scaleslMin");
	//scaleslMin = new QSlider((int)(pMatrix->TableMinScale()), (int)(pMatrix->TableMaxScale()),
	//	 (int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20), (int)(pMatrix->TableMinScale()),Qt::Vertical,this,"scaleslMin");
    if (!scaleslMin) arnCriticalExit();
    zslayout->addWidget(scaleslMax);
    zslayout->addWidget(scaleslMin);
        
    layout->addLayout(sldlayout, 1);
    layout->addLayout(gltablelayout, 8);
    layout->addLayout(zslayout, 1);

    QObject::connect( xsl, SIGNAL(valueChanged(int)),pMatrix,SLOT(setXRotation(int)) );
    QObject::connect( ysl, SIGNAL(valueChanged(int)),pMatrix,SLOT(setYRotation(int)) );
    QObject::connect( zsl, SIGNAL(valueChanged(int)),pMatrix,SLOT(setZRotation(int)) );

    QObject::connect( scaleslMax, SIGNAL(valueChanged(int)),this,SLOT(scaleZMax(int)) );
	QObject::connect( scaleslMin, SIGNAL(valueChanged(int)),this,SLOT(scaleZMin(int)) );
    
}

arnGLMatrixViewer::~arnGLMatrixViewer(void)
{
}

void arnGLMatrixViewer::setXValue(int indx, double val)
{
    pMatrix->setColValue(indx,val);
}

void arnGLMatrixViewer::setYValue(int indx, double val)
{
    pMatrix->setRowValue(indx,val);
}

void arnGLMatrixViewer::setValue(int x, int y, double val)
{
    pMatrix->setValue(y,x,val); // row, col
}

void arnGLMatrixViewer::setValue(int x, int y)
{
    if (!pSender) arnCriticalExit();
    bool ok;
    double tNum = pSender->text(x,y).toDouble(&ok);
    if (!ok) return;
    pMatrix->setValue(x,y ,tNum);
    pMatrix->invalidate();
    pMatrix->updateGL();
}

QString arnGLMatrixViewer::text(int x, int y)
{
    return pMatrix->text(y,x); // row, col
}

void arnGLMatrixViewer::setValueMinScale(double val) 
{
	pMatrix->setTableMinScale(val);
	scaleZMinValue = val;
// 	arnDebug("scaleZMinValue:%f",scaleZMinValue);
	scaleslMax->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMax->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMax->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMax->setValue((int)(pMatrix->TableMaxScale()));
	scaleslMin->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMin->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMin->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMin->setValue((int)(pMatrix->TableMinScale()));
}
void arnGLMatrixViewer::setValueMaxScale(double val) 
{
	pMatrix->setTableMaxScale(val);
	scaleZMaxValue = val;
// 	arnDebug("scaleZMaxValue:%f",scaleZMaxValue);
	scaleslMax->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMax->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMax->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMax->setValue((int)(pMatrix->TableMaxScale()));
	scaleslMin->setMinimum((int)(pMatrix->TableMinScale()));
	scaleslMin->setMaximum((int)(pMatrix->TableMaxScale()));
	scaleslMin->setPageStep((int)((pMatrix->TableMaxScale() - pMatrix->TableMinScale()) / 20));
	scaleslMin->setValue((int)(pMatrix->TableMinScale()));
}

void arnGLMatrixViewer::scaleZMax(int val)
{
	//double sclZ = val * scaleZMaxValue / scaleslMax->maxValue();
	double sclZ = val;
	pMatrix->setTableMaxScale(sclZ);
	pMatrix->invalidate();
	pMatrix->updateGL();
}

void arnGLMatrixViewer::scaleZMin(int val)
{
	//double sclZ = val * scaleZMinValue / scaleslMin->maxValue();
	double sclZ = val;
// arnDebug("sclZ:%f",sclZ);
	pMatrix->setTableMinScale(sclZ);
	pMatrix->invalidate();
	pMatrix->updateGL();
}
