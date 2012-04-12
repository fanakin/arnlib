/***************************************************************************
                          arnPacketItem.h  -  description
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
#ifndef ArnPackectItemH
#define ArnPackectItemH

#include <qlabel.h>
#include <qframe.h>
#include <qlcdnumber.h>
#include <qlayout.h>
#include <QMenu>
#include <qaction.h>
#include <qtimer.h>

#include "arnlibtypes.h"

class arnPacketItem : public QFrame {
	Q_OBJECT

	private:
		void init(void);
	private slots:
		void Nascondi_Hndl(void);
	protected:
		arnPacketItemType_t tpe;
		QLabel* Name;
		QHBoxLayout *pHLayout;
		QMenu *pPopUp;

		virtual void mousePressEvent(QMouseEvent *e) = 0;
	public:
		QAction *Nascondi;

        /*! \brief constructor in QT style \n
        *
        */
        arnPacketItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnPacketItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnPacketItem(void);

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
        inline QString name(void) {return Name->text();}

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
        inline void setName(const QString& name) {Name->setText(name);}

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
		inline arnPacketItemType_t type(void) {return tpe;}
        
		/*! \brief It sets the name alignment\n
		*
		* @param a is the alignment as Qt::AlignmentFlags\n
		*
		* This function uses a bitwised OR of Qt::AlignmentFlags to aling the name\n
		* See Qt::AlignmentFlags documentation.
		*
		* Ex:\n
		* ...\n
		* a->alignName(Qt::AlignVCenter | Qt::AlignHCenter); // H and V center alignment
		*/
		inline void alignName(int a) {Name->setAlignment(a);}

		/*! \brief It sets the Packet Item name font size\n
		*
		* @param a is the font size as in QFont::setPointSize(int)\n
		*
		* This function sets the point size for the font of the Name label\n
		* See QFont documentation.
		*
		* Ex:\n
		* ...\n
		* a->setFontSize(24); // set the point size feature of the font to 24
		*/
		inline void setNameFontSize(int a) {
			QFont F(Name->font());
			F.setPointSize(a);
			Name->setFont(F);
			}

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
		virtual void setValue(unsigned char a) = 0;

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
		virtual void setValue(unsigned short a) = 0;

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
		virtual void setValue(unsigned long a) = 0;

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
		virtual void setValue(signed char a) = 0;

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
		virtual void setValue(signed short a) = 0;

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
		virtual void setValue(signed long a) = 0;

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
		virtual void setValue(int a) = 0;

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
		virtual void setValue(float a) = 0;

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
		virtual void setValue(double a) = 0;

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
		virtual void setValue(char* text) = 0;

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
		virtual void setValue(QString& text) = 0;
};

#endif
