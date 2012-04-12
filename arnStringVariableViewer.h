/***************************************************************************
                          arnStringVariableViewer.h  -  description
                             -------------------
    begin                : mer set 24 2003
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

#ifndef ArnStringVariableViewerH
#define ArnStringVariableViewerH

#include <qlabel.h>
#include <qtextedit.h>
#include <qtextedit.h>
#include <qlayout.h>
#include "arnObjectViewer.h"

class arnStringVariableViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
    private slots:
        void doValueChange();

    protected:
        QHBoxLayout *pValueLayout;
        QVBoxLayout *pMainLayout;
        QLabel *pName;
        QTextEdit *pComment;
        QTextEdit *pValue;
        unsigned prec;

    protected slots:

    signals:
        void valueChanged( const QString &);

    public :

        arnStringVariableViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnStringVariableViewer(void);
        inline void setName(const char* name) {pName->setText(name);}
        inline void setComment(const char* cm) {pComment->setText(cm);}
        inline const char* comment(void) {return pComment->text();}
        inline const QTextEdit* Value(void) {return pValue;}
        inline void  setPrec(unsigned char pc) {prec = pc;}

        virtual void setValue(const QString& val);
};

#endif
