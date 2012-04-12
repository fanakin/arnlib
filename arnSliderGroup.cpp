/***************************************************************************
                          arnSliderGroup.cpp  -  description
                             -------------------
    begin                : dom feb 23 2003
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
#include "arnSliderGroup.h"

arnSliderGroup::arnSliderGroup(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
    SliderList = new QList<arnSliderItem *>;
    if (!SliderList) arnCriticalExit();
//    SliderList->setAutoDelete(true);
    SliderList->clear();
    pVLayout = new QVBoxLayout(this,0,-1,"arnSliderGroupLayout");//QGridLayout( this, 1, 1, 0, 0, "arnSliderGroupLayout"); 
    if (!pVLayout) arnCriticalExit();
    synchronized = false;
}

arnSliderGroup::~arnSliderGroup(void)
{
    if (SliderList) {delete SliderList; SliderList = 0;};
}

void arnSliderGroup::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
    for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//    if (e->button () == Qt::RightButton) {
//        for (int  i = 0; i < int(SliderList->count()); ++i ) {showChannel(i);}
//        }
//    else  QFrame::mouseDoubleClickEvent(e);
}

bool arnSliderGroup::addSlider(const char* Label)
{
    arnSliderItem *pSliderItem = new arnSliderItem(Label,this,Label);
    if (!pSliderItem) return false;
    SliderList->append(pSliderItem);
    pVLayout->addWidget(pSliderItem);
    return true;
}

bool arnSliderGroup::deleteSlider(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    pVLayout->removeChild(((arnSliderItem *)SliderList->at(i)));
//    ((arnSliderItem *)SliderList->at(i))->Slider->removeEventFilter( this );

    arnSliderItem *ptr = SliderList->at(i);
    if (!ptr) return false;
    SliderList->removeAt(i);
    delete ptr;

//    if (!(SliderList->remove(i))) return false;
    update();
    return true;
}

double arnSliderGroup::getSliderValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnSliderItem *)SliderList->at(i))->sliderValue();

//    return ((int)(((arnSliderItem *)SliderList->at(i))->Value->text().toDouble()));

}

double arnSliderGroup::getValue(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
    return ((arnSliderItem *)SliderList->at(i))->value();
}

QString arnSliderGroup::text(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnSliderItem *)SliderList->at(i))->text();
}

void arnSliderGroup::setSliderMin(const char* Label, int min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->setSliderMin(min);
}

void arnSliderGroup::setSliderMax(const char* Label, int max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->setSliderMax(max);
}

void arnSliderGroup::setSliderValue(const char* Label, int val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
	if (val <= ((arnSliderItem *)SliderList->at(i))->SliderMin()) {
		((arnSliderItem *)SliderList->at(i))->setSliderValue((int)((arnSliderItem *)SliderList->at(i))->SliderMin());
		return;
		}
	if (val >= ((arnSliderItem *)SliderList->at(i))->SliderMax()) {
		((arnSliderItem *)SliderList->at(i))->setSliderValue((int)((arnSliderItem *)SliderList->at(i))->SliderMax());
		return;
		}
	((arnSliderItem *)SliderList->at(i))->setSliderValue(val);
}

void arnSliderGroup::setSliderValue(int index, int val)
{
	if (index < int(SliderList->count())) {
		if (val <= ((arnSliderItem *)SliderList->at(index))->SliderMin()) {
			((arnSliderItem *)SliderList->at(index))->setSliderValue((int)((arnSliderItem *)SliderList->at(index))->SliderMin());
			return;
			}
		if (val >= ((arnSliderItem *)SliderList->at(index))->SliderMax()) {
			((arnSliderItem *)SliderList->at(index))->setSliderValue((int)((arnSliderItem *)SliderList->at(index))->SliderMax());
			return;
			}
		((arnSliderItem *)SliderList->at(index))->setSliderValue(val);
		}
}


void arnSliderGroup::setSynchronized(bool synch)
{
    int i,j;
    synchronized = synch;
    if (synchronized) {
        for ( i = 0; i < int(SliderList->count()); ++i ) 
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                connect(((arnSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
    else {
        for ( i = 0; i < int(SliderList->count()); ++i )
            for ( j = 0; j < int(SliderList->count()); ++j ) {
                disconnect(((arnSliderItem *)SliderList->at(i)), SIGNAL(valueChanged(int)),
                    ((arnSliderItem *)SliderList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
}

void arnSliderGroup::setValueSize(const char* Label,  NumericFixedFormat_t sz, char f ,int pr)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->setValueSize(sz,f,pr);
}

void arnSliderGroup::setValueMin(const char* Label, double min)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->setValueMin(min);
}

void arnSliderGroup::setValueMax(const char* Label,  double max)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->setValueMax(max);
}

void arnSliderGroup::showChannel(int index)
{
    if (index < int(SliderList->count())) ((arnSliderItem *)SliderList->at(index))->show();
}

void arnSliderGroup::hideChannel(int index)
{
    if (index < int(SliderList->count())) ((arnSliderItem *)SliderList->at(index))->hide();
}

void arnSliderGroup::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->show();
}

void arnSliderGroup::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnSliderItem *)SliderList->at(i))->hide();
}

bool arnSliderGroup::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return ((arnSliderItem *)SliderList->at(i))->isVisibleTo(this);
}

QString arnSliderGroup::getSliderName(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(SliderList->count()); ++i ) {
        if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
    return ((arnSliderItem *)SliderList->at(i))->name();
}

double arnSliderGroup::ValueMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnSliderItem *)SliderList->at(i))->ValueMin();
}

double arnSliderGroup::ValueMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnSliderItem *)SliderList->at(i))->ValueMax();
}

int arnSliderGroup::SliderMin(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnSliderItem *)SliderList->at(i))->SliderMin();
}

int arnSliderGroup::SliderMax(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnSliderItem *)SliderList->at(i))->SliderMax();
}

bool arnSliderGroup::isChannelConnected(int index)
{
    if (index < int(SliderList->count())) return ((arnSliderItem *)SliderList->at(index))->isConnected();
	return false;
}

bool arnSliderGroup::isChannelConnected(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
    return ((arnSliderItem *)SliderList->at(i))->isConnected();
}

void arnSliderGroup::setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnSliderItem *)SliderList->at(index))->Nascondi->setText(name);
				((arnSliderItem *)SliderList->at(index))->Nascondi->setMenuText(name);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnSliderItem *)SliderList->at(index))->Connetti->setText(name);
				((arnSliderItem *)SliderList->at(index))->Connetti->setMenuText(name);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnSliderGroup::setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnSliderItem *)SliderList->at(i))->Nascondi->setText(name);
			((arnSliderItem *)SliderList->at(i))->Nascondi->setMenuText(name);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnSliderItem *)SliderList->at(i))->Connetti->setText(name);
			((arnSliderItem *)SliderList->at(i))->Connetti->setMenuText(name);
			break;
		default: break;
		}
}

void arnSliderGroup::setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnSliderItem *)SliderList->at(index))->Nascondi->setToolTip(tip);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnSliderItem *)SliderList->at(index))->Connetti->setToolTip(tip);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnSliderGroup::setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnSliderItem *)SliderList->at(i))->Nascondi->setToolTip(tip);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnSliderItem *)SliderList->at(i))->Connetti->setToolTip(tip);
			break;
		default: break;
		}
}

void arnSliderGroup::setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en)
{
	if (index < int(SliderList->count())) {
		switch (miIndx) {
			case arn_mli_SLIDERITEM_HIDE:
				((arnSliderItem *)SliderList->at(index))->Nascondi->setVisible(en);
				break;
			case arn_mli_SLIDERITEM_CONNECT:
				((arnSliderItem *)SliderList->at(index))->Connetti->setVisible(en);
				break;
			default: break;
			}
		}
	else arnCriticalExit();
}
    
void arnSliderGroup::setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx, bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			((arnSliderItem *)SliderList->at(i))->Nascondi->setVisible(en);
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			((arnSliderItem *)SliderList->at(i))->Connetti->setVisible(en);
			break;
		default: break;
		}
}

void arnSliderGroup::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			popupText_Nascondi = txt;
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			popupText_Connetti = txt;
			break;
		default: break;
		}
}
    
void arnSliderGroup::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			popupTip_Nascondi = txt;
			break;
		case arn_mli_SLIDERITEM_CONNECT:
			popupTip_Connetti = txt;
			break;
		default: break;
		}
}

QString arnSliderGroup::popupText(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			return popupText_Nascondi;
		case arn_mli_SLIDERITEM_CONNECT:
			return popupText_Connetti;
		default: return QString("");
		}
}

QString arnSliderGroup::popupTip(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			return popupTip_Nascondi;
		case arn_mli_SLIDERITEM_CONNECT:
			return popupTip_Connetti;
		default:  return QString("");
		}
}

void arnSliderGroup::setVisiblem(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(SliderList->count()); ++i ) {
		if (!strcmp(((arnSliderItem *)SliderList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnSliderItem *)SliderList->at(i))->setVisible(en);
}

//bool arnSliderGroup::eventFilter(QObject *obj, QEvent *ev)
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
