/***************************************************************************
						  arnSimplePacketVisualizer.h  -  description
                             -------------------
	begin                : ven lug 2 2010
	copyright            : (C) 2003 - 2010 by Aurion s.r.l.
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

#ifndef ArnSimplePackectVisualizerH
#define ArnSimplePackectVisualizerH

#include <qframe.h>
#include <qptrlist.h>
#include <qlayout.h>

#include "arnSimplePacketItem.h"


class arnSimplePacketVisualizer : public QFrame {

    Q_OBJECT

    private:
    protected:
		QPtrList<arnSimplePacketItem> *ChannelList;
        QHBoxLayout *pHLayout;
        QVBoxLayout *pVLayout1,*pVLayout2;

//        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseDoubleClickEvent(QMouseEvent *e);

    public:

        /*! \brief constructor in QT style \n
        *
        */
        arnPacketVisualizer(QWidget *parent = 0, const char* name = 0, WFlags f = 0);

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
        virtual bool eventFilter(QObject* watched, QEvent* e);
        
        /*! \brief get the channel item number in the group\n
        *
        * @return the number of the channels in the group
        *
        * Ex:\n
        * ...\n
        *
        */
        inline unsigned int count(void) {return ChannelList->count();}

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
        bool addChannel(const char* Label);

        /*! \brief delete a channel from the visualizer\n
        *
        * @param Label is name of the channel\n
        * @return true if deleting has been successfull, false otherwise\n
        *
        * Ex:\n
        * ...\n
        */
        bool deleteChannel(const char* Label);

    public slots:
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
        inline void setChannelValue (int index, unsigned char val) {
                        if (index < int(ChannelList->count())) {
                            ((arnPacketItem *)ChannelList->at(index))->setValue(val);
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
        inline void setChannelValue (int index, unsigned short val) {
                        if (index < int(ChannelList->count())) {
                            ((arnPacketItem *)ChannelList->at(index))->setValue(val);
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
        inline void setChannelValue (int index, unsigned long val) {
                        if (index < int(ChannelList->count())) {
                            ((arnPacketItem *)ChannelList->at(index))->setValue((double)val);
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
        inline void setChannelValue (int index, signed char val) {
                        if (index < int(ChannelList->count())) {
                            ((arnPacketItem *)ChannelList->at(index))->setValue(val);
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
        inline void setChannelValue (int index, signed short val) {
                        if (index < int(ChannelList->count())) {
                            ((arnPacketItem *)ChannelList->at(index))->setValue(val);
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
        inline void setChannelValue (int index, signed long val) {
                        if (index < int(ChannelList->count())) {
                            ((arnPacketItem *)ChannelList->at(index))->setValue((double)val);
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
                            QString str;
                            ((arnPacketItem *)ChannelList->at(index))->lcdValue()->setSmallDecimalPoint(true);
                            str.setNum(val,fmt,prec);
                            ((arnPacketItem *)ChannelList->at(index))->setValue(str);
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
        inline void setChannelValue (int index, double val,int prec = 1,char fmt = 'f') {
                        if (index < int(ChannelList->count())) {
                            QString str;
                            ((arnPacketItem *)ChannelList->at(index))->lcdValue()->setSmallDecimalPoint(true);
                            str.setNum(val,fmt,prec);
                            ((arnPacketItem *)ChannelList->at(index))->setValue(str);
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
        void setChannelValue (const char* Label, unsigned char val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, signed char val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, unsigned short val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, signed short val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, unsigned long val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        void setChannelValue (const char* Label, signed long val);

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

        /*! \brief update all the widget children of his\n
        *
        * It updates all the children widget using their update member.
        *
        * Ex:\n
        * ...\n
        */
        void update(void);
        
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
        void showChannel(int index);
        
        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        void hideChannel(int index);

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        void showChannel (const char* Label);

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        void hideChannel (const char* Label);

        /*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
        bool  isChannelVisible(int index);

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        bool isChannelVisible (const char* Label);

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
