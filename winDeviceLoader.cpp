/***************************************************************************
                          arnDeviceLoader.cpp  -  description
                             -------------------
    begin                : gio giu 3 2004
    copyright            : (C) 2004 by fgiovagnini
    email                : fgiovagnini@obione
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "winDeviceLoader.h"
#include <malloc.h>

arnDeviceLoader::arnDeviceLoader(const char* devName)
:	lib(0),
	error (0)
{
	lib = new QLibrary (devName);

	if (!lib->load()) {
		setError ("Error while loading Library", GetLastError());
	}
}
arnDeviceLoader::~arnDeviceLoader()
{
	if (error) free (error);

	lib->unload();
	delete lib;
}

arnSOKPDevice* arnDeviceLoader::loadKPDevice(QWidget *parent, const char* name)
{
	error = 0;
	KPconstructor =  (arnSOKPDevice *(*)(QWidget *parent, const char* name))lib->resolve("CreateKPDevice");
	if (0 == KPconstructor) {
		setError("Error while binding CreateKPDevice", GetLastError());
		return 0;
	}
	return ((*KPconstructor)(parent,name));
}

arnSOKCDevice* arnDeviceLoader::loadKCDevice(QWidget *parent, const char* name)
{
	error = 0;
	KCconstructor =  (arnSOKCDevice *(*)(QWidget *parent, const char* name))lib->resolve( "CreateKCDevice");
	if (0 == KCconstructor) {
		setError("Error while binding CreateKCDevice", GetLastError());
		return 0;
		}
	return ((*KCconstructor)(parent,name));
}

arnSOKLDevice* arnDeviceLoader::loadKLDevice(QWidget *parent, const char* name)
{
	error = 0;
	KLconstructor =  (arnSOKLDevice *(*)(QWidget *parent, const char* name))lib->resolve( "CreateKLDevice");
	if (0 == KLconstructor) {
		setError("Error while binding CreateKLDevice", GetLastError());
		return 0;
		}
	return ((*KLconstructor)(parent,name));
}

arnSOCfg* arnDeviceLoader::loadCfg(QWidget *parent, const char* name)
{
	error = 0;
	Cfgconstructor =  (arnSOCfg *(*)(QWidget *parent, const char* name))lib->resolve( "CreateCfg");
	if (0 == Cfgconstructor) {
		setError("Error while binding CreateCfg", GetLastError());
		return 0;
		}
	return ((*Cfgconstructor)(parent,name));
}

void arnDeviceLoader::unloadKPDevice(arnSOKPDevice* dev)
{
	if (dev) {delete dev; dev = 0;}
}

void arnDeviceLoader::unloadKCDevice(arnSOKCDevice* dev)
{
	if (dev) {delete dev; dev = 0;}
}

void arnDeviceLoader::unloadKLDevice(arnSOKLDevice* dev)
{
	if (dev) {delete dev; dev = 0;}
}

void arnDeviceLoader::unloadCfg(arnSOCfg* dev)
{
	if (dev) {delete dev; dev = 0;}
}

const char* arnDeviceLoader::getError(void)
{
	if (error) return error;
	return 0;
}

void arnDeviceLoader::setError (char *msg, DWORD e)
{
	LPTSTR buffer;
	if (error) free(error);

	error = (char *)malloc(256);

	FormatMessage (FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, 
		NULL, e, 
		MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), // Default language
		(LPTSTR) &buffer, 0, NULL);

	char my[256];
	wcstombs (my, buffer, 256);

	snprintf (error, 256, "%s (%d): %s", msg, e, my);
	LocalFree (buffer);
}
