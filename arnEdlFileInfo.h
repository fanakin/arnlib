/***************************************************************************
                          arnEdlFileInfo.h  -  description
                             -------------------
    begin                : gio giu 16 2005
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

#ifndef ArnEdlFileInfoH
#define ArnEdlFileInfoH

#include <qstring.h>

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlFileInfo -------------------
// ***************************************************
// ---------------------------------------------------
class arnEdlFileInfo
{
	private:
		/*!
		* \brief Inizialization  function
		*
		* It will be called in every constructor; so it implement the common part of the construction process
		*/
		void init(void);
	protected:
		QString copyrigth;
		QString version;
		QString devicecode; /*!< embedded device form which we build the file */
		QString creationdate; /*!< date of file building */
		QString creationtime; /*!< time of file building */
		QString lastmodifydate; /*!< date of file building */
		QString lastmodifytime; /*!< time of file building */
		QString description; /*!< description of the file and comment */
		unsigned int channelNumber; /*!< number of channels of the device */
		unsigned int systemTimer;  /*!< base time counter of the remote system; the sampling rate of the channel is a multiple */
		unsigned int baseAddressOfConfigArea;
		unsigned int sizeOfConfigArea;
		unsigned int blockSizeOfConfigArea;
		unsigned int baseAddressOfDataArea;
		unsigned int sizeOfDataArea;
		unsigned int blockSizeOfDataArea;
		unsigned int numberOfFrames;
		unsigned int numberOfPackets;
		unsigned int numberOfNotValidPackets;
		/*!
		* \brief It builds teh real comma separated value part of the data file during a downloading operation
		*
		* @param fd is the file descriptor
		* @param bff is the buffer containg the data for teh remote device
		* @param len is the length of the buffer
		* @return true, if no problem occurs during the building process and the file is properly made, false otherwise.
		* 
		* This function is called inside the buildFile funtion.
		*/
		//bool buildCSV(FILE *fd,unsigned char* bff,unsigned int len);
	public:
		/*!
		* \brief Basic constructor
		*
		* @param nm is the name of the channel.
		* @param vport is the selected viewport for drawing the channel on idps server.
		* 
		* It build a datalogger channel data container
		*/
		arnEdlFileInfo (void);
		
		/*!
		* \brief Basic destructor
		*
		* It destoryes a datalogger channel data container
		*/
		~arnEdlFileInfo(void);

		inline void setCopyrigth(QString d) {copyrigth = d;}
		
		inline QString Copyrigth(void) {return copyrigth;}
		
		inline void setVersion(QString d) {version = d;}
		
		inline QString Version(void) {return version;}
		
		inline void setDeviceCode(QString d) {devicecode = d;}
		
		inline QString DeviceCode(void) {return devicecode;}
		
		inline void setCreationDate(QString d) {creationdate = d;}
		
		inline QString CreationDate(void) {return creationdate;}
		
		inline void setCreationTime(QString d) {creationtime = d;}
		
		inline QString CreationTime(void) {return creationtime;}
		
		inline void setLastmodifyDate(QString d) {lastmodifydate = d;}
		
		inline QString LastmodifyDate(void) {return lastmodifydate;}
		
		inline void setLastmodifyTime(QString d) {lastmodifytime = d;}
		
		inline QString LastmodifyTime(void) {return lastmodifytime;}
		
		inline void setDescription(QString d) {description = d;}
		
		inline QString Description(void) {return description;}
		
		inline void setChannelNumber(unsigned int d) {channelNumber = d;}
		
		inline unsigned int ChannelNumber(void) {return channelNumber;}
		
		inline void setSystemTimer(unsigned int d) {systemTimer = d;}
		
		inline unsigned int SystemTimer(void) {return systemTimer;}
		
		inline void setBaseAddressOfConfigArea(unsigned int d) {baseAddressOfConfigArea = d;}
		
		inline unsigned int BaseAddressOfConfigArea(void) {return baseAddressOfConfigArea;}
		
		inline void setSizeOfConfigArea(unsigned int d) {sizeOfConfigArea = d;}
		
		inline unsigned int SizeOfConfigArea(void) {return sizeOfConfigArea;}
		
		inline void setBlockSizeOfConfigArea(unsigned int d) {blockSizeOfConfigArea = d;}
		
		inline unsigned int BlockSizeOfConfigArea(void) {return blockSizeOfConfigArea;}
		
		inline void setBaseAddressOfDataArea(unsigned int d) {baseAddressOfDataArea = d;}
		
		inline unsigned int BaseAddressOfDataArea(void) {return baseAddressOfDataArea;}
		
		inline void setSizeOfDataArea(unsigned int d) {sizeOfDataArea = d;}
		
		inline unsigned int SizeOfDataArea(void) {return sizeOfDataArea;}
		
		inline void setBlockSizeOfDataArea(unsigned int d) {blockSizeOfDataArea = d;}
		
		inline unsigned int BlockSizeOfDataArea(void) {return blockSizeOfDataArea;}
		
		inline void setNumberOfFrames(unsigned int d) {numberOfFrames = d;}
		
		inline unsigned int NumberOfFrames(void) {return numberOfFrames;}
		
		inline void setNumberOfPackets(unsigned int d) {numberOfPackets = d;}
		
		inline unsigned int NumberOfPackets(void) {return numberOfPackets;}
		
		inline void setNumberOfNotValidPackets(unsigned int d) {numberOfNotValidPackets = d;}
		
		inline unsigned int NumberOfNotValidPackets(void) {return numberOfNotValidPackets;}

};

#endif
