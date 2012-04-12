/***************************************************************************
                          arnObjectViewer.h  -  description
                             -------------------
    begin                : mer apr 23 2003
    copyright            : (C) 2003 by fabio giovagnini
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

#ifndef ArnObjectViewerH
#define ArnObjectViewerH

#include <qframe.h>
#include "CommonFunctions.h"

typedef enum arnViewerType {
    avt_ObjectViewer,
    avt_NumericVariableViewer,
    avt_StringVariableViewer,
    avt_NumericArrayViewer,
    avt_NumericMatrixViewer,
    avt_GLMatrixViewer,
    avt_GLArrayViewer,
    avt_GLMultipleArrayViewer,
    avt_CompositeArrayViewer,
    avt_EnCompositeArrayViewer,
    avt_CompositeMatrixViewer,
    avt_EnCompositeMatrixViewer,
    avt_MiscMatrixViewer,
    avt_BitValueMatrixViewer,
	avt_StringMatrixViewer,
    avt_NoneViewer
    } arnViewerType_t;


class arnObjectViewer : public QFrame
{
    Q_OBJECT

    private:
    protected:
        arnViewerType_t tpy;
    public :
		virtual inline arnViewerType_t type(void) {return tpy;}
        arnObjectViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnObjectViewer(void);
    public slots:
        virtual void setValue(double) {arnDebug("to be reimplemented\n");}
        virtual void setValue(int, double) {arnDebug("to be reimplemented\n");}
        virtual void setValue(int, int, double) {arnDebug("to be reimplemented\n");}
        virtual void setValue(QString&) {arnDebug("to be reimplemented\n");}
        virtual void setValue(int, QString&) {arnDebug("to be reimplemented\n");}
        virtual void setValue(int, int, QString&) {arnDebug("to be reimplemented\n");}
        virtual double value(void) {arnDebug("to be reimplemented\n"); return -1;}
        virtual double value(int) {arnDebug("to be reimplemented\n"); return -1;}
        virtual double value(int, int) {arnDebug("to be reimplemented\n"); return -1;}
        virtual QString text(void) {arnDebug("to be reimplemented\n"); return "";}
        virtual QString text(int) {arnDebug("to be reimplemented\n"); return "";}
        virtual QString text(int, int) {arnDebug("to be reimplemented\n"); return "";}
};

#endif
