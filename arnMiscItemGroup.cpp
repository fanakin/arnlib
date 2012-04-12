/***************************************************************************
						  arnMiscItemGroup.cpp  -  description
                             -------------------
	begin                : mar set 28 2010
	copyright            : (C) 2003-2010 by fabio giovagnini
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
#include "arnPushButtonItem.h"
#include "arnToggleButtonItem.h"
#include "arnMiscItemGroup.h"

arnMiscItemGroup::arnMiscItemGroup(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
	ItemList = new QList<QWidget*>;
	if (!ItemList) arnCriticalExit();
	ItemList->clear();
	ItemTypeList = new QList<arnGroupItemType_t>;
	if (!ItemTypeList) arnCriticalExit();
	ItemTypeList->clear();
	pVLayout = new QVBoxLayout(this,0,-1,"arnItemGroupLayout");//QGridLayout( this, 1, 1, 0, 0, "arnMiscItemGroupLayout");
    if (!pVLayout) arnCriticalExit();
    synchronized = false;
}

arnMiscItemGroup::~arnMiscItemGroup(void)
{
	if (ItemList) {delete ItemList; ItemList = 0;};
	if (ItemTypeList) {delete ItemTypeList; ItemTypeList = 0;};
}

void arnMiscItemGroup::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
	for (int  i = 0; i < int(ItemList->count()); ++i ) {showChannel(i);}
//    if (e->button () == Qt::RightButton) {
//        for (int  i = 0; i < int(ItemList->count()); ++i ) {showChannel(i);}
//        }
//    else  QFrame::mouseDoubleClickEvent(e);
}

bool arnMiscItemGroup::addItem(const char* Label,arnGroupItemType_t typ)
{
	switch (typ) {
		case agit_PushButtonItem: {
			QWidget *pItem = 0;
			pItem = new arnPushButtonItem(this,Label);
			if (!pItem) return false;
			ItemList->append(pItem);
			pVLayout->addWidget(pItem);
			ItemTypeList->append(agit_PushButtonItem);
			}
			break;
		case agit_ToggleButtonItem: {
			QWidget *pItem = 0;
			pItem = new arnToggleButtonItem(this,Label);
			if (!pItem) return false;
			ItemList->append(pItem);
			pVLayout->addWidget(pItem);
			ItemTypeList->append(agit_ToggleButtonItem);
			}
		break;
		default: return false;
	}
    return true;
}

bool arnMiscItemGroup::deleteItem(const char* Label)
{
    bool found = false;
    int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
	pVLayout->removeChild(((QWidget *)ItemList->at(i)));
//    ((arnSliderItem *)ItemList->at(i))->Slider->removeEventFilter( this );

	QWidget* ptr = (QWidget*)(ItemList->at(i));
    if (!ptr) return false;
	ItemList->removeAt(i);
    delete ptr;
	ItemTypeList->removeAt(i);

//    if (!(ItemList->remove(i))) return false;
    update();
    return true;
}

double arnMiscItemGroup::getValue(int index)
{
	if (index < int(ItemList->count())) {
		arnGroupItemType_t t = (arnGroupItemType_t)(ItemTypeList->at(index));
		switch (t) {
			case agit_PushButtonItem:
				return (double) (((arnPushButtonItem*)ItemList->at(index))->value());
				break;
			case agit_ToggleButtonItem:
				return (double) (((arnToggleButtonItem*)ItemList->at(index))->value());
				break;
			default: return double(0);
		}
	}
	return double(0);
}

double arnMiscItemGroup::getValue(const char* Label)
{
	bool found = false;
    int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return double(0);
	arnGroupItemType_t t = (arnGroupItemType_t)(ItemTypeList->at(i));
	switch (t) {
		case agit_PushButtonItem:
			return (double) (((arnPushButtonItem*)ItemList->at(i))->value());
			break;
		case agit_ToggleButtonItem:
			return (double) (((arnToggleButtonItem*)ItemList->at(i))->value());
			break;
		default: return false;
	}
	return (double)0;
}

void arnMiscItemGroup::setValue(int index,double val)
{
	if (index < int(ItemList->count())) {
		arnGroupItemType_t t = (arnGroupItemType_t)(ItemTypeList->at(index));
		switch (t) {
			case agit_PushButtonItem:
				(((arnPushButtonItem*)ItemList->at(index))->setValue(val));
				break;
			case agit_ToggleButtonItem:
				(((arnToggleButtonItem*)ItemList->at(index))->setValue(val));
				break;
			default: return;
		}
	}
}

void arnMiscItemGroup::setValue(const char* Label,double val)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return;
	arnGroupItemType_t t = (arnGroupItemType_t)(ItemTypeList->at(i));
	switch (t) {
		case agit_PushButtonItem:
			(((arnPushButtonItem*)ItemList->at(i))->setValue(val));
			break;
		case agit_ToggleButtonItem:
			(((arnToggleButtonItem*)ItemList->at(i))->setValue(val));
			break;
		default: return;
	}
}

QString arnMiscItemGroup::text(int index) {
	if (index < int(ItemList->count())) {
		arnGroupItemType_t t = (arnGroupItemType_t)(ItemTypeList->at(index));
		switch (t) {
			case agit_PushButtonItem:
				return ((arnPushButtonItem *)ItemList->at(index))->text();
				break;
		case agit_ToggleButtonItem:
			return ((arnToggleButtonItem *)ItemList->at(index))->text();
			break;
			default: return QString("");
		}
	}
	return QString("");
}


QString arnMiscItemGroup::text(const char* Label)
{
    bool found = false;
    int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return QString("");
	arnGroupItemType_t t = (arnGroupItemType_t)(ItemTypeList->at(i));
	switch (t) {
		case agit_PushButtonItem:
			return (((arnPushButtonItem*)ItemList->at(i))->text());
			break;
	case agit_ToggleButtonItem:
		return (((arnToggleButtonItem*)ItemList->at(i))->text());
		break;
                default: return QString("");
	}
	return QString("");
}


void arnMiscItemGroup::setSynchronized(bool synch)
{
	//int i,j;
    synchronized = synch;
	/*
    if (synchronized) {
		for ( i = 0; i < int(ItemList->count()); ++i )
			for ( j = 0; j < int(ItemList->count()); ++j ) {
				connect(((arnGenericGroupItem *)ItemList->at(i)), SIGNAL(valueChanged(int)),
					((arnSliderItem *)ItemList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
    else {
		for ( i = 0; i < int(ItemList->count()); ++i )
			for ( j = 0; j < int(ItemList->count()); ++j ) {
				disconnect(((arnSliderItem *)ItemList->at(i)), SIGNAL(valueChanged(int)),
					((arnSliderItem *)ItemList->at(j)), SLOT(setSliderValue(int)));
                    }
        }
	*/
}


void arnMiscItemGroup::showChannel(int index)
{
	if (index < int(ItemList->count())) ((QWidget *)ItemList->at(index))->show();
}

void arnMiscItemGroup::hideChannel(int index)
{
	if (index < int(ItemList->count())) ((QWidget *)ItemList->at(index))->hide();
}

void arnMiscItemGroup::showChannel (const char* Label)
{
    bool found = false;
    int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
	((QWidget *)ItemList->at(i))->show();
}

void arnMiscItemGroup::hideChannel (const char* Label)
{
    bool found = false;
    int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
	((QWidget *)ItemList->at(i))->hide();
}

bool arnMiscItemGroup::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
	return ((QWidget *)ItemList->at(i))->isVisibleTo(this);
}

/*
bool arnMiscItemGroup::isChannelConnected(int index)
{
	if (index < int(ItemList->count())) return ((arnSliderItem *)ItemList->at(index))->isConnected();
	return false;
}

bool arnMiscItemGroup::isChannelConnected(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((arnGenericGroupItem *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((arnGenericGroupItem *)ItemList->at(i))->isConnected();
}
*/
void arnMiscItemGroup::setPopupMenuItemName(int /*index*/,arnMultiLangItemType_t /*miIndx*/,QString /*name*/)
{
}
    
void arnMiscItemGroup::setPopupMenuItemName(const char* /*Label*/,arnMultiLangItemType_t /*miIndx*/,QString /*name*/)
{
}

void arnMiscItemGroup::setPopupMenuItemTip(int /*index*/,arnMultiLangItemType_t /*miIndx*/,QString /*tip*/)
{
}
    
void arnMiscItemGroup::setPopupMenuItemTip(const char* /*Label*/,arnMultiLangItemType_t /*miIndx*/,QString /*tip*/)
{
}

void arnMiscItemGroup::setVisiblePopupMenuItem(int /*index*/,arnMultiLangItemType_t /*miIndx*/,bool /*en*/)
{
}
    
void arnMiscItemGroup::setVisiblePopupMenuItem(const char* /*Label*/,arnMultiLangItemType_t /*miIndx*/, bool /*en*/)
{
}

void arnMiscItemGroup::setPopupText(arnMultiLangItemType_t miIndx,QString txt)
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
    
void arnMiscItemGroup::setPopupTip(arnMultiLangItemType_t miIndx,QString txt)
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

QString arnMiscItemGroup::popupText(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			return popupText_Nascondi;
		case arn_mli_SLIDERITEM_CONNECT:
			return popupText_Connetti;
		default: return QString("");
		}
}

QString arnMiscItemGroup::popupTip(arnMultiLangItemType_t miIndx)
{
	switch (miIndx) {
		case arn_mli_SLIDERITEM_HIDE:
			return popupTip_Nascondi;
		case arn_mli_SLIDERITEM_CONNECT:
			return popupTip_Connetti;
		default:  return QString("");
		}
}

void arnMiscItemGroup::setVisible(const char* Label,bool en)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ItemList->count()); ++i ) {
		if (!strcmp(((QWidget *)ItemList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) arnCriticalExit();
	return ((QWidget *)ItemList->at(i))->setVisible(en);
}

//bool arnMiscItemGroup::eventFilter(QObject *obj, QEvent *ev)
//{
//    if (ev->type() == QEvent::MouseButtonRelease) {
//            // special processing for key press
//            QMouseEvent *k = (QMouseEvent *)ev;
//            if (k->button() == Qt::RightButton) {
//                int i;
//                bool found = false;
//                for ( i = 0; i < int(ItemList->count()); ++i ) {
//                    if (ItemList->at(i)->Slider == obj) { // variabile gia' trovata
//                        found = true;
//                        break;
//                        }
//                    }
//                if (found) {ItemList->at(i)->Slider->setFocus();}
//                }
//            return false; // don't eat event
//        }
//    else {
//            // standard event processing
//            return QFrame::eventFilter(obj, ev );
//        }
//}
