/***************************************************************************
                          arnNumericVariableViewer.h  -  description
                             -------------------
    begin                : gio apr 17 2003
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

#ifndef ArnNumericVariableViewerH
#define ArnNumericVariableViewerH

#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtextedit.h>
#include "arnlibtypes.h"
#include "arnObjectViewer.h"

class arnNumericVariableViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
		NumericRepresentationFormat_t numFormatVal;
	private slots:
        void doValueChange( const QString &);

    protected:
        QHBoxLayout *pValueLayout;
        QVBoxLayout *pMainLayout;
        QLabel *pName;
        QTextEdit *pComment;
        QLineEdit *pValue;
        unsigned prec;

    protected slots:

    signals:
        void valueChanged( const QString &);

    public :

        arnNumericVariableViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnNumericVariableViewer(void);
        inline void setName(const char* name) {pName->setText(name);}
        inline void setComment(const char* cm) {pComment->setText(QString(cm));}
        inline const char* comment(void) {return pComment->text();}
        inline const QLineEdit* Value(void) {return pValue;}
        inline void  setPrec(unsigned char pc) {prec = pc;}

        virtual void setValue(double val);
		inline void setNumFormat(NumericRepresentationFormat_t nm) {numFormatVal = nm;}
};

#endif
