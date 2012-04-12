/***************************************************************************
                          arnNumEnPacketVisualizer.h  -  description
                             -------------------
    begin                : mar apr 19 2005
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

#ifndef ArnNumEnPackectVisualizerH
#define ArnNumEnPackectVisualizerH

#include <qframe.h>
#include <QList>
#include <qlayout.h>
#include <qlcdnumber.h>

#include "arnlibtypes.h"
#include "arnPacketVisualizer.h"
#include "arnNumEnPacketItem.h"


class arnNumEnPacketVisualizer : public arnPacketVisualizer {

    Q_OBJECT

    private:
    protected:
        QList<arnNumEnPacketItem *> *ChannelList;

		QString popupText_Nascondi;
		QString popupTip_Nascondi;
		QString popupText_Allarmi;
		QString popupTip_Allarmi;
//        virtual void mousePressEvent(QMouseEvent *e);
        virtual void mouseDoubleClickEvent(QMouseEvent *e);
    public:

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnPacketVisualizer(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnNumEnPacketVisualizer(void);

        /*! \brief get the channel item number in the group\n
        *
        * @return the number of the channels in the group
        *
        * Ex:\n
        * ...\n
        *
        */
		virtual inline unsigned int count(void) {return ChannelList->count();}

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
		virtual bool addChannel(const char* Label);

        /*! \brief delete a channel from the visualizer\n
        *
        * @param Label is name of the channel\n
        * @return true if deleting has been successfull, false otherwise\n
        *
        * Ex:\n
        * ...\n
        */
		virtual bool deleteChannel(const char* Label);

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
		virtual inline void setChannelValue (int index, unsigned char val) {
                        if (index < int(ChannelList->count())) {
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(val);
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
		virtual inline void setChannelValue (int index, unsigned short val) {
                        if (index < int(ChannelList->count())) {
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(val);
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
		virtual inline void setChannelValue (int index, unsigned long val) {
                        if (index < int(ChannelList->count())) {
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue((double)val);
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
		virtual inline void setChannelValue (int index, signed char val) {
                        if (index < int(ChannelList->count())) {
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(val);
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
		virtual inline void setChannelValue (int index, signed short val) {
                        if (index < int(ChannelList->count())) {
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(val);
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
		virtual inline void setChannelValue (int index, signed long val) {
                        if (index < int(ChannelList->count())) {
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue((double)val);
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
		virtual inline void setChannelValue (int index, float val,int prec = 1,char fmt = 'f') {
                        if (index < int(ChannelList->count())) {
                            QString str;
                            ((arnNumEnPacketItem *)ChannelList->at(index))->lcdValue()->setSmallDecimalPoint(true);
                            str.setNum(val,fmt,prec);
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(str);
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
        //                    ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(val);
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
		virtual inline void setChannelValue (int index, double val,int prec = 1,char fmt = 'f') {
                        if (index < int(ChannelList->count())) {
                            QString str;
                            ((arnNumEnPacketItem *)ChannelList->at(index))->lcdValue()->setSmallDecimalPoint(true);
                            str.setNum(val,fmt,prec);
                            ((arnNumEnPacketItem *)ChannelList->at(index))->setValue(str);
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
		virtual void setChannelValue (const char* Label, unsigned char val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, signed char val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, unsigned short val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, signed short val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, unsigned long val);

        /*! \brief overloaded function : set the value for the channel Label\n
        *
        * @param Label is name of the channel\n
        * @param val is the value to set\n
        *
        * Ex:\n
        * ...\n
        */
		virtual void setChannelValue (const char* Label, signed long val);

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
		virtual void update(void);
        
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
		
		/*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		inline QLCDNumber* lcdValue (int index) {return ((index < int(ChannelList->count())) ?                              ((arnNumEnPacketItem *)ChannelList->at(index))->lcdValue() : 0);}

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		QLCDNumber* lcdValue (const char* Label);

		/*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		inline void setAlarmEnabled(int index, bool v) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setAlarmEnabled(v);
				}
			}

		/*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		inline bool isAlarmEnabled (int index) {return ((index < int(ChannelList->count())) ?  ((arnNumEnPacketItem *)ChannelList->at(index))->isAlarmEnabled() : false);}

		/*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		void setAlarmEnabled(const char* Label, bool v);
        
		/*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
		bool isAlarmEnabled (const char* Label);
		
        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        inline void setUpperTh(int index, const QString& val) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setUpperTh(val);
				}
			}

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        void setUpperTh(const char* Label, const QString& val);
        
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
        inline void setUpperTh(int index, int val) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setUpperTh(val);
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
        void setUpperTh(const char* Label, int val);
        
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
        inline void setUpperTh(int index, double val) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setUpperTh(val);
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
        void setUpperTh(const char* Label, double val);
        
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
        inline void setLowerTh(int index, const QString& val) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setLowerTh(val);
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
        void setLowerTh(const char* Label, const QString& val);

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
        inline void setLowerTh(int index, int val) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setLowerTh(val);
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
        void setLowerTh(const char* Label, int val);
        
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
        inline void setLowerTh(int index, double val) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setLowerTh(val);
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
        void setLowerTh(const char* Label, double val);

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
        inline double UpperTh(int index) {
			if (index < int(ChannelList->count())) {
				return ((arnNumEnPacketItem *)ChannelList->at(index))->UpperTh();
				}
			return 0;
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
        double UpperTh(const char* Label);

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
        inline double LowerTh(int index) {
			if (index < int(ChannelList->count())) {
				return ((arnNumEnPacketItem *)ChannelList->at(index))->LowerTh();
				}
			return 0;
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
        double LowerTh(const char* Label);

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
        inline void checkWarning(int index) {
			if (index < int(ChannelList->count())) {
				if (((arnNumEnPacketItem *)ChannelList->at(index))->isAlarmEnabled()) {
					((arnNumEnPacketItem *)ChannelList->at(index))->checkWarning();
					}
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
        void checkWarning(const char* Label);

		/*! \brief it sreturn the name property of the selected channel\n
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
		virtual inline QString name(int index) {
			if (index < int(ChannelList->count())) {
				return ((arnNumEnPacketItem *)ChannelList->at(index))->name();
				}
			return QString("");
			}

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
		virtual QString name(const char* Label);

		/*! \brief it sets the aligment of the name property of the selected channel\n
		*
		* @param index is the index in the list of the channels\n
		* @param a is the aligment value to set\n
		*
		* This function does the direct setting of the index channel algnment\n
		* it is an optimized function to reduce the access time to the list.\n
		* See arnPacketItem documentation.
		*
		* Ex:\n
		* ...\n
		*/
		inline void alignName(int index,int a) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->alignName(a);
				}
			}

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
		void alignName(const char* Label,int a);

		/*! \brief it sets the font size of the name property of the selected channel\n
		*
		* @param index is the index in the list of the channels\n
		* @param a is the font size value to set\n
		*
		* This function does the direct setting of the index channel font size;\n
		* it is an optimized function to reduce the access time to the list.\n
		* See arnPacketItem documentation.
		*
		* Ex:\n
		* ...\n
		*/
		inline void setNameFontSize(int index,int a) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setNameFontSize(a);
				}
			}

		/*! \brief overloaded function : it sets the font size of the name property of the selected channel\n
		*
		* @param Label is the name  of the channel\n
		* @param a is the font size value to set\n
		*
		* This function does the setting of the font size property by name of the channel\n
		* iee arnPacketItem documentation.
		*
		* Ex:\n
		* ...\n
		*/
		void setNameFontSize(const char* Label,int a);

        /*! \brief enable the manual blink property\n
        *
        * @param en enable or disable \n
        *
        * This function enables the one shot manual blink property
        *
        * Ex:\n
        * ...\n
        */
        inline void EnableManualBlink(int index,bool en) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->EnableManualBlink(en);
				}
			}

        /*! \brief enable the manual blink property\n
        *
        * @param en enable or disable \n
        *
        * This function enables the one shot manual blink property
        *
        * Ex:\n
        * ...\n
        */
        void EnableManualBlink(const char* Label,bool en);

        /*! \brief it checks if the manual blink property in enabled \n
        *
        * @param blinkShot is the duration in ms of the blink \n
        *
        * This function activates the one shot blink and sets the time of the blink to blinkShot
        *
        * Ex:\
        * ... \n
        * EnableManualBlink(3,true); \n
        * setManualBlink(3,500); \n
        * ...\n
        */
        inline void setManualBlink(int index,unsigned short blinkShot) {
			if (index < int(ChannelList->count())) {
				((arnNumEnPacketItem *)ChannelList->at(index))->setManualBlink(blinkShot);
				}
			}

        /*! \brief it checks if the manual blink property in enabled \n
        *
        * @param blinkShot is the duration in ms of the blink \n
        *
        * This function activates the one shot blink and sets the time of the blink to blinkShot
        *
        * Ex:\
        * ... \n
        * EnableManualBlink("Channel",true); \n
        * setManualBlink("Channel",500); \n
        * ...\n
        */
        void setManualBlink(const char* Label,unsigned short blinkShot);

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
