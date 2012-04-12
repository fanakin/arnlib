/***************************************************************************
                          arnDeviceLoader.h  -  description
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
#ifndef ArnDeviceLoaderH
#define ArnDeviceLoaderH

#include "qstring.h"
#include "arnSODevice.h"

class arnDeviceLoader {
	private:
	protected:
		void* __handle;
		arnSOKPDevice *(*KPconstructor)(QWidget *parent, const char* name);
		arnSOKCDevice *(*KCconstructor)(QWidget *parent, const char* name);
		arnSOKLDevice *(*KLconstructor)(QWidget *parent, const char* name);
		arnSOCfg *(*Cfgconstructor)(QWidget *parent, const char* name);
		char *error;
	public:
		/*! \brief constructor using device file name
		*
		* With this constructor we build the arnDeviceLoader\n
		* using the portdef description.\n
		*/
		arnDeviceLoader(const char* devName);

		/*! \brief default destructor
		*
		*/
		~arnDeviceLoader();

		/*! \brief It load the device
		*
		* @param parent widget.
		* @param widget name.
		* @return device pointer.
		*
		* It load the device from the .so file returning the pointer to the arnParVier\n
		*/
		arnSOKPDevice* loadKPDevice(QWidget *parent, const char* name);

		/*! \brief It load the device
		*
		* @param parent widget.
		* @param widget name.
		* @return device pointer.
		*
		* It load the device from the .so file returning the pointer to the ...\n
		*/
		arnSOKCDevice* loadKCDevice(QWidget *parent, const char* name);

		/*! \brief It load the device
		*
		* @param parent widget.
		* @param widget name.
		* @return device pointer.
		*
		* It load the device from the .so file returning the pointer to the ...\n
		*/
		arnSOKLDevice* loadKLDevice(QWidget *parent, const char* name);

		/*! \brief It load the device
		*
		* @param parent widget.
		* @param widget name.
		* @return device pointer.
		*
		* It load the device from the .so file returning the pointer to the ...\n
		*/
		arnSOCfg* loadCfg(QWidget *parent, const char* name);

		/*! \brief It unload teh .so device
		*
		* @param device pointer.
		*
		* It unload the device\n
		*/
		void unloadKPDevice(arnSOKPDevice* dev);
		
		/*! \brief It unload teh .so device
		*
		* @param device pointer.
		*
		* It unload the device\n
		*/
		void unloadKCDevice(arnSOKCDevice* dev);

		/*! \brief It unload teh .so device
		*
		* @param device pointer.
		*
		* It unload the device\n
		*/
		void unloadKLDevice(arnSOKLDevice* dev);
		
		/*! \brief It unload teh .so device
		*
		* @param device pointer.
		*
		* It unload the device\n
		*/
		void unloadCfg(arnSOCfg* dev);

		/*! \brief It gets the error state
		*
		* @return teh error string pointer.
		*
		* It return the error string pointer for debugging and messages\n
		*/
		const char* getError(void);
};


#endif
