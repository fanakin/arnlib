/***************************************************************************
                          arnGenericLogger.h  -  description
                             -------------------
    begin                : lun apr 7 2003
    copyright            : (C) 2003 by fabio giovagnini
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
/* *********************************************************************** */
/*! \file arnGenericLogger.h.
    \brief Header file for of a generic logger system.

 We define a generic logger system for storing data in logger files in text format\n
 for freeze some values in a particular condition. In partim\n
 this abstract class.\n

*/
/* *********************************************************************** */

#ifndef ArnGenericLoggerH
#define ArnGenericLoggerH

#include <qstring.h>
#include <QList>
#include <sys/param.h>
#include <stdio.h>

class arnGenericLogger {
	protected:
        char fname[MAXPATHLEN];
        FILE* fd;
        struct ChannelItem {
            QString Name;
            QString Value;
            ChannelItem(void) {Name = ""; Value = "";}
            ~ChannelItem(void) {;}
            };
        QList<struct ChannelItem *> *ChannelList;
	public:
		/*! \brief generic constructor
		*
		*/
		arnGenericLogger(void);

		/*! \brief set the file name for data storing
		*
		*/
		arnGenericLogger(char* filename);
        
		/*! \brief Generic destructor
		*
		*/
		virtual ~arnGenericLogger(void);

        /*! \brief set the file name for data storing
        *
        * @param filename is the name of the file\n
        *
        * This function does the direct setting of the datalogger file name\n
        * that has to be not longer than MAXPATHLEN as defined in <sys/params.h>.\n
        * If the internal filename is already set, this function overload the name\n
        * and close the file descriptor.
        *
        * Ex:\n
        * ...\n
        */
        inline void setFilename (char* filename) {
            if (fd) {fclose(fd); fd = 0;}
            if (!filename) return;
            strcpy(fname,filename);
            }

        /*! \brief init the format of the datalogger.
        *
        *
        * This function checks if the filename is set. If yes open the file\n
        * and write in the file the format we prefer. This function is virtual\n
        * for allowing the deriving of other datalogger classes where we can change\n
        * only the init function to change the format. It assumes all the channels name\n
        * we like to store are set.
        *
        * Ex:\n
        * ...\n
        */
        virtual bool init (void);

        /*! \brief get the channel item number in the group\n
        *
        * @return the number of the channels in the group
        *
        * Ex:\n
        * ...\n
        *
        */
        inline unsigned int count(void) {return ChannelList->count();}

        /*! \brief add a channel to the logger\n
        *
        * @param Label is name of the channel\n
        * @return true if adding has been successfull, false otherwise\n
        *
        * Adding a label means to add a channelItem structure for adding\n
        * a channel to store in the logged file. In this way we\n
        * set the name but we have to set the value which will\n
        * be store when the store event happens
        * Ex:\n
        * ...\n
        */
        bool addChannel(const char* Label);

        /*! \brief delete a channel from the logger\n
        *
        * @param Label is name of the channel\n
        * @return true if deleting has been successfull, false otherwise\n
        *
        * Ex:\n
        * ...\n
        */
        bool deleteChannel(const char* Label);

        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline void setChannelValue (int index, char* val) {
                        if (index < int(ChannelList->count())) {
                            ((struct ChannelItem *)ChannelList->at(index))->Value = val;
                            }
                        }
        
        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline void setChannelValue (int index, int val) {
                        if (index < int(ChannelList->count())) {
                            QString vvl;
                            vvl.setNum(val);
                            ((struct ChannelItem *)ChannelList->at(index))->Value = vvl;
                            }
                        }

        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline void setChannelValue (int index, float val,int prec = 1,char fmt = 'f') {
                        if (index < int(ChannelList->count())) {
                            QString vvl;
                            vvl.setNum(val,fmt,prec);
                            ((struct ChannelItem *)ChannelList->at(index))->Value = vvl;
                            }
                        }

        /*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the index channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline void setChannelValue (int index, double val,int prec = 1,char fmt = 'f') {
                        if (index < int(ChannelList->count())) {
                            QString vvl;
                            vvl.setNum(val,fmt,prec);
                            ((struct ChannelItem *)ChannelList->at(index))->Value = vvl;
                            }
                        }

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, char* val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, int val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, float val,int prec = 1,char fmt = 'f');

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, double val,int prec = 1,char fmt = 'f');

        /*! \brief log the value in the opened file\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        virtual void logg (void);
};
#endif
