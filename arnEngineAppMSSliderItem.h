/***************************************************************************
                          arnEngineAppMSSliderItem.h  -  description
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

#ifndef ArnEngineAppMSSliderItemH
#define ArnEngineAppMSSliderItemH

#include "arnObjectViewer.h"
#include "arnMSSliderItem.h"
#include "arnSObjectContainer.h"

class arnEngineAppMSSliderItem : public arnMSSliderItem {
	Q_OBJECT
	private:
		void init(void);
	private slots:
	protected:
		arnSObjectContainer *pReplaceObj;
		arnObjectViewer *Viewer;
	protected slots:
		virtual void AbilitaCopertura_Hndl(bool tg);
		virtual void EditCopertura_Hndl(void);
	signals:
	public:
		QAction *AbilitaCopertura;
		QAction *EditCopertura;
		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSSliderItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSSliderItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSSliderItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppMSSliderItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief default destructor\n
		*
		*/
		~arnEngineAppMSSliderItem(void);
		
		inline void setReplaceObject(arnSObjectContainer *pRo) {pReplaceObj = pRo;}
		inline arnSObjectContainer *replaceObject(void) {return pReplaceObj;}
	public slots:
		inline bool isCOPEnabled(void) {return ((AbilitaCopertura != 0) ? AbilitaCopertura->isOn() : false);}

};

#endif
