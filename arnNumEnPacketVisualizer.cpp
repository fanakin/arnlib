/***************************************************************************
                          arnNumEnPacketVisualizer.cpp  -  description
                             -------------------
    begin                : mar apr 19 2005
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
#include "arnNumEnPacketVisualizer.h"

arnNumEnPacketVisualizer::arnNumEnPacketVisualizer(QWidget *parent, const char* name , Qt::WFlags f)
	: arnPacketVisualizer(parent,name,f)
{
    ChannelList = new QList<arnNumEnPacketItem *>;
    if (!ChannelList) arnCriticalExit();
//    ChannelList->setAutoDelete(true);  // Must remove manually.
    ChannelList->clear();
}

arnNumEnPacketVisualizer::~arnNumEnPacketVisualizer(void)
{
    if (ChannelList) {delete ChannelList; ChannelList = 0;}
}

bool arnNumEnPacketVisualizer::addChannel(const char* Label)
{
    // non finito: fare tutta l'assegnazione delle propreta'

    QString vln(Label);

    arnNumEnPacketItem *tmp = new arnNumEnPacketItem(vln,0,this);
    if (!tmp) return false;

    if (!layout()) {
        pHLayout = new QHBoxLayout(this,0,-1,"arnNumEnPacketVisualizerLayout");
        if (!pHLayout) arnCriticalExit();
        }
    if (pVLayout1) {delete pVLayout1; pVLayout1 = 0;}
    if (pVLayout2) {delete pVLayout2; pVLayout2 = 0;}
    

    pVLayout1 = new QVBoxLayout(pHLayout,-1,"Vlayout1");
    if (!pVLayout1) arnCriticalExit();
    pVLayout2 = new QVBoxLayout(pHLayout,-1,"Vlayout2");
    if (!pVLayout2) arnCriticalExit();


    tmp->lcdValue()->setPaletteBackgroundColor(QColor(0,0,0));
    tmp->lcdValue()->setPaletteForegroundColor(QColor(255,0,0));
    tmp->lcdValue()->setSegmentStyle( QLCDNumber::Filled );
    ChannelList->append(tmp);

    for (int i = 0; i < int(ChannelList->count()); i++) {
        ((i % 2) == 0)? pVLayout2->addWidget(((arnNumEnPacketItem *)ChannelList->at(i)))
        : pVLayout1->addWidget(((arnNumEnPacketItem *)ChannelList->at(i)));
        }
    return true;
}

bool arnNumEnPacketVisualizer::deleteChannel(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    arnNumEnPacketItem *ptr = ChannelList->at(0);
    if ( ptr == 0) return false;
    
    ChannelList->removeAt (i);
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
//        ((i % 2) == 0)? pVLayout2->addWidget(((arnNumEnPacketItem*)ChannelList->at(i)))
//        : pVLayout1->addWidget(((arnNumEnPacketItem *)ChannelList->at(i)));
//        }

    return true;
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, unsigned char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, signed char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, unsigned short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, signed short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, unsigned long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, signed long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, float val, int prec, char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    ((arnNumEnPacketItem *)ChannelList->at(i))->lcdValue()->setSmallDecimalPoint(true);
    str.setNum(val,fmt,prec);
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue(str);
}

void arnNumEnPacketVisualizer::setChannelValue (const char* Label, double val,int prec ,char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    ((arnNumEnPacketItem *)ChannelList->at(i))->lcdValue()->setSmallDecimalPoint(true);
    str.setNum(val,fmt,prec);
    ((arnNumEnPacketItem *)ChannelList->at(i))->setValue(str);
}

void arnNumEnPacketVisualizer::update(void)
{
    for (int i = 0; i < int(ChannelList->count()); ++i ) {
		((arnNumEnPacketItem *)ChannelList->at(i))->lcdValue()->update();
        }
    QFrame::update();
}

//void arnPacketVisualizer::setChannelValue (const char* Label, const char* val)
//{
//    bool found = false;
//    int i;
//    for ( i = 0; i < int(ChannelList->count()); ++i ) {
//        if (!strcmp(((struct ChannelItem *)ChannelList->at(i))->Name->text(),Label)) { // variabile gia' trovata
//            found = true;
//            break;
//            }
//        }
//    if (!found) return;
//    ((struct ChannelItem *)ChannelList->at(i))->Value->setText(val);
//}

void arnNumEnPacketVisualizer::showChannel(int index)
{
    if (index < int(ChannelList->count())) ((arnNumEnPacketItem *)ChannelList->at(index))->show();
}

void arnNumEnPacketVisualizer::hideChannel(int index)
{
     if (index < int(ChannelList->count())) ((arnNumEnPacketItem *)ChannelList->at(index))->hide();
}

void arnNumEnPacketVisualizer::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->show();
}

void arnNumEnPacketVisualizer::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnPacketItem *)ChannelList->at(i))->hide();
}

bool  arnNumEnPacketVisualizer::isChannelVisible(int index)
{
     if (index < int(ChannelList->count())) return ((arnNumEnPacketItem *)ChannelList->at(index))->isVisibleTo(this);
     return  false;
}

bool arnNumEnPacketVisualizer::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->isVisibleTo(this);
}

//void arnPacketVisualizer::mousePressEvent(QMouseEvent *e)
//{
//    if (e->button() == Qt::LeftButton) {
//        arnDebug("arnPacketVisualizer::mousePressEvent\n");
//        }
//    else QFrame::mousePressEvent(e);
//}
//

void arnNumEnPacketVisualizer::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        showChannel(i);
        }
    // QFrame::mouseDoubleClickEvent(e);
}

QLCDNumber* arnNumEnPacketVisualizer::lcdValue (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->lcdValue();
}

void arnNumEnPacketVisualizer::setAlarmEnabled(const char* Label, bool v)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setAlarmEnabled(v);
}

bool arnNumEnPacketVisualizer::isAlarmEnabled (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->isAlarmEnabled();
}

void arnNumEnPacketVisualizer::setUpperTh(const char* Label, const QString& val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setUpperTh(val);
}

void arnNumEnPacketVisualizer::setUpperTh(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setUpperTh(val);
}

void arnNumEnPacketVisualizer::setUpperTh(const char* Label, double val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setUpperTh(val);
}

double arnNumEnPacketVisualizer::UpperTh(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->UpperTh();
}


void arnNumEnPacketVisualizer::setLowerTh(const char* Label, const QString& val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setLowerTh(val);
}

void arnNumEnPacketVisualizer::setLowerTh(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setLowerTh(val);
}

void arnNumEnPacketVisualizer::setLowerTh(const char* Label, double val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->setLowerTh(val);
}

double arnNumEnPacketVisualizer::LowerTh(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnNumEnPacketItem *)ChannelList->at(i))->LowerTh();
}

void arnNumEnPacketVisualizer::checkWarning(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	if (((arnNumEnPacketItem *)ChannelList->at(i))->isAlarmEnabled()) {
		return  ((arnNumEnPacketItem *)ChannelList->at(i))->checkWarning();
		}
}

QString arnNumEnPacketVisualizer::name(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return QString("");
	return ((arnNumEnPacketItem *)ChannelList->at(i))->name();
}

void arnNumEnPacketVisualizer::alignName(const char* Label,int a)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnPacketItem *)ChannelList->at(i))->alignName(a);
}

void arnNumEnPacketVisualizer::setNameFontSize(const char* Label,int a)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnPacketItem *)ChannelList->at(i))->setNameFontSize(a);
}

void arnNumEnPacketVisualizer::EnableManualBlink(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnPacketItem *)ChannelList->at(i))->EnableManualBlink(en);
}

void arnNumEnPacketVisualizer::setManualBlink(const char* Label,unsigned short blinkShot)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnPacketItem *)ChannelList->at(i))->setManualBlink(blinkShot);
}

void arnNumEnPacketVisualizer::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnNumEnPacketItem *)ChannelList->at(index))->Nascondi->setText(name);
				((arnNumEnPacketItem *)ChannelList->at(index))->Nascondi->setMenuText(name);
				break;
			case arn_mli_PACKETITEM_ENWARNING:
				((arnNumEnPacketItem *)ChannelList->at(index))->AbilitaAllarme->setText(name);
				((arnNumEnPacketItem *)ChannelList->at(index))->AbilitaAllarme->setMenuText(name);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnNumEnPacketVisualizer::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnNumEnPacketItem *)ChannelList->at(i))->Nascondi->setText(name);
			((arnNumEnPacketItem *)ChannelList->at(i))->Nascondi->setMenuText(name);
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			((arnNumEnPacketItem *)ChannelList->at(i))->AbilitaAllarme->setText(name);
			((arnNumEnPacketItem *)ChannelList->at(i))->AbilitaAllarme->setMenuText(name);
			break;
		default: break;
		}
}

void arnNumEnPacketVisualizer::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnNumEnPacketItem *)ChannelList->at(index))->Nascondi->setToolTip(tip);
				break;
			case arn_mli_PACKETITEM_ENWARNING:
				((arnNumEnPacketItem *)ChannelList->at(index))->AbilitaAllarme->setToolTip(tip);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnNumEnPacketVisualizer::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnNumEnPacketItem *)ChannelList->at(i))->Nascondi->setToolTip(tip);
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			((arnNumEnPacketItem *)ChannelList->at(i))->AbilitaAllarme->setToolTip(tip);
			break;
		default: break;
		}
}

void arnNumEnPacketVisualizer::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnNumEnPacketItem *)ChannelList->at(index))->Nascondi->setVisible(en);
				break;
			case arn_mli_PACKETITEM_ENWARNING:
				((arnNumEnPacketItem *)ChannelList->at(index))->AbilitaAllarme->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnNumEnPacketVisualizer::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnNumEnPacketItem *)ChannelList->at(i))->Nascondi->setVisible(en);
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			((arnNumEnPacketItem *)ChannelList->at(i))->AbilitaAllarme->setVisible(en);
			break;
		default: break;
		}
}

void arnNumEnPacketVisualizer::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			popupText_Nascondi = txt;
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			popupText_Allarmi = txt;
			break;
		default: break;
		}
}
    
void arnNumEnPacketVisualizer::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			popupTip_Nascondi = txt;
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			popupTip_Allarmi = txt;
			break;
		default: break;
		}
}

QString arnNumEnPacketVisualizer::popupText(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			return popupText_Nascondi;
		case arn_mli_PACKETITEM_ENWARNING:
			return popupText_Allarmi;
		default: return QString("");
		}
}

QString arnNumEnPacketVisualizer::popupTip(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			return popupTip_Nascondi;
		case arn_mli_PACKETITEM_ENWARNING:
			return popupTip_Allarmi;
		default: return QString("");
		}
}
