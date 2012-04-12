/***************************************************************************
                          arnNumEnPacketItem.cpp  -  description
                             -------------------
    begin                : mar apr 4 2003
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
#include <QtGui>
#include "CommonFunctions.h"
#include "arnNumEnPacketItem.h"


arnNumEnPacketItem::arnNumEnPacketItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumPacketItem(parent,name,f)
{
	this->init();
}

arnNumEnPacketItem::arnNumEnPacketItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumPacketItem(label,parent,name,f)
{
	this->init();
}


arnNumEnPacketItem::arnNumEnPacketItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumPacketItem(label,value,parent,name,f)
{
	this->init();
}

arnNumEnPacketItem::arnNumEnPacketItem(const QString& label, int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumPacketItem(label,value,parent,name,f)
{
	this->init();
}

arnNumEnPacketItem::arnNumEnPacketItem(const QString& label, double value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnNumPacketItem(label,value,parent,name,f)
{
	this->init();
}

arnNumEnPacketItem::~arnNumEnPacketItem(void)
{

}

void arnNumEnPacketItem::init(void)
{
	tpe = apit_NumEnPacketItem;

	inizialized = false;
	
	AbilitaAllarme = new QAction( this, "AbilitaAllarme");
	if (!AbilitaAllarme) arnCriticalExit();
	AbilitaAllarme->setToggleAction(true);
	AbilitaAllarme->setText( trUtf8("Alarm"));
	AbilitaAllarme->setMenuText( trUtf8("Alarm"));
	AbilitaAllarme->setToolTip( trUtf8("Enable the alarm on the channel"));

	ModificaThUP = new QAction( this, "ModificaThUP");
	if (!ModificaThUP) arnCriticalExit();
	ModificaThUP->setText( trUtf8("ThUP"));
	ModificaThUP->setMenuText( trUtf8("ThUP"));
	ModificaThUP->setToolTip( trUtf8("Show and modify the Alarm Upper Threshold"));

	ModificaThDOWN = new QAction( this, "ModificaThDOWN");
	if (!ModificaThDOWN) arnCriticalExit();
	ModificaThDOWN->setText( trUtf8("ThDOWN"));
	ModificaThDOWN->setMenuText( trUtf8("ThDOWN"));
	ModificaThDOWN->setToolTip( trUtf8("Show and modify the Alarm Lower Threshold"));

	connect( AbilitaAllarme,SIGNAL( toggled(bool) ), this, SLOT( AbilitaAllarme_Hndl(bool) ) );
	connect( ModificaThUP,SIGNAL( activated() ), this, SLOT(ModificaThUP_Hndl() ) );
	connect( ModificaThDOWN,SIGNAL( activated() ), this, SLOT( ModificaThDOWN_Hndl() ) );
	AbilitaAllarme->addTo(pPopUp);
	ModificaThUP->addTo(pPopUp);
	ModificaThDOWN->addTo(pPopUp);

	upperTh = 0;
	lowerTh = 0;
	timer = new QTimer(this, "blinkingTimer");
	if (!timer) arnCriticalExit();
	connect (timer,SIGNAL( timeout()), this, SLOT(Timeout_Hndl(void)));

	ThUPVal = new QLineEdit(QString::number(upperTh,'f',2),this,"ThUPVal");
	if (!ThUPVal) arnCriticalExit();
	ThUPVal->hide();
	connect( ThUPVal,SIGNAL( returnPressed() ), this, SLOT( ThUPValRetPress_hndl() ) );

	ThDOWNVal = new QLineEdit(QString::number(lowerTh,'f',2),this,"ThUPVal");
	if (!ThDOWNVal) arnCriticalExit();
	ThDOWNVal->hide();
	connect( ThDOWNVal,SIGNAL( returnPressed() ), this, SLOT( ThDOWNValRetPress_hndl() ) );

}

//
// ---- uso quello definito in arnNumPacketItem
//
// void arnPacketItem::mousePressEvent(QMouseEvent *e)
// {
// 	if (e->button () == Qt::LeftButton) {
// 		QFrame::mousePressEvent(e);
// 		}
// 	else if (e->button () == Qt::RightButton) {
// 		if (pPopUp) pPopUp->exec(QCursor::pos());
// 		QFrame::mousePressEvent(e);
// 		}
// 	else QFrame::mousePressEvent(e);
// }

void arnNumEnPacketItem::setUpperTh(const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setUpperTh(tNum);
}

void arnNumEnPacketItem::setLowerTh(const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setLowerTh(tNum);
}

void arnNumEnPacketItem::checkWarning(void)
{
	if (manualBlinkEnabled) return;

	if (timer->isActive()) {
		if ((Value->value() >= lowerTh) && (Value->value() <= upperTh)) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(BACKGROUNDCOLOR));
			Value->setPalette (pal);
			Value->update();
			timer->stop();
			}
		}
	else {
		if ((Value->value() > upperTh)) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(TOHIGHCOLOR));
			Value->setPalette (pal);
			Value->update();
			timer->start(1000);
			}
		else if (Value->value() < lowerTh) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(TOLOWCOLOR));
			Value->setPalette (pal);
			Value->update();
			timer->start(1000);
			}
		else {
			}
		}
}

void arnNumEnPacketItem::Timeout_Hndl(void)
{
	if (manualBlinkEnabled) return;

	if ((Value->value() > upperTh)) {
		if (Value->paletteBackgroundColor() == QColor(TOHIGHCOLOR)) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(BACKGROUNDCOLOR));
			Value->setPalette (pal);
			Value->update();
			}
		else if (Value->paletteBackgroundColor() == QColor(BACKGROUNDCOLOR)) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(TOHIGHCOLOR));
			Value->setPalette (pal);
			Value->update();
			}
		}
	else if (Value->value() < lowerTh) {
		if (Value->paletteBackgroundColor() == QColor(TOLOWCOLOR)) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(BACKGROUNDCOLOR));
			Value->setPalette (pal);
			Value->update();
			}
		else if (Value->paletteBackgroundColor() == QColor(BACKGROUNDCOLOR)) {
			QPalette pal = Value->palette();
			pal.setColor(QPalette::Window,QColor(TOLOWCOLOR));
			Value->setPalette (pal);
			Value->update();
			}
		}
	Value->update();
}

void arnNumEnPacketItem::AbilitaAllarme_Hndl(bool tg)
{
	if (!tg) {
		QPalette pal = Value->palette();
		pal.setColor(QPalette::Window,QColor(BACKGROUNDCOLOR));
		Value->setPalette (pal);
		Value->setAutoFillBackground(true);
		Value->update();
		timer->stop();
		}
	else {
		timer->start(1000);
		}
}

void arnNumEnPacketItem::showEvent ( QShowEvent * event )
{
	if (!inizialized) {
		inizialized = true;
		QPalette pal = Value->palette();
		pal.setColor(QPalette::Window,QColor(BACKGROUNDCOLOR));
		pal.setColor(QPalette::WindowText,QColor(DIGITCOLOR));
		Value->setPalette (pal);
		Value->setAutoFillBackground(true);
		Value->update();
		event->accept();
		}
}

void arnNumEnPacketItem::ModificaThUP_Hndl(void)
{
	ThUPVal->setText(QString::number(upperTh,'f',2));
	ThUPVal->setFocus();
	ThUPVal->show();
}

void arnNumEnPacketItem::ModificaThDOWN_Hndl(void)
{
	ThDOWNVal->setText(QString::number(lowerTh,'f',2));
	ThDOWNVal->setFocus();
	ThDOWNVal->show();
}

void arnNumEnPacketItem::ThUPValRetPress_hndl(void)
{
	bool ok;
	double tmp = ThUPVal->text().toDouble(&ok);
	if (ok) {upperTh = tmp;}
	ThUPVal->hide();
}

void arnNumEnPacketItem::ThDOWNValRetPress_hndl(void)
{
	bool ok;
	double tmp = ThDOWNVal->text().toDouble(&ok);
	if (ok) {lowerTh = tmp;}
	ThDOWNVal->hide();
}
