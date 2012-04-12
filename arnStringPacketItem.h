/***************************************************************************
                          arnStringPacketItem.h  -  description
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
#ifndef ArnStringPackectItemH
#define ArnStringPackectItemH

#include "arnPacketItem.h"

class arnStringPacketItem : public arnPacketItem {
	Q_OBJECT

	private:
		void init(void);
	private slots:
	protected:
		QLabel* Value;
		virtual void mousePressEvent(QMouseEvent *e);
	public:

        /*! \brief constructor in QT style \n
        *
        */
        arnStringPacketItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnStringPacketItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnStringPacketItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnStringPacketItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnStringPacketItem(const QString& label = "", double value = 0.0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnStringPacketItem(void);

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
		virtual inline QString value(void) {return Value->text();}
        
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
		virtual inline void setValue(QString& val) {Value->setText(val);}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue("24"); // set the value of the Packe Item to 24
		*/
		virtual inline void setValue(char* text) {Value->setText(QString::fromAscii(text));}



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
		virtual inline void setValue(int val) {Value->setText(QString::number(val));}

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
        inline void setValue(double val) {Value->setText(QString::number(val));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(unsigned char a) {Value->setText(QString::number(a));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(unsigned short a){Value->setText(QString::number(a));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(unsigned long a) {Value->setText(QString::number(a));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(signed char a) {Value->setText(QString::number(a));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(signed short a) {Value->setText(QString::number(a));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(signed long a) {Value->setText(QString::number(a));}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(24); // set the value of the Packe Item to 24
		*/
		virtual void setValue(float a) {Value->setText(QString::number(a));}













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
		void setValueFontSize(int size);

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
		void setValueFontColor(QColor color);
};


#endif
