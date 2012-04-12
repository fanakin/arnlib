/***************************************************************************
                          arnNumericMatrixViewer.h  -  description
                             -------------------
    begin                : ven apr 18 2003
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

#ifndef ArnNumericMatrixViewerH
#define ArnNumericMatrixViewerH

#include <qlabel.h>
#include <qtextedit.h>
#include <Q3Table>
#include <QMenu>
#include <qaction.h>
#include <qlayout.h>
#include <qclipboard.h>
#include "arnObjectViewer.h"

class arnNumericMatrixViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
        QClipboard* pClip;

    private slots:
        void doValueChange(int row, int col);

    protected:
        Q3Table *pMatrix;
        
        QVBoxLayout *pMainLayout;
        QTextEdit *pComment;
        QLabel *pName;

        QMenu *pPopUp;
        //QAction *SelezionaTutto;
        QAction *Inizializza;
        QAction *Interpola;
        QAction *InterpolaX;
        QAction *InterpolaY;
        QAction *Azzera;
        QAction *Aggiungi;
        QAction *Moltiplica;
        QAction *Nascondi;
        QAction *Mostratutti;
        QAction *Copia;
        QAction *Incolla;

        unsigned char prec,precX,precY;
		virtual void contextMenuEvent ( QContextMenuEvent * e );

    protected slots:
        //void SelezionaTutto_Hndl(void);
        void Inizializza_Hndl(void);
        void Interpola_Hndl(void);
        void InterpolaX_Hndl(void);
        void InterpolaY_Hndl(void);
        void Azzera_Hndl(void);
        void Aggiungi_Hndl(void);
        void Moltiplica_Hndl(void);
        void Nascondi_Hndl(void);
        void Mostratutti_Hndl(void);
        void Copia_Hndl(void);
        void Incolla_Hndl(void);
        virtual void enterEvent(QEvent *e);
        
    signals:
        void valueChanged(int row, int col);

    public slots:
        void selectCells(int sRow, int sCol, int eRow, int eCol);

    public :

        arnNumericMatrixViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        arnNumericMatrixViewer(int rows = 5, int cols = 5, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnNumericMatrixViewer(void);
        //virtual bool eventFilter(QObject* watched, QEvent* e);

        inline const Q3Table *matrix(void) {return pMatrix;}
        void setXValue(int col, double val);
        void setYValue(int row, double val);
        inline void setName(const char* name) {pName->setText(name);}
        inline void setComment(const char* cm) {pComment->setText(cm);}
        inline const char* comment(void) {return pComment->text();}
        inline void setPrec(unsigned char pc) {prec = pc;}
        inline void setPrecX(unsigned char pc) {precX = pc;}
        inline void setPrecY(unsigned char pc) {precY = pc;}

        virtual void setValue(int row, int col, double val);
        virtual QString text(int row, int col);
};

#endif
