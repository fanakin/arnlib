/***************************************************************************
                          arnThermoPacketVisualizer.cpp  -  description
                             -------------------
    begin                : ven Mag 22 2009
    copyright            : (C) 2009 by fabio giovagnini
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
#include "arnThermoPacketVisualizer.h"

arnThermoPacketVisualizer::arnThermoPacketVisualizer(QWidget *parent, const char* name , Qt::WFlags f)
    : QFrame(parent,name,f)
{
	nItemPerLine = 5;
    ChannelList = new QList<arnThermoPacketItem*>;
    if (!ChannelList) arnCriticalExit();
    //ChannelList->setAutoDelete(true);
    ChannelList->clear();

	layout = new QGridLayout(this);
    if (!layout) arnCriticalExit();
}

arnThermoPacketVisualizer::~arnThermoPacketVisualizer(void)
{
    if (ChannelList) {delete ChannelList; ChannelList = 0;}
}

bool arnThermoPacketVisualizer::addChannel(const char* Label)
{
    // non finito: fare tutta l'assegnazione delle propreta'
	QString vln(Label);
	arnThermoPacketItem *tmp = new arnThermoPacketItem(vln,50,this);
	if (!tmp) return false;

	ChannelList->append(tmp);

	layout->addWidget(tmp,
		int((ChannelList->count() > 0) ? (ChannelList->count() - 1) : 0) / nItemPerLine,
		int((ChannelList->count() > 0) ? (ChannelList->count() - 1) : 0) % nItemPerLine,
		Qt::AlignLeft);

	return true;
}

bool arnThermoPacketVisualizer::deleteChannel(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
 
   arnThermoPacketItem *ptr = ChannelList->at(i);
    if (!ptr) return false;
    
    ChannelList->removeAt(i);
    delete ptr;

    update();

//
// per un futuro studio su come implementare la delete di un canale
//
//    if (!layout()) {
//        pHLayout = new QHBoxLayout(this,0,-1,"arnThermoPacketVisualizerLayout");
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
//        ((i % 2) == 0)? pVLayout2->addWidget(((arnThermoPacketItem*)ChannelList->at(i)))
//        : pVLayout1->addWidget(((arnThermoPacketItem *)ChannelList->at(i)));
//        }

    return true;
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, unsigned char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, signed char val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, unsigned short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, signed short val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue(val);
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, unsigned long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, signed long val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue((double)val);
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, float val, int prec, char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    str.setNum(val,fmt,prec);
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue(str.toDouble());
}

void arnThermoPacketVisualizer::setChannelValue (const char* Label, double val,int prec ,char fmt)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    QString str;
    str.setNum(val,fmt,prec);
    ((arnThermoPacketItem *)ChannelList->at(i))->setValue(str.toDouble());
}

void arnThermoPacketVisualizer::update(void)
{
    for (int i = 0; i < int(ChannelList->count()); ++i ) {
		((arnThermoPacketItem *)ChannelList->at(i))->update();
        }
    QFrame::update();
}

//void arnThermoPacketVisualizer::setChannelValue (const char* Label, const char* val)
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

void arnThermoPacketVisualizer::showChannel(int index)
{
    if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->show();
}

void arnThermoPacketVisualizer::hideChannel(int index)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->hide();
}

void arnThermoPacketVisualizer::showChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->show();
}

void arnThermoPacketVisualizer::hideChannel (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->hide();
}

bool  arnThermoPacketVisualizer::isChannelVisible(int index)
{
     if (index < int(ChannelList->count())) return ((arnThermoPacketItem *)ChannelList->at(index))->isVisibleTo(this);
     return  false;
}

bool arnThermoPacketVisualizer::isChannelVisible (const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return  ((arnThermoPacketItem *)ChannelList->at(i))->isVisibleTo(this);
}

void arnThermoPacketVisualizer::alignName(int index, int a)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->alignName(a);
}
void arnThermoPacketVisualizer::alignName(const char* Label, int a)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->alignName(a);
}

void arnThermoPacketVisualizer::setNameFontSize(int index,int a)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setNameFontSize(a);
}
void arnThermoPacketVisualizer::setNameFontSize(const char* Label,int a)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setNameFontSize(a);
}

void arnThermoPacketVisualizer::setRange(int index, double vmin, double vmax, bool lg)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setRange( vmin, vmax, lg);
}
void arnThermoPacketVisualizer::setRange(const char* Label, double vmin, double vmax, bool lg)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setRange( vmin, vmax, lg);
}

void arnThermoPacketVisualizer::setBorderWidth(int index, int m)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setBorderWidth( m);
}

void arnThermoPacketVisualizer::setBorderWidth(const char* Label,int m)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setBorderWidth( m);
}

void arnThermoPacketVisualizer::setAlarmLevel(int index, double v)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setAlarmLevel( v);
}
void arnThermoPacketVisualizer::setAlarmLevel(const char* Label,double v)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setAlarmLevel( v);
}

double arnThermoPacketVisualizer::alarmLevel(int index) const
{
	if (index < int(ChannelList->count())) return ((arnThermoPacketItem *)ChannelList->at(index))->alarmLevel();
     return  0;
}
double arnThermoPacketVisualizer::alarmLevel(const char* Label) const
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return  ((arnThermoPacketItem *)ChannelList->at(i))->alarmLevel();
}

void arnThermoPacketVisualizer::setAlarmEnabled(int index, bool tf)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setAlarmEnabled( tf);
}
void arnThermoPacketVisualizer::setAlarmEnabled(const char* Label,bool tf)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setAlarmEnabled( tf);
}

bool arnThermoPacketVisualizer::alarmEnabled(int index) const
{
	if (index < int(ChannelList->count())) return ((arnThermoPacketItem *)ChannelList->at(index))->alarmEnabled();
	return  false;
}
bool arnThermoPacketVisualizer::alarmEnabled(const char* Label) const
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    return ((arnThermoPacketItem *)ChannelList->at(i))->alarmEnabled();
}

void arnThermoPacketVisualizer::setPipeWidth(int index, int w)
{
     if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setPipeWidth( w);
}
void arnThermoPacketVisualizer::setPipeWidth(const char* Label, int w)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((arnThermoPacketItem *)ChannelList->at(i))->setPipeWidth( w);
}

int arnThermoPacketVisualizer::pipeWidth(int index) const
{
	if (index < int(ChannelList->count())) return ((arnThermoPacketItem *)ChannelList->at(index))->pipeWidth();
	return 0;
}
int arnThermoPacketVisualizer::pipeWidth(const char* Label) const
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return ((arnThermoPacketItem *)ChannelList->at(i))->pipeWidth();
}

void arnThermoPacketVisualizer::setMaxValue(int index, double v)
{
	if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setMaxValue(v);
}
void arnThermoPacketVisualizer::setMaxValue(const char* Label,double v)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return ;
    ((arnThermoPacketItem *)ChannelList->at(i))->setMaxValue(v);
}

double arnThermoPacketVisualizer::maxValue(int index) const
{
	if (index < int(ChannelList->count())) return ((arnThermoPacketItem *)ChannelList->at(index))->maxValue();
	return 0;
}
double arnThermoPacketVisualizer::maxValue(const char* Label) const
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return ((arnThermoPacketItem *)ChannelList->at(i))->maxValue();
}

void arnThermoPacketVisualizer::setMinValue(int index, double v)
{
	if (index < int(ChannelList->count())) ((arnThermoPacketItem *)ChannelList->at(index))->setMinValue(v);
}
void arnThermoPacketVisualizer::setMinValue(const char* Label,double v)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return ;
    ((arnThermoPacketItem *)ChannelList->at(i))->setMinValue(v);
}

double arnThermoPacketVisualizer::minValue(int index) const
{
	if (index < int(ChannelList->count())) return ((arnThermoPacketItem *)ChannelList->at(index))->minValue();
	return 0;
}
double arnThermoPacketVisualizer::minValue(const char* Label) const
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((arnThermoPacketItem *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return 0;
    return ((arnThermoPacketItem *)ChannelList->at(i))->minValue();
}


// bool arnThermoPacketVisualizer::eventFilter(QObject* watched, QEvent* e)
// {
//     if (e->type() == QEvent::MouseButtonDblClick) {
//         int i;
//         for ( i = 0; i < int(ChannelList->count()); ++i ) {
//             ((arnThermoPacketItem *)ChannelList->at(i))->show();
//             }
//         return true;
//         }
//     return QFrame::eventFilter(watched, e);
// }

//void arnThermoPacketVisualizer::mousePressEvent(QMouseEvent *e)
//{
//    if (e->button() == Qt::LeftButton) {
//        arnDebug("arnThermoPacketVisualizer::mousePressEvent\n");
//        }
//    else QFrame::mousePressEvent(e);
//}
//

void arnThermoPacketVisualizer::mouseDoubleClickEvent(QMouseEvent */*e*/)
{
/*    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        showChannel(i);
        }*/
    // QFrame::mouseDoubleClickEvent(e);
}
