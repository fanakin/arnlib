/***************************************************************************
                          arnThermoPacketItem.cpp  -  description
                             -------------------
    begin                : ven Mag 22 2009
    copyright            : (C) 2009 by fabio giovagnini
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
#include "CommonFunctions.h"
#include "arnThermoPacketItem.h"

arnThermoPacketItem::arnThermoPacketItem(QWidget *parent, Qt::WFlags f)
    : QWidget(parent,f)
{
	this->init("",0);
}

arnThermoPacketItem::arnThermoPacketItem(const QString& label,double value, QWidget *parent, Qt::WFlags f)
    : QWidget(parent,f)
{
	this->init(label,value);
	Name->setText(label);
}


arnThermoPacketItem::~arnThermoPacketItem(void)
{

}

void arnThermoPacketItem::init(const QString& label,double value)
{
	tpe = apit_ThermoPacketItem;
        QBrush aBrush;

	Value = new QwtThermo(this);
	if (!Value) arnCriticalExit();
	Value->setPipeWidth(30);
	Value->setRange(0,100);
	Value->setValue(value);
        Value->setFillBrush( Qt::blue );
        Value->setAlarmBrush( Qt::red );
        Value->setAlarmLevel(80);
	Value->setAlarmEnabled(true);

	Name = new QLabel(label, this);
	if (!Name) arnCriticalExit();
	Name->setAlignment(Qt::AlignTop | Qt::AlignLeft);
	QFont F(Name->font());
	F.setPointSize(10);
	Name->setFont(F);

	NumValue = new QLabel(QString::number(Value->value(),'f',1), this);
	if (!NumValue) arnCriticalExit();
	NumValue->setAlignment(Qt::AlignTop | Qt::AlignRight);
	//F.setBold(true);
	NumValue->setFont(F);

	pGLayout = new QGridLayout(this);
	if (!pGLayout) arnCriticalExit();
	pGLayout->setMargin(0);
	pGLayout->setSpacing(0);
	pGLayout->addWidget(Value, 0,0,10,2,Qt::AlignJustify);
	pGLayout->addWidget(NumValue,11,0,Qt::AlignRight);
	pGLayout->addWidget(Name,11,1,Qt::AlignRight);

	pPopUp = new QMenu(this);
	if (!pPopUp) arnCriticalExit();

	Nascondi = new QAction( this, "Nascondi");
	if (!Nascondi) arnCriticalExit();
	Nascondi->setText( trUtf8("Hide"));
	Nascondi->setMenuText( trUtf8("Hide"));
	Nascondi->setToolTip( trUtf8("Hide the channel if you are not interested of"));

	connect( Nascondi,SIGNAL( activated() ), this, SLOT( Nascondi_Hndl() ) );
	Nascondi->addTo(pPopUp);
}

// void arnPacketItem::mousePressEvent(QMouseEvent *e)
// {
// 	if (e->button () == Qt::LeftButton) {
// 		QFrame::mousePressEvent(e);arnPacketItem
// 		}
// 	else if (e->button () == Qt::RightButton) {
// 		if (pPopUp) pPopUp->exec(QCursor::pos());
// 		QFrame::mousePressEvent(e);
// 		}
// 	else QFrame::mousePressEvent(e);
// }


void arnThermoPacketItem::Nascondi_Hndl(void)
{
	hide();
}
