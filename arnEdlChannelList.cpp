/***************************************************************************
                          arnEdlChannelList.cpp  -  description
                             -------------------
    begin                : gio gnu 16 2005
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

#include "CommonFunctions.h"
#include "arnEdlChannelList.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlChannelList -------------------
// ***************************************************
// ---------------------------------------------------

arnEdlChannelList::arnEdlChannelList (void)
{
	this->init();
}

// arnEdlChannelList::arnEdlChannelList (unsigned int nm )
// {
// 	this->init();
// }

arnEdlChannelList::~arnEdlChannelList(void)
{
//arnDebug("%s\n","~arnEdlChannelList");
	if (ChannelList) {delete ChannelList; ChannelList = 0;}
}

void arnEdlChannelList::init(void)
{
	ChannelList = new QList<arnEdlChannel *>;
	if (!ChannelList) arnCriticalExit();
	ChannelList->clear();
//	ChannelList->setAutoDelete(true);
}

bool arnEdlChannelList::addChannel(const char* Label)
{
	arnEdlChannel* tmp = new arnEdlChannel(Label);
	if (!tmp) arnCriticalExit();
	ChannelList->append(tmp);
	return true;
}

bool arnEdlChannelList::deleteChannel(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnEdlChannel *)ChannelList->at(i))->Name().latin1(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return false;
	
	arnEdlChannel *ptr = ChannelList->at(i);
	if (!ptr) return false;
	ChannelList->removeAt(i);
	delete ptr;
//	if (!(ChannelList->remove(i))) return false;
	return true;
}

arnEdlChannel* arnEdlChannelList::channel(const char* Label)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(ChannelList->count()); ++i ) {
		if (!strcmp(((arnEdlChannel*)ChannelList->at(i))->Name().latin1(),Label)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return 0;
	return ((arnEdlChannel *)ChannelList->at(i));
}
