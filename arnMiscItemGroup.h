/***************************************************************************
						  arnMiscItemGroup.h  -  description
                             -------------------
	begin                : mar set 28 2010
	copyright            : (C) 2003-2010 by fabio giovagnini
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

#ifndef ArnMiscItemGroupH
#define ArnMiscItemGroupH

#include <QFrame>
#include <QList>
#include <QLayout>
#include "arnlibtypes.h"
 

class arnMiscItemGroup : public QFrame {

    Q_OBJECT

    private:
    protected:

		QVBoxLayout *pVLayout;
		QList<QWidget *> *ItemList;
		QList<arnGroupItemType_t> *ItemTypeList;
		bool synchronized;

		QString popupText_Nascondi;
		QString popupTip_Nascondi;
		QString popupText_Connetti;
		QString popupTip_Connetti;
        virtual void mouseDoubleClickEvent(QMouseEvent *e);
    public:
        /*! \brief constructor in QT style \n
        *
        */
		arnMiscItemGroup(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
		~arnMiscItemGroup(void);

        /*! \brief add a slider to the group\n
        *
        * @param Label is name of the slider\n
        * @return true if adding has been successfull, false otherwise\n
        *
        * Adding a slider means to add 1 QLabel for name and 1 QSlider:\n
        * the former is\n
        * the real label, the latter is slader to introduce a change in the system\n
        *
        * Ex:\n
        * ...\n
        */
		virtual bool addItem(const char* Label,arnGroupItemType_t ty);

        /*! \brief get the slider item number in the group\n
        *
        * @return the number of the sliders in the group
        *
        * Ex:\n
        * ...\n
        *
        */
		inline unsigned int count(void) {return ItemList->count();}

        /*! \brief delete a slider from the group\n
        *
        * @param Label is name of the slider\n
        * @return true if deleting has been successfull, false otherwise\n
        *
        * Ex:\n
        * ...\n
        */
		virtual bool deleteItem(const char* Label);
        

        /*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
		double getValue(int index);
        
		/*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
		double getValue(const char* Label);

		/*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
		QString text(int index);
        
		/*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
        QString text(const char* Label);

		/*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
		inline QString getItemName(int index) {
			if (index < int(ItemList->count()))
				return ((QWidget *)ItemList->at(index))->name();
			}

        /*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
		//QString getItemName(const char* Label);

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

		/*! \brief set the numeric value of a slider from the group\n
		*
		* @param index is the index of the slider.
		* @param val is the value of the slider.
		*
		* Ex:\n
		* ...\n
		*/
		void setValue(int index,double val);

		/*! \brief set the numeric value of a slider from the group\n
		*
		* @param Label is name of the slider.
		* @param val is the value of the slider.
		*
		* Ex:\n
		* ...\n
		*/
		void setValue(const char* Label,double val);

		/*! \brief set the sychronized property in the slider group\n
        *
        * @param synch is truth value for setting  Synchronized property.
        *
        * Synchronized is a property to handle all togheter the slidersw in the group.\n
        * If you set this property you can adjust the first slider and obtaining the\n
        * same result upon the others of the gruop.
        *
        * Ex:\n
        * ...\n
        */
        void setSynchronized(bool synch);

        /*! \brief get the sychronized property in the slider group\n
        *
        * @return true if the group is synchronized, false otehrwise
        *
        * Ex:\n
        * ...\n
        */
        inline bool Synchronized(void) {return synchronized;}
        

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
        bool  isChannelVisible(int index) {
			if (index < int(ItemList->count())) {
				return ((QWidget *)ItemList->at(index))->isVisibleTo(this);
				}
			return false;
			}

        /*! \brief update all the widget children of his\n
        *
        * It hides the channel index.
        *
        * Ex:\n
        * ...\n
        */
        bool isChannelVisible (const char* Label);

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

			/*! \brief hide the popup item\n
		*
		* @param index is the index of the slider into the list.
		* @param miIndx is the index of the menu item in the popup menu.
		* @param en if en is true the popup menu item is visible, otherwise false
		*
		* Ex:\n
		* ...\n
		*/
		void setVisible(int index,bool en) {
			if (index < int(ItemList->count()))
				((QWidget *)ItemList->at(index))->setVisible(en);
			}

		/*! \brief set the popup item tip\n
		*
		* @param Label is the name of the slider into the list.
		* @param miIndx is the index of the menu item in the popup menu.
		* @param en if en is true the popup menu item is visible, otherwise false
		*
		* Ex:\n
		* ...\n
		*/
		void setVisible(const char* Label,bool en);
};
#endif
