/***************************************************************************
                          arnEdlFileInfo.cpp  -  description
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

#include "arnEdlFileInfo.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlFileInfo -------------------
// ***************************************************
// ---------------------------------------------------
arnEdlFileInfo::arnEdlFileInfo (void )
{
	this->init();
}

arnEdlFileInfo::~arnEdlFileInfo(void)
{
//arnDebug("%s\n",text(0).latin1());
}

void arnEdlFileInfo::init(void)
{
	copyrigth = "";
	version = "";
	devicecode = ""; 
	creationdate = "";
	creationtime = "";
	lastmodifydate = "";
	lastmodifytime = "";
	description = "";
	channelNumber = 0;
	systemTimer = 0;
	baseAddressOfConfigArea = 0;
	sizeOfConfigArea = 0;
	blockSizeOfConfigArea = 0;
	baseAddressOfDataArea = 0;
	sizeOfDataArea = 0;
	blockSizeOfDataArea = 0;
	numberOfFrames = 0;
	numberOfPackets = 0;
	numberOfNotValidPackets = 0;
}

