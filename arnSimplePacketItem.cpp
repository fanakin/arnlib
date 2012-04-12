/***************************************************************************
						  arnSimplePacketItem.cpp  -  description
                             -------------------
	begin                : ven lug 2 2010
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
#include "arnSimplePacketItem.h"

arnSimplePacketItem::arnSimplePacketItem(QWidget *parent, const char* name, Qt::WFlags f)
    : QFrame(parent,name,f)
{
	this->init();
}

arnSimplePacketItem::arnSimplePacketItem(const QString& label, QWidget *parent, const char* name, Qt::WFlags f)
    : QFrame(parent,name,f)
{
	this->init();
	Name->setText(label);
}


arnSimplePacketItem::~arnSimplePacketItem(void)
{

}

void arnSimplePacketItem::init(void)
{
	tpe = apit_PacketItem;
    
	pHLayout = new QHBoxLayout(this,0,-1,"arnSimplePacketItemLayout");
	if (!pHLayout) arnCriticalExit();

	Name = new QLabel(this, QString(), 0);      /** check this, please */
	if (!Name) arnCriticalExit();
	
	Name->setAlignment(Qt::AlignVCenter | Qt::AlignHCenter);

	QFont F(Name->font());
	F.setPointSize(16);
	Name->setFont(F);
	
	pHLayout->addWidget(Name);
	
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

// void arnSimplePacketItem::mousePressEvent(QMouseEvent *e)
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


void arnSimplePacketItem::Nascondi_Hndl(void)
{
	hide();
}
