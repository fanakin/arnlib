/***************************************************************************
                          arnNumericMatrixViewer.cpp  -  description
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

#include <qapplication.h>
#include <qcursor.h>
#include <qinputdialog.h>
#include <qstringlist.h>
#include "CommonFunctions.h"
#include "arnCompositeMatrixViewer.h"
#include <QContextMenuEvent>

void arnCompositeMatrixViewer::init(int rows, int cols)
{
    tpy = avt_CompositeMatrixViewer;
	numFormatVal = nrf_dec;
	numFormatX = nrf_dec;
	numFormatY = nrf_dec;

    singlepointRow = singlepointCol = -1;
    Form1Layout = new QGridLayout( this, 1, 1, 11, 6, "Form1Layout");

	mainsplitter = new QSplitter (Qt::Vertical, this, "mainsplitter");
	if (!mainsplitter) arnCriticalExit();

    pMatrix = new Q3Table(rows,cols,this,"Matrix");
    if (!pMatrix) arnCriticalExit();
    pMatrix->setVScrollBarMode( Q3ScrollView::Auto );
    pMatrix->setHScrollBarMode( Q3ScrollView::Auto );
    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pMatrix, SIGNAL(valueChanged(int, int)), this, SLOT(doValueChange(int, int)));
    mainsplitter->addWidget( pMatrix );

    pGLMatrix = new arnGLMatrixViewer(cols, rows, arn_glTPM_MASHED_SURFACE, this, "GLMatrix"); // row, col
    if (!pGLMatrix) arnCriticalExit();
	connect(pGLMatrix->matrix(), SIGNAL(selectionChanged(int, int, int, int)),this , SLOT(Graph3DSelection_hndl(int, int, int, int)));
    mainsplitter->addWidget( pGLMatrix );
	
	pMultiVector = new arnGLMultipleArrayViewer(rows,cols,arn_glAPM_MASHED_LINES, this, "multiGLArray");
	if (!pMultiVector) arnCriticalExit();
	connect(pMultiVector->array(), SIGNAL(selectionChanged(int, int, int, int)),this , SLOT(GraphSliceSelection_hndl(int, int, int, int)));
    mainsplitter->addWidget( pMultiVector );

	gridGroupBox = new QGroupBox("");
	if (!gridGroupBox) arnCriticalExit();

	gridLayout = new QGridLayout;
	if (!gridLayout) arnCriticalExit();
	 
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
	gridLayout->addWidget(pComment,0,0,4,1);


    LXValLabel = new QLabel( this, "LXValLabel" );
    if (!LXValLabel) arnCriticalExit();
	gridLayout->addWidget(LXValLabel,1,1);

    XValLabel = new QLabel( this, "XValLabel" );
    if (!XValLabel) arnCriticalExit();
	gridLayout->addWidget(XValLabel,1,2);

    LYValLabel = new QLabel( this, "LYValLabel" );
    if (!LYValLabel) arnCriticalExit();
	gridLayout->addWidget(LYValLabel,2,1);

    YValLabel = new QLabel( this, "YValLabel" );
    if (!YValLabel) arnCriticalExit();
	gridLayout->addWidget(YValLabel,2,2);

    LZValLabel = new QLabel( this, "LZValLabel" );
    if (!LZValLabel) arnCriticalExit();
	gridLayout->addWidget(LZValLabel,3,1);

    ZVallineEdit = new QLineEdit( this, "ZVallineEdit" );
    if (!ZVallineEdit) arnCriticalExit();
	gridLayout->addWidget(ZVallineEdit,3,2);
    connect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));

    ViewMatrixButton = new QPushButton( this, "ViewMatrixButton" );
    if (!ViewMatrixButton) arnCriticalExit();
	gridLayout->addWidget(ViewMatrixButton,1,3);
    connect(ViewMatrixButton, SIGNAL(clicked()), this, SLOT(MatrixViewerButton_hndl(void)));
    
    View3DGraphButton = new QPushButton( this, "View3DGraphButton" );
    if (!View3DGraphButton) arnCriticalExit();
	gridLayout->addWidget(View3DGraphButton,2,3);
    connect(View3DGraphButton, SIGNAL(clicked()), this, SLOT(Graph3DViewerButton_hndl(void)));

    ViewSliceButton = new QPushButton( this, "ViewSliceButton" );
    if (!ViewSliceButton) arnCriticalExit();
	gridLayout->addWidget(ViewSliceButton,3,3);
	connect(ViewSliceButton,SIGNAL(clicked()), this, SLOT(SliceButton_hndl(void)));
	
	gridGroupBox->setLayout(gridLayout);
	mainsplitter->addWidget(gridGroupBox);

    Form1Layout->addWidget( mainsplitter, 0, 0 );
    languageChange();
    resize( QSize(516, 455).expandedTo(minimumSizeHint()) );



    // parte in sviluppo
    pPopUp = new QMenu(this);
    if (!pPopUp) arnCriticalExit();

//    SelezionaTutto = new QAction( this, "SelezionaTutto");
//    if (!SelezionaTutto) arnCriticalExit();
//    SelezionaTutto->setText( trUtf8("Seleziona Tutto"));
//    SelezionaTutto->setMenuText( trUtf8("Seleziona Tutto"));
//    SelezionaTutto->setToolTip( trUtf8("seleziona tutte le caselle della tabella"));

    Inizializza = new QAction( this, "Inizializza");
    if (!Inizializza) arnCriticalExit();
    Inizializza->setText( trUtf8("Inizializza"));
    Inizializza->setMenuText( trUtf8("Inizializza"));
    Inizializza->setToolTip( trUtf8("Inizializza le caselle selezionate."));

    Interpola = new QAction( this, "Interpola");
    if (!Interpola) arnCriticalExit();
    Interpola->setText( trUtf8("Interpola"));
    Interpola->setMenuText( trUtf8("Interpola"));
    Interpola->setToolTip( trUtf8("Interpola le caselle selezionate."));

    InterpolaX = new QAction( this, "InterpolaX");
    if (!InterpolaX) arnCriticalExit();
    InterpolaX->setText( trUtf8("InterpolaX"));
    InterpolaX->setMenuText( trUtf8("InterpolaX"));
    InterpolaX->setToolTip( trUtf8("Interpola le caselle selezionate lungo le righe."));

    InterpolaY = new QAction( this, "InterpolaY");
    if (!InterpolaY) arnCriticalExit();
    InterpolaY->setText( trUtf8("InterpolaY"));
    InterpolaY->setMenuText( trUtf8("InterpolaY"));
    InterpolaY->setToolTip( trUtf8("Interpola le caselle selezionate lungo colonne."));

    Azzera = new QAction( this, "Azzera");
    if (!Azzera) arnCriticalExit();
    Azzera->setText( trUtf8("Azzera"));
    Azzera->setMenuText( trUtf8("Azzera"));
    Azzera->setToolTip( trUtf8("Azzera le caselle selezionate."));

    Aggiungi = new QAction( this, "Aggiungi");
    if (!Aggiungi) arnCriticalExit();
    Aggiungi->setText( trUtf8("Aggiungi"));
    Aggiungi->setMenuText( trUtf8("Aggiungi"));
    Aggiungi->setToolTip( trUtf8("Aggiungi alle caselle selezionate."));

    Moltiplica = new QAction( this, "Moltiplica");
    if (!Moltiplica) arnCriticalExit();
    Moltiplica->setText( trUtf8("Moltiplica"));
    Moltiplica->setMenuText( trUtf8("Moltiplica"));
    Moltiplica->setToolTip( trUtf8("Moltiplica alle caselle selezionate."));

    Nascondi = new QAction( this, "Nascondi");
    if (!Nascondi) arnCriticalExit();
    Nascondi->setText( trUtf8("Nascondi"));
    Nascondi->setMenuText( trUtf8("Nascondi"));
    Nascondi->setToolTip( trUtf8("Nasconde le caselle selezionate."));

    Mostratutti = new QAction( this, "Mostratutti");
    if (!Mostratutti) arnCriticalExit();
    Mostratutti->setText( trUtf8("Mostra Tutti"));
    Mostratutti->setMenuText( trUtf8("Mostra Tutti"));
    Mostratutti->setToolTip( trUtf8("Mostra tutte le caselle."));

    Copia = new QAction( this, "Copia");
    if (!Copia) arnCriticalExit();
    Copia->setText( trUtf8("Copia"));
    Copia->setMenuText( trUtf8("Copia"));
    Copia->setToolTip( trUtf8("Copia la parte selezionata della matrice."));

    Incolla = new QAction( this, "Incolla");
    if (!Incolla) arnCriticalExit();
    Incolla->setText( trUtf8("Incolla"));
    Incolla->setMenuText( trUtf8("Incolla"));
    Incolla->setToolTip( trUtf8("Incolla la parte selezionata della matrice."));

    // connessione actions
//    connect( SelezionaTutto, SIGNAL( activated() ), this, SLOT( SelezionaTutto_Hndl() ) );
    connect( Inizializza, SIGNAL( activated() ), this, SLOT( Inizializza_Hndl() ) );
    connect( Interpola, SIGNAL( activated() ), this, SLOT( Interpola_Hndl() ) );
    connect( InterpolaX, SIGNAL( activated() ), this, SLOT( InterpolaX_Hndl() ) );
    connect( InterpolaY, SIGNAL( activated() ), this, SLOT( InterpolaY_Hndl() ) );
    connect( Azzera, SIGNAL( activated() ), this, SLOT( Azzera_Hndl() ) );
    connect( Aggiungi, SIGNAL( activated() ), this, SLOT( Aggiungi_Hndl() ) );
    connect( Moltiplica, SIGNAL( activated() ), this, SLOT( Moltiplica_Hndl() ) );
    connect( Nascondi, SIGNAL( activated() ), this, SLOT( Nascondi_Hndl() ) );
    connect( Mostratutti, SIGNAL( activated() ), this, SLOT( Mostratutti_Hndl() ) );
    connect( Copia, SIGNAL( activated() ), this, SLOT( Copia_Hndl() ) );
    connect( Incolla, SIGNAL( activated() ), this, SLOT( Incolla_Hndl() ) );

    // aggiunta popup
//    SelezionaTutto->addTo(pPopUp);
    Inizializza->addTo(pPopUp);
    Interpola->addTo(pPopUp);
    InterpolaX->addTo(pPopUp);
    InterpolaY->addTo(pPopUp);
    Azzera->addTo(pPopUp);
    Aggiungi->addTo(pPopUp);
    Moltiplica->addTo(pPopUp);
    Nascondi->addTo(pPopUp);
    Mostratutti->addTo(pPopUp);
    Copia->addTo(pPopUp);
    Incolla->addTo(pPopUp);

    prec = precX = precY = -1;

    pClip = QApplication::clipboard();
    if (!pClip) arnCriticalExit();

	setGeometry(50,50,400,400);

	LXValLabel->hide();
	XValLabel->hide();
	LYValLabel->hide();
	YValLabel->hide();
	LZValLabel->hide();
	ZVallineEdit->hide();
	
	pGLMatrix->setEnabled(false);
	pGLMatrix->hide();
	pMultiVector->setEnabled(false);
	pMultiVector->hide();
    pMatrix->show();

}

arnCompositeMatrixViewer::arnCompositeMatrixViewer(int rows, int cols, QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
	init(rows,cols);
}
    
arnCompositeMatrixViewer::arnCompositeMatrixViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
	init(5,5);
}

arnCompositeMatrixViewer::~arnCompositeMatrixViewer(void)
{

}

void arnCompositeMatrixViewer::setXValue(int col, double val)
{
	if (precX == -1) {
		switch (numFormatX) {
			case nrf_hex:
				if (pMatrix) pMatrix->horizontalHeader()->setLabel(col,QString::number((int)val, 16).toUpper());
			break;
			case nrf_bin:
				if (pMatrix) pMatrix->horizontalHeader()->setLabel(col,QString::number((int)val, 2));
			break;
			case nrf_dec:
			default:
				if (pMatrix) pMatrix->horizontalHeader()->setLabel(col,QString::number(val));
			break;
		}
	}
	else {
		switch (numFormatX) {
			case nrf_hex:
				if (pMatrix) pMatrix->horizontalHeader()->setLabel(col,QString::number((int)val, 16).toUpper());
			break;
			case nrf_bin:
				if (pMatrix) pMatrix->horizontalHeader()->setLabel(col,QString::number((int)val, 2));
			break;
			case nrf_dec:
			default:
				if (pMatrix) pMatrix->horizontalHeader()->setLabel(col,QString::number(val,'f',precX));
			break;
		}
	}
	if (pGLMatrix) pGLMatrix->setXValue(col,val);
	if (pMultiVector) pMultiVector->setXValue(col,val);
}

void arnCompositeMatrixViewer::setYValue(int row, double val)
{
	if (precY == -1) {
		switch (numFormatY) {
			case nrf_hex:
				if (pMatrix) pMatrix->verticalHeader()->setLabel(row,QString::number((int)val, 16).toUpper());
			break;
			case nrf_bin:
				if (pMatrix) pMatrix->verticalHeader()->setLabel(row,QString::number((int)val, 2));
			break;
			case nrf_dec:
			default:
				if (pMatrix) pMatrix->verticalHeader()->setLabel(row,QString::number(val));
			break;
		}
	}
	else {
		switch (numFormatY) {
			case nrf_hex:
				if (pMatrix) pMatrix->verticalHeader()->setLabel(row,QString::number((int)val, 16).toUpper());
			break;
			case nrf_bin:
				if (pMatrix) pMatrix->verticalHeader()->setLabel(row,QString::number((int)val, 2));
			break;
			case nrf_dec:
			default:
				if (pMatrix) pMatrix->verticalHeader()->setLabel(row,QString::number(val,'f',precY));
			break;
		}
	}
	if (pGLMatrix) pGLMatrix->setYValue(row,val);
	if (pMultiVector) pMultiVector->setYValue(row,val);
}

void arnCompositeMatrixViewer::setValue(int row, int col, double val)
{
   if (prec == -1) {
		switch (numFormatVal) {
			case nrf_hex:
				if (pMatrix) pMatrix->setText(row,col,QString::number((int)val, 16).toUpper());
			break;
			case nrf_bin:
				if (pMatrix) pMatrix->setText(row,col,QString::number((int)val, 2));
			break;
			case nrf_dec:
			default:
				if (pMatrix) pMatrix->setText(row,col,QString::number(val));
			break;
		}
	}
	else {
		switch (numFormatVal) {
			case nrf_hex:
				if (pMatrix) pMatrix->setText(row,col,QString::number((int)val, 16).toUpper());
			break;
			case nrf_bin:
				if (pMatrix) pMatrix->setText(row,col,QString::number((int)val, 2));
			break;
			case nrf_dec:
			default:
				if (pMatrix) pMatrix->setText(row,col,QString::number(val,'f',prec));
			break;
		}
	}
	doValueChange(row,col);
}

QString arnCompositeMatrixViewer::text(int row, int col)
{
    QString ts;
    ts = pMatrix->text(row,col);
    return ts;
}

void arnCompositeMatrixViewer::contextMenuEvent ( QContextMenuEvent * e )
{
//arnDebug("Entrato\n");
	pPopUp->exec(QCursor::pos());
	e->accept();
}

// bool arnCompositeMatrixViewer::eventFilter(QObject* watched, QEvent* e)
// {
//     if (e->type() == QEvent::ContextMenu) {
//         pPopUp->exec(QCursor::pos());
//         return true;
//         }
//     return arnObjectViewer::eventFilter(watched, e);
// }

//void arnNumericMatrixViewer::SelezionaTutto_Hndl(void)
//{
//    pMatrix->clearSelection();
//}

void arnCompositeMatrixViewer::Inizializza_Hndl(void)
{
    bool ok = false;
    double res = QInputDialog::getDouble(
        tr( "Inizializza" ),
        tr( "Inserisci Numero." ),
        0, -2147483647, 2147483647, prec + 3, &ok, this, "InizializeValueBox" );
    if ( ok ) { // user entered something and pressed OK
        for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
            Q3TableSelection sel = pMatrix->selection(indxSel);
            for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
                for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
                    if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
                        setValue(indR,indC,res);
                        }
                    }
                }
            }
        }
	else {;}// user pressed Cancel

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::Interpola_Hndl(void)
{
    for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
        Q3TableSelection sel = pMatrix->selection(indxSel);
        double valP1 = pMatrix->text(sel.topRow(),sel.leftCol()).toDouble();
        double valP2 = pMatrix->text(sel.topRow(),sel.rightCol()).toDouble();
        double valP3 = pMatrix->text(sel.bottomRow(),sel.leftCol()).toDouble();
        double valP4 = pMatrix->text(sel.bottomRow(),sel.rightCol()).toDouble();
        double step,start;
        step = (valP2 - valP1) / (sel.rightCol() - sel.leftCol());
        start = valP1;
        for (int indC = sel.leftCol() + 1; indC < sel.rightCol(); indC++) {
            start += step;
            setValue(sel.topRow(),indC,start);
            }

        step = (valP4 - valP2) / (sel.bottomRow() - sel.topRow());
        start = valP2;
        for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++)  {
            start += step;
            setValue(indR,sel.rightCol(),start);
            }
        
        step = (valP4 - valP3) / (sel.rightCol() - sel.leftCol());
        start = valP3;
        for (int indC = sel.leftCol() + 1; indC < sel.rightCol(); indC++) {
            start += step;
            setValue(sel.bottomRow(),indC,start);
            }

        step = (valP3 - valP1) / (sel.bottomRow() - sel.topRow());
        start = valP1;
        for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++)  {
            start += step;
            setValue(indR,sel.leftCol(),start);
            }

        for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++) {
            double valP1= pMatrix->text(indR,sel.leftCol()).toDouble();
            double valP2 = pMatrix->text(indR,sel.rightCol()).toDouble();
            double step = (valP2 - valP1) / (sel.rightCol() - sel.leftCol());
            for (int indC = sel.leftCol() + 1; indC < sel.rightCol(); indC++) {
                valP1 += step;
                setValue(indR,indC,valP1);
                }
            }
        }

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::InterpolaX_Hndl(void)
{
    for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
        Q3TableSelection sel = pMatrix->selection(indxSel);
        for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
            double valP1= pMatrix->text(indR,sel.leftCol()).toDouble();
            double valP2 = pMatrix->text(indR,sel.rightCol()).toDouble();
            double step = (valP2 - valP1) / (sel.rightCol() - sel.leftCol());
            for (int indC = sel.leftCol() + 1; indC < sel.rightCol(); indC++) {
                valP1 += step;
                setValue(indR,indC,valP1);
                }
            }
        }

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::InterpolaY_Hndl(void)
{
    for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
        Q3TableSelection sel = pMatrix->selection(indxSel);
        for (int indC = sel.leftCol() ; indC <= sel.rightCol(); indC++) {
            double valP1= pMatrix->text(sel.topRow(),indC).toDouble();
            double valP2 = pMatrix->text(sel.bottomRow(),indC).toDouble();
            double step = (valP2 - valP1) / (sel.bottomRow() - sel.topRow());
            for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++) {
                valP1 += step;
                setValue(indR,indC,valP1);
                }
            }
        }

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::Azzera_Hndl(void)
{
    for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
        Q3TableSelection sel = pMatrix->selection(indxSel);
        for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
            for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
                if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
                    setValue(indR,indC,0);
                    }
                }
            }
        }

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::Aggiungi_Hndl(void)
{
    bool ok = false;
    double res = QInputDialog::getDouble(
        tr( "Aggiungi" ),
        tr( "Inserisci Numero." ),
        0, -2147483647, 2147483647, prec + 3, &ok, this, "InizializeValueBox" );
    if ( ok ) { // user entered something and pressed OK
        for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
            Q3TableSelection sel = pMatrix->selection(indxSel);
            for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
                for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
                    if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
                        double val = pMatrix->text(indR,indC).toDouble();
                        val += res;
                        setValue(indR,indC,val);
                        }
                    }
                }
            }
        }
	else {;}// user pressed Cancel

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::Moltiplica_Hndl(void)
{
    bool ok = false;
    double res = QInputDialog::getDouble(
        tr( "Aggiungi" ),
        tr( "Inserisci Numero." ),
        0, -2147483647, 2147483647, prec + 3, &ok, this, "InizializeValueBox" );
    if ( ok ) { // user entered something and pressed OK
        for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
            Q3TableSelection sel = pMatrix->selection(indxSel);
            for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
                for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
                    if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
                        double val = pMatrix->text(indR,indC).toDouble();
                        val *= res;
                        setValue(indR,indC,val);
                        }
                    }
                }
            }
        }
	else {;}// user pressed Cancel

    pMatrix->clearSelection();
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::Nascondi_Hndl(void)
{
    for (int indC = 0; indC < pMatrix->numCols(); indC++) {
        if (pMatrix->isColumnSelected(indC,true)) 
            pMatrix->hideColumn(indC);
        }

    for (int indR = 0; indR < pMatrix->numRows(); indR++)  {
        if (pMatrix->isRowSelected(indR,true))
            pMatrix->hideRow(indR);
        }

    pMatrix->clearSelection();
}

void arnCompositeMatrixViewer::Mostratutti_Hndl(void)
{
    for (int indR = 0; indR < pMatrix->numRows(); indR++) pMatrix->showRow(indR);
    for (int indC = 0; indC < pMatrix->numCols(); indC++) pMatrix->showColumn(indC);

    pMatrix->clearSelection();
}

void arnCompositeMatrixViewer::Copia_Hndl(void)
{
	QString aTxt("MATRIX\n");
	int minR, minC;
	minR = pMatrix->numRows();
	minC = pMatrix->numCols();
	for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
		Q3TableSelection sel = pMatrix->selection(indxSel);
		for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
			for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
				if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
					if (indR < minR) minR = indR;
					if (indC < minC) minC = indC;
					}
				}
			}
		}
	for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
		Q3TableSelection sel = pMatrix->selection(indxSel);
		for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
			for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
				if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
					QString r,c;
					r.setNum(indR - minR);
					c.setNum(indC - minC);
					aTxt += r; aTxt += ",";
					aTxt += c; aTxt += ",";
					aTxt += pMatrix->text(indR,indC);
					aTxt += "\n";
					}
				}
			}
		}

	if (pClip) {
		if (pClip->supportsSelection()) {
			//pClip->clear(QClipboard::Clipboard);
			//pClip->clear(QClipboard::Selection);
			pClip->setText( aTxt, QClipboard::Selection);
			pMatrix->clearSelection();
			Incolla->setEnabled(true);
			}
		else {
			//pClip->clear(QClipboard::Clipboard);
			//pClip->clear(QClipboard::Selection);
			pClip->setText( aTxt, QClipboard::Clipboard);
			pMatrix->clearSelection();
			Incolla->setEnabled(true);
			}
		}
}

void arnCompositeMatrixViewer::Incolla_Hndl(void)
{
	if (pClip) {
		if (pClip->supportsSelection()) {
			QString tmpS(pClip->text(QClipboard::Selection));
			int pos = tmpS.find("MATRIX");
			if ((pos == -1) || (pos > 0)) return;
			int rOff,cOff;
			rOff = pMatrix->currentRow();
			cOff = pMatrix->currentColumn();
			QStringList strList = QStringList::split("\n", tmpS );
			for (int indx = 1; indx < int(strList.count()); indx++)  {
				QStringList line = QStringList::split(",", strList[indx] );
				int indR,indC;
				indR = rOff + line[0].toInt();
				indC = cOff + line[1].toInt();
				QString st(line[2]);
				setValue(indR,indC,st.toDouble());
				}
			}
		else {
			QString tmpS(pClip->text(QClipboard::Clipboard));
			int pos = tmpS.find("MATRIX");
			if ((pos == -1) || (pos > 0)) return;
			int rOff,cOff;
			rOff = pMatrix->currentRow();
			cOff = pMatrix->currentColumn();
			QStringList strList = QStringList::split("\n", tmpS );
			for (int indx = 1; indx < int(strList.count()); indx++)  {
				QStringList line = QStringList::split(",", strList[indx] );
				int indR,indC;
				indR = rOff + line[0].toInt();
				indC = cOff + line[1].toInt();
				QString st(line[2]);
				setValue(indR,indC,st.toDouble());
				}
			}
		}
    if (pGLMatrix) pGLMatrix->invalidate();
}

void arnCompositeMatrixViewer::selectCells(int sRow, int sCol, int eRow, int eCol)
{
//	Q3TableSelection sel;
//	sel.init(sRow,1);
//	sel.expandTo(eRow,1);
//	pArray->addSelection(sel);
	int scrRCalstep,scrCCalstep, tmp;
	pMatrix->clearSelection();
	if (sRow > eRow) {tmp = sRow; sRow = eRow; eRow = tmp;}
	if (sCol > eCol) {tmp = sCol; sCol = eCol; eCol = tmp;}
	if ((sRow == eRow) && (sCol == eCol)) {
		for (int rinx = sRow; rinx < eRow + 1; rinx++) {
			pMatrix->selectRow(rinx);
			}
		for (int cinx = sCol; cinx < eCol + 1; cinx++) {
			pMatrix->selectColumn(cinx);
			}
		}
	else {
		pMatrix->selectCells(sRow,sCol,eRow,eCol);
		}
	scrRCalstep = (pMatrix->verticalScrollBar()->maxValue() - pMatrix->horizontalScrollBar()->minValue()) / pMatrix->numRows();
	pMatrix->verticalScrollBar()->setValue(sRow * scrRCalstep);
	scrCCalstep = (pMatrix->horizontalScrollBar()->maxValue() - pMatrix->horizontalScrollBar()->minValue()) / pMatrix->numCols();
	pMatrix->horizontalScrollBar()->setValue(sCol * scrCCalstep);
}

void arnCompositeMatrixViewer::doValueChange(int row, int col)
{
	if (pGLMatrix) {
		pGLMatrix->setValue(col,row,pMatrix->text(row,col).toDouble());
		}
	if (pMultiVector) {
		pMultiVector->setValue(row,col,pMatrix->text(row,col).toDouble());
		}
	emit valueChanged(row,col);
}

void arnCompositeMatrixViewer::languageChange()
{
    LXValLabel->setText( tr( "X" ) );
    XValLabel->setText( tr( "" ) );
    LYValLabel->setText( tr( "Y" ) );
    YValLabel->setText( tr( "" ) );
    LZValLabel->setText( tr( "Z" ) );
    ViewMatrixButton->setText( tr( "Matrix" ) );
    View3DGraphButton->setText( tr( "3DGraph" ) );
    ViewSliceButton->setText( tr( "Slice" ) );
}

void arnCompositeMatrixViewer::MatrixViewerButton_hndl(void)
{
	singlepointRow = singlepointCol = -1;

	QList<int> sList = mainsplitter->sizes();
	for (int i = 0; i < sList.size() - 1; ++i) {
		if (sList.at(i)) {
			sList[0] = sList.at(i);
/*			arnDebug("%d",sList.at(0));*/
			break;
			}
		}
	mainsplitter->setSizes(sList);

	// hide all
	if (pGLMatrix) {
		if (mainsplitter->widget(mainsplitter->indexOf(pGLMatrix)) != 0) {
			pGLMatrix->setEnabled(false);
			pGLMatrix->hide();
			}
		}
	if (pMatrix) {
		if (mainsplitter->widget(mainsplitter->indexOf(pMatrix )) != 0) {
			pMatrix->setEnabled(false);
			pMatrix->hide();
			}
		}
	if (pMultiVector) {
		if (mainsplitter->widget(mainsplitter->indexOf(pMultiVector )) != 0) {
			pMultiVector->setEnabled(false);
			pMultiVector->hide();
			}
		}
	if (pMatrix) {
		LXValLabel->hide();
		XValLabel->hide();
		LYValLabel->hide();
		YValLabel->hide();
		LZValLabel->hide();
		ZVallineEdit->hide();
		pMatrix->setEnabled(true);
		pMatrix->show();
		}
	resize( QSize(516, 455).expandedTo(minimumSizeHint()) );
}

void arnCompositeMatrixViewer::Graph3DViewerButton_hndl(void)
{
	singlepointRow = singlepointCol = -1;

	QList<int> sList = mainsplitter->sizes();
	for (int i = 0; i < sList.size() - 1; ++i) {
		if (sList.at(i)) {
			sList[1] = sList.at(i);
/*			arnDebug("%d",sList.at(1));*/
			break;
			}
		}
	mainsplitter->setSizes(sList);

	// hide all
	if (pGLMatrix) {
		if (mainsplitter->widget(mainsplitter->indexOf(pGLMatrix )) != 0) {
			pGLMatrix->setEnabled(false);
			pGLMatrix->hide();
			}
		}
	if (pMatrix) {
		if (mainsplitter->widget(mainsplitter->indexOf(pMatrix)) != 0) {
			pMatrix->setEnabled(false);
			pMatrix->hide();
			}
		}
	if (pMultiVector) {
		if (mainsplitter->widget(mainsplitter->indexOf(pMultiVector)) != 0) {
			pMultiVector->setEnabled(false);
			pMultiVector->hide();
			}
		}
	if (pGLMatrix) {
		disconnect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
		XValLabel->setText("");
		YValLabel->setText("");
		ZVallineEdit->setText("");
		connect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
		LXValLabel->show();
		XValLabel->show();
		LYValLabel->show();
		YValLabel->show();
		LZValLabel->show();
		ZVallineEdit->show();
		pGLMatrix->setEnabled(true);
		pGLMatrix->invalidate();
		pGLMatrix->show();
		}
	resize( QSize(516, 455).expandedTo(minimumSizeHint()) );
}

void arnCompositeMatrixViewer::Graph3DSelection_hndl(int start_row, int start_col,int end_row, int end_col)
{
	disconnect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
	if ((start_row == end_row) && (start_col == end_col)) {
		if (pMatrix) {
			ZVallineEdit->setReadOnly(false);
			singlepointRow = start_row;
			singlepointCol = start_col;
			XValLabel->setText(pMatrix->horizontalHeader()->label(start_col));
			YValLabel->setText(pMatrix->verticalHeader()->label(start_row));
			ZVallineEdit->setText(pMatrix->text(start_row,start_col));
			pMatrix->clearSelection(true);
			pMatrix->selectCells(start_row, start_col, end_row, end_col);
			}
		}
	else {
		if (end_row <= start_row) {int tmp = start_row; start_row = end_row; end_row = tmp;}
		if (end_col <= start_col) {int tmp = start_col; start_col = end_col; end_col = tmp;}
		if (pMatrix) {
			ZVallineEdit->setReadOnly(true);
			singlepointRow = -1;
			singlepointCol = -1;
			XValLabel->setText("");
			YValLabel->setText("");
			ZVallineEdit->setText("");
			pMatrix->clearSelection(true);
			pMatrix->selectCells(start_row, start_col, end_row, end_col);
			}
		}
	connect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
}

void arnCompositeMatrixViewer::GraphSliceSelection_hndl(int start_row, int start_col,int end_row, int end_col)
{
	disconnect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
	if ((start_row == end_row) && (start_col == end_col)) {
		if (pMultiVector && pMatrix) {
			ZVallineEdit->setReadOnly(false);
			singlepointRow = start_row;
			singlepointCol = start_col;
			XValLabel->setText(((arnGLMultipleArray*)(pMultiVector->array()))->rowText(start_row));
			YValLabel->setText(((arnGLMultipleArray*)(pMultiVector->array()))->colText(start_col));
			ZVallineEdit->setText(pMultiVector->text(start_row,start_col));
			//pMatrix->selectCells(start_row, start_col, end_row, end_col);
			}
		}
	else {
		if (pMatrix) {
			ZVallineEdit->setReadOnly(true);
			singlepointRow = -1;
			singlepointCol = -1;
			XValLabel->setText("");
			YValLabel->setText("");
			ZVallineEdit->setText("");
			pMatrix->clearSelection(true);
			//pMatrix->selectCells(start_row, start_col, end_row, end_col);
			}
		}
	connect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
}

void arnCompositeMatrixViewer::ZLineEditTextChange_hndl(const QString& text)
{
	if ((singlepointRow != -1) && (singlepointCol != -1)) {
		setValue(singlepointRow,singlepointCol,text.toDouble());
		if (pGLMatrix) pGLMatrix->invalidate();
		if (pMultiVector) pMultiVector->invalidate();
		}
}

void arnCompositeMatrixViewer::SliceButton_hndl(void)
{
	int selRow, selCol;
/*	int arrDim,rowDim = 0;*/
/*	QHeader *XHeader = 0;
	QHeader *YHeader = 0;*/
	singlepointRow = singlepointCol = -1;

	QList<int> sList = mainsplitter->sizes();
	for (int i = 0; i < sList.size() - 1; ++i) {
		if (sList.at(i)) {
			sList[2] = sList.at(i);
/*			arnDebug("%d",sList.at(2));*/
			break;
			}
		}
	mainsplitter->setSizes(sList);

	selRow = pMatrix->currentRow();
	selCol = pMatrix->currentColumn();
	bool isAFullRowSelected = pMatrix->isRowSelected(selRow,true);
	bool isAFullColSelected = pMatrix->isColumnSelected(selCol,true);
	if (!(isAFullRowSelected || isAFullColSelected)) return;
	// una colonna intera e' selezionata oppure una riga intera e' selezionata
	if (pGLMatrix) {
		if (mainsplitter->widget(mainsplitter->indexOf(pGLMatrix )) != 0) {
			pGLMatrix->setEnabled(false);
			pGLMatrix->hide();
			}
		}
	if (pMatrix) {
		if (mainsplitter->widget(mainsplitter->indexOf(pMatrix)) != 0) {
			pMatrix->setEnabled(false);
			pMatrix->hide();
			}
		}
	if (pMultiVector) {
		disconnect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
		XValLabel->setText("");
		YValLabel->setText("");
		ZVallineEdit->setText("");
		connect(ZVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(ZLineEditTextChange_hndl(const QString&)));
		LXValLabel->show();
		XValLabel->show();
		LYValLabel->show();
		YValLabel->show();
		LZValLabel->show();
		ZVallineEdit->show();
		pMultiVector->setEnabled(true);
		pMultiVector->HideAllRows();
		pMultiVector->HideAllCols();
		pMultiVector->HideRows();
		pMultiVector->HideCols();
		if (isAFullRowSelected) {
			LXValLabel->setText(pGLMatrix->YAxisLabel());
			LYValLabel->setText(pGLMatrix->XAxisLabel());
			LZValLabel->setText(pGLMatrix->ZAxisLabel());
			pMultiVector->setValueMinScale(pGLMatrix->ValueMinScale());
			pMultiVector->setValueMaxScale(pGLMatrix->ValueMaxScale());
			pMultiVector->setXAxisLabel(pGLMatrix->XAxisLabel());
			pMultiVector->setYAxisLabel(pGLMatrix->ZAxisLabel());
			pMultiVector->setCaptionLabel(QString("sezione lungo il ") + pGLMatrix->YAxisLabel());
			pMultiVector->setRowVisible(selRow - 1,true);
			pMultiVector->setRowColor(selRow - 1,QColor("yellow"));
			pMultiVector->setRowVisible(selRow,true);
			pMultiVector->setRowColor(selRow,QColor("black"));
			pMultiVector->setRowVisible(selRow + 1,true);
			pMultiVector->setRowColor(selRow + 1,QColor("green"));
			pMultiVector->ShowRows();
			}
		else if (isAFullColSelected) {
			LXValLabel->setText(pGLMatrix->YAxisLabel());
			LYValLabel->setText(pGLMatrix->XAxisLabel());
			LZValLabel->setText(pGLMatrix->ZAxisLabel());
			pMultiVector->setValueMinScale(pGLMatrix->ValueMinScale());
			pMultiVector->setValueMaxScale(pGLMatrix->ValueMaxScale());
			pMultiVector->setXAxisLabel(pGLMatrix->YAxisLabel());
			pMultiVector->setYAxisLabel(pGLMatrix->ZAxisLabel());
			pMultiVector->setCaptionLabel(QString("sezione lungo il ") + pGLMatrix->XAxisLabel());
			pMultiVector->setColVisible(selCol - 1,true);
			pMultiVector->setColColor(selCol - 1,QColor("yellow"));
			pMultiVector->setColVisible(selCol,true);
			pMultiVector->setColColor(selCol,QColor("black"));
			pMultiVector->setColVisible(selCol + 1,true);
			pMultiVector->setColColor(selCol + 1,QColor("green"));
			pMultiVector->ShowCols();
			}
		pMultiVector->invalidate();
		pMultiVector->show();
		}
	resize( QSize(516, 455).expandedTo(minimumSizeHint()) );
}

void arnCompositeMatrixViewer::enterEvent(QEvent */*e*/)
{
	if (pClip) {
		if (pClip->supportsSelection()) {
			if (!(pClip->text(QClipboard::Selection).isNull())) {
				QString tmpS(pClip->text(QClipboard::Selection));
				int pos = tmpS.find("MATRIX");
				if ((pos == -1) || (pos > 0)) Incolla->setEnabled(false);
				else Incolla->setEnabled(true);
				}
			else Incolla->setEnabled(false);
			}
		else {
			if (!(pClip->text(QClipboard::Clipboard).isNull())) {
				QString tmpS(pClip->text(QClipboard::Clipboard));
				int pos = tmpS.find("MATRIX");
				if ((pos == -1) || (pos > 0)) Incolla->setEnabled(false);
				else Incolla->setEnabled(true);
				}
			else Incolla->setEnabled(false);
			}
		}
	else {
		Incolla->setEnabled(false);
		Copia->setEnabled(false);
		}
}

void arnCompositeMatrixViewer::adjustRows(void)
{
	for (int indR = 0; indR < pMatrix->numRows(); indR++) pMatrix->adjustRow(indR);
}

void arnCompositeMatrixViewer::adjustCols(void)
{
	for (int indC = 0; indC < pMatrix->numCols(); indC++) pMatrix->adjustColumn(indC);
}



// void arnCompositeMatrixViewer::resizeEvent ( QResizeEvent * e )
// {
// 
// }

// void arnCompositeMatrixViewer::paintEvent ( QPaintEvent * event )
// {
// 	if (pMatrix && pMatrix->isEnabled() && pMatrix->isShown()) {
// 		pMatrix->repaintContents(true);
// 		}
// 	return arnObjectViewer::paintEvent(event);
// }
