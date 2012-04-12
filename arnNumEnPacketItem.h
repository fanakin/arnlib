/***************************************************************************
                          arnNumEnPacketItem.h  -  description
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
#ifndef ArnNumEnPackectItemH
#define ArnNumEnPackectItemH

#include <qlineedit.h>
#include "arnNumPacketItem.h"

class arnNumEnPacketItem : public arnNumPacketItem {
	Q_OBJECT

	private:
		void init(void);
		bool inizialized;
		QLineEdit* ThUPVal;
		QLineEdit* ThDOWNVal;
	private slots:
		void AbilitaAllarme_Hndl(bool tg);
		void ModificaThUP_Hndl(void);
		void ModificaThDOWN_Hndl(void);
		void Timeout_Hndl(void);
		void ThUPValRetPress_hndl(void);
		void ThDOWNValRetPress_hndl(void);
	protected:
		QTimer* timer;
		double upperTh,lowerTh;
		virtual void showEvent ( QShowEvent * event );
	public:
		QAction *AbilitaAllarme;
		QAction *ModificaThUP;
		QAction *ModificaThDOWN;

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnPacketItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnPacketItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnPacketItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnPacketItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnPacketItem(const QString& label = "", double value = 0.0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnNumEnPacketItem(void);

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
        inline void setAlarmEnabled(bool v) {AbilitaAllarme->setOn(v);}
        
		/*! \brief overloaded function : set the value for the channel of a fixed index\n
        *
        * @param index is the index in the list of the channels\n
        * @param val is the value to set\n
        *
        * This function does the direct setting of the ndex channel\n
        * it is an optimized function to reduce the access time to the list.
        *
        * Ex:\n
        * ...\n
        */
        inline bool isAlarmEnabled(void) {return AbilitaAllarme->isOn();}

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
        void setUpperTh(const QString& val);

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
        inline void setUpperTh(int val) {upperTh = val;}

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
        inline void setUpperTh(double val) {upperTh = val;}

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
        void setLowerTh(const QString& val);

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
        inline void setLowerTh(int val) {lowerTh = val;}

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
        inline void setLowerTh(double val) {lowerTh = val;}

        /*! \brief overloaded function : get the value of the upper alarm function for the channel\n
        *
        *
        * This function does the direct getting of the upper alarm threshold.
        *
        * Ex:\n
        * ...\n
        */
        inline double UpperTh(void) {return upperTh;}

        /*! \brief overloaded function : get the value of the lower alarm function for the channel\n
        *
        *
        * This function does the direct getting of the lower alarm threshold.
        *
        * Ex:\n
        * ...\n
        */
        inline double LowerTh(void) {return lowerTh;}

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
		void checkWarning(void);

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
		virtual inline void setValue(unsigned char val) {Value->display(val);}

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
		virtual inline void setValue(unsigned short val) {Value->display(val);}

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
		virtual inline void setValue(unsigned long val) {Value->display(QString::number(val));}

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
		virtual inline void setValue(signed char val) {Value->display(val);}

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
		virtual inline void setValue(signed short val) {Value->display(val);}

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
		virtual inline void setValue(signed long val) {Value->display(QString::number(val));}

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
		virtual inline void setValue(float val) {Value->display(val);}

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
		virtual inline void setValue(double val) {Value->display(val);}

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
		virtual inline void setValue(char* text) {Value->display(text);}

		/*! \brief It sets the value of the Packet Item. Pure Virtual\n
		*
		* @param a is the value to set\n
		*
		* This function sets the value of the Packet Item\n
		*
		*
		* Ex:\n
		* ...\n
		* a->setvalue(QString("24")); // set the value of the Packe Item to 24
		*/
		virtual inline void setValue(QString& text) {Value->display(text);}
};


#endif
