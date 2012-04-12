/***************************************************************************
                          arnBitValueMatrixViewer.h  -  description
                             -------------------
    begin                : lun mag 26 2008
    copyright            : (C) 2008 by Aurion s.r.l.
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

#ifndef ArnBitValueMatrixViewerH
#define ArnBitValueMatrixViewerH

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qslider.h>
#include <QSplitter>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
#include <Q3Table>
#include <QMenu>
#include <qaction.h>
#include <qclipboard.h>
#include "arnObjectViewer.h"
#include "arnGLArrayViewer.h"
#include "arnGLMatrixViewer.h"


class arnBitValueMatrixViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
        QClipboard* pClip;
        int singlepointRow, singlepointCol;
		void init(int rows, int cols);
		NumericRepresentationFormat_t numFormatVal;
		NumericRepresentationFormat_t numFormatY;
    private slots:
        void doValueChange(int row, int col);
        void MatrixViewerButton_hndl(void);
        void Graph3DViewerButton_hndl(void);
        void Graph3DSelection_hndl(int start_row, int end_row);
        void ZLineEditTextChange_hndl(const QString& text);
        void SliceButton_hndl(void);
        void GraphSliceSelection_hndl(int start_row, int end_row);
		void selectionChangedHndl(void);
    protected:
        QTextEdit* pComment;
        QLabel* LXValLabel;
        QLabel* XValLabel;
        QLabel* LYValLabel;
        QLabel* YValLabel;
        QLabel* LZValLabel;
        QLineEdit* ZVallineEdit;
        QPushButton* ViewMatrixButton;
        QPushButton* View3DGraphButton;
        QPushButton* ViewSliceButton;

		QGridLayout* Form1Layout;
		QSplitter* mainsplitter;
		QGroupBox* gridGroupBox;
		QGridLayout* gridLayout;

        Q3Table *pMatrix;
        arnGLArrayViewer* pVector;

        QString Name;
        
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

        signed char prec,precX,precY;
		//virtual void resizeEvent ( QResizeEvent * e );
		//virtual void paintEvent ( QPaintEvent * event );
		virtual void contextMenuEvent ( QContextMenuEvent * e );
		
	protected slots:
        virtual void languageChange();
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
		void adjustRows(void);
		void adjustCols(void);

    public :

        arnBitValueMatrixViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        arnBitValueMatrixViewer(int rows = 5, int cols = 5, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnBitValueMatrixViewer(void);
        //virtual bool eventFilter(QObject* watched, QEvent* e);

		inline void setNumFormat(NumericRepresentationFormat_t nm) {numFormatVal = nm;}
		inline void setYNumFormat(NumericRepresentationFormat_t nm) {numFormatY = nm;}

        inline const Q3Table *matrix(void) {return pMatrix;}
        void setXValue(int col, double val);
        void setYValue(int row, double val);
        inline void setName(const char* name) {Name = name;}
        inline void setComment(const char* cm) {pComment->setText(cm);}
        inline const char* comment(void) {return pComment->text();}
        inline void setPrec(signed char pc) {prec = pc;}
        inline void setPrecX(signed char pc) {precX = pc;}
        inline void setPrecY(signed char pc) {precY = pc;}

        virtual void setValue(int row, int col, double val);
        virtual QString text(int row, int col);

		inline void setYMinScale(double ) {}
		inline void setYMaxScale(double ) {}
		inline void setXMinScale(double ) {}
		inline void setXMaxScale(double ) {}
		inline void setValueMinScale(double ) {}
		inline void setValueMaxScale(double ) {}
		inline void setXAxisCaption(const QString& ) {}
		inline void setYAxisCaption(const QString& ) {}
		inline void setZAxisCaption(const QString& ) {}
		inline void setCaptionLabel(const QString& ) {}
		inline QString XAxisCaption(void) {return QString("");}
		inline QString YAxisCaption(void) {return QString("");}
		inline QString ZAxisCaption(void) {return QString("");}
		inline QString CaptionLabel(void) {return QString("");}
};

#endif
