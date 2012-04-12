/***************************************************************************
                          arnEngineAppMSTraceSliderGroup.cpp  -  description
                             -------------------
    begin                : gio Feb 9 2006
    copyright            : (C) 2006 by Aurion s.r.l.
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
#include <QKeyEvent>
#include "CommonFunctions.h"
#include "arnEngineAppMSTraceSliderGroup.h"
#include "qapplication.h"

arnEngineAppMSTraceSliderGroup::arnEngineAppMSTraceSliderGroup(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    SliderList = new QList<arnEngineAppMSTraceSliderItem*>;
    if (!SliderList) arnCriticalExit();
    //SliderList->setAutoDelete(true);
    SliderList->clear();
    pVLayout = new QVBoxLayout(this,0,-1,"arnEngineAppMSTraceSliderGroupLayout");//QGridLayout( this, 1, 1, 0, 0, "arnEngineAppMSTraceSliderGroupLayout");
    if (!pVLayout) arnCriticalExit();
    synchronized = false;
	mulSelEnabled = false;
	popupText_Nascondi = "Hide";
	popupTip_Nascondi = "Hide the slider if you are not interested of it";
	popupText_Connetti = "Connect";
	popupTip_Connetti = "Connect the slider to the parameter file for adjustment fitting";
	popupText_AbilitaCOP = "Enable COP";
	popupTip_AbilitaCOP = "Enable the adjustment table as source of real time adjustment";
	popupText_ModificaCOP = "Edit COP";
	popupTip_ModificaCOP = "Edit the adjustment table for manual adjustment";
}

arnEngineAppMSTraceSliderGroup::~arnEngineAppMSTraceSliderGroup(void)
{
    if (SliderList) {delete SliderList; SliderList = 0;};
}

void arnEngineAppMSTraceSliderGroup::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//    if (e->button () == Qt::RightButton) {
//        for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//        }
//    else  QFrame::mouseDoubleClickEvent(e);
}

bool arnEngineAppMSTraceSliderGroup::addSlider(const char* Label)
{
    arnEngineAppMSTraceSliderItem *pSliderItem = new arnEngineAppMSTraceSliderItem(Label,this,Label);
    if (!pSliderItem) return false;
	pSliderItem->Nascondi->setText(popupText_Nascondi);
	pSliderItem->Nascondi->setMenuText(popupText_Nascondi);
	pSliderItem->Nascondi->setToolTip(popupTip_Nascondi);
	pSliderItem->Connetti->setText(popupText_Connetti);
	pSliderItem->Connetti->setMenuText(popupText_Connetti);
	pSliderItem->Connetti->setToolTip(popupTip_Connetti);
	pSliderItem->AbilitaCopertura->setText(popupText_AbilitaCOP);
	pSliderItem->AbilitaCopertura->setMenuText(popupText_AbilitaCOP);
	pSliderItem->AbilitaCopertura->setToolTip(popupTip_AbilitaCOP);
	pSliderItem->EditCopertura->setText(popupText_ModificaCOP);
	pSliderItem->EditCopertura->setMenuText(popupText_ModificaCOP);
	pSliderItem->EditCopertura->setToolTip(popupTip_ModificaCOP);
    SliderList->append(pSliderItem);
    pVLayout->addWidget(pSliderItem);
    return true;
}

bool arnEngineAppMSTraceSliderGroup::deleteSlider(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    pVLayout->removeChild(((arnEngineAppMSTraceSliderItem *)SliderList->at(i)));
//    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Slider->removeEventFilter( this );
    
    arnEngineAppMSTraceSliderItem *ptr = SliderList->at(i);
    if (!ptr) return false;
    SliderList->removeAt (i);
    delete ptr;
	
	//if (!(SliderList->remove(i))) return false;
    update();
    return true;
}

double arnEngineAppMSTraceSliderGroup::getSliderValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->sliderValue();

//    return ((int)(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Value->text().toDouble()));

}

double arnEngineAppMSTraceSliderGroup::getValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->value();
}

QString arnEngineAppMSTraceSliderGroup::text(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->text();
}

void arnEngineAppMSTraceSliderGroup::setSliderMin(const char* Label, int min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setSliderMin(min);
}

void arnEngineAppMSTraceSliderGroup::setSliderMax(const char* Label, int max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setSliderMax(max);
}

void arnEngineAppMSTraceSliderGroup::setSliderValue(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
	if (val <= ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->SliderMin()) {
		((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setSliderValue((int)((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->SliderMin());
		return;
		}
	if (val >= ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->SliderMax()) {
		((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setSliderValue((int)((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->SliderMax());
		return;
		}
	((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setSliderValue(val);
}

void arnEngineAppMSTraceSliderGroup::setSliderValue(int index, int val)
{
	if (index < int(SliderList->count())) {
		if (val <= ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->SliderMin()) {
			((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->setSliderValue((int)((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->SliderMin());
			return;
			}
		if (val >= ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->SliderMax()) {
			((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->setSliderValue((int)((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->SliderMax());
			return;
			}
		((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->setSliderValue(val);
		}
}


void arnEngineAppMSTraceSliderGroup::setSynchronized(bool synch)
{
    int i,j;
    synchronized = synch;
    if (synchronized) {
        for ( i = 0; i < int(SliderList->count()); ++i ) 
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                connect(((arnEngineAppMSTraceSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnEngineAppMSTraceSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
    else {
        for ( i = 0; i < int(SliderList->count()); ++i )
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                disconnect(((arnEngineAppMSTraceSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnEngineAppMSTraceSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
}

void arnEngineAppMSTraceSliderGroup::setValueSize(const char* Label,  NumericFixedFormat_t sz, char f ,int pr)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setValueSize(sz,f,pr);
}

void arnEngineAppMSTraceSliderGroup::setValueMin(const char* Label, double min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setValueMin(min);
}

void arnEngineAppMSTraceSliderGroup::setValueMax(const char* Label,  double max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setValueMax(max);
}

void arnEngineAppMSTraceSliderGroup::showChannel(int index)
{
    if (index < int(SliderList->count())) ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->show();
}

void arnEngineAppMSTraceSliderGroup::hideChannel(int index)
{
    if (index < int(SliderList->count())) ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->hide();
}

void arnEngineAppMSTraceSliderGroup::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->show();
}

void arnEngineAppMSTraceSliderGroup::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->hide();
}

bool arnEngineAppMSTraceSliderGroup::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->isVisibleTo(this);
}

QString arnEngineAppMSTraceSliderGroup::getSliderName(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name();
}

double arnEngineAppMSTraceSliderGroup::ValueMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->ValueMin();
}

double arnEngineAppMSTraceSliderGroup::ValueMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->ValueMax();
}

int arnEngineAppMSTraceSliderGroup::SliderMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->SliderMin();
}

int arnEngineAppMSTraceSliderGroup::SliderMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->SliderMax();
}

bool arnEngineAppMSTraceSliderGroup::isChannelConnected(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->isConnected();
	return false;
}

bool arnEngineAppMSTraceSliderGroup::isChannelConnected(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->isConnected();
}

void arnEngineAppMSTraceSliderGroup::setReplaceObject(const char* Label,arnSObjectContainer *pRo)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setReplaceObject(pRo);
}

arnSObjectContainer *arnEngineAppMSTraceSliderGroup::replaceObject(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->replaceObject();
}

bool arnEngineAppMSTraceSliderGroup::isCOPEnabled(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->isCOPEnabled();
	return false;
}

bool arnEngineAppMSTraceSliderGroup::isCOPEnabled(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->isCOPEnabled();
}

void arnEngineAppMSTraceSliderGroup::setMulSelKeyUP(const char* Label, Qt::Key K)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setMulSelKeyUP(K);
}

void arnEngineAppMSTraceSliderGroup::setMulSelKeyDOWN(const char* Label, Qt::Key K)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setMulSelKeyDOWN(K);
}

void arnEngineAppMSTraceSliderGroup::keyPressEvent ( QKeyEvent * e )
{
	int i;
	if (!mulSelEnabled) {e->ignore(); return;}
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		arnEngineAppMSTraceSliderItem *item = ((arnEngineAppMSTraceSliderItem *)SliderList->at(i));
		if ((item->getMulSelKeyUP() == Qt::Key_Escape) || (item->getMulSelKeyDOWN() == Qt::Key_Escape)) {
			e->accept();
			}
		else {
			if (e->key() == item->getMulSelKeyUP()) item->setSliderValue( ((int)item->sliderValue()) +  item->lineStep());
			else if (e->key() == item->getMulSelKeyDOWN())  item->setSliderValue( ((int)item->sliderValue()) -  item->lineStep());
			e->accept();
			}
		}
}

void arnEngineAppMSTraceSliderGroup::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Nascondi->setText(name);
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Nascondi->setMenuText(name);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Connetti->setText(name);
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Connetti->setMenuText(name);
				break;
		case arn_mli_SLIDERITEM_ENCOP:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->AbilitaCopertura->setText(name);
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->AbilitaCopertura->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->EditCopertura->setText(name);
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->EditCopertura->setMenuText(name);
			break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineAppMSTraceSliderGroup::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Nascondi->setText(name);
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Nascondi->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Connetti->setText(name);
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Connetti->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->AbilitaCopertura->setText(name);
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->AbilitaCopertura->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->EditCopertura->setText(name);
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->EditCopertura->setMenuText(name);
			break;
		default: break;
		}
}

void arnEngineAppMSTraceSliderGroup::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Nascondi->setToolTip(tip);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Connetti->setToolTip(tip);
				break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->AbilitaCopertura->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->EditCopertura->setToolTip(tip);
			break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineAppMSTraceSliderGroup::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Nascondi->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Connetti->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->AbilitaCopertura->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->EditCopertura->setToolTip(tip);
			break;
		default: break;
		}
}

void arnEngineAppMSTraceSliderGroup::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Nascondi->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->Connetti->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_ENCOP:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->AbilitaCopertura->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_EDITCOP:
				((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->EditCopertura->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineAppMSTraceSliderGroup::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Nascondi->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->Connetti->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->AbilitaCopertura->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->EditCopertura->setVisible(en);
			break;
		default: break;
		}
}

void arnEngineAppMSTraceSliderGroup::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			popupText_Nascondi = txt;
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			popupText_Connetti = txt;
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			popupText_AbilitaCOP = txt;
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			popupText_ModificaCOP = txt;
			break;
		default: break;
		}
}
    
void arnEngineAppMSTraceSliderGroup::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			popupTip_Nascondi = txt;
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			popupTip_Connetti = txt;
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			popupTip_AbilitaCOP = txt;
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			popupTip_ModificaCOP = txt;
			break;
		default: break;
		}
}

QString arnEngineAppMSTraceSliderGroup::popupText(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			return popupText_Nascondi;
		case arn_mli_SLIDERITEM_CONNECT:
			return popupText_Connetti;
		case arn_mli_SLIDERITEM_ENCOP:
			return popupText_AbilitaCOP;
		case arn_mli_SLIDERITEM_EDITCOP:
			return popupText_ModificaCOP;
		default: return QString("");
		}
}

QString arnEngineAppMSTraceSliderGroup::popupTip(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			return popupTip_Nascondi;
		case arn_mli_SLIDERITEM_CONNECT:
			return popupTip_Connetti;
		case arn_mli_SLIDERITEM_ENCOP:
			return popupTip_AbilitaCOP;
		case arn_mli_SLIDERITEM_EDITCOP:
			return popupTip_ModificaCOP;
		default:  return QString("");
		}
}

bool arnEngineAppMSTraceSliderGroup::isTraceEnabled(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineAppMSTraceSliderItem *)SliderList->at(index))->isTraceEnabled();
	return false;
}

bool arnEngineAppMSTraceSliderGroup::isTraceEnabled(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->isTraceEnabled();
}

void arnEngineAppMSTraceSliderGroup::setVisiblem(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppMSTraceSliderItem *)SliderList->at(i))->setVisible(en);
}

//bool arnEngineAppMSTraceSliderGroup::eventFilter(QObject *obj, QEvent *ev)
//{
//    if (ev->type() == QEvent::MouseButtonRelease) {
//            // special processing for key press
//            QMouseEvent *k = (QMouseEvent *)ev;
//            if (k->button() == Qt::RightButton) {
//                int i;
//                bool found = false;
//                for ( i = 0; i < int(SliderList->count()); ++i ) {
//                    if (SliderList->at(i)->Slider == obj) { // variabile gia' trovata
//                        found = true;
//                        break;
//                        }
//                    }
//                if (found) {SliderList->at(i)->Slider->setFocus();}
//                }
//            return false; // don't eat event
//        }
//    else {
//            // standard event processing
//            return QFrame::eventFilter(obj, ev );
//        }
//}
