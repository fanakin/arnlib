/***************************************************************************
                          arnStringPacketVisualizer.cpp  -  description
                             -------------------
    begin                : gio apr 21 2005
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

#include <stdlib.h>
#include <QObjectList>
#include "CommonFunctions.h"
#include "arnStringPacketVisualizer.h"

arnStringPacketVisualizer::arnStringPacketVisualizer(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    ChannelList = new QList<arnStringPacketItem *>;
    if (!ChannelList) arnCriticalExit();
//    ChannelList->setAutoDelete(true);
    ChannelList->clear();

    pHLayout = 0;
    pVLayout1 = 0;
    pVLayout2 = 0;

}

arnStringPacketVisualizer::~arnStringPacketVisualizer(void)
{
    if (ChannelList) {delete ChannelList; ChannelList = 0;}
}

bool arnStringPacketVisualizer::addChannel(const char* Label)
{
    // non finito: fare tutta l'assegnazione delle propreta'

    QString vln(Label);

    arnStringPacketItem *tmp = new arnStringPacketItem(vln,0,this);
    if (!tmp) return false;

    if (!layout()) {
        pHLayout = new QHBoxLayout(this,0,-1,"arnStringPacketVisualizerLayout");
        if (!pHLayout) arnCriticalExit();
        }
    if (pVLayout1) {delete pVLayout1; pVLayout1 = 0;}
    if (pVLayout2) {delete pVLayout2; pVLayout2 = 0;}
    

    pVLayout1 = new QVBoxLayout(pHLayout,-1,"Vlayout1");
    if (!pVLayout1) arnCriticalExit();
    pVLayout2 = new QVBoxLayout(pHLayout,-1,"Vlayout2");
    if (!pVLayout2) arnCriticalExit();


    ChannelList->append(tmp);

    for (int i = 0; i < int(ChannelList->count()); i++) {
        ((i % 2) == 0)? pVLayout2->addWidget(((arnStringPacketItem *)ChannelList->at(i)))
        : pVLayout1->addWidget(((arnStringPacketItem *)ChannelList->at(i)));
        }
    return true;
}

bool arnStringPacketVisualizer::deleteChannel(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    arnStringPacketItem *ptr = ChannelList->at(i);
    if (!ptr) return false;
    
    ChannelList->removeAt(i);
    delete ptr;
//    if (!(ChannelList->remove(i))) return false;

    update();

//
// per un futuro studio su come implementare la delete di un canale
//
//    if (!layout()) {
//        pHLayout = new QHBoxLayout(this,0,-1,"arnPacketVisualizerLayout");
//        if (!pHLayout) arnCriticalExit();
//        }
//    if (pVLayout1) {delete pVLayout1; pVLayout1 = 0;}
//    if (pVLayout2) {delete pVLayout2; pVLayout2 = 0;}
//
//
//    pVLayout1 = new QVBoxLayout(pHLayout,-1,"Vlayout1");
//    if (!pVLayout1) arnCriticalExit();
//    pVLayout2 = new QVBoxLayout(pHLayout,-1,"Vlayout2");
//    if (!pVLayout2) arnCriticalExit();
//
//    for (int i = 0; i < int(ChannelList->count()); i++) {
//        ((i % 2) == 0)? pVLayout2->addWidget(((arnStringPacketItem*)ChannelList->at(i)))
//        : pVLayout1->addWidget(((arnStringPacketItem *)ChannelList->at(i)));
//        }

    return true;
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, unsigned char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, signed char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, unsigned short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, signed short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, unsigned long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, signed long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, float val, int prec, char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    str.setNum(val,fmt,prec);
    ((arnStringPacketItem *)ChannelList->at(i))->setValue(str);
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, double val,int prec ,char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    str.setNum(val,fmt,prec);
    ((arnStringPacketItem *)ChannelList->at(i))->setValue(str);
}

void arnStringPacketVisualizer::update(void)
{
    for (int i = 0; i < int(ChannelList->count()); ++i ) {
		((arnStringPacketItem *)ChannelList->at(i))->update();
        }
    QFrame::update();
}

void arnStringPacketVisualizer::setChannelValue (const char* Label, const char* val)
{
   bool found = false;
   int i;
   for ( i = 0; i < int(ChannelList->count()); ++i ) {
       if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
           found = true;
           break;
           }
       }
   if (!found) return;
   ((arnStringPacketItem *)ChannelList->at(i))->setValue((char*)val);
}

void arnStringPacketVisualizer::showChannel(int index)
{
    if (index < int(ChannelList->count())) ((arnStringPacketItem *)ChannelList->at(index))->show();
}

void arnStringPacketVisualizer::hideChannel(int index)
{
     if (index < int(ChannelList->count())) ((arnStringPacketItem *)ChannelList->at(index))->hide();
}

void arnStringPacketVisualizer::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->show();
}

void arnStringPacketVisualizer::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->hide();
}

bool  arnStringPacketVisualizer::isChannelVisible(int index)
{
     if (index < int(ChannelList->count())) return ((arnStringPacketItem *)ChannelList->at(index))->isVisibleTo(this);
     return  false;
}

bool arnStringPacketVisualizer::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return  ((arnStringPacketItem *)ChannelList->at(i))->isVisibleTo(this);
}

void arnStringPacketVisualizer::setChannelValueFontSize (const char* Label, int size)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValueFontSize(size);
}

void arnStringPacketVisualizer::setChannelValueFontColor (const char* Label, QColor color)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnStringPacketItem *)ChannelList->at(i))->setValueFontColor(color);
}

//void arnPacketVisualizer::mousePressEvent(QMouseEvent *e)
//{
//    if (e->button() == Qt::LeftButton) {
//        arnDebug("arnPacketVisualizer::mousePressEvent\n");
//        }
//    else QFrame::mousePressEvent(e);
//}
//

void arnStringPacketVisualizer::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        showChannel(i);
        }
    // QFrame::mouseDoubleClickEvent(e);
}

void arnStringPacketVisualizer::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnStringPacketItem *)ChannelList->at(index))->Nascondi->setText(name);
				((arnStringPacketItem *)ChannelList->at(index))->Nascondi->setMenuText(name);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnStringPacketVisualizer::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnStringPacketItem *)ChannelList->at(i))->Nascondi->setText(name);
			((arnStringPacketItem *)ChannelList->at(i))->Nascondi->setMenuText(name);
			break;
		default: break;
		}
}

void arnStringPacketVisualizer::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnStringPacketItem *)ChannelList->at(index))->Nascondi->setToolTip(tip);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnStringPacketVisualizer::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnStringPacketItem *)ChannelList->at(i))->Nascondi->setToolTip(tip);
			break;
		default: break;
		}
}

void arnStringPacketVisualizer::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnStringPacketItem *)ChannelList->at(index))->Nascondi->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnStringPacketVisualizer::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnStringPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnStringPacketItem *)ChannelList->at(i))->Nascondi->setVisible(en);
			break;
		default: break;
		}
}

void arnStringPacketVisualizer::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			popupText_Nascondi = txt;
			break;
		default: break;
		}
}
    
void arnStringPacketVisualizer::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			popupTip_Nascondi = txt;
			break;
		default: break;
		}
}

QString arnStringPacketVisualizer::popupText(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			return popupText_Nascondi;
		default: return QString("");
		}
}

QString arnStringPacketVisualizer::popupTip(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			return popupTip_Nascondi;
		default: return QString("");
		}
}
