/***************************************************************************
                          arnThrottleCycleVisualizer.cpp  -  description
                             -------------------
    begin                : lun giu 11 2007
    copyright            : (C) 2007 by Aurion s.r.l.
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

#include <stdlib.h>
#include <qfiledialog.h>
#include "CommonFunctions.h"
#include "arnThrottleCycleVisualizer.h"

arnThrottleCycleVisualizer::arnThrottleCycleVisualizer(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
	layout = new QGridLayout(this);
	StartCycle = new QPushButton(this);
	if (!StartCycle) arnCriticalExit();
	StartCycle->setObjectName(QString::fromUtf8("actStartCycle"));
	StartCycle->setText(QString::fromUtf8("Start"));
	StartCycle->setCheckable ( true );
	connect( StartCycle, SIGNAL(  toggled (bool)), this, SLOT( StartCycleButtonToggle_hndl(bool) ) );
	layout->addWidget(StartCycle,0,0,Qt::AlignLeft);

	openCycleFile = new QPushButton(this);
	if (!openCycleFile) arnCriticalExit();
	openCycleFile->setObjectName(QString::fromUtf8("OpenCycle"));
	openCycleFile->setText(QString::fromUtf8("Open Cycle"));
	connect( openCycleFile, SIGNAL(  clicked ()), this, SLOT( OpenCycleFileButtonClicked_hndl() ) );
	layout->addWidget(openCycleFile,0,1,Qt::AlignRight);

	checkFuelPump = new QPushButton(this);
	if (!checkFuelPump) arnCriticalExit();
	checkFuelPump->setObjectName(QString::fromUtf8("actCheckFuelPump"));
	checkFuelPump->setText(QString::fromUtf8("Check Fuel Pump"));
	//checkFuelPump->setCheckable ( true );
	connect( checkFuelPump, SIGNAL(  clicked ()), this, SLOT( checkFuelPumpButtonToggle_hndl() ) );
	layout->addWidget(checkFuelPump,1,0,Qt::AlignLeft);

	ThrCycle = 0;
	cleFName = "";
	timerExp = 1000;

	arnNumEnPacketItem* FuelPress = new arnNumEnPacketItem(QString("FuelPrs"),0,this);
	if (!FuelPress) arnCriticalExit();
    FuelPress->lcdValue()->setPaletteBackgroundColor(QColor(0,0,0));
    FuelPress->lcdValue()->setPaletteForegroundColor(QColor(255,0,0));
    FuelPress->lcdValue()->setSegmentStyle( QLCDNumber::Filled );

	arnNumEnPacketItem* BattV = new arnNumEnPacketItem(QString("VBatt"),0,this);
	if (!BattV) arnCriticalExit();
    BattV->lcdValue()->setPaletteBackgroundColor(QColor(0,0,0));
    BattV->lcdValue()->setPaletteForegroundColor(QColor(255,0,0));
    BattV->lcdValue()->setSegmentStyle( QLCDNumber::Filled );

	arnNumEnPacketItem* DutyPump = new arnNumEnPacketItem(QString("DutyPump"),0,this);
	if (!DutyPump) arnCriticalExit();
    DutyPump->lcdValue()->setPaletteBackgroundColor(QColor(0,0,0));
    DutyPump->lcdValue()->setPaletteForegroundColor(QColor(255,0,0));
    DutyPump->lcdValue()->setSegmentStyle( QLCDNumber::Filled );

	layout->addWidget(BattV,1,1,Qt::AlignLeft);
	layout->addWidget(DutyPump,2,0,Qt::AlignLeft);
	layout->addWidget(FuelPress,2,1,Qt::AlignLeft);

	checkOilPump1 = new QPushButton(this);
	if (!checkOilPump1) arnCriticalExit();
	checkOilPump1->setObjectName(QString::fromUtf8("actCheckOilPump1"));
	checkOilPump1->setText(QString::fromUtf8("Check Oil Pump1"));
	//checkFuelPump->setCheckable ( true );
	connect( checkOilPump1, SIGNAL(  clicked ()), this, SLOT( checkOilPump1ButtonToggle_hndl() ) );
	layout->addWidget(checkOilPump1,3,0,Qt::AlignLeft);

	checkOilPump2 = new QPushButton(this);
	if (!checkOilPump2) arnCriticalExit();
	checkOilPump2->setObjectName(QString::fromUtf8("actCheckOilPump2"));
	checkOilPump2->setText(QString::fromUtf8("Check Oil Pump2"));
	//checkFuelPump->setCheckable ( true );
	connect( checkOilPump2, SIGNAL(  clicked ()), this, SLOT( checkOilPump2ButtonToggle_hndl() ) );
	layout->addWidget(checkOilPump2,3,1,Qt::AlignLeft);
}

arnThrottleCycleVisualizer::~arnThrottleCycleVisualizer(void)
{
	if (ThrCycle) {delete ThrCycle; ThrCycle = 0;}
}

void arnThrottleCycleVisualizer::setPopupText(arnMultiLangItemType_t /*miIndx*/,QString /*txt*/)
{
}

void arnThrottleCycleVisualizer::setPopupTip(arnMultiLangItemType_t /*miIndx*/,QString /*txt*/)
{
}

QString arnThrottleCycleVisualizer::popupText(arnMultiLangItemType_t /*miIndx*/)
{
	return QString("");
}

QString arnThrottleCycleVisualizer::popupTip(arnMultiLangItemType_t /*miIndx*/)
{
	return QString("");
}

void arnThrottleCycleVisualizer::StartCycleButtonToggle_hndl(bool toggle)
{
	if (toggle) {
		if (cleFName == "") {
			if ((cleFName = QFileDialog::getOpenFileName (this, 
					QString("Open .cle File"), 
					QString("./"), 
					QString("*.cle")
					)) != "") {
				//arnDebug("%s\n",cleFName.latin1());
				}
			else return;
			}
		if (ThrCycle) {delete ThrCycle; ThrCycle = 0;}
		ThrCycle = new arnThrottleCycle(cleFName);
		if (!ThrCycle) return;
		timer = new QTimer(this);
		if (!timer) return;
		timer->setInterval(timerExp);
		connect( timer , SIGNAL(timeout()),this , SLOT(timer_hndl()));
		if (ThrCycle->getCycleSize() > 0) {
			cleIndx = 0;
			timer->setInterval(ThrCycle->getTimeStepDuring(cleIndx) / 2);
			timer->start();
			emit ThrottleValueChanged(ThrCycle->getOpenPercentage(cleIndx));
			}
		}
	else {
		if (ThrCycle)  {delete ThrCycle; ThrCycle = 0;}
		if (timer) {
			timer->stop();
			disconnect( timer , SIGNAL(timeout()),this , SLOT(timer_hndl()));
			delete timer;
			timer = 0;
			}
		}
}

void arnThrottleCycleVisualizer::OpenCycleFileButtonClicked_hndl(void)
{
	if ((cleFName = QFileDialog::getOpenFileName (this, 
			QString("Open .cle File"), 
			QString("./"), 
			QString("*.cle")
			)) != "") {
		//arnDebug("%s\n",cleFName.latin1());
		}
}

void arnThrottleCycleVisualizer::checkFuelPumpButtonToggle_hndl(void)
{
}

void arnThrottleCycleVisualizer::checkOilPump1ButtonToggle_hndl(void)
{
}

void arnThrottleCycleVisualizer::checkOilPump2ButtonToggle_hndl(void)
{
}

void arnThrottleCycleVisualizer::timer_hndl(void)
{
	cleIndx++;
	if (cleIndx == ThrCycle->getCycleSize()) cleIndx = 0;
	timer->stop();
	timer->setInterval(ThrCycle->getTimeStepDuring(cleIndx) / 2);
	timer->start();
	emit ThrottleValueChanged(ThrCycle->getOpenPercentage(cleIndx));
}

void arnThrottleCycleVisualizer::SetButtonVisible(unsigned char indx,bool flg)
{
	switch (indx) {
		case 0: StartCycle->setVisible(flg); break;
		case 1: openCycleFile->setVisible(flg); break;
		case 2: checkFuelPump->setVisible(flg); break;
		default: break;
		}
}

void arnThrottleCycleVisualizer::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
	FuelPress->show();
	BattV->show();
	DutyPump->show();
}
