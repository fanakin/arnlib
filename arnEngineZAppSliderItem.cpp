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
#include "arnNumericFilter.h"
#include "CommonFunctions.h"
#include "arnEngineZAppSliderItem.h"
#include "arnSMiscMarkNumericMatrix.h"
#include "arnEnCompositeMatrixViewer.h"
#include <QMouseEvent>

arnEngineZAppSliderItem::arnEngineZAppSliderItem(QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppSliderItem(parent,name,f)
{
	this->init();
}

arnEngineZAppSliderItem::arnEngineZAppSliderItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppSliderItem(label,parent,name,f)
{
	this->init();
}

arnEngineZAppSliderItem::arnEngineZAppSliderItem(const QString& label, const QString& value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppSliderItem(label,value,parent,name,f)
{
	this->init();
}

arnEngineZAppSliderItem::arnEngineZAppSliderItem(const QString& label , int value, QWidget *parent, const char* name, Qt::WFlags f)
    : arnEngineAppSliderItem(label,value,parent,name,f)
{
	this->init();
}

arnEngineZAppSliderItem::~arnEngineZAppSliderItem(void)
{
}

void arnEngineZAppSliderItem::init(void)
{
	directCVal = new QLineEdit(Value->text(),this,"directCVal");
	if (!directCVal) arnCriticalExit();
	connect( directCVal,SIGNAL( returnPressed() ), this, SLOT( directCValRetPress_hndl() ) );
}

void arnEngineZAppSliderItem::mouseDoubleClickEvent(QMouseEvent *e)
{
	if (((e->x() >= Value->x()) && (e->x() < (Value->x() + Value->width ()))) &&
		((e->y() >= Value->y()) && (e->y() < (Value->y() + Value->height())))
		) {
			directCVal->setText(Value->text());
			directCVal->setFocus();
			directCVal->show();
			e->accept();
			return;
			}
	e->ignore();
}

void arnEngineZAppSliderItem::directCValRetPress_hndl(void)
{
	bool ok;
	double tmp = directCVal->text().toDouble(&ok);
	if (ok) {
		switch (Value->Size()) {
			case nff_u8:
				Slider->setValue(arnNumericFilter::toRawUnsignedChar(tmp,Value->Min(),Value->Max()));
				break;
			case nff_u16:
				Slider->setValue(arnNumericFilter::toRawUnsignedShort(tmp,Value->Min(),Value->Max()));
				break;
			case nff_u32:
				Slider->setValue(arnNumericFilter::toRawUnsignedLong(tmp,Value->Min(),Value->Max()));
				break;
			case nff_s8:
				Slider->setValue(arnNumericFilter::toRawSignedChar(tmp,Value->Min(),Value->Max()));
				break;
			case nff_s16:
				Slider->setValue(arnNumericFilter::toRawSignedShort(tmp,Value->Min(),Value->Max()));
				break;
			case nff_s32:
				Slider->setValue(arnNumericFilter::toRawSignedLong(tmp,Value->Min(),Value->Max()));
				break;
			case nff_float:  break;
			case nff_double: break;
			default: break;
			}
		}
	directCVal->hide();
}
