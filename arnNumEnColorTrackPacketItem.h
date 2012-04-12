/***************************************************************************
                          arnNumEnColorTrackPacketItem.h  -  description
                             -------------------
    begin                : mar luglio 26 2005
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
#ifndef ArnNumEnColorTrackPackectItemH
#define ArnNumEnColorTrackPackectItemH

#include "arnNumEnPacketItem.h"

class arnNumEnColorTrackPacketItem : public arnNumEnPacketItem {
	Q_OBJECT

	private:
		void init(void);
	private slots:
		void enTrackColor_Hndl(bool tg);
		void selTrackColor_Hndl(void);
	protected:
		QColor defaultColor;
		QColor clr;
	public:
		QAction *enTrackColor;
		QAction *selTrackColor;

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnColorTrackPacketItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnColorTrackPacketItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnColorTrackPacketItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnColorTrackPacketItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief constructor in QT style \n
        *
        */
        arnNumEnColorTrackPacketItem(const QString& label = "", double value = 0.0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

        /*! \brief default destructor\n
        *
        */
        ~arnNumEnColorTrackPacketItem(void);

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
		inline const QColor& trackColor(void) {return clr;}
		
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
		void setTrackColor(const QColor& c);
		
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
		inline void hideTrackColor(void) {enTrackColor->setOn(false);Name->setPaletteBackgroundColor(defaultColor);}
        
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
		void showTrackColor(void);
};


#endif
