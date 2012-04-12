/***************************************************************************
                          arnNumericVariableViewer.cpp  -  description
                             -------------------
    begin                : gio apr 17 2003
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

#include "CommonFunctions.h"
#include "arnNumericVariableViewer.h"

arnNumericVariableViewer::arnNumericVariableViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
    tpy = avt_NumericVariableViewer;
	numFormatVal = nrf_dec;
	pMainLayout = new QVBoxLayout(this, 10, -1, "MainLayout");
    if (!pMainLayout) arnCriticalExit();
    pValueLayout = new QHBoxLayout(0, 10, -1, "ValueLayout");
    if (!pValueLayout) arnCriticalExit();
    pMainLayout->addLayout(pValueLayout,1);
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
    pName = new QLabel("Nome",this,"Name",0);
    if (!pName) arnCriticalExit();
    pValue = new QLineEdit(this,"Name");
    if (!pValue) arnCriticalExit();
    pValueLayout->addWidget(pName,1);
    pValueLayout->addWidget(pValue,30);
    pMainLayout->addWidget(pComment,50);

    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pValue, SIGNAL(textChanged( const QString &)), this, SLOT(doValueChange( const QString &)));
    
    prec = 0;
}

arnNumericVariableViewer::~arnNumericVariableViewer(void)
{

}

void arnNumericVariableViewer::setValue(double val)
{
    QString t;
	if (!prec) {
		switch (numFormatVal) {
			case nrf_hex:
				t.setNum((int)val,16);
			break;
			case nrf_bin:
				t.setNum((int)val,2);
			break;
			case nrf_dec:
			default:
				t.setNum(val);
			break;
		}
	}
    else {
		switch (numFormatVal) {
			case nrf_hex:
				t.setNum((int)val,16);
			break;
			case nrf_bin:
				t.setNum((int)val,2);
			break;
			case nrf_dec:
			default:
				t.setNum(val,'f',prec);
			break;
		}
	}
    pValue->setText(t);
}

void arnNumericVariableViewer::doValueChange( const QString & p)
{
    emit valueChanged(p);
}
