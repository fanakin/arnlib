/***************************************************************************
                          arnGraphVisualizer.cpp  -  description
                             -------------------
    begin                : mar giu 14 2005
    copyright            : (C) 2005 by Aurion s.r.l.
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

#include <qmessagebox.h>
#include "CommonFunctions.h"

#ifdef HAVE_IDPS
#include "libidps.h"
#endif

#include "arnGraphVisualizer.h"

arnGraphVisualizer::arnGraphVisualizer(QObject * parent, const char * name)
	: QObject(parent, name)
{
	hostname = 0;
	status = 0;
	samplingTime = 10000;
	// creao una lista vuota di canale; le funzioni di add e delete la monupoleranno
	ChannelList = new QList<arnGraphDataStream *>;
	if (!ChannelList) arnCriticalExit();
	//ChannelList->setAutoDelete(true);
	ChannelList->clear();
	// Creo la connessione
#ifdef HAVE_IDPS
	status = idpsConnect(hostname, 0);
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
	// Faccio una specie di ping alla stessa
	status = idpsCheck();
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
	// proteggo il server da eventuali interrupt e signals
	status = idpsSigEnable(0);
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
#else
	status = 0;
#endif
}

arnGraphVisualizer::~arnGraphVisualizer(void)
{
#ifdef HAVE_IDPS
	status = idpsClose();
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
#else
	status = 0;
#endif
}


const char* arnGraphVisualizer::emessage(int code)
{
#ifdef HAVE_IDPS
	static char text[128];
	idpsMessage(code, text, sizeof(text));
#else
	static char text[128] = "Unspecified Error.";
#endif
	return text;
}

void arnGraphVisualizer::Show(void)
{
	if (!CheckChannelList()) {
		QMessageBox::critical( 0, "arnGraphVisualizer Error...",
			"Mismatched channel list for one viewport drawing.",
			QMessageBox::Ok,
			QMessageBox::NoButton,
			QMessageBox::NoButton);
		return;
		}
#ifdef HAVE_IDPS
	status = idpsSetCaption("Realtime Stream");
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
	status = idpsErase();
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
	status = idpsNewViewPort("RTPacket Channels","time (s)","data");
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
	status = idpsGetLastPort(&viewPortID);
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		} 
#else
	status = 0;
#endif
}

void arnGraphVisualizer::Hide(void)
{
#ifdef HAVE_IDPS
	status = idpsErase();
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		} 
#else
	status = 0;
#endif
}

void arnGraphVisualizer::Update(void)
{
	float *xBff;
	float *yBff;
	static float fTime = 0;
	float fval;
	int i;
	if (int(ChannelList->count()) == 0) {
		arnDebug("%s\n", "Channel list empty.");
		return;
		}
	for (i = 0; i < int(ChannelList->count()); i++) {
		arnGraphDataStream *channel = ((arnGraphDataStream *)ChannelList->at(i));
		if (!channel) arnCriticalExit();
		if ((int(channel->count()) < visibleWinSize)) {
			//arnDebug("%s\n", "Queue not et full.");
			return;
			}
		}
#ifdef HAVE_IDPS
	// Tutte le code sono piene
	// cancello la viewport
	status = idpsClear(viewPortID);
	if( status ) {
		arnDebug("%s\n", emessage(status));
		for (i = 0; i < int(ChannelList->count()); i++) {
			arnGraphDataStream *channel = ((arnGraphDataStream *)ChannelList->at(i));
			if (!channel) arnCriticalExit();
			channel->clear();
			}
		return;
		}
#else
	status = 0;
#endif
	xBff = new float[visibleWinSize + 4];
	yBff = new float[visibleWinSize + 4];
	if (!xBff || !yBff) arnCriticalExit();
	for (i = 0; i < visibleWinSize; i++) {
		xBff[i] = fTime + (float(i) * (samplingTime / 1000000.0));
		//arnDebug("xBff[%d] = %f\n",i,xBff[i]);
		}
	fTime += float(i) * (samplingTime / 1000000.0);
#ifdef HAVE_IDPS
	status = idpsAutoUpdate(0);
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
#endif
	for (i = 0; i < int(ChannelList->count()); i++) {
		arnGraphDataStream *channel = ((arnGraphDataStream *)ChannelList->at(i));
		if (!channel) arnCriticalExit();
		int j = 0;
		while (channel->deQueue(&fval)) {
			yBff[j++] = fval;
			//arnDebug("yBff[%d] = %f\n",j - 1,fval);
			}
#ifdef HAVE_IDPS
		status = idpsDefPlotColor(channel->Color().red(),channel->Color().green(),channel->Color().blue());
		if( status ) {
			arnDebug("%s\n", emessage(status));
			arnCriticalExit();
			}
		status = idpsPolyLine(viewPortID, visibleWinSize, xBff,  yBff);
		if( status ) {
			arnDebug("%s\n", emessage(status));
			arnCriticalExit();
			}
#endif
		}
#ifdef HAVE_IDPS
	status = idpsAutoUpdate(1);
	if( status ) {
		arnDebug("%s\n", emessage(status));
		arnCriticalExit();
		}
#endif
	delete [] xBff; xBff = 0;
	delete [] yBff; yBff = 0;
}

bool arnGraphVisualizer::addChannel(const char* Label)
{
	arnGraphDataStream *elem;
	elem = new arnGraphDataStream(this,Label);
	if (!elem) return false;
	elem->setName(Label);
	ChannelList->append(elem);
	return true;
}

bool arnGraphVisualizer::deleteChannel(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnGraphDataStream *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return false;
	
	arnGraphDataStream *ptr = ChannelList->at(i) ;
	if (ptr == 0) return false;
	ChannelList->removeAt(i);
	delete ptr;
	//if (!(ChannelList->remove(i))) return false;
	
	return true;
}

arnGraphDataStream* arnGraphVisualizer::Channel(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnGraphDataStream *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return 0;
	return ((arnGraphDataStream *)ChannelList->at(i));
}

bool arnGraphVisualizer::PushValue(const char* Label, float val)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnGraphDataStream *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return false;
	((arnGraphDataStream*)ChannelList->at(i))->enQueue(val);
	return true;
}

bool arnGraphVisualizer::PushSegment(const char* Label, float *bff, unsigned int len)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnGraphDataStream *)ChannelList->at(i))->name(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return false;
	unsigned int j;
	for (j = 0; j < len; j++) {
		((arnGraphDataStream*)ChannelList->at(i))->enQueue(bff[j]);
		}
	return true;
}

bool arnGraphVisualizer::PushValue(int indx, float val)
{
	if (indx < int(ChannelList->count())) {
		((arnGraphDataStream*)ChannelList->at(indx))->enQueue(val);
		return true;
		}
	return false;
}

bool arnGraphVisualizer::PushSegment(int indx, float *bff, unsigned int len)
{
	if (indx < int(ChannelList->count())) {
		unsigned int j;
		for (j = 0; j < len; j++) {
			((arnGraphDataStream*)ChannelList->at(indx))->enQueue(bff[j]);
			}
		return true;
		}
	return false;
}

bool arnGraphVisualizer::CheckChannelList(void)
{
	int i;
	int tb;
	int vWS;
	arnGraphDataStream *channel;
	if (int(ChannelList->count()) == 0) {
		arnDebug("Empty Channel List.\n");
		return false;
		}
	channel = ((arnGraphDataStream *)ChannelList->at(0));
	tb = channel->Timebase();
	vWS = channel->VisibleWinSize();
	if (!tb || !vWS) {
		arnDebug("Zero value for Timebase or VisibleWinSize on channel(0).\n");
		return false;
		}
	for ( i = 1; i < int(ChannelList->count()); ++i ) {
		channel = ((arnGraphDataStream *)ChannelList->at(i));
		if (tb != channel->Timebase()) {
			arnDebug("Timebase incoherent for channel %d.\n",i);
			return false;
			}
		if (vWS != channel->VisibleWinSize()) {
			arnDebug("VisibleWinSize incoherent for channel %d.\n",i);
			return false;
			}
		}
	// caricamento grandezze utili in update
	samplingTime = tb;
	visibleWinSize = vWS;
	//arnDebug("tb,%d;vWS,%d\n",samplingTime,visibleWinSize);
	return true;
}
