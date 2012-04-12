/***************************************************************************
                          arnThrottleCycleVisualizer.h  -  description
                             -------------------
    begin                : lun giu 11 2007
    copyright            : (C) 2007 by Aurion s.r.l.
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

#ifndef ArnThrottleCycleVisualizerH
#define ArnThrottleCycleVisualizerH

#include <qframe.h>
#include <qlayout.h>
#include <qpushbutton.h>
#include <qtimer.h>

#include "arnlibtypes.h"
#include "arnNumEnPacketItem.h"
#include "arnThrottleCycle.h"


class arnThrottleCycleVisualizer : public QFrame {

    Q_OBJECT

    private:
    protected:
		QGridLayout *layout;
		QPushButton *StartCycle;
		QPushButton *openCycleFile;
		QPushButton *checkFuelPump;
		QPushButton *checkOilPump1;
		QPushButton *checkOilPump2;
		arnThrottleCycle *ThrCycle;
		QString cleFName;
		QTimer *timer;
		arnNumEnPacketItem* FuelPress;
		arnNumEnPacketItem* BattV;
		arnNumEnPacketItem* DutyPump;
		unsigned int cleIndx;
		int timerExp;
        virtual void mouseDoubleClickEvent(QMouseEvent *e);
    protected slots:
		void StartCycleButtonToggle_hndl(bool toggle);
		void OpenCycleFileButtonClicked_hndl(void);
		void checkFuelPumpButtonToggle_hndl(void);
		void checkOilPump1ButtonToggle_hndl(void);
		void checkOilPump2ButtonToggle_hndl(void);
		void timer_hndl(void);
    public:

        /*! \brief constructor in QT style \n
        *
        */
        arnThrottleCycleVisualizer(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnThrottleCycleVisualizer(void);

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

        /*! \brief it sets the start button text\n
        *
        * @param txt is the text to set\n
        *
        * Ex:\n
        * ...\n
        */
        inline void setStartButtonText(const QString &txt) {if (StartCycle) StartCycle->setText(txt);}

        /*! \brief it gets the start button text\n
        *
        * @return the text into Start button\n
        *
        * Ex:\n
        * ...\n
        */
        inline QString StartButtonText(void) {if (!StartCycle) return QString(""); else return StartCycle->text();}

        /*! \brief it gets the check fuel pump button status\n
        *
        * @return fuel pump button status \n
        *
        * Ex:\n
        * ...\n
        */
		inline bool isCheckFuelPump(void) {return  checkFuelPump->isDown();}

        /*! \brief it gets the check fuel pump button status\n
        *
        * @return fuel pump button status \n
        *
        * Ex:\n
        * ...\n
        */
		inline bool isCheckOilPump1(void) {return  checkOilPump1->isDown();}

        /*! \brief it gets the check fuel pump button status\n
        *
        * @return fuel pump button status \n
        *
        * Ex:\n
        * ...\n
        */
		inline bool isCheckOilPump2(void) {return  checkOilPump2->isDown();}

        /*! \brief it sets the visible or not a button\n
        *
        *
        * Ex:\n
        * ...\n
        */
		void SetButtonVisible(unsigned char indx,bool flg);

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
        inline void setUpperTh(int index, const QString& val) {
			switch (index) {
				case 0: return BattV->setUpperTh(val);
				case 1: return DutyPump->setUpperTh(val);
				case 2: return FuelPress->setUpperTh(val);
				default: break;
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
        inline void setUpperTh(int index, int val) {
			switch (index) {
				case 0: return BattV->setUpperTh(val);
				case 1: return DutyPump->setUpperTh(val);
				case 2: return FuelPress->setUpperTh(val);
				default: break;
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
        inline void setUpperTh(int index, double val) {
			switch (index) {
				case 0: return BattV->setUpperTh(val);
				case 1: return DutyPump->setUpperTh(val);
				case 2: return FuelPress->setUpperTh(val);
				default: break;
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
        inline void setLowerTh(int index, const QString& val) {
			switch (index) {
				case 0: return BattV->setLowerTh(val);
				case 1: return DutyPump->setLowerTh(val);
				case 2: return FuelPress->setLowerTh(val);
				default: break;
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
        inline void setLowerTh(int index, int val) {
			switch (index) {
				case 0: return BattV->setLowerTh(val);
				case 1: return DutyPump->setLowerTh(val);
				case 2: return FuelPress->setLowerTh(val);
				default: break;
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
        inline void setLowerTh(int index, double val) {
			switch (index) {
				case 0: return BattV->setLowerTh(val);
				case 1: return DutyPump->setLowerTh(val);
				case 2: return FuelPress->setLowerTh(val);
				default: break;
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
        inline double UpperTh(int index) {
			switch (index) {
				case 0: return BattV->UpperTh();
				case 1: return DutyPump->UpperTh();
				case 2: return FuelPress->UpperTh();
				default: return 0;
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
        inline double LowerTh(int index) {
			switch (index) {
				case 0: return BattV->LowerTh();
				case 1: return DutyPump->LowerTh();
				case 2: return FuelPress->LowerTh();
				default: return 0;
				}
			return 0;
			}

	public slots:
		inline void setBaseInterval(int time)  {timerExp = time;}
		inline int getBaseInterval(void)  {return timerExp;}
	signals:
		void ThrottleValueChanged(int val);
};

#endif
