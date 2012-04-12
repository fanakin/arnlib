/***************************************************************************
                          arnEnCompositeMatrixViewer.h  -  description
                             -------------------
    begin                : mar giu 28 2005
    copyright            : (C) 2005 by Aurion s.r.l.
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

#ifndef ArnEnCompositeMatrixViewerH
#define ArnEnCompisiteMatrixViewerH

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtextedit.h>
#include <qlineedit.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qslider.h>
#include <qsplitter.h>
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
#include "arnColorTableItem.h"

class myQ3Table : public Q3Table
{
	Q_OBJECT
	protected:
	virtual void keyPressEvent ( QKeyEvent * event );

	public:
		myQ3Table ( QWidget * w, const char * p);
		myQ3Table ( int o, int u, QWidget * w, const char * p);
		~myQ3Table (void);
};


class arnEnCompositeMatrixViewer : public arnObjectViewer
{
    Q_OBJECT

    private:
		void init(int rows, int cols);
        QClipboard* pClip;
        int singlepointRow, singlepointCol;
		int traceUpdateRow, traceUpdateCol;
		QColor prevCellColor;
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

        myQ3Table *pMatrix;
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
        QAction *defCChange;
        QAction *CChange;

        signed char prec,precX,precY;
		//virtual void resizeEvent ( QResizeEvent * e );
		//virtual void paintEvent ( QPaintEvent * event );
		virtual void contextMenuEvent ( QContextMenuEvent * e );
		virtual void keyPressEvent(QKeyEvent*);
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
        void defCChange_Hndl(void);
        void CChange_Hndl(void);
        virtual void enterEvent(QEvent *e);
        
    signals:
        void valueChanged(int row, int col);
		void defColorChanged(const QColor&);
		void ColorChanged(int , int , const QColor&);

    public slots:
        void selectCells(int sRow, int sCol, int eRow, int eCol);
		inline void TraceColorUpdate(int row, int col, const QColor& c) {
			if (pMatrix && pMatrix->isEnabled()) {
				if (traceUpdateRow != row || traceUpdateCol != col) { // spostamento del quadrato blu
					if ((traceUpdateRow != -1) && (traceUpdateCol != -1)) {
						setMatrixItemColor(traceUpdateRow,traceUpdateCol,prevCellColor);
						pMatrix->updateCell(traceUpdateRow,traceUpdateCol);
/*						arnDebug("row=%d,col=%d",row,col);
						arnDebug("r=%d,g=%d,b=%d",prevCellColor.red(),prevCellColor.green(),prevCellColor.blue());*/
						}
/*					arnDebug("row=%d,col=%d",row,col);
					arnDebug("r=%d,g=%d,b=%d",c.red(),c.green(),c.blue());*/
					setMatrixItemColor(row,col,QColor("blue")); // !!!! sequenza settaggio colori obbligata
					prevCellColor = c;	// per poter controllare sia il set con scarra spazio che il default behaviour
					traceUpdateRow = row;
					traceUpdateCol = col;
					}
				}
			//BEGIN test on 3D
			if (pGLMatrix && pGLMatrix->isEnabled()) {
				pGLMatrix->updateTrace(row,col);
				}
			//END test on 3D
			}
		void adjustRows(void);
		void adjustCols(void);
		inline void setPrec(unsigned char prc) {prec = prc;}
		inline void setMatrixItemColor(int row, int col, const QColor& c) {
			arnColorTableItem* pIt = (arnColorTableItem *)(pMatrix->item( row, col ));
			if (pIt) {
				prevCellColor = c;
				pIt->setColor(c);
				}
			pMatrix->updateCell(row,col);
			}
        inline QColor MatrixItemColor(int row, int col) {
			arnColorTableItem* pIt = (arnColorTableItem *)(pMatrix->item( row, col ));
			if (pIt) return pIt->Color();
			else return QColor("white");
			}
        inline void _setValue(int row, int col, double val) {setValue(row, col, val);}
    public :

        arnEnCompositeMatrixViewer(QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        arnEnCompositeMatrixViewer(int rows = 5, int cols = 5, QWidget *parent = 0, const char *name = 0, Qt::WFlags f = 0);
        ~arnEnCompositeMatrixViewer(void);
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
		inline void setValueMinScale(double val) {pGLMatrix->setValueMinScale(val); pMultiVector->setValueMinScale(val);}
		inline void setValueMaxScale(double val) {pGLMatrix->setValueMaxScale(val); pMultiVector->setValueMaxScale(val);}
		inline void setXAxisCaption(const QString& str) {pGLMatrix->setXAxisLabel(str);}
		inline void setYAxisCaption(const QString& str) {pGLMatrix->setYAxisLabel(str);}
		inline void setZAxisCaption(const QString& str) {pGLMatrix->setZAxisLabel(str);}
		inline void setCaptionLabel(const QString& str) {pGLMatrix->setCaptionLabel(str);}
		inline QString XAxisCaption(void) {return pGLMatrix->XAxisLabel();}
		inline QString YAxisCaption(void) {return pGLMatrix->YAxisLabel();}
		inline QString ZAxisCaption(void) {return pGLMatrix->ZAxisLabel();}
		inline QString CaptionLabel(void) {return pGLMatrix->CaptionLabel();}
		inline void updatePrevCellColor( const QColor& c) {prevCellColor = c;}
};

#endif
