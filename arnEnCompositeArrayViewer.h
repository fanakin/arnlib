/***************************************************************************
                          arnEnCompositeArrayViewer.h  -  description
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

#ifndef ArnEnCompositeArrayViewerH
#define ArnEnCompositeArrayViewerH

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qslider.h>
//#include <qtooltip.h>
//#include <qwhatsthis.h>
#include <Q3Table>
#include <QMenu>
#include <qaction.h>
#include <qclipboard.h>
#include "arnObjectViewer.h"
#include "arnGLArrayViewer.h"
#include "arnColorTableItem.h"

class arnEnCompositeArrayViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
		void init(int rows);
        QClipboard* pClip;
        int singlepointRow;
		NumericRepresentationFormat_t numFormatVal;
		NumericRepresentationFormat_t numFormatX;

    private slots:
        void doValueChange(int row, int col);
        void ArrayViewerButton_hndl(void);
        void Graph2DViewerButton_hndl(void);
        void Graph2DSelection_hndl(int start_row, int end_row);
        void YLineEditTextChange_hndl(const QString& text);
        
    protected:
        QLabel* pComment;
        QLabel* LXValLabel;
        QLabel* XValLabel;
        QLabel* LYValLabel;
        QLineEdit* YVallineEdit;
        QPushButton* ViewArrayButton;
        QPushButton* View2DGraphButton;

        QGridLayout* Form1Layout;
		QSplitter* mainsplitter;
		QGroupBox* gridGroupBox;
		QGridLayout* gridLayout;

        Q3Table *pArray;
        arnGLArrayViewer* pGLArray;

        QString name;
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
        QAction *defCChange;
        QAction *CChange;

        unsigned char prec,precX;
		//virtual void resizeEvent ( QResizeEvent * e );
		virtual void paintEvent ( QPaintEvent * event );
		virtual void contextMenuEvent ( QContextMenuEvent * e );
    protected slots:
        virtual void languageChange();
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
        void defCChange_Hndl(void);
        void CChange_Hndl(void);
        virtual void enterEvent(QEvent *e);
    signals:
        void valueChanged(int row, int col);
		void defColorChanged(const QColor&);
		void ColorChanged(int , int , const QColor&);
    public slots:
        void selectCells(int sRow, int eRow);
        
    public :

        arnEnCompositeArrayViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        arnEnCompositeArrayViewer(int rows = 5, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnEnCompositeArrayViewer(void);
        //virtual bool eventFilter(QObject* watched, QEvent* e);
        
		inline void setNumFormat(NumericRepresentationFormat_t nm) {numFormatVal = nm;}
		inline void setXNumFormat(NumericRepresentationFormat_t nm) {numFormatX = nm;}
		inline void setComment(const char* cm) {pComment->setText(cm);}
        inline const char* comment(void) {return pComment->text();}
        inline void setPrec(unsigned char pc) {prec = pc;}
        inline void setPrecX(unsigned char pc) {precX = pc;}

        void setXValue(int row, double val);
        inline const Q3Table *array(void) {return pArray;}
        virtual QString text(int row);
        virtual QString text(int row, int col);
        virtual void setValue(int row, double val);

        inline void setName(const char* Nm) {name = Nm;}//pArray->horizontalHeader()->setLabel(0, Name);
		inline void setName(const QString& nm) {name = nm;}
		inline QString Name(void) {return name;}
		inline void setXAxisCaption(const QString& xc) {if (pGLArray) pGLArray->setXAxisLabel(xc);}
		inline QString XAxisCaption(void) {if (pGLArray) return pGLArray->XAxisLabel(); else return QString("X");}
		inline void setYAxisCaption(const QString& yc) {if (pGLArray) pGLArray->setYAxisLabel(yc);}
		inline QString YAxisCaption(void) {if (pGLArray) return pGLArray->YAxisLabel(); else return QString("Y");}
		inline void setXMinScale(double val) {pGLArray->setXMinScale(val);}
		inline void setXMaxScale(double val) {pGLArray->setXMaxScale(val);}
		inline void setValueMinScale(double val) {pGLArray->setValueMinScale(val); }
		inline void setValueMaxScale(double val) {pGLArray->setValueMaxScale(val);}
		inline void setXAxisLabel(const QString& str) {pGLArray->setXAxisLabel(str);}
		inline void setYAxisLabel(const QString& str) {pGLArray->setYAxisLabel(str);}
		inline void setCaptionLabel(const QString& str) {pGLArray->setCaptionLabel(str);}
		inline void setArrayItemColor(int row, const QColor& c) {
			arnColorTableItem* pIt = (arnColorTableItem *)(pArray->item( row ,0));
			if (pIt) pIt->setColor(c);
			}
};

#endif
