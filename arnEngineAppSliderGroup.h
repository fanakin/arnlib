/***************************************************************************
                          arnEngineAppSliderGroup.h  -  description
                             -------------------
    begin                : dom apr 24 2005
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

#ifndef ArnEngineAppSliderGroupH
#define ArnEngineAppSliderGroupH

#include <qframe.h>
#include <QList>
#include <qlayout.h>
#include "arnEngineAppSliderItem.h"
// test test test
#include "CommonFunctions.h"

 

class arnEngineAppSliderGroup : public QFrame {

    Q_OBJECT

    private:
    protected:

        QVBoxLayout /*QGridLayout*/ *pVLayout;
        QList<arnEngineAppSliderItem *> *SliderList;
        bool synchronized;
		QString popupText_Nascondi;
		QString popupTip_Nascondi;
		QString popupText_Connetti;
		QString popupTip_Connetti;
		QString popupText_AbilitaCOP;
		QString popupTip_AbilitaCOP;
		QString popupText_ModificaCOP;
		QString popupTip_ModificaCOP;

        virtual void mouseDoubleClickEvent(QMouseEvent *e);
    public:
        /*! \brief constructor in QT style \n
        *
        */
        arnEngineAppSliderGroup(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnEngineAppSliderGroup(void);

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
        virtual bool addSlider(const char* Label);

        /*! \brief get the slider item number in the group\n
        *
        * @return the number of the sliders in the group
        *
        * Ex:\n
        * ...\n
        *
        */
        inline unsigned int count(void) {return SliderList->count();}

        /*! \brief delete a slider from the group\n
        *
        * @param Label is name of the slider\n
        * @return true if deleting has been successfull, false otherwise\n
        *
        * Ex:\n
        * ...\n
        */
        virtual bool deleteSlider(const char* Label);
        

        /*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
        inline double getSliderValue(int index) {
			if (index < int(SliderList->count()))
				return ((arnEngineAppSliderItem *)SliderList->at(index))->sliderValue();
			return double(0);
			}
        
		/*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
        double getSliderValue(const char* Label);

        /*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
        inline double getValue(int index) {
			if (index < int(SliderList->count()))
				return ((arnEngineAppSliderItem *)SliderList->at(index))->value();
			return double(0);
			}
        
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
        inline QString text(int index) {
			if (index < int(SliderList->count()))
				return ((arnEngineAppSliderItem *)SliderList->at(index))->text();
			return QString("");
			}
        
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
        inline QString getSliderName(int index) {
			if (index < int(SliderList->count()))
				return ((arnEngineAppSliderItem *)SliderList->at(index))->name();
			}

        /*! \brief get the numeric value of a slider from the group\n
        *
        * @param Label is name of the slider.
        * @return the value in double format.
        *
        * Ex:\n
        * ...\n
        */
        QString getSliderName(const char* Label);

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
        /*! \brief set the numeric value of a slider minimum in the group\n
        *
        * @param Label is name of the slider.
        * @param min is value of the minimum value.
        *
        * Ex:\n
        * ...\n
        */
        void setSliderMin(const char* Label, int min);
        
        /*! \brief set the numeric value of a slider maximum in the group\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value.
        *
        * Ex:\n
        * ...\n
        */
        void setSliderMax(const char* Label,  int max);

        /*! \brief set the numeric value of a slider  in the group\n
        *
        * @param Label is name of the slider.
        * @param val is the current value of the slider.
        *
        * Ex:\n
        * ...\n
        */
        void setSliderValue(const char* Label, int val);
        
        /*! \brief set the numeric value of a slider minimum in the group\n
        *
        * @param index is the index of the slider in the group
        * @param min is value of the minimum value.
        *
        * Ex:\n
        * ...\n
        */
        inline void setSliderMin(int index, int min) {
            if (index < int(SliderList->count()))
                ((arnEngineAppSliderItem *)SliderList->at(index))->setSliderMin(min);
            }

        /*! \brief set the numeric value of a slider minimum in the group\n
        *
        * @param index is the index of the slider in the group
        * @param min is value of the minimum value.
        *
        * Ex:\n
        * ...\n
        */
        inline void setSliderMax(int index, int max) {
            if (index < int(SliderList->count()))
                ((arnEngineAppSliderItem *)SliderList->at(index))->setSliderMax(max);
            }

        /*! \brief set the numeric value of a slider  in the group\n
        *
        * @param index is the index of the slider in the group.
        * @param val is the current value of the slider.
        *
        * Ex:\n
        * ...\n
        */
        void setSliderValue(int index, int val);

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
        
        /*! \brief set the size of the value if it is a number for scaling\n
        *
        * @param Label is name of the slider.
        * @param sz is the size of the value for scaling.
        *
        * if you put nff_float or nff_double or nff_string or nff_none,\n
        * the value is considered an int value.
        *
        * Ex:\n
        * ...\n
        */
        void setValueSize(const char* Label,  NumericFixedFormat_t sz, char f = 'f' ,int pr = 3);

        /*! \brief set the numeric value of a value minimum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param min is value of the minimum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        void setValueMin(const char* Label, double min);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        void setValueMax(const char* Label,  double max);

        /*! \brief set the size of the value if it is a number for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param sz is the size of the value for scaling.
        *
        * if you put nff_float or nff_double or nff_string or nff_none,\n
        * the value is considered an int value.
        *
        * Ex:\n
        * ...\n
        */
        inline void setValueSize(int index,  NumericFixedFormat_t sz, char f = 'f' ,int pr = 3) {
            if (index < int(SliderList->count()))
                ((arnEngineAppSliderItem *)SliderList->at(index))->setValueSize(sz,f,pr);
            }

        /*! \brief set the numeric value of a value minimum in the group for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param min is value of the minimum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        inline void setValueMin(int index, double min) {
            if (index < int(SliderList->count()))
                ((arnEngineAppSliderItem *)SliderList->at(index))->setValueMin(min);
            }

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        inline void setValueMax(int index,  double max) {
            if (index < int(SliderList->count()))
                ((arnEngineAppSliderItem *)SliderList->at(index))->setValueMax(max);
            }

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
			if (index < int(SliderList->count())) {
				return ((arnEngineAppSliderItem *)SliderList->at(index))->isVisibleTo(this);
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

        /*! \brief set the numeric value of a value minimum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param min is value of the minimum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        double ValueMin(const char* Label);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        double ValueMax(const char* Label);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        inline double ValueMin(int index) {
            if (index < int(SliderList->count()))
                return ((arnEngineAppSliderItem *)SliderList->at(index))->ValueMin();
            else arnCriticalExit();
            }

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        inline double ValueMax(int index) {
            if (index < int(SliderList->count()))
                return ((arnEngineAppSliderItem *)SliderList->at(index))->ValueMax();
            else arnCriticalExit();
            }
        /*! \brief set the numeric value of a value minimum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param min is value of the minimum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        int SliderMin(const char* Label);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        int SliderMax(const char* Label);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        inline int SliderMin(int index) {
            if (index < int(SliderList->count()))
                return ((arnEngineAppSliderItem *)SliderList->at(index))->SliderMin();
            else arnCriticalExit();
            }

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param index is the index of the slider in the group.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        inline int SliderMax(int index) {
            if (index < int(SliderList->count()))
                return ((arnEngineAppSliderItem *)SliderList->at(index))->SliderMax();
            else arnCriticalExit();
            }

		/*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
        bool isChannelConnected(int index);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        bool isChannelConnected(const char* Label);
    
		/*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
        inline void setReplaceObject(int index,arnSObjectContainer *pRo) {
            if (index < int(SliderList->count())) ((arnEngineAppSliderItem *)SliderList->at(index))->setReplaceObject(pRo);
            else arnCriticalExit();
            }

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        void setReplaceObject(const char* Label,arnSObjectContainer *pRo);
	
		/*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
        arnSObjectContainer *replaceObject(int index) {
            if (index < int(SliderList->count()))
                return ((arnEngineAppSliderItem *)SliderList->at(index))->replaceObject();
            else arnCriticalExit();
            }

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        arnSObjectContainer *replaceObject(const char* Label);

		/*! \brief update all the widget children of his\n
        *
        * It shows the channel index.
        *
        * Ex:\n
        * ...\n
        */
        bool isCOPEnabled(int index);

        /*! \brief set the numeric value of a value maximum in the group for scaling\n
        *
        * @param Label is name of the slider.
        * @param max is value of the maximum value for scaling.
        *
        * Ex:\n
        * ...\n
        */
        bool isCOPEnabled(const char* Label);

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
			if (index < int(SliderList->count()))
				((arnEngineAppSliderItem *)SliderList->at(index))->setVisible(en);
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
		void setVisiblem(const char* Label,bool en);
};
#endif
