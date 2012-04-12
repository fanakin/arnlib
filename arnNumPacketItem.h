/***************************************************************************
                          arnNumPacketItem.h  -  description
                             -------------------
    begin                : ven lug 4 2003
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
#ifndef ArnNumPackectItemH
#define ArnNumPackectItemH

#include "arnPacketItem.h"

#define BACKGROUNDCOLOR "white"
#define DIGITCOLOR "red"
#define TOLOWCOLOR "blue"
#define TOHIGHCOLOR "yellow"

class arnNumPacketItem : public arnPacketItem {
	Q_OBJECT

	private:
		void init(void);
		QTimer* timerManualBlink;
	private slots:
		void TimeoutManualBlink_Hndl(void);
	protected:
		bool manualBlinkEnabled;
		QLCDNumber* Value;
		virtual void mousePressEvent(QMouseEvent *e);
	public:

        /*! \brief constructor in QT style \n
        *
        */
        arnNumPacketItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumPacketItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumPacketItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumPacketItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumPacketItem(const QString& label = "", double value = 0.0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnNumPacketItem(void);

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
        inline QLCDNumber* lcdValue(void) {return Value;}

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
        inline double value(void) {return Value->value();}

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
        inline double intValue(void) {return Value->intValue();}

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
		inline void setValue(const QString& val) {Value->display(val);}

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
		inline void setValue(int val) {Value->display(val);}

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
		inline void setValue(double val) {Value->display(val);}

        /*! \brief enable the manual blink property\n
        *
        * @param en enable or disable \n
        *
        * This function enables the one shot manual blink property
        *
        * Ex:\n
        * ...\n
        */
        inline void EnableManualBlink(bool en) {manualBlinkEnabled = en;}

        /*! \brief it checks if the manual blink property in enabled \n
        *
        * @return the value of manualBlinkEnabled \n
        *
        * This function checks if the one shot manual blink property is enabled
        *
        * Ex:\n
        * ...\n
        */
        inline bool isManualBlinkEnabled(void) {return manualBlinkEnabled;}

        /*! \brief it checks if the manual blink property in enabled \n
        *
        * @param blinkShot is the duration in ms of the blink \n
        *
        * This function activates the one shot blink and sets the time of the blink to blinkShot
        *
        * Ex:\
        * ... \n
        * EnableManualBlink(true); \n
        * setManualBlink(500); \n
        * ...\n
        */
        void setManualBlink(unsigned short blinkShot);
};


#endif
