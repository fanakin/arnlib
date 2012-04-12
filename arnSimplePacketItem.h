/***************************************************************************
						  arnSimplePacketItem.h  -  description
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
#ifndef ArnSimplePackectItemH
#define ArnSimplePackectItemH

#include <qlabel.h>
#include <qframe.h>
#include <qlcdnumber.h>
#include <qlayout.h>
#include <QMenu>
#include <qaction.h>
#include <qtimer.h>

#include "arnlibtypes.h"

class arnSimplePacketItem : public QFrame {
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
		arnSimplePacketItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
		arnSimplePacketItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
		~arnSimplePacketItem(void);

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

		/*! \brief It sets the name alignment\n
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
		virtual inline void setValue(unsigned char /*a*/) {;}

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
		virtual inline void setValue(unsigned short /*a*/) {;}

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
		virtual inline void setValue(unsigned long /*a*/) {;}

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
		virtual inline void setValue(signed char /*a*/) {;}

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
		virtual inline void setValue(signed short /*a*/) {;}

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
		virtual inline void setValue(signed long /*a*/) {;}

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
		virtual inline void setValue(float /*a*/) {;}

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
		virtual inline void setValue(double /*a*/) {;}

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
		virtual inline void setValue(char* /*text*/) {;}

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
		virtual inline void setValue(QString& /*text*/) {;}
};


#endif
