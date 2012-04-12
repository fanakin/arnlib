/***************************************************************************
                          arnPacketVisualizerSelectPanel.cpp  -  description
                             -------------------
    begin                : lun Gen 04 2010
    copyright            : (C) 2010 by Aurion s.r.l., fabio giovagnini
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

#include <stdlib.h>
#include <QObjectList>
#include <QCheckBox>
#include <QGridLayout>
#include <QScrollBar>
#include <QMouseEvent>
#include "CommonFunctions.h"
#include "arnPacketVisualizerSelectPanel.h"

arnPacketVisualizerSelectPanel::arnPacketVisualizerSelectPanel(QWidget *parent, const char* /*name*/ , Qt::WFlags /*f*/)
    : QAbstractScrollArea(parent)/*QFrame(parent,name,f)*/
{
	nOfCols = 0;
	nOfRows = 0;
	timerID = 0;
	groupBox = new QGroupBox("",viewport());
	if (!groupBox) arnCriticalExit();

	QGridLayout* Lo = new QGridLayout;
	if (!Lo) arnCriticalExit();
	groupBox->setLayout(Lo);

	group = new QButtonGroup(this);
	if (!group) arnCriticalExit();
	group->setExclusive(false);
}

arnPacketVisualizerSelectPanel::~arnPacketVisualizerSelectPanel(void)
{
	if (timerID) killTimer(timerID);
}

void arnPacketVisualizerSelectPanel::resizeEvent ( QResizeEvent * event )
{
	QSize areaSize = viewport()->size();
	QSize  widgetSize = groupBox->size();

	verticalScrollBar()->setPageStep(widgetSize.height());
	horizontalScrollBar()->setPageStep(widgetSize.width());
	verticalScrollBar()->setRange(0, widgetSize.height() - areaSize.height());
	horizontalScrollBar()->setRange(0, widgetSize.width() - areaSize.width());
	updateWidgetPosition();
	event->accept();
}

void arnPacketVisualizerSelectPanel::updateWidgetPosition(void)
{
	int hvalue = horizontalScrollBar()->value();
	int vvalue = verticalScrollBar()->value();
	QPoint topLeft = viewport()->rect().topLeft();

	groupBox->move(topLeft.x() - hvalue, topLeft.y() - vvalue);
}

// void arnPacketVisualizerSelectPanel::mousePressEvent(QMouseEvent *e)
// {
// arnDebug("18");
//     mousePressPos = e->pos();
//     scrollBarValuesOnMousePress.rx() = horizontalScrollBar()->value();
//     scrollBarValuesOnMousePress.ry() = verticalScrollBar()->value();
//     e->accept();
// }
// 
// void arnPacketVisualizerSelectPanel::mouseMoveEvent(QMouseEvent *e)
// {
// arnDebug("19");
//     if (mousePressPos.isNull()) {
//         e->ignore();
//         return;
//     }
// 
//     horizontalScrollBar()->setValue(scrollBarValuesOnMousePress.x() - e->pos().x() + mousePressPos.x());
//     verticalScrollBar()->setValue(scrollBarValuesOnMousePress.y() - e->pos().y() + mousePressPos.y());
//     horizontalScrollBar()->update();
//     verticalScrollBar()->update();
// 	updateWidgetPosition();
//    e->accept();
// }
// 
// void arnPacketVisualizerSelectPanel::mouseReleaseEvent(QMouseEvent *e)
// {
// arnDebug("20");
//     mousePressPos = QPoint();
//     e->accept();
// }

void arnPacketVisualizerSelectPanel::scrollContentsBy ( int /*dx*/, int /*dy*/ )
{
	updateWidgetPosition();
}

void arnPacketVisualizerSelectPanel::setVisualizer(arnPacketVisualizer* vis)
{
	if (!vis) return;
	if (!groupBox) return;
	if (!groupBox->layout()) return;
	PacketVisualizer = vis;
	nItem = PacketVisualizer->count();
	nOfCols = 2;
	nOfRows = nItem / 2;
	if (nItem % 2) nOfRows++;
	for (int i = 0; i < nItem; i++) {
		QCheckBox* pChkB = new QCheckBox(PacketVisualizer->name(i),0);
		if (!pChkB) arnCriticalExit();
		if (i < nOfRows) {
			((QGridLayout*)groupBox->layout())->addWidget(pChkB,i,0);
			//((QGridLayout*)Sa->layout())->addWidget(pChkB,i,0);
			}
		else {
			((QGridLayout*)groupBox->layout())->addWidget(pChkB,i - nOfRows,1);
			//((QGridLayout*)Sa->layout())->addWidget(pChkB,i - nOfRows,1);
			}
		if (PacketVisualizer->isChannelVisible(i)) pChkB->setCheckState(Qt::Checked);
		else pChkB->setCheckState(Qt::Unchecked);
		group->addButton(pChkB,i);
		}
	connect(group, SIGNAL(buttonClicked(int)), this, SLOT(ClickedButton_Hndl(int)));
	timerID = startTimer(100);
}

void arnPacketVisualizerSelectPanel::ClickedButton_Hndl(int iD)
{
	if (PacketVisualizer) {
		QCheckBox* pChkB = (QCheckBox*)(group->button(iD));
		if (pChkB) {
			if (pChkB->checkState() == Qt::Checked) {PacketVisualizer->showChannel(iD);}
			else  {PacketVisualizer->hideChannel(iD);}
			}
		}
}

void arnPacketVisualizerSelectPanel::timerEvent ( QTimerEvent * event )
{
	if (!PacketVisualizer) return;
	for (int i = 0; i < nItem; i++) {
		QCheckBox* pChkB = (QCheckBox*)(group->button(i));
		if (PacketVisualizer->isChannelVisible(i)) pChkB->setCheckState(Qt::Checked);
		else pChkB->setCheckState(Qt::Unchecked);
		group->addButton(pChkB,i);
		}
	event->accept();
}
