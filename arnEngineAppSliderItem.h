/***************************************************************************
                          arnEngineAppSliderItem.h  -  description
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

#ifndef ArnEngineAppSliderItemH
#define ArnEngineAppSliderItemH

#include "arnObjectViewer.h"
#include "arnSliderItem.h"
#include "arnSObjectContainer.h"

class arnEngineAppSliderItem : public arnSliderItem {
	Q_OBJECT
	private:
		void init(void);
	private slots:
		void AbilitaCopertura_Hndl(bool tg);
		void EditCopertura_Hndl(void);
	protected:
		arnSObjectContainer *pReplaceObj;
		arnObjectViewer *Viewer;
	protected slots:
	signals:
	public:
		QAction *AbilitaCopertura;
		QAction *EditCopertura;
		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppSliderItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppSliderItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppSliderItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineAppSliderItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief default destructor\n
		*
		*/
		~arnEngineAppSliderItem(void);
		
		inline void setReplaceObject(arnSObjectContainer *pRo) {pReplaceObj = pRo;}
		inline arnSObjectContainer *replaceObject(void) {return pReplaceObj;}
	public slots:
		inline bool isCOPEnabled(void) {return ((AbilitaCopertura != 0) ? AbilitaCopertura->isOn() : false);}

};

#endif
