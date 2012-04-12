/***************************************************************************
                          arnSliderItem.cpp  -  description
                             -------------------
    begin                : ven lug 4 2003
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
#include "CommonFunctions.h"
#include "arnSliderItem.h"
#include <QMouseEvent>

arnSliderItem::arnSliderItem(QWidget *parent, const char* name, Qt::WFlags f)
    : QFrame(parent,name,f)
{
    pHLayout = new QHBoxLayout(this);
    if (!pHLayout) arnCriticalExit();

    this->init();
	Name = new QLabel("",this,0,0);
    if (!Name) arnCriticalExit();
    Slider = new  QSlider( Qt::Horizontal, this, 0);
    if (!Slider) arnCriticalExit();
	Slider->setAutoFillBackground(true);
    //Slider->installEventFilter( this );  per gestire correttamente cosa accade ad un evento.

    QString tval;
    tval.setNum(Slider->value());
    Value = new arnQLabel(tval,this,0,0);
    if (!Value) arnCriticalExit();

    connect( Slider, SIGNAL( valueChanged(int) ), Value, SLOT( setNum(int) ) );
    connect(Slider, SIGNAL(valueChanged(int)), this, SLOT(doValueChange(int)));

    Value->setPaletteForegroundColor(QColor(255,0,0));
    Value->update();
}

arnSliderItem::arnSliderItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : QFrame(parent,name,f)
{
    pHLayout = new QHBoxLayout( this);//new QHBoxLayout( 0, 0, 1, 0);
    if (!pHLayout) arnCriticalExit();

    this->init();
    Name = new QLabel(label,this,label,0);
    if (!Name) arnCriticalExit();
    Slider = new  QSlider( Qt::Horizontal, this, 0);
    if (!Slider) arnCriticalExit();
	Slider->setAutoFillBackground(true);
    //Slider->installEventFilter( this );  per gestire correttamente cosa accade ad un evento.

    QString tval;
    tval.setNum(Slider->value());
    Value = new arnQLabel(tval,this,0,0);
    if (!Value) arnCriticalExit();

    pHLayout->addWidget(Name);
    pHLayout->addWidget(Value);
    pHLayout->addWidget(Slider);

    connect( Slider, SIGNAL( valueChanged(int) ), Value, SLOT( setNum(int) ) );
    connect(Slider, SIGNAL(valueChanged(int)), this, SLOT(doValueChange(int)));

    Value->setPaletteForegroundColor(QColor(255,0,0));
    Value->update();
}

arnSliderItem::arnSliderItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : QFrame(parent,name,f)
{
    pHLayout = new QHBoxLayout(this);
    if (!pHLayout) arnCriticalExit();

    this->init();
    Name = new QLabel(label,this,label,0);
    if (!Name) arnCriticalExit();
    Slider = new  QSlider( Qt::Horizontal, this, 0);
    if (!Slider) arnCriticalExit();
	Slider->setAutoFillBackground(true);
    //Slider->installEventFilter( this );  per gestire correttamente cosa accade ad un evento.

    Slider->setValue(value.toInt());
    Value = new arnQLabel(value,this,0,0);
    if (!Value) arnCriticalExit();

    connect( Slider, SIGNAL( valueChanged(int) ),Value, SLOT( setNum(int) ) );
    connect(Slider, SIGNAL(valueChanged(int)), this, SLOT(doValueChange(int)));


    Value->setPaletteForegroundColor(QColor(255,0,0));
    Value->update();
}

arnSliderItem::arnSliderItem(const QString& label , int value, QWidget *parent, const char* name, Qt::WFlags f)
    : QFrame(parent,name,f)
{
    pHLayout = new QHBoxLayout(this);
    if (!pHLayout) arnCriticalExit();

    this->init();
    Name = new QLabel(label,this,label,0);
    if (!Name) arnCriticalExit();
    Slider = new  QSlider( Qt::Horizontal, this, 0);
    if (!Slider) arnCriticalExit();
	Slider->setAutoFillBackground(true);
    Slider->setValue(value);
	Slider->setAutoFillBackground(true);
    //Slider->installEventFilter( this );  per gestire correttamente cosa accade ad un evento.

    QString tval;
    tval.setNum(Slider->value());
    Value = new arnQLabel(tval,this,0,0);
    if (!Value) arnCriticalExit();

    connect( Slider, SIGNAL( valueChanged(int) ),Value, SLOT( setNum(int) ) );
    connect(Slider, SIGNAL(valueChanged(int)), this, SLOT(doValueChange(int)));

    Value->setPaletteForegroundColor(QColor(255,0,0));
    Value->update();
}

arnSliderItem::~arnSliderItem(void)
{
}

void arnSliderItem::init(void)
{
	pPopUp = new QMenu(this);
	if (!pPopUp) arnCriticalExit();

	Nascondi = new QAction( this, "Nascondi");
	if (!Nascondi) arnCriticalExit();
	//Nascondi->setToggleAction(true);
	Nascondi->setText( trUtf8("Hide"));
	Nascondi->setMenuText( trUtf8("Hide"));
	Nascondi->setToolTip( trUtf8("Hide the slider if you are not interested of"));

	Connetti = new QAction( this, "Connetti");
	if (!Connetti) arnCriticalExit();
	Connetti->setToggleAction(true);
	Connetti->setText( trUtf8("Connect"));
	Connetti->setMenuText( trUtf8("Connect"));
	Connetti->setToolTip( trUtf8("Connect the slider to the parameter file"));

	connect( Nascondi,SIGNAL( activated() ), this, SLOT( Nascondi_Hndl() ) );
	connect( Connetti,SIGNAL( toggled(bool) ), this, SLOT( Connetti_Hndl(bool) ) );
	Nascondi->addTo(pPopUp);
	Connetti->addTo(pPopUp);
}

void arnSliderItem::mousePressEvent(QMouseEvent *e)
{
    if (e->button () == Qt::LeftButton) {
        Slider->setFocus();
        QFrame::mousePressEvent(e);
        }
    else if (e->button () == Qt::RightButton)  {
		if (pPopUp) pPopUp->exec(QCursor::pos());
        QFrame::mousePressEvent(e);
        }
    else QFrame::mousePressEvent(e);
}

void arnSliderItem::Nascondi_Hndl(void)
{
	hide();
}

void arnSliderItem::Connetti_Hndl(bool tg)
{
	if (tg) {
		Slider->setPaletteBackgroundColor(QColor(0,0,255));
		Name->setPaletteForegroundColor(QColor(0,0,255));
		((QFont)(Name->font())).setUnderline(true);
		((QFont)(Name->font())).setBold(true);
		Name->update();
		}
	else {
		Slider->setPaletteBackgroundColor(QColor(238,238,238));
		Name->setPaletteForegroundColor(QColor(0,0,0));
		((QFont)(Name->font())).setUnderline(false);
		((QFont)(Name->font())).setBold(false);
		Name->update();
		}
}

double arnSliderItem::value(void)
{
    bool ok;
    double tNum = Value->text().toDouble(&ok);
    if (!ok) return 0;
    return tNum;
}
