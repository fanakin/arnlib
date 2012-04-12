/***************************************************************************
                          arnCompositeMatrixViewer.h  -  description
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

#ifndef ArnCompositeMatrixViewerH
#define ArnCompisiteMatrixViewerH

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qslider.h>
#include <QSplitter>
#include <qgroupbox.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
#include <Q3Table>
#include <QMenu>
#include <qaction.h>
#include <qclipboard.h>
#include "arnObjectViewer.h"
#include "arnGLMultipleArrayViewer.h"
#include "arnGLMatrixViewer.h"


class arnCompositeMatrixViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
		void init(int rows, int cols);
        QClipboard* pClip;
        int singlepointRow, singlepointCol;
		NumericRepresentationFormat_t numFormatVal;
		NumericRepresentationFormat_t numFormatX;
		NumericRepresentationFormat_t numFormatY;

    private slots:
        void doValueChange(int row, int col);
        void MatrixViewerButton_hndl(void);
        void Graph3DViewerButton_hndl(void);
        void Graph3DSelection_hndl(int start_row, int start_col,int end_row, int end_col);
        void ZLineEditTextChange_hndl(const QString& text);
        void SliceButton_hndl(void);
        void GraphSliceSelection_hndl(int start_row, int start_col,int end_row, int end_col);

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
        arnGLMatrixViewer* pGLMatrix;
        arnGLMultipleArrayViewer* pMultiVector;
        
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

        arnCompositeMatrixViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        arnCompositeMatrixViewer(int rows = 5, int cols = 5, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnCompositeMatrixViewer(void);
        //virtual bool eventFilter(QObject* watched, QEvent* e);

		inline void setNumFormat(NumericRepresentationFormat_t nm) {numFormatVal = nm;}
		inline void setXNumFormat(NumericRepresentationFormat_t nm) {numFormatX = nm;}
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

		inline void setYMinScale(double val) {pGLMatrix->setYMinScale(val); pMultiVector->setYMinScale(val);}
		inline void setYMaxScale(double val) {pGLMatrix->setYMaxScale(val); pMultiVector->setYMaxScale(val);}
		inline void setXMinScale(double val) {pGLMatrix->setXMinScale(val); pMultiVector->setXMinScale(val);}
		inline void setXMaxScale(double val) {pGLMatrix->setXMaxScale(val); pMultiVector->setXMaxScale(val);}
		inline void setValueMinScale(double val) {pGLMatrix->setValueMinScale(val); pMultiVector->setValueMinScale(val);/*arnDebug("scaleZMinValue:%f",val);*/}
		inline void setValueMaxScale(double val) {pGLMatrix->setValueMaxScale(val); pMultiVector->setValueMaxScale(val);/*arnDebug("scaleZMaxValue:%f",val);*/}
		inline void setXAxisCaption(const QString& str) {pGLMatrix->setXAxisLabel(str);}
		inline void setYAxisCaption(const QString& str) {pGLMatrix->setYAxisLabel(str);}
		inline void setZAxisCaption(const QString& str) {pGLMatrix->setZAxisLabel(str);}
		inline void setCaptionLabel(const QString& str) {pGLMatrix->setCaptionLabel(str);}
		inline QString XAxisCaption(void) {return pGLMatrix->XAxisLabel();}
		inline QString YAxisCaption(void) {return pGLMatrix->YAxisLabel();}
		inline QString ZAxisCaption(void) {return pGLMatrix->ZAxisLabel();}
		inline QString CaptionLabel(void) {return pGLMatrix->CaptionLabel();}
};

#endif
