/***************************************************************************
                          arnSMiscMarkNumericMatrix.cpp  -  description
                             -------------------
    begin                : mar apr 26 2005
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

#include "arnNumericFilter.h"
#include "arnSMiscMarkNumericMatrix.h"
#include "arnEnCompositeMatrixViewer.h"
// ---------------------------------------------------
// ***************************************************
// --------- arnSMiscMarkNumericMatrix ----------------------
// ***************************************************
// ---------------------------------------------------
arnSMiscMarkNumericMatrix::arnSMiscMarkNumericMatrix ( QObject * parent, const char * name )
    : arnSMiscNumericMatrix( parent, name)
{
    this->init();
}

arnSMiscMarkNumericMatrix::~arnSMiscMarkNumericMatrix(void)
{
//arnDebug("%s\n",name());
	for (int i = 0; i < NRows; i++) {
		if (mark[i]) {delete [] mark[i]; mark[i] = 0;}
		}
	if (mark) {delete [] mark; mark = 0;}
}

void arnSMiscMarkNumericMatrix::init(void)
{
    tpe = sot_MiscMarkNumericMatrix;
	defColor = QColor("red");
    xAxis = 0;
    yAxis = 0;
    prcX = 0;
    mnX = 0;
    mxX = NCols - 1;
    prcY = 0;
    mnY = 0;
    mxY = NRows - 1;
	mark = new struct mark_info*[NRows];
	if (!mark) arnCriticalExit();
	for (int i = 0; i < NRows; i++) {
		mark[i] = new struct mark_info[NCols];
		if (!mark[i]) arnCriticalExit();
		}
/*	for (int i = 0; i < NRows; i++) {
		for (int j = 0; j < NCols; j++) {
			mark[i][j] = false;
			}
		}
*/
}

void arnSMiscMarkNumericMatrix::setDims(int rows, int cols)
{
	for (int i = 0; i < NRows; i++) {
		if (mark[i]) {delete [] mark[i]; mark[i] = 0;}
		}
	if (mark) {delete [] mark; mark = 0;}
	if (!xAxis) NCols = cols;
	else NCols = yAxis->rows();
	if (!yAxis) NRows = rows;
	else NRows = xAxis->rows();
	mark = new struct mark_info*[NRows];
	if (!mark) arnCriticalExit();
	for (int i = 0; i < NRows; i++) {
		mark[i] = new struct mark_info[NCols];
		if (!mark[i]) arnCriticalExit();
		}
/*	for (int i = 0; i < NRows; i++) {
		for (int j = 0; j < NCols; j++) {
			mark[i][j] = false;
			}
		}*/
}

void arnSMiscMarkNumericMatrix::setValueAndMark(int row, int col, double val)
{
/*	arnDebug("passo1");*/
	arnSMiscNumericMatrix::setValue(row,col,val);
	if (mark && mark[row] && row < NRows && col < NCols) {
		mark[row][col].marked = true;
		mark[row][col].color = defColor;
		if (pViewer) {
			switch (pViewer->type()) {
				case avt_EnCompositeMatrixViewer:
/*					arnDebug("passo3");*/
					((arnEnCompositeMatrixViewer*)pViewer)->setValue(row,col,val);
					((arnEnCompositeMatrixViewer*)pViewer)->setMatrixItemColor(row,col, mark[row][col].color);
					((arnEnCompositeMatrixViewer*)pViewer)->updatePrevCellColor( mark[row][col].color );
					break;
				default : arnCriticalExit(); break;
				}
			}
		}
}

void arnSMiscMarkNumericMatrix::setValueAndMark(int row, int col, const QString& val)
{
    bool ok;
    double tNum = val.toDouble(&ok);
    if (!ok) return;
    setValue(row, col, tNum);
	if (mark && mark[row] && row < NRows && col < NCols) {
		mark[row][col].marked = true;
		mark[row][col].color = defColor;
		}
}

void arnSMiscMarkNumericMatrix::setValueAndMark(int row, int col)
{
    if (!pViewer) arnCriticalExit();
    bool ok;
    double tNum = pViewer->text(row,col).toDouble(&ok);
    if (!ok) return;
    setValue(row, col ,tNum);
	if (mark && mark[row] && row < NRows && col < NCols) {
		mark[row][col].marked = true;
		mark[row][col].color = defColor;
		//emit TraceChanged(col,row/*,itrace.value*/);
		if (pViewer && (pViewer->type() == avt_EnCompositeMatrixViewer)) {
			arnDebug("passo3");
			((arnEnCompositeMatrixViewer*)pViewer)->setMatrixItemColor(row,col, mark[row][col].color);
			}
		}
}

bool arnSMiscMarkNumericMatrix::isMarked(int row, int col)
{
	if (mark && mark[row] && row < NRows && col < NCols) return mark[row][col].marked;
	return false;
}

void arnSMiscMarkNumericMatrix::resetMark(int row, int col)
{
	if (mark && mark[row] && row < NRows && col < NCols) mark[row][col].marked = false;
}

void arnSMiscMarkNumericMatrix::setDefaultColor(const QColor& c)
{
	defColor = c;
}

void arnSMiscMarkNumericMatrix::setColor(int row, int col, const QColor& c)
{
	if (mark && mark[row] && row < NRows && col < NCols) mark[row][col].color = c;
}

QColor arnSMiscMarkNumericMatrix::Color(int row, int col)
{
	if (mark && mark[row] && row < NRows && col < NCols) return mark[row][col].color;
	return defColor;
}
