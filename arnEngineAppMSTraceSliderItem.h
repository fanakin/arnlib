/***************************************************************************
                          arnEngineAppMSTraceSliderItem.h  -  description
                             -------------------
    begin                : gio Feb 9 2006
    copyright            : (C) 2006 by fabio giovagnini
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

#ifndef ArnEngineAppMSTraceSliderItemH
#define ArnEngineAppMSTraceSliderItemH

#include "arnEngineAppMSSliderItem.h"

class arnEngineAppMSTraceSliderItem : public arnEngineAppMSSliderItem {
	Q_OBJECT
	private:
		void init(void);
	private slots:
		void AbilitaTrace_Hndl(void);
	protected:
	protected slots:
		virtual void EditCopertura_Hndl(void);
	signals:
	public:
		QAction *AbilitaTrace;
		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSTraceSliderItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSTraceSliderItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSTraceSliderItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSTraceSliderItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief default destructor\n
		*
		*/
		~arnEngineAppMSTraceSliderItem(void);
		
	public slots:
		inline bool isTraceEnabled(void) {return ((AbilitaTrace != 0) ? AbilitaTrace->isOn() : false);}

};

#endif
