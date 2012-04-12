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

#include <dlfcn.h>
#include "arnDeviceLoader.h"

arnDeviceLoader::arnDeviceLoader(const char* devName)
{
	__handle = dlopen(devName, RTLD_LAZY);
	error = 0;
	if (0 == __handle) {
		error = dlerror();
		}
}
arnDeviceLoader::~arnDeviceLoader()
{
	int res = 0;
	if(__handle) res = dlclose(__handle);
	if (res) arnCriticalExit();
}

arnSOKPDevice* arnDeviceLoader::loadKPDevice(QWidget *parent, const char* name)
{
	error = 0;
	KPconstructor =  (arnSOKPDevice *(*)(QWidget *parent, const char* name))dlsym(__handle, "CreateKPDevice");
	if (0 == KPconstructor) {
		error = dlerror();
		return 0;
		}
	return ((*KPconstructor)(parent,name));
}

arnSOKCDevice* arnDeviceLoader::loadKCDevice(QWidget *parent, const char* name)
{
	error = 0;
	KCconstructor =  (arnSOKCDevice *(*)(QWidget *parent, const char* name))dlsym(__handle, "CreateKCDevice");
	if (0 == KCconstructor) {
		error = dlerror();
		return 0;
		}
	return ((*KCconstructor)(parent,name));
}

arnSOKLDevice* arnDeviceLoader::loadKLDevice(QWidget *parent, const char* name)
{
	error = 0;
	KLconstructor =  (arnSOKLDevice *(*)(QWidget *parent, const char* name))dlsym(__handle, "CreateKLDevice");
	if (0 == KLconstructor) {
		error = dlerror();
		return 0;
		}
	return ((*KLconstructor)(parent,name));
}

arnSOCfg* arnDeviceLoader::loadCfg(QWidget *parent, const char* name)
{
	error = 0;
	Cfgconstructor =  (arnSOCfg *(*)(QWidget *parent, const char* name))dlsym(__handle, "CreateCfg");
	if (0 == Cfgconstructor) {
		error = dlerror();
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
	if (dev) {delete dev;dev = 0;}
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
