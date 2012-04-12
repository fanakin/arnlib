/***************************************************************************
                          arnNumEnColorTrackPacketVisualizer.cpp  -  description
                             -------------------
    begin                : mar luglio 26 2005
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
#include "arnNumEnColorTrackPacketVisualizer.h"

arnNumEnColorTrackPacketVisualizer::arnNumEnColorTrackPacketVisualizer(QWidget *parent, const char* name , Qt::WFlags f)
	: arnPacketVisualizer(parent,name,f)
{
    ChannelList = new QList<arnNumEnColorTrackPacketItem *>;
    if (!ChannelList) arnCriticalExit();
//    ChannelList->setAutoDelete(true);        // remove manually
    ChannelList->clear();

    pHLayout = 0;
    pVLayout1 = 0;
    pVLayout2 = 0;

}

arnNumEnColorTrackPacketVisualizer::~arnNumEnColorTrackPacketVisualizer(void)
{
    if (ChannelList) {delete ChannelList; ChannelList = 0;}
}

bool arnNumEnColorTrackPacketVisualizer::addChannel(const char* Label)
{
    // non finito: fare tutta l'assegnazione delle propreta'

    QString vln(Label);

    arnNumEnColorTrackPacketItem *tmp = new arnNumEnColorTrackPacketItem(vln,0,this);
    if (!tmp) return false;

    if (!layout()) {
        pHLayout = new QHBoxLayout(this,0,-1,"arnNumEnColorTrackPacketVisualizerLayout");
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
        ((i % 2) == 0)? pVLayout2->addWidget(((arnNumEnColorTrackPacketItem *)ChannelList->at(i)))
        : pVLayout1->addWidget(((arnNumEnColorTrackPacketItem *)ChannelList->at(i)));
        }
    return true;
}

bool arnNumEnColorTrackPacketVisualizer::deleteChannel(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    
    arnNumEnColorTrackPacketItem *ptr = ChannelList->at(i);
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
//        ((i % 2) == 0)? pVLayout2->addWidget(((arnNumEnColorTrackPacketItem*)ChannelList->at(i)))
//        : pVLayout1->addWidget(((arnNumEnColorTrackPacketItem *)ChannelList->at(i)));
//        }

    return true;
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, unsigned char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, signed char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, unsigned short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, signed short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, unsigned long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, signed long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, float val, int prec, char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->lcdValue()->setSmallDecimalPoint(true);
    str.setNum(val,fmt,prec);
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue(str);
}

void arnNumEnColorTrackPacketVisualizer::setChannelValue (const char* Label, double val,int prec ,char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->lcdValue()->setSmallDecimalPoint(true);
    str.setNum(val,fmt,prec);
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setValue(str);
}

void arnNumEnColorTrackPacketVisualizer::update(void)
{
    for (int i = 0; i < int(ChannelList->count()); ++i ) {
		((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->lcdValue()->update();
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

void arnNumEnColorTrackPacketVisualizer::showChannel(int index)
{
    if (index < int(ChannelList->count())) ((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->show();
}

void arnNumEnColorTrackPacketVisualizer::hideChannel(int index)
{
     if (index < int(ChannelList->count())) ((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->hide();
}

void arnNumEnColorTrackPacketVisualizer::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->show();
}

void arnNumEnColorTrackPacketVisualizer::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->hide();
}

bool  arnNumEnColorTrackPacketVisualizer::isChannelVisible(int index)
{
     if (index < int(ChannelList->count())) return ((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->isVisibleTo(this);
     return  false;
}

bool arnNumEnColorTrackPacketVisualizer::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->isVisibleTo(this);
}

//void arnPacketVisualizer::mousePressEvent(QMouseEvent *e)
//{
//    if (e->button() == Qt::LeftButton) {
//        arnDebug("arnPacketVisualizer::mousePressEvent\n");
//        }
//    else QFrame::mousePressEvent(e);
//}
//

void arnNumEnColorTrackPacketVisualizer::mouseDoubleClickEvent(QMouseEvent* /*e*/)
{
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        showChannel(i);
        }
    // QFrame::mouseDoubleClickEvent(e);
}

QLCDNumber* arnNumEnColorTrackPacketVisualizer::lcdValue (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->lcdValue();
}

void arnNumEnColorTrackPacketVisualizer::setAlarmEnabled(const char* Label, bool v)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setAlarmEnabled(v);
}

bool arnNumEnColorTrackPacketVisualizer::isAlarmEnabled (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->isAlarmEnabled();
}

void arnNumEnColorTrackPacketVisualizer::setUpperTh(const char* Label, const QString& val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setUpperTh(val);
}

void arnNumEnColorTrackPacketVisualizer::setUpperTh(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setUpperTh(val);
}

void arnNumEnColorTrackPacketVisualizer::setUpperTh(const char* Label, double val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setUpperTh(val);
}

double arnNumEnColorTrackPacketVisualizer::UpperTh(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->UpperTh();
}

void arnNumEnColorTrackPacketVisualizer::setLowerTh(const char* Label, const QString& val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setLowerTh(val);
}

void arnNumEnColorTrackPacketVisualizer::setLowerTh(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setLowerTh(val);
}

void arnNumEnColorTrackPacketVisualizer::setLowerTh(const char* Label, double val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setLowerTh(val);
}

double arnNumEnColorTrackPacketVisualizer::LowerTh(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->LowerTh();
}

void arnNumEnColorTrackPacketVisualizer::checkWarning(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	if (((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->isAlarmEnabled()) {
		return  ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->checkWarning();
		}
}

QString arnNumEnColorTrackPacketVisualizer::name(const char* Label)
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

void arnNumEnColorTrackPacketVisualizer::alignName(const char* Label,int a)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->alignName(a);
}

void arnNumEnColorTrackPacketVisualizer::setNameFontSize(const char* Label,int a)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setNameFontSize(a);
}

void arnNumEnColorTrackPacketVisualizer::setTrackColor(const char* Label,const QColor& c)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setTrackColor(c);
}

const QColor arnNumEnColorTrackPacketVisualizer::trackColor(const char* Label)
{
	QColor res("black");
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return res;
	return ((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->trackColor();
}

void arnNumEnColorTrackPacketVisualizer::hideTrackColor(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->hideTrackColor();
}

void arnNumEnColorTrackPacketVisualizer::showTrackColor(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->showTrackColor();
}

void arnNumEnColorTrackPacketVisualizer::EnableManualBlink(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->EnableManualBlink(en);
}

void arnNumEnColorTrackPacketVisualizer::setManualBlink(const char* Label,unsigned short blinkShot)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->setManualBlink(blinkShot);
}

void arnNumEnColorTrackPacketVisualizer::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->Nascondi->setText(name);
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->Nascondi->setMenuText(name);
				break;
			case arn_mli_PACKETITEM_ENWARNING:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->AbilitaAllarme->setText(name);
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->AbilitaAllarme->setMenuText(name);
				break;
			case arn_mli_PACKETITEM_TRACKCOLOR:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->enTrackColor->setText(name);
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->enTrackColor->setMenuText(name);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnNumEnColorTrackPacketVisualizer::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->Nascondi->setText(name);
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->Nascondi->setMenuText(name);
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->AbilitaAllarme->setText(name);
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->AbilitaAllarme->setMenuText(name);
			break;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->enTrackColor->setText(name);
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->enTrackColor->setMenuText(name);
			break;
		default: break;
		}
}

void arnNumEnColorTrackPacketVisualizer::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->Nascondi->setToolTip(tip);
				break;
			case arn_mli_PACKETITEM_ENWARNING:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->AbilitaAllarme->setToolTip(tip);
				break;
			case arn_mli_PACKETITEM_TRACKCOLOR:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->enTrackColor->setToolTip(tip);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnNumEnColorTrackPacketVisualizer::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->Nascondi->setToolTip(tip);
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->AbilitaAllarme->setToolTip(tip);
			break;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->enTrackColor->setToolTip(tip);
			break;
		default: break;
		}
}

void arnNumEnColorTrackPacketVisualizer::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(ChannelList->count())) {
		switch (miIndx) {
			case arn_mli_PACKETITEM_HIDE:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->Nascondi->setVisible(en);
				break;
			case arn_mli_PACKETITEM_ENWARNING:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->AbilitaAllarme->setVisible(en);
				break;
			case arn_mli_PACKETITEM_TRACKCOLOR:
				((arnNumEnColorTrackPacketItem *)ChannelList->at(index))->enTrackColor->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnNumEnColorTrackPacketVisualizer::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->Nascondi->setVisible(en);
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->AbilitaAllarme->setVisible(en);
			break;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			((arnNumEnColorTrackPacketItem *)ChannelList->at(i))->enTrackColor->setVisible(en);
			break;
		default: break;
		}
}

void arnNumEnColorTrackPacketVisualizer::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			popupText_Nascondi = txt;
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			popupText_Allarmi = txt;
			break;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			popupText_ColorTrack = txt;
			break;
		default: break;
		}
}
    
void arnNumEnColorTrackPacketVisualizer::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			popupTip_Nascondi = txt;
			break;
		case arn_mli_PACKETITEM_ENWARNING:
			popupTip_Allarmi = txt;
			break;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			popupTip_ColorTrack = txt;
			break;
		default: break;
		}
}

QString arnNumEnColorTrackPacketVisualizer::popupText(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			return popupText_Nascondi;
		case arn_mli_PACKETITEM_ENWARNING:
			return popupText_Allarmi;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			return popupText_ColorTrack;
		default: return QString("");
		}
}

QString arnNumEnColorTrackPacketVisualizer::popupTip(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_PACKETITEM_HIDE:
			return popupTip_Nascondi;
		case arn_mli_PACKETITEM_ENWARNING:
			return popupTip_Allarmi;
		case arn_mli_PACKETITEM_TRACKCOLOR:
			return popupTip_ColorTrack;
		default: return QString("");
		}
}
