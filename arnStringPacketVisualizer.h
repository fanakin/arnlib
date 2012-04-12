/***************************************************************************
                          arnStringPacketVisualizer.h  -  description
                             -------------------
    begin                : gio apr 21 2005
    copyright            : (C) 2005 by fabio giovagnini
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

#ifndef ArnStringPackectVisualizerH
#define ArnStringPackectVisualizerH

#include <qframe.h>
#include <QList>
#include <qlayout.h>
#include <qlcdnumber.h>

#include "arnlibtypes.h"
#include "arnStringPacketItem.h"


class arnStringPacketVisualizer : public QFrame {

    Q_OBJECT

    private:
    protected:
        QList<arnStringPacketItem *> *ChannelList;
        QHBoxLayout *pHLayout;
        QVBoxLayout *pVLayout1,*pVLayout2;

		QString popupText_Nascondi;
		QString popupTip_Nascondi;
//        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseDoubleClickEvent(QMouseEvent *e);

    public:

        /*! \brief constructor in QT style \n
        *
        */
        arnStringPacketVisualizer(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnStringPacketVisualizer(void);

       
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

        /*! \brief set the visualizer popup text for the items\n
        *
        * @param miIndx is the menu item index to set the text where\n
        * @param txt is the text will be displayed into the popup menu item\n
        *
        * Ex:\n
        * ...\n
        */
        void setPopupText(arnMultiLangItemType_t miIndx,QString txt);
    
        /*! \brief set the visualizer popup text for the items\n
        *
        * @param miIndx is the menu item index to set the tip where\n
        * @param txt is the tip will be displayed into the popup menu item\n
        *
        * Ex:\n
        * ...\n
        */
        void setPopupTip(arnMultiLangItemType_t miIndx,QString txt);
	
        /*! \brief gets the visualizer popup text of the items\n
        *
        * @param miIndx is the menu item index to get the text from\n
        * @return text returned\n
        *
        * Ex:\n
        * ...\n
        */
        QString popupText(arnMultiLangItemType_t miIndx);
    
        /*! \brief set the visualizer popup text for the items\n
        *
        * @param miIndx is the menu item index to get the tip from\n
        * @return tip returned\n
        *
        * Ex:\n
        * ...\n
        */
        QString popupTip(arnMultiLangItemType_t miIndx);
    
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
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue(val);
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
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue(val);
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
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue((double)val);
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
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue(val);
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
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue(val);
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
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue((double)val);
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
                            str.setNum(val,fmt,prec);
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue(str);
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
        inline void setChannelValue (int index, const char* val) {
                       if (index < int(ChannelList->count()))
						   ((arnStringPacketItem *)ChannelList->at(index))->setValue((char*)val);
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
                            QString str;
                            str.setNum(val,fmt,prec);
                            ((arnStringPacketItem *)ChannelList->at(index))->setValue(str);
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
        void setChannelValue (const char* Label, const char* val);

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

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        inline void setChannelValueFontSize (int index, int size)  {
                        if (index < int(ChannelList->count())) {
                            ((arnStringPacketItem *)ChannelList->at(index))->setValueFontSize(size);
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
        void setChannelValueFontSize (const char* Label, int size);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
        inline void setChannelValueFontColor (int index, QColor color)  {
                        if (index < int(ChannelList->count())) {
                            ((arnStringPacketItem *)ChannelList->at(index))->setValueFontColor(color);
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
        void setChannelValueFontColor (const char* Label, QColor color);

        /*! \brief set the popup item name and text\n
        *
        * @param index is the index of the slider into the list.
        * @param miIndx is the index of the menu item in the popup menu.
        * @param name is the text shown into the popup menu.
        *
        * Ex:\n
        * ...\n
        */
        void setPopupMenuItemName(int index,arnMultiLangItemType_t miIndx,QString name);
    
        /*! \brief set the popup item name and text\n
        *
        * @param Label is the name of the slider into the list.
        * @param miIndx is the index of the menu item in the popup menu.
        * @param name is the text shown into the popup menu.
        *
        * Ex:\n
        * ...\n
        */
        void setPopupMenuItemName(const char* Label,arnMultiLangItemType_t miIndx,QString name);
	
		/*! \brief set the popup item tip\n
        *
        * @param index is the index of the slider into the list.
        * @param miIndx is the index of the menu item in the popup menu.
        * @param name is the text shown into the popup menu.
        *
        * Ex:\n
        * ...\n
        */
        void setPopupMenuItemTip(int index,arnMultiLangItemType_t miIndx,QString tip);
    
        /*! \brief set the popup item tip\n
        *
        * @param Label is the name of the slider into the list.
        * @param miIndx is the index of the menu item in the popup menu.
        * @param name is the text shown into the popup menu.
        *
        * Ex:\n
        * ...\n
        */
        void setPopupMenuItemTip(const char* Label,arnMultiLangItemType_t miIndx,QString tip);
		
		/*! \brief hide the popup item\n
        *
        * @param index is the index of the slider into the list.
        * @param miIndx is the index of the menu item in the popup menu.
        * @param en if en is true the popup menu item is visible, otherwise false
        *
        * Ex:\n
        * ...\n
        */
        void setVisiblePopupMenuItem(int index,arnMultiLangItemType_t miIndx,bool en);
    
        /*! \brief set the popup item tip\n
        *
        * @param Label is the name of the slider into the list.
        * @param miIndx is the index of the menu item in the popup menu.
        * @param en if en is true the popup menu item is visible, otherwise false
        *
        * Ex:\n
        * ...\n
        */
        void setVisiblePopupMenuItem(const char* Label,arnMultiLangItemType_t miIndx,bool en);
};

#endif
