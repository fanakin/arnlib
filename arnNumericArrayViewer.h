/***************************************************************************
                          arnNumericArrayViewer.h  -  description
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

#ifndef ArnNumericArrayViewerH
#define ArnNumericArrayViewerH

#include <qlabel.h>
#include <Q3Table>
#include <qlayout.h>
#include <QMenu>
#include <qaction.h>
#include <qclipboard.h>
#include "arnlibtypes.h"
#include "arnObjectViewer.h"

class arnNumericArrayViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
        QClipboard* pClip;
		NumericRepresentationFormat_t numFormatVal;
		NumericRepresentationFormat_t numFormatX;
	private slots:
        void doValueChange(int row, int col);
        
    protected:
        QVBoxLayout *pMainLayout;
        QLabel *pComment;
        Q3Table *pArray;

        QMenu *pPopUp;
        //QAction *SelezionaTutto;
        QAction *Inizializza;
        QAction *Interpola;
        QAction *Azzera;
        QAction *Aggiungi;
        QAction *Moltiplica;
        QAction *Nascondi;
        QAction *Mostratutti;
        QAction *Copia;
        QAction *Incolla;

        unsigned char prec,precX;
		virtual void contextMenuEvent ( QContextMenuEvent * e );

    protected slots:
        //void SelezionaTutto_Hndl(void);
        void Inizializza_Hndl(void);
        void Interpola_Hndl(void);
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
        void selectCells(int sRow, int eRow);
        
    public :

        arnNumericArrayViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        arnNumericArrayViewer(int rows = 5, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnNumericArrayViewer(void);
        //virtual bool eventFilter(QObject* watched, QEvent* e);
		inline void setNumFormat(NumericRepresentationFormat_t nm) {numFormatVal = nm;}
		inline void setXNumFormat(NumericRepresentationFormat_t nm) {numFormatX = nm;}
		void setName(const char* Name) {
            pArray->horizontalHeader()->setLabel(0, Name);
            }
        inline void setComment(const char* cm) {pComment->setText(cm);}
        inline const char* comment(void) {return pComment->text();}
        inline void setPrec(unsigned char pc) {prec = pc;}
        inline void setPrecX(unsigned char pc) {precX = pc;}

        void setXValue(int row, double val);
        inline const Q3Table *array(void) {return pArray;}
        virtual QString text(int row);
        virtual QString text(int row, int col);
        virtual void setValue(int row, double val);
};

#endif
