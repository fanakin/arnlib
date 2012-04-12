/***************************************************************************
						  arnPushButtonItem.h  -  description
                             -------------------
	begin                : sab sett 25 2010
	copyright            : (C) 2003-2010 by fabio giovagnini
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

#ifndef ArnPushButtonItemH
#define ArnPushButtonItemH

#include <QPushButton>
#include "arnlibtypes.h"
#include "CommonFunctions.h"

class arnPushButtonItem : public QPushButton {
	Q_OBJECT

	private:
		arnGroupItemType_t typ;
	private slots:
		//void clicked_hndl(bool cled);
		//void pressed_hndl(void);
		//void released_hndl(void);
	protected:
	protected slots:
	public:
        
		/*! \brief constructor in QT style \n
		*
        */
		arnPushButtonItem(QWidget *parent = 0, const char* name = 0);

        /*! \brief default destructor\n
        *
        */
		~arnPushButtonItem(void) {;}

		inline int value(void) {return ((isDown()) ? 1 : 0);}

		inline void setValue(double /*val*/) {;}

	signals:
	public slots:
};

#endif
