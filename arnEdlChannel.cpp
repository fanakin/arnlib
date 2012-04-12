/***************************************************************************
                          arnEdlChannel.h  -  description
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
#include "arnEdlChannel.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlChannel -------------------
// ***************************************************
// ---------------------------------------------------
arnEdlChannel::arnEdlChannel (QString nm, int vport )
{
	name = nm;
	viewport = vport;
	this->init();
}

arnEdlChannel::~arnEdlChannel(void)
{
//arnDebug("%s\n","~arnEdlChannel");
	QList<arnEdlFrame_t*>::iterator i;
	for (i = frames->begin(); i != frames->end(); ++i) {
		if (*i) delete (*i);
		}
	if (frames) {delete frames; frames = 0;}
}

void arnEdlChannel::init(void)
{
	color = QColor("blue");
	samplingtime = 1000;
	floor = 0 ; // not yet used
	ceil = 0; // not yet used
	min = 0; // not yet used
	max = 0; // not yet used
#ifdef HAVE_IDPS
	linetype = LINESTYLE_SOLID;
#else
	linetype = 0;
#endif
	frames = new QList<arnEdlFrame_t*>;
	if (!frames) arnCriticalExit();
	frames->clear();
	//frames->setAutoDelete(true);
	dataID = 0;
	shown = false;
	open = false;
}

bool arnEdlChannel::addFrame(void)
{
	arnEdlFrame_t *tmp;
	tmp = new arnEdlFrame_t;
	if (!tmp) arnCriticalExit();
	frames->append(tmp);
	return true;
}
