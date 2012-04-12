/***************************************************************************
                          arnPacketVisualizer.h  -  description
                             -------------------
    begin                : sab feb 22 2003
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

#ifndef ArnPackectVisualizerH
#define ArnPackectVisualizerH

#include <qframe.h>
#include <QList>
#include <qlayout.h>

#include "arnPacketItem.h"


class arnPacketVisualizer : public QFrame {

    Q_OBJECT

    private:
    protected:
        QHBoxLayout *pHLayout;
        QVBoxLayout *pVLayout1,*pVLayout2;

    public:

        /*! \brief constructor in QT style \n
        *
        */
		arnPacketVisualizer(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnPacketVisualizer(void);

        /*! \brief get the channel item number in the group\n
        *
        * @return the number of the channels in the group
        *
        * Ex:\n
        * ...\n
        *
        */
		virtual unsigned int count(void) = 0;

        /*! \brief add a channel to the visualizer\n
        *
        * @param Label is name of the channel\n
        * @return true if adding has been successfull, false otherwise\n
        *
        * Adding a label means to add 2 QLabel objects: the former is\n
        * the real label, the latter is a QLabel where to display\n
        * the channel value really. This class at laest for now\n
        * doesn't matter about scaling the value. Elsewhere some other\n
        * agents have to do the right scaling before seeting the Channel\n
        * value.
        * Ex:\n
        * ...\n
        */
		virtual bool addChannel(const char* Label) = 0;

        /*! \brief delete a channel from the visualizer\n
        *
        * @param Label is name of the channel\n
        * @return true if deleting has been successfull, false otherwise\n
        *
        * Ex:\n
        * ...\n
        */
		virtual bool deleteChannel(const char* Label) = 0;

    public slots:
		/*! \brief it return the name property of the selected channel\n
		*
		* @param index is the index in the list of the channels\n
		*
		* This function does the direct setting of the index channel algnment\n
		* it is an optimized function to reduce the access time to the list.\n
		* See arnPacketItem documentation.
		*
		* Ex:\n
		* ...\n
		*/
		virtual QString name(int index) = 0;

		/*! \brief overloaded function : it sets the aligment of the name property of the selected channel\n
		*
		* @param Label is the name  of the channel\n
		* @param a is the alignment value to set\n
		*
		* This function does the setting of the aligment property by name of the channel\n
		* iee arnPacketItem documentation.
		*
		* Ex:\n
		* ...\n
		*/
		virtual QString name(const char* Label) = 0;

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
		virtual void setChannelValue (int index, unsigned char val) = 0;

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
		virtual void setChannelValue (int index, unsigned short val) = 0;

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
		virtual void setChannelValue (int index, unsigned long val) = 0;

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
		virtual void setChannelValue (int index, signed char val) = 0;

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
		virtual void setChannelValue (int index, signed short val) = 0;

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
		virtual void setChannelValue (int index, signed long val) = 0;

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
		virtual void setChannelValue (int index, float val,int prec = 1,char fmt = 'f') = 0;

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
        //inline void setChannelValue (int index, const char* val) {
        //                if (index < int(ChannelList->count()))
        //                    ((arnPacketItem *)ChannelList->at(index))->setValue(val);
        //                }

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
		virtual void setChannelValue (int index, double val,int prec = 1,char fmt = 'f')  = 0;
                        

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, unsigned char val) = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, signed char val) = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, unsigned short val) = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, signed short val) = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, unsigned long val) = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, signed long val) = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, float val,int prec = 1,char fmt = 'f') = 0;

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, double val,int prec = 1,char fmt = 'f') = 0;

        /*! \brief update all the widget children of his\n
        *
        * It updates all the children widget using their update member.
        *
        * Ex:\n
        * ...\n
        */
		virtual void update(void) = 0;
        
        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        //void setChannelValue (const char* Label, const char* val);

        /*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
		virtual void showChannel(int index) = 0;
        
        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		virtual void hideChannel(int index) = 0;

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		virtual void showChannel (const char* Label) = 0;

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		virtual void hideChannel (const char* Label) = 0;

        /*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
		virtual  bool isChannelVisible(int index) = 0;

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		virtual bool isChannelVisible (const char* Label) = 0;

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        //virtual void show ();
};

#endif
