/***************************************************************************
                          arnEngineAppSliderGroup.cpp  -  description
                             -------------------
    begin                : dom apr 24 2005
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

#include "CommonFunctions.h"
#include "arnEngineAppSliderGroup.h"

arnEngineAppSliderGroup::arnEngineAppSliderGroup(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    SliderList = new QList<arnEngineAppSliderItem *>;
    if (!SliderList) arnCriticalExit();
//    SliderList->setAutoDelete(true);
    SliderList->clear();
    pVLayout = new QVBoxLayout(this,0,-1,"arnEngineAppSliderGroupLayout");//QGridLayout( this, 1, 1, 0, 0, "arnEngineAppSliderGroupLayout");
    if (!pVLayout) arnCriticalExit();
    synchronized = false;
	popupText_Nascondi = "Hide";
	popupTip_Nascondi = "Hide the slider if you are not interested of it";
	popupText_Connetti = "Connect";
	popupTip_Connetti = "Connect the slider to the parameter file for adjustment fitting";
	popupText_AbilitaCOP = "Enable COP";
	popupTip_AbilitaCOP = "Enable the adjustment table as source of real time adjustment";
	popupText_ModificaCOP = "Edit COP";
	popupTip_ModificaCOP = "Edit the adjustment table for manual adjustment";
}

arnEngineAppSliderGroup::~arnEngineAppSliderGroup(void)
{
    if (SliderList) {delete SliderList; SliderList = 0;};
}

void arnEngineAppSliderGroup::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//    if (e->button () == Qt::RightButton) {
//        for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//        }
//    else  QFrame::mouseDoubleClickEvent(e);
}

bool arnEngineAppSliderGroup::addSlider(const char* Label)
{
    arnEngineAppSliderItem *pSliderItem = new arnEngineAppSliderItem(Label,this,Label);
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

bool arnEngineAppSliderGroup::deleteSlider(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    pVLayout->removeChild(((arnEngineAppSliderItem *)SliderList->at(i)));
//    ((arnEngineAppSliderItem *)SliderList->at(i))->Slider->removeEventFilter( this );

    arnEngineAppSliderItem *ptr = SliderList->at(i);
    if (!ptr) return false;
    SliderList->removeAt (i);
    delete ptr;

//    if (!(SliderList->remove(i))) return false;
    update();
    return true;
}

double arnEngineAppSliderGroup::getSliderValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnEngineAppSliderItem *)SliderList->at(i))->sliderValue();

//    return ((int)(((arnEngineAppSliderItem *)SliderList->at(i))->Value->text().toDouble()));

}

double arnEngineAppSliderGroup::getValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnEngineAppSliderItem *)SliderList->at(i))->value();
}

QString arnEngineAppSliderGroup::text(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnEngineAppSliderItem *)SliderList->at(i))->text();
}

void arnEngineAppSliderGroup::setSliderMin(const char* Label, int min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->setSliderMin(min);
}

void arnEngineAppSliderGroup::setSliderMax(const char* Label, int max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->setSliderMax(max);
}

void arnEngineAppSliderGroup::setSliderValue(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
	if (val <= ((arnEngineAppSliderItem *)SliderList->at(i))->SliderMin()) {
		((arnEngineAppSliderItem *)SliderList->at(i))->setSliderValue((int)((arnEngineAppSliderItem *)SliderList->at(i))->SliderMin());
		return;
		}
	if (val >= ((arnEngineAppSliderItem *)SliderList->at(i))->SliderMax()) {
		((arnEngineAppSliderItem *)SliderList->at(i))->setSliderValue((int)((arnEngineAppSliderItem *)SliderList->at(i))->SliderMax());
		return;
		}
	((arnEngineAppSliderItem *)SliderList->at(i))->setSliderValue(val);
}

void arnEngineAppSliderGroup::setSliderValue(int index, int val)
{
	if (index < int(SliderList->count())) {
		if (val <= ((arnEngineAppSliderItem *)SliderList->at(index))->SliderMin()) {
			((arnEngineAppSliderItem *)SliderList->at(index))->setSliderValue((int)((arnEngineAppSliderItem *)SliderList->at(index))->SliderMin());
			return;
			}
		if (val >= ((arnEngineAppSliderItem *)SliderList->at(index))->SliderMax()) {
			((arnEngineAppSliderItem *)SliderList->at(index))->setSliderValue((int)((arnEngineAppSliderItem *)SliderList->at(index))->SliderMax());
			return;
			}
		((arnEngineAppSliderItem *)SliderList->at(index))->setSliderValue(val);
		}
}


void arnEngineAppSliderGroup::setSynchronized(bool synch)
{
    int i,j;
    synchronized = synch;
    if (synchronized) {
        for ( i = 0; i < int(SliderList->count()); ++i ) 
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                connect(((arnEngineAppSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnEngineAppSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
    else {
        for ( i = 0; i < int(SliderList->count()); ++i )
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                disconnect(((arnEngineAppSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnEngineAppSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
}

void arnEngineAppSliderGroup::setValueSize(const char* Label,  NumericFixedFormat_t sz, char f ,int pr)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->setValueSize(sz,f,pr);
}

void arnEngineAppSliderGroup::setValueMin(const char* Label, double min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->setValueMin(min);
}

void arnEngineAppSliderGroup::setValueMax(const char* Label,  double max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->setValueMax(max);
}

void arnEngineAppSliderGroup::showChannel(int index)
{
    if (index < int(SliderList->count())) ((arnEngineAppSliderItem *)SliderList->at(index))->show();
}

void arnEngineAppSliderGroup::hideChannel(int index)
{
    if (index < int(SliderList->count())) ((arnEngineAppSliderItem *)SliderList->at(index))->hide();
}

void arnEngineAppSliderGroup::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->show();
}

void arnEngineAppSliderGroup::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineAppSliderItem *)SliderList->at(i))->hide();
}

bool arnEngineAppSliderGroup::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return ((arnEngineAppSliderItem *)SliderList->at(i))->isVisibleTo(this);
}

QString arnEngineAppSliderGroup::getSliderName(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnEngineAppSliderItem *)SliderList->at(i))->name();
}

double arnEngineAppSliderGroup::ValueMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppSliderItem *)SliderList->at(i))->ValueMin();
}

double arnEngineAppSliderGroup::ValueMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppSliderItem *)SliderList->at(i))->ValueMax();
}

int arnEngineAppSliderGroup::SliderMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppSliderItem *)SliderList->at(i))->SliderMin();
}

int arnEngineAppSliderGroup::SliderMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineAppSliderItem *)SliderList->at(i))->SliderMax();
}

bool arnEngineAppSliderGroup::isChannelConnected(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineAppSliderItem *)SliderList->at(index))->isConnected();
	return false;
}

bool arnEngineAppSliderGroup::isChannelConnected(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppSliderItem *)SliderList->at(i))->isConnected();
}

void arnEngineAppSliderGroup::setReplaceObject(const char* Label,arnSObjectContainer *pRo)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	((arnEngineAppSliderItem *)SliderList->at(i))->setReplaceObject(pRo);
}

arnSObjectContainer *arnEngineAppSliderGroup::replaceObject(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppSliderItem *)SliderList->at(i))->replaceObject();
}

bool arnEngineAppSliderGroup::isCOPEnabled(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineAppSliderItem *)SliderList->at(index))->isCOPEnabled();
	return false;
}

bool arnEngineAppSliderGroup::isCOPEnabled(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppSliderItem *)SliderList->at(i))->isCOPEnabled();
}

void arnEngineAppSliderGroup::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineAppSliderItem *)SliderList->at(index))->Nascondi->setText(name);
				((arnEngineAppSliderItem *)SliderList->at(index))->Nascondi->setMenuText(name);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineAppSliderItem *)SliderList->at(index))->Connetti->setText(name);
				((arnEngineAppSliderItem *)SliderList->at(index))->Connetti->setMenuText(name);
				break;
		case arn_mli_SLIDERITEM_ENCOP:
				((arnEngineAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setText(name);
				((arnEngineAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
				((arnEngineAppSliderItem *)SliderList->at(index))->EditCopertura->setText(name);
				((arnEngineAppSliderItem *)SliderList->at(index))->EditCopertura->setMenuText(name);
			break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineAppSliderGroup::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineAppSliderItem *)SliderList->at(i))->Nascondi->setText(name);
			((arnEngineAppSliderItem *)SliderList->at(i))->Nascondi->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineAppSliderItem *)SliderList->at(i))->Connetti->setText(name);
			((arnEngineAppSliderItem *)SliderList->at(i))->Connetti->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setText(name);
			((arnEngineAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppSliderItem *)SliderList->at(i))->EditCopertura->setText(name);
			((arnEngineAppSliderItem *)SliderList->at(i))->EditCopertura->setMenuText(name);
			break;
		default: break;
		}
}

void arnEngineAppSliderGroup::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineAppSliderItem *)SliderList->at(index))->Nascondi->setToolTip(tip);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineAppSliderItem *)SliderList->at(index))->Connetti->setToolTip(tip);
				break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppSliderItem *)SliderList->at(index))->EditCopertura->setToolTip(tip);
			break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineAppSliderGroup::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineAppSliderItem *)SliderList->at(i))->Nascondi->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineAppSliderItem *)SliderList->at(i))->Connetti->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppSliderItem *)SliderList->at(i))->EditCopertura->setToolTip(tip);
			break;
		default: break;
		}
}

void arnEngineAppSliderGroup::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineAppSliderItem *)SliderList->at(index))->Nascondi->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineAppSliderItem *)SliderList->at(index))->Connetti->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_ENCOP:
				((arnEngineAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_EDITCOP:
				((arnEngineAppSliderItem *)SliderList->at(index))->EditCopertura->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineAppSliderGroup::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineAppSliderItem *)SliderList->at(i))->Nascondi->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineAppSliderItem *)SliderList->at(i))->Connetti->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineAppSliderItem *)SliderList->at(i))->EditCopertura->setVisible(en);
			break;
		default: break;
		}
}

void arnEngineAppSliderGroup::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
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
    
void arnEngineAppSliderGroup::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
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

QString arnEngineAppSliderGroup::popupText(arnMultiLangItemType_t miIndx)
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

QString arnEngineAppSliderGroup::popupTip(arnMultiLangItemType_t miIndx)
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

void arnEngineAppSliderGroup::setVisiblem(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineAppSliderItem *)SliderList->at(i))->setVisible(en);
}


//bool arnEngineAppSliderGroup::eventFilter(QObject *obj, QEvent *ev)
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
