/***************************************************************************
                          arnEngineAppSliderItem.cpp  -  description
                             -------------------
    begin                : dom apr 24 2003
    copyright            : (C) 2005 by fabio giovagnini
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
#include "arnEngineAppSliderItem.h"
#include "arnSMiscMarkNumericMatrix.h"
#include "arnEnCompositeMatrixViewer.h"

arnEngineAppSliderItem::arnEngineAppSliderItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnSliderItem(parent,name,f)
{
	this->init();
}

arnEngineAppSliderItem::arnEngineAppSliderItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnSliderItem(label,parent,name,f)
{
	this->init();
}

arnEngineAppSliderItem::arnEngineAppSliderItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnSliderItem(label,value,parent,name,f)
{
	this->init();
}

arnEngineAppSliderItem::arnEngineAppSliderItem(const QString& label , int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnSliderItem(label,value,parent,name,f)
{
	this->init();
}

arnEngineAppSliderItem::~arnEngineAppSliderItem(void)
{
	if (Viewer) {delete Viewer; Viewer = 0;}
}

void arnEngineAppSliderItem::init(void)
{
	pReplaceObj = 0;
	Viewer = 0;
	
	AbilitaCopertura = new QAction( this, "AbilitaCopertura");
	if (!AbilitaCopertura) arnCriticalExit();
	AbilitaCopertura->setToggleAction(true);
	AbilitaCopertura->setText( trUtf8("En COP"));
	AbilitaCopertura->setMenuText( trUtf8("En COP"));
	AbilitaCopertura->setToolTip( trUtf8("Abilita il piano di copertura come sorgente di correzione"));
	connect( AbilitaCopertura,SIGNAL( toggled(bool) ), this, SLOT( AbilitaCopertura_Hndl(bool) ) );
	AbilitaCopertura->addTo(pPopUp);

	
	EditCopertura = new QAction( this, "EditCopertura");
	if (!EditCopertura) arnCriticalExit();
	//EditCopertura->setToggleAction(true);
	EditCopertura->setText( trUtf8("Edit COP"));
	EditCopertura->setMenuText( trUtf8("Edit COP"));
	EditCopertura->setToolTip( trUtf8("edita il piano di copertura come sorgente di correzione"));
	connect( EditCopertura,SIGNAL( activated() ), this, SLOT( EditCopertura_Hndl() ) );
	EditCopertura->addTo(pPopUp);
}

void arnEngineAppSliderItem::AbilitaCopertura_Hndl(bool /*tg*/)
{
}

void arnEngineAppSliderItem::EditCopertura_Hndl(void)
{
	if (!pReplaceObj) return;
	if (Viewer) {delete Viewer; Viewer = 0;}
	switch (pReplaceObj->type()) {
		case sot_MiscMarkNumericMatrix: {
			arnSMiscMarkNumericMatrix *NumM = (arnSMiscMarkNumericMatrix*)pReplaceObj;
			arnEnCompositeMatrixViewer *pNumericMat = new arnEnCompositeMatrixViewer(NumM->rows(),NumM->cols(),0,"MatrixValues");

			if (!pNumericMat) arnCriticalExit();
			Viewer = pNumericMat;
			pNumericMat->resize(550,500);
			pNumericMat->move(50,50);
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
			}
			break;
		default:
			break;
		}
}
