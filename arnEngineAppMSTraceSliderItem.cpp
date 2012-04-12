/***************************************************************************
                          arnEngineAppMSTraceSliderItem.cpp  -  description
                             -------------------
    begin                : gio Feb 9 2006
    copyright            : (C) 2006 by Aurion s.r.l.
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
#include "CommonFunctions.h"
#include "arnEngineAppMSTraceSliderItem.h"
#include "arnSMiscMarkNumericArray.h"
#include "arnSMiscMarkNumericMatrix.h"
#include "arnSMiscMarkTraceNumericMatrix.h"
#include "arnEnCompositeArrayViewer.h"
#include "arnEnCompositeMatrixViewer.h"

arnEngineAppMSTraceSliderItem::arnEngineAppMSTraceSliderItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppMSSliderItem(parent,name,f)
{
	this->init();
}

arnEngineAppMSTraceSliderItem::arnEngineAppMSTraceSliderItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppMSSliderItem(label,parent,name,f)
{
	this->init();
}

arnEngineAppMSTraceSliderItem::arnEngineAppMSTraceSliderItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppMSSliderItem(label,value,parent,name,f)
{
	this->init();
}

arnEngineAppMSTraceSliderItem::arnEngineAppMSTraceSliderItem(const QString& label , int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppMSSliderItem(label,value,parent,name,f)
{
	this->init();
}

arnEngineAppMSTraceSliderItem::~arnEngineAppMSTraceSliderItem(void)
{
}

void arnEngineAppMSTraceSliderItem::init(void)
{
	AbilitaTrace = new QAction( this, "AbilitaTrace");
	if (!AbilitaTrace) arnCriticalExit();
	AbilitaTrace->setToggleAction(true);
	AbilitaTrace->setText("Enable Trace");
	AbilitaTrace->setMenuText("Enable Trace");
	AbilitaTrace->setToolTip("Enable the trace capability on selected COP");
	connect( AbilitaTrace,SIGNAL( activated() ), this, SLOT( AbilitaTrace_Hndl()));
	AbilitaTrace->addTo(pPopUp);
}

void arnEngineAppMSTraceSliderItem::EditCopertura_Hndl(void)
{
	if (!pReplaceObj) return;
	if (Viewer) {delete Viewer; Viewer = 0;}
	switch (pReplaceObj->type()) {
		case sot_MiscMarkNumericMatrix: {
			arnSMiscMarkNumericMatrix *NumM = (arnSMiscMarkNumericMatrix*)pReplaceObj;
			arnEnCompositeMatrixViewer *pNumericMat = new arnEnCompositeMatrixViewer(NumM->rows(),NumM->cols(),0,"MatrixValues");

			if (!pNumericMat) arnCriticalExit();
			Viewer = pNumericMat;
			pNumericMat->setGeometry(pNumericMat->x(),pNumericMat->y(),550,500);
			pNumericMat->setComment(NumM->comment());
			pNumericMat->setPrecX(NumM->precX()); //arnDebug("NumM->precX() %d\n",NumM->precX());
			pNumericMat->setPrecY(NumM->precY()); //arnDebug("NumM->precY() %d\n",NumM->precY());
			pNumericMat->setPrec(NumM->prec()); //arnDebug("NumM->prec() %d\n",NumM->prec());
			pNumericMat->setCaptionLabel(NumM->name());
			pNumericMat->setValueMinScale(NumM->floor());
			pNumericMat->setValueMaxScale(NumM->ceil());
			pNumericMat->setXAxisCaption(NumM->XAxisCaption());
			pNumericMat->setYAxisCaption(NumM->YAxisCaption());
			pNumericMat->setZAxisCaption(NumM->ZAxisCaption());
			for (int indx = 0; indx < NumM->cols(); indx++) {pNumericMat->setXValue(indx,NumM->valueX(indx));}
			for (int indx = 0; indx < NumM->rows(); indx++) {pNumericMat->setYValue(indx,NumM->valueY(indx));}
			for (int rowI = 0; rowI < NumM->rows(); rowI++)
				for (int colI = 0; colI < NumM->cols(); colI++) {
					if (NumM->isMarked(rowI,colI)) pNumericMat->setMatrixItemColor(rowI,colI, NumM->Color(rowI,colI));
					pNumericMat->setValue(rowI,colI,NumM->value(rowI,colI));
					}
			pNumericMat->setName(NumM->name());
			NumM->setViewer(pNumericMat);
			connect(pNumericMat, SIGNAL(valueChanged(int, int)), NumM, SLOT(setValue(int, int)));
			connect(pNumericMat, SIGNAL(defColorChanged(const QColor&)), NumM, SLOT(setDefaultColor(const QColor&)));
			connect(pNumericMat, SIGNAL(ColorChanged(int , int , const QColor&)), NumM, SLOT(setColor(int , int , const QColor&)));
			pNumericMat->show();
			pNumericMat->resize(pNumericMat->size());
			pNumericMat->adjustRows();
			pNumericMat->adjustCols();
			}
			break;
		case sot_MiscMarkNumericArray: {
			arnSMiscMarkNumericArray *NumA = (arnSMiscMarkNumericArray*)pReplaceObj;
			arnEnCompositeArrayViewer *pNumericArr = new arnEnCompositeArrayViewer(NumA->rows(),0,"ArrayValues");
			if (!pNumericArr) arnCriticalExit();
			Viewer = pNumericArr;
			pNumericArr->setGeometry(pNumericArr->x(),pNumericArr->y(),550,500);
			pNumericArr->setComment(NumA->comment());
			pNumericArr->setPrecX(NumA->precX()); //arnDebug("NumM->precX() %d\n",NumM->precX());
			pNumericArr->setPrec(NumA->prec()); //arnDebug("NumM->prec() %d\n",NumM->prec());
			pNumericArr->setCaptionLabel(NumA->name());
			pNumericArr->setValueMinScale(NumA->floor());
			pNumericArr->setValueMaxScale(NumA->ceil());
			pNumericArr->setXAxisCaption(NumA->XAxisCaption());
			pNumericArr->setCaption(NumA->YAxisCaption());
			for (int indx = 0; indx < NumA->rows(); indx++) {pNumericArr->setXValue(indx,NumA->valueX(indx));}
			for (int rowI = 0; rowI < NumA->rows(); rowI++) {
				if (NumA->isMarked(rowI)) pNumericArr->setArrayItemColor(rowI,NumA->Color(rowI));
				pNumericArr->setValue(rowI,NumA->value(rowI));
				}
			pNumericArr->setName(NumA->name());
			NumA->setViewer(pNumericArr);
			connect(pNumericArr, SIGNAL(valueChanged(int)), NumA, SLOT(setValue(int)));
			connect(pNumericArr, SIGNAL(defColorChanged(const QColor&)), NumA, SLOT(setDefaultColor(const QColor&)));
			connect(pNumericArr, SIGNAL(ColorChanged(int, const QColor&)), NumA, SLOT(setColor(int , const QColor&)));
			pNumericArr->show();
			pNumericArr->resize(pNumericArr->size());
			}
			break;
		case sot_MiscMarkTraceNumericMatrix: {
			arnSMiscMarkTraceNumericMatrix *NumM = (arnSMiscMarkTraceNumericMatrix*)pReplaceObj;
			arnEnCompositeMatrixViewer *pNumericMat = new arnEnCompositeMatrixViewer(NumM->rows(),NumM->cols(),0,"MatrixValues");

			if (!pNumericMat) arnCriticalExit();
			Viewer = pNumericMat;
			pNumericMat->setGeometry(pNumericMat->x(),pNumericMat->y(),550,500);
			pNumericMat->setComment(NumM->comment());
			pNumericMat->setPrecX(NumM->precX()); //arnDebug("NumM->precX() %d\n",NumM->precX());
			pNumericMat->setPrecY(NumM->precY()); //arnDebug("NumM->precY() %d\n",NumM->precY());
			pNumericMat->setPrec(NumM->prec()); //arnDebug("NumM->prec() %d\n",NumM->prec());
			pNumericMat->setCaptionLabel(NumM->name());
			pNumericMat->setValueMinScale(NumM->floor());
			pNumericMat->setValueMaxScale(NumM->ceil());
			pNumericMat->setXAxisCaption(NumM->XAxisCaption());
			pNumericMat->setYAxisCaption(NumM->YAxisCaption());
			pNumericMat->setZAxisCaption(NumM->ZAxisCaption());
			for (int indx = 0; indx < NumM->cols(); indx++) {pNumericMat->setXValue(indx,NumM->valueX(indx));}
			for (int indx = 0; indx < NumM->rows(); indx++) {pNumericMat->setYValue(indx,NumM->valueY(indx));}
			for (int rowI = 0; rowI < NumM->rows(); rowI++)
				for (int colI = 0; colI < NumM->cols(); colI++) {
					if (NumM->isMarked(rowI,colI)) pNumericMat->setMatrixItemColor(rowI,colI, NumM->Color(rowI,colI));
					pNumericMat->setValue(rowI,colI,NumM->value(rowI,colI));
					}
			pNumericMat->setName(NumM->name());
			NumM->setViewer(pNumericMat);
			connect(pNumericMat, SIGNAL(valueChanged(int, int)), NumM, SLOT(setValue(int, int)));
			connect(pNumericMat, SIGNAL(defColorChanged(const QColor&)), NumM, SLOT(setDefaultColor(const QColor&)));
			connect(pNumericMat, SIGNAL(ColorChanged(int , int , const QColor&)), NumM, SLOT(setColor(int , int , const QColor&)));
			connect(NumM, SIGNAL(MarkChanged(int, int, const QColor&)), pNumericMat, SLOT(setMatrixItemColor(int, int, const QColor&)));
			connect(NumM, SIGNAL(ValueChanged(int, int, double)), pNumericMat, SLOT(_setValue(int , int , double)));
			pNumericMat->show();
			pNumericMat->resize(pNumericMat->size());
			//BEGIN abilitazione del trace
			if (AbilitaTrace->isChecked()) {
				connect(NumM, SIGNAL(TraceChanged(int, int, const QColor&)), pNumericMat, SLOT(TraceColorUpdate(int, int, const QColor&)));
				}
			//END abilitazione del trace
			pNumericMat->adjustRows();
			pNumericMat->adjustCols();
			}
			break;
		default:
			break;
		}

}

void arnEngineAppMSTraceSliderItem::AbilitaTrace_Hndl(void)
{
	if (AbilitaTrace->isChecked()) {
		//arnDebug("Checked\n");
		}
	else {
		//arnDebug("Not Checked\n");
		}
}
