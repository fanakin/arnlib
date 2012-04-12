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
#include "arnEngineZAppSliderGroup.h"

arnEngineZAppSliderGroup::arnEngineZAppSliderGroup(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    SliderList = new QList<arnEngineZAppSliderItem *>;
    if (!SliderList) arnCriticalExit();
//    SliderList->setAutoDelete(true);
    SliderList->clear();
    pVLayout = new QVBoxLayout(this,0,-1,"arnEngineAppSliderGroupLayout");//QGridLayout( this, 1, 1, 0, 0, "arnEngineAppSliderGroupLayout");
    if (!pVLayout) arnCriticalExit();
    synchronized = false;
}

arnEngineZAppSliderGroup::~arnEngineZAppSliderGroup(void)
{
    if (SliderList) {delete SliderList; SliderList = 0;};
}

void arnEngineZAppSliderGroup::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//    if (e->button () == Qt::RightButton) {
//        for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//        }
//    else  QFrame::mouseDoubleClickEvent(e);
}

bool arnEngineZAppSliderGroup::addSlider(const char* Label)
{
    arnEngineZAppSliderItem *pSliderItem = new arnEngineZAppSliderItem(Label,this,Label);
    if (!pSliderItem) return false;
    SliderList->append(pSliderItem);
    pVLayout->addWidget(pSliderItem);
    return true;
}

bool arnEngineZAppSliderGroup::deleteSlider(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    pVLayout->removeChild(((arnEngineZAppSliderItem *)SliderList->at(i)));
//    ((arnEngineZAppSliderItem *)SliderList->at(i))->Slider->removeEventFilter( this );
//    if (!(SliderList->remove(i))) return false;
    arnEngineZAppSliderItem *ptr = SliderList->at(i);
    if (!ptr) return false;
    
    SliderList->removeAt(i);
    delete ptr;

    update();
    return true;
}

double arnEngineZAppSliderGroup::getSliderValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->sliderValue();

//    return ((int)(((arnEngineZAppSliderItem *)SliderList->at(i))->Value->text().toDouble()));

}

double arnEngineZAppSliderGroup::getValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->value();
}

QString arnEngineZAppSliderGroup::text(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->text();
}

void arnEngineZAppSliderGroup::setSliderMin(const char* Label, int min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->setSliderMin(min);
}

void arnEngineZAppSliderGroup::setSliderMax(const char* Label, int max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->setSliderMax(max);
}

void arnEngineZAppSliderGroup::setSliderValue(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
	if (val <= ((arnEngineZAppSliderItem *)SliderList->at(i))->SliderMin()) {
		((arnEngineZAppSliderItem *)SliderList->at(i))->setSliderValue((int)((arnEngineZAppSliderItem *)SliderList->at(i))->SliderMin());
		return;
		}
	if (val >= ((arnEngineZAppSliderItem *)SliderList->at(i))->SliderMax()) {
		((arnEngineZAppSliderItem *)SliderList->at(i))->setSliderValue((int)((arnEngineZAppSliderItem *)SliderList->at(i))->SliderMax());
		return;
		}
	((arnEngineZAppSliderItem *)SliderList->at(i))->setSliderValue(val);
}

void arnEngineZAppSliderGroup::setSliderValue(int index, int val)
{
	if (index < int(SliderList->count())) {
		if (val <= ((arnEngineZAppSliderItem *)SliderList->at(index))->SliderMin()) {
			((arnEngineZAppSliderItem *)SliderList->at(index))->setSliderValue((int)((arnEngineZAppSliderItem *)SliderList->at(index))->SliderMin());
			return;
			}
		if (val >= ((arnEngineZAppSliderItem *)SliderList->at(index))->SliderMax()) {
			((arnEngineZAppSliderItem *)SliderList->at(index))->setSliderValue((int)((arnEngineZAppSliderItem *)SliderList->at(index))->SliderMax());
			return;
			}
		((arnEngineZAppSliderItem *)SliderList->at(index))->setSliderValue(val);
		}
}


void arnEngineZAppSliderGroup::setSynchronized(bool synch)
{
    int i,j;
    synchronized = synch;
    if (synchronized) {
        for ( i = 0; i < int(SliderList->count()); ++i ) 
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                connect(((arnEngineZAppSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnEngineZAppSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
    else {
        for ( i = 0; i < int(SliderList->count()); ++i )
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                disconnect(((arnEngineZAppSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnEngineZAppSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
}

void arnEngineZAppSliderGroup::setValueSize(const char* Label,  NumericFixedFormat_t sz, char f ,int pr)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->setValueSize(sz,f,pr);
}

void arnEngineZAppSliderGroup::setValueMin(const char* Label, double min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->setValueMin(min);
}

void arnEngineZAppSliderGroup::setValueMax(const char* Label,  double max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->setValueMax(max);
}

void arnEngineZAppSliderGroup::showChannel(int index)
{
    if (index < int(SliderList->count())) ((arnEngineZAppSliderItem *)SliderList->at(index))->show();
}

void arnEngineZAppSliderGroup::hideChannel(int index)
{
    if (index < int(SliderList->count())) ((arnEngineZAppSliderItem *)SliderList->at(index))->hide();
}

void arnEngineZAppSliderGroup::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->show();
}

void arnEngineZAppSliderGroup::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnEngineZAppSliderItem *)SliderList->at(i))->hide();
}

bool arnEngineZAppSliderGroup::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->isVisibleTo(this);
}

QString arnEngineZAppSliderGroup::getSliderName(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->name();
}

double arnEngineZAppSliderGroup::ValueMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->ValueMin();
}

double arnEngineZAppSliderGroup::ValueMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->ValueMax();
}

int arnEngineZAppSliderGroup::SliderMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->SliderMin();
}

int arnEngineZAppSliderGroup::SliderMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnEngineZAppSliderItem *)SliderList->at(i))->SliderMax();
}

bool arnEngineZAppSliderGroup::isChannelConnected(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineZAppSliderItem *)SliderList->at(index))->isConnected();
	return false;
}

bool arnEngineZAppSliderGroup::isChannelConnected(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineZAppSliderItem *)SliderList->at(i))->isConnected();
}

void arnEngineZAppSliderGroup::setReplaceObject(const char* Label,arnSObjectContainer *pRo)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	((arnEngineZAppSliderItem *)SliderList->at(i))->setReplaceObject(pRo);
}

arnSObjectContainer *arnEngineZAppSliderGroup::replaceObject(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineZAppSliderItem *)SliderList->at(i))->replaceObject();
}

bool arnEngineZAppSliderGroup::isCOPEnabled(int index)
{
    if (index < int(SliderList->count())) return ((arnEngineZAppSliderItem *)SliderList->at(index))->isCOPEnabled();
	return false;
}

bool arnEngineZAppSliderGroup::isCOPEnabled(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineZAppSliderItem *)SliderList->at(i))->isCOPEnabled();
}

void arnEngineZAppSliderGroup::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineZAppSliderItem *)SliderList->at(index))->Nascondi->setText(name);
				((arnEngineZAppSliderItem *)SliderList->at(index))->Nascondi->setMenuText(name);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineZAppSliderItem *)SliderList->at(index))->Connetti->setText(name);
				((arnEngineZAppSliderItem *)SliderList->at(index))->Connetti->setMenuText(name);
				break;
		case arn_mli_SLIDERITEM_ENCOP:
				((arnEngineZAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setText(name);
				((arnEngineZAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
				((arnEngineZAppSliderItem *)SliderList->at(index))->EditCopertura->setText(name);
				((arnEngineZAppSliderItem *)SliderList->at(index))->EditCopertura->setMenuText(name);
			break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineZAppSliderGroup::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineZAppSliderItem *)SliderList->at(i))->Nascondi->setText(name);
			((arnEngineZAppSliderItem *)SliderList->at(i))->Nascondi->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineZAppSliderItem *)SliderList->at(i))->Connetti->setText(name);
			((arnEngineZAppSliderItem *)SliderList->at(i))->Connetti->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineZAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setText(name);
			((arnEngineZAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineZAppSliderItem *)SliderList->at(i))->EditCopertura->setText(name);
			((arnEngineZAppSliderItem *)SliderList->at(i))->EditCopertura->setMenuText(name);
			break;
		default: break;
		}
}

void arnEngineZAppSliderGroup::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineZAppSliderItem *)SliderList->at(index))->Nascondi->setToolTip(tip);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineZAppSliderItem *)SliderList->at(index))->Connetti->setToolTip(tip);
				break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineZAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineZAppSliderItem *)SliderList->at(index))->EditCopertura->setToolTip(tip);
			break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineZAppSliderGroup::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineZAppSliderItem *)SliderList->at(i))->Nascondi->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineZAppSliderItem *)SliderList->at(i))->Connetti->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineZAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineZAppSliderItem *)SliderList->at(i))->EditCopertura->setToolTip(tip);
			break;
		default: break;
		}
}

void arnEngineZAppSliderGroup::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnEngineZAppSliderItem *)SliderList->at(index))->Nascondi->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnEngineZAppSliderItem *)SliderList->at(index))->Connetti->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_ENCOP:
				((arnEngineZAppSliderItem *)SliderList->at(index))->AbilitaCopertura->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_EDITCOP:
				((arnEngineZAppSliderItem *)SliderList->at(index))->EditCopertura->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnEngineZAppSliderGroup::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnEngineZAppSliderItem *)SliderList->at(i))->Nascondi->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnEngineZAppSliderItem *)SliderList->at(i))->Connetti->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_ENCOP:
			((arnEngineZAppSliderItem *)SliderList->at(i))->AbilitaCopertura->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_EDITCOP:
			((arnEngineZAppSliderItem *)SliderList->at(i))->EditCopertura->setVisible(en);
			break;
		default: break;
		}
}

void arnEngineZAppSliderGroup::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
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
    
void arnEngineZAppSliderGroup::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
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

QString arnEngineZAppSliderGroup::popupText(arnMultiLangItemType_t miIndx)
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

QString arnEngineZAppSliderGroup::popupTip(arnMultiLangItemType_t miIndx)
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

void arnEngineZAppSliderGroup::setVisiblem(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnEngineZAppSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnEngineZAppSliderItem *)SliderList->at(i))->setVisible(en);
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
