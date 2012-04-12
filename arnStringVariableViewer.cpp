/***************************************************************************
                          arnStringVariableViewer.cpp  -  description
                             -------------------
    begin                : mer set 24 2003
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
#include "arnStringVariableViewer.h"

arnStringVariableViewer::arnStringVariableViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
    tpy = avt_StringVariableViewer;
    pMainLayout = new QVBoxLayout(this, 10, -1, "MainLayout");
    if (!pMainLayout) arnCriticalExit();
    pValueLayout = new QHBoxLayout(0, 10, -1, "ValueLayout");
    if (!pValueLayout) arnCriticalExit();
    pMainLayout->addLayout(pValueLayout,50);
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
    pName = new QLabel("Nome",this,"Name",0);
    if (!pName) arnCriticalExit();
    pValue = new QTextEdit(this,"Name");
    if (!pValue) arnCriticalExit();
    pValueLayout->addWidget(pName,1);
    pValueLayout->addWidget(pValue,30);
    pMainLayout->addWidget(pComment,2);

    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pValue, SIGNAL(textChanged()), this, SLOT(doValueChange()));

    prec = 0;
}

arnStringVariableViewer::~arnStringVariableViewer(void)
{

}

void arnStringVariableViewer::setValue(const QString& val)
{
    pValue->setText(val);
}

void arnStringVariableViewer::doValueChange( )
{
    emit valueChanged(pValue->text());
}
