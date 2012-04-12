/***************************************************************************
                          arnPacketVisualizerSelectPanel.h  -  description
                             -------------------
    begin                : lun Gen 04 2010
    copyright            : (C) 2009 by Aurion s.r.l. , fabio giovagnini
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

#ifndef ArnPackectVisualizerSelectPanelH
#define ArnPackectVisualizerSelectPanelH

#include <QAbstractScrollArea>
#include <QButtonGroup>
#include <QGroupBox>

#include "arnPacketVisualizer.h"


class arnPacketVisualizerSelectPanel : public QAbstractScrollArea {
	 Q_OBJECT
	private:
		arnPacketVisualizer* PacketVisualizer;
		QButtonGroup* group;
		QGroupBox* groupBox;
		//QPoint mousePressPos;
		//QPoint scrollBarValuesOnMousePress;
		int timerID;
		unsigned short nOfRows;
		unsigned short nOfCols;
		unsigned short nItem;

		void updateWidgetPosition(void);
	private slots:
			void ClickedButton_Hndl(int iD);
	protected:
		virtual void resizeEvent ( QResizeEvent * event );
		//virtual void mousePressEvent(QMouseEvent *e);
		//virtual void mouseMoveEvent(QMouseEvent *e);
		//virtual void mouseReleaseEvent(QMouseEvent *e);
		virtual void scrollContentsBy ( int dx, int dy );
		void timerEvent ( QTimerEvent * event );
	public:
		/*! \brief constructor in QT style \n
		*
		*/
		arnPacketVisualizerSelectPanel(QWidget *parent = 0, const char* name = 0,  Qt::WFlags f = 0);
		
		/*! \brief default destructor\n
		*
		*/
		~arnPacketVisualizerSelectPanel(void);
	public slots:

		/*! \brief set the visualizer to manage \n
		*
		*/
		void setVisualizer(arnPacketVisualizer* vis);

};

#endif
