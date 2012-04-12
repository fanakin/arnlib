/***************************************************************************
                          arnEngineZAppSliderItem.h  -  description
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

#ifndef ArnEngineZAppSliderItemH
#define ArnEngineZAppSliderItemH

#include <qlineedit.h>
#include "arnObjectViewer.h"
#include "arnEngineAppSliderItem.h"
#include "arnSObjectContainer.h"

class arnEngineZAppSliderItem : public arnEngineAppSliderItem {
	Q_OBJECT
	private:
		void init(void);
		QLineEdit* directCVal;
	private slots:
		void directCValRetPress_hndl(void);
	protected:
		virtual void mouseDoubleClickEvent(QMouseEvent *e);
	protected slots:
	signals:
	public:
		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineZAppSliderItem(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineZAppSliderItem(const QString& label = "", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineZAppSliderItem(const QString& label = "", const QString& value = "0", QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief constructor in QT style \n
		*
		*/
		arnEngineZAppSliderItem(const QString& label = "", int value = 0, QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0);

		/*! \brief default destructor\n
		*
		*/
		~arnEngineZAppSliderItem(void);
		
	public slots:

};

#endif
