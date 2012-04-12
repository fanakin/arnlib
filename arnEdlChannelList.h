/***************************************************************************
                          arnEdlChannelList.h  -  description
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

#ifndef ArnEdlChannelListH
#define ArnEdlChannelListH

#include <QList>
#include "arnEdlChannel.h"

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlChannelList -------------------
// ***************************************************
// ---------------------------------------------------
class arnEdlChannelList
{
	private:
		/*!
		* \brief Inizialization  function
		*
		* It will be called in every constructor; so it implement the common part of the construction process
		*/
		void init(void);
	protected:
		QList<arnEdlChannel *> *ChannelList;
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
		*
		* It build a datalogger channel data container
		*/
		arnEdlChannelList (void);
		
		/*!
		* \brief Basic constructor
		*
		* @param nm is the name of the channel.
		* @param vport is the selected viewport for drawing the channel on idps server.
		* 
		* It build a datalogger channel data container
		*/
		//arnEdlChannelList (unsigned int num);
		
		/*!
		* \brief Basic destructor
		*
		* It destoryes a datalogger channel data container
		*/
		~arnEdlChannelList(void);

		 inline unsigned int count(void) {return ChannelList->count();}
		 
		 bool addChannel(const char* Label);

		 bool deleteChannel(const char* Label);

		 arnEdlChannel* channel(const char* Label);

		 inline arnEdlChannel* channel(unsigned int indx) {
		 	if (indx < (unsigned int)ChannelList->count()) {
				return ((arnEdlChannel *)ChannelList->at(indx));
				}
			return 0;
			}
};

#endif
