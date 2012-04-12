/***************************************************************************
                          arnqslider.h  -  description
                             -------------------
    begin                : mar feb 7 2006
    copyright            : (C) 2006 by Aurion s.r.l.
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

#ifndef ArnQSliderH
#define ArnQSliderH

#include <qslider.h>


class arnQSlider : public QSlider
{
	public:
		arnQSlider( QWidget * parent, const char * name = 0 );
		arnQSlider( Qt::Orientation orientation, QWidget * parent, const char * name = 0 );
		arnQSlider( int minValue, int maxValue, int pageStep, int value, Qt::Orientation orientation, QWidget * parent, const char * name = 0 );
		~arnQSlider();
	public slots:
		inline void setMulSelKeyUP(Qt::Key K) {MulSelKeyUp = K;}
		inline void setMulSelKeyDOWN(Qt::Key K) {MulSelKeyDown = K;}
		inline Qt::Key getMulSelKeyUP(void) {return MulSelKeyUp;}
		inline Qt::Key getMulSelKeyDOWN(void) {return MulSelKeyDown;}
	protected:
		//virtual void keyPressEvent ( QKeyEvent * e );
		//void focusInEvent ( QFocusEvent * );
	protected slots:
	private:
		Qt::Key MulSelKeyUp; // Key for moving the slider; we add a key to default left and rigth arrows
		Qt::Key MulSelKeyDown; // Key for moving the slider; we add a key to default left and rigth arrows
		void init (void);
	private slots:
};

#endif // ArnQSliderH
