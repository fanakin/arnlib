/***************************************************************************
                          arnCompositeArrayViewer.cpp  -  description
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

#include <qapplication.h>
#include <qcursor.h>
#include <qinputdialog.h>
#include "CommonFunctions.h"
#include "arnCompositeArrayViewer.h"
#include <QContextMenuEvent>

void arnCompositeArrayViewer::init(int rows)
{
    tpy = avt_CompositeArrayViewer;
	numFormatVal = nrf_dec;
	numFormatX = nrf_dec;
	singlepointRow = -1;
    Form1Layout = new QGridLayout( this, 1, 1, 11, 6, "Form1Layout");

	mainsplitter = new QSplitter (Qt::Vertical, this, "mainsplitter");
	if (!mainsplitter) arnCriticalExit();

    pArray = new Q3Table(rows,1,this,"Array");
    if (!pArray) arnCriticalExit();
    pArray->setVScrollBarMode( Q3ScrollView::Auto );
    pArray->setHScrollBarMode( Q3ScrollView::Auto );
    pArray->horizontalHeader()->setStretchEnabled(true);
    //pArray->setMaximumHeight(300);
    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pArray, SIGNAL(valueChanged(int, int)), this, SLOT(doValueChange(int, int)));
	mainsplitter->addWidget( pArray );

    pGLArray = new arnGLArrayViewer(rows,arn_glAPM_MASHED_LINES, this, "GLArray"); // row, 
    if (!pGLArray) arnCriticalExit();
    //pGLArray->resize( QSize(300, 455).expandedTo(minimumSizeHint()) );
	connect(pGLArray->array(), SIGNAL(selectionChanged(int, int)),this , SLOT(Graph2DSelection_hndl(int, int)));
	mainsplitter->addWidget( pGLArray );

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

    YVallineEdit = new QLineEdit( this, "YVallineEdit" );
    if (!YVallineEdit) arnCriticalExit();
	gridLayout->addWidget(YVallineEdit,2,2);
    connect(YVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(YLineEditTextChange_hndl(const QString&)));


    ViewArrayButton = new QPushButton( this, "ViewArrayButton" );
    if (!ViewArrayButton) arnCriticalExit();
	gridLayout->addWidget(ViewArrayButton,1,3);
    connect(ViewArrayButton, SIGNAL(clicked()), this, SLOT(ArrayViewerButton_hndl(void)));

    View2DGraphButton = new QPushButton( this, "View2DGraphButton" );
    if (!View2DGraphButton) arnCriticalExit();
	gridLayout->addWidget(View2DGraphButton,2,3);
    connect(View2DGraphButton, SIGNAL(clicked()), this, SLOT(Graph2DViewerButton_hndl(void)));

	
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
    Azzera->addTo(pPopUp);
    Aggiungi->addTo(pPopUp);
    Moltiplica->addTo(pPopUp);
    Nascondi->addTo(pPopUp);
    Mostratutti->addTo(pPopUp);
    Copia->addTo(pPopUp);
    Incolla->addTo(pPopUp);

    prec = precX = 0;

    pClip = QApplication::clipboard();
    if (!pClip) arnCriticalExit();

	setGeometry(50,50,400,400);

	LXValLabel->setText( tr( "X" ) );
	LYValLabel->setText( tr( "Y" ) );

	LXValLabel->hide();
	LYValLabel->hide();
	XValLabel->hide();
	YVallineEdit->hide();

	pGLArray->hide();
    pArray->show();
}

arnCompositeArrayViewer::arnCompositeArrayViewer(int rows, QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
	init(rows);
}

arnCompositeArrayViewer::arnCompositeArrayViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
	init(5);
}

arnCompositeArrayViewer::~arnCompositeArrayViewer(void)
{

}

void arnCompositeArrayViewer::setXValue(int row, double val)
{
	//QString ts;
	if (row < pArray->numRows()) {
		if (!precX) {
			switch (numFormatX) {
				case nrf_hex:
					pArray->verticalHeader()->setLabel(row,QString::number((int)val, 16).toUpper());
				break;
				case nrf_bin:
					pArray->verticalHeader()->setLabel(row,QString::number((int)val, 2));
				break;
				case nrf_dec:
				default:
					pArray->verticalHeader()->setLabel(row,QString::number(val));
				break;
			}
			if (pGLArray) pGLArray->setXValue(row,val);
			}
		else {
			switch (numFormatX) {
				case nrf_hex:
					pArray->verticalHeader()->setLabel(row,QString::number((int)val, 16).toUpper());
				break;
				case nrf_bin:
					pArray->verticalHeader()->setLabel(row,QString::number((int)val, 2));
				break;
				case nrf_dec:
				default:
					pArray->verticalHeader()->setLabel(row,QString::number(val,'f',precX));
				break;
			}
			if (pGLArray) pGLArray->setXValue(row,val);
			}
		}
}

void arnCompositeArrayViewer::setValue(int row, double val)
{
	if (row < pArray->numRows()) {
		//QString ts;
		if (!prec) {
			switch (numFormatVal) {
				case nrf_hex:
					pArray->setText(row,0,QString::number((int)val, 16).toUpper());
				break;
				case nrf_bin:
					pArray->setText(row,0,QString::number((int)val, 2));
				break;
				case nrf_dec:
				default:
					pArray->setText(row,0,QString::number(val));
				break;
			}
		}
		else {
			switch (numFormatVal) {
				case nrf_hex:
					pArray->setText(row,0,QString::number((int)val, 16).toUpper());
				break;
				case nrf_bin:
					pArray->setText(row,0,QString::number((int)val, 2));
				break;
				case nrf_dec:
				default:
					pArray->setText(row,0,QString::number(val,'f',prec));
				break;
			}
		}
		doValueChange(row,0);
	}
}

QString arnCompositeArrayViewer::text(int row)
{
    QString ts("");
    if (row < pArray->numRows()) {ts = pArray->text(row,0);}
    return ts;
}

QString arnCompositeArrayViewer::text(int row,int col)
{
    QString ts("");
	if (row < pArray->numRows() && col < pArray->numCols()) { ts = pArray->text(row,col);}
    return ts;
}

void arnCompositeArrayViewer::contextMenuEvent ( QContextMenuEvent * e )
{
//arnDebug("Entrato\n");
	pPopUp->exec(QCursor::pos());
	e->accept();
}

// bool arnCompositeArrayViewer::eventFilter(QObject* watched, QEvent* e)
// {
//     if (e->type() == QEvent::ContextMenu) {
//         pPopUp->exec(QCursor::pos());
//         return true;
//         }
//     return arnObjectViewer::eventFilter(watched, e);
// }

//void arnNumericArrayViewer::SelezionaTutto_Hndl(void)
//{
//    Q3TableSelection sel;
//    sel.init(0,0);
//    sel.expandTo(pArray->numRows(),0);
//    pArray->addSelection(sel);
//}

void arnCompositeArrayViewer::Inizializza_Hndl(void)
{
    bool ok = false;
    double res = QInputDialog::getDouble(
        tr( "Inizializza" ),
        tr( "Inserisci Numero." ),
        0, -2147483647, 2147483647, prec + 3, &ok, this, "InizializeValueBox" );
    if ( ok ) { // user entered something and pressed OK
        if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
            for (int indx = 0; indx < pArray->numRows(); indx++) {
                setValue(indx,res);
                }
            }
        else if (pArray->isColumnSelected(pArray->currentColumn())) {
            for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
                Q3TableSelection sel = pArray->selection(indxSel);
                for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                    if (indx < pArray->numRows()) {
                        setValue(indx,res);
                        }
                    }
                }
            }
        else {}
        }
	else {;}// user pressed Cancel

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}



void arnCompositeArrayViewer::Interpola_Hndl(void)
{
    if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
        double min = pArray->text(0,pArray->currentColumn()).toDouble();
        double max = pArray->text(pArray->numRows() - 1,pArray->currentColumn()).toDouble();
        double step = (max - min) / (pArray->numRows() - 1);
        for (int indx = 1; indx < pArray->numRows() - 1 ; indx++) {
            min += step;
            setValue(indx,min);
            }
        }
    else if (pArray->isColumnSelected(pArray->currentColumn())) {
        for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
            Q3TableSelection sel = pArray->selection(indxSel);
            double min = pArray->text(sel.topRow(),pArray->currentColumn()).toDouble();
            double max = pArray->text(sel.bottomRow(),pArray->currentColumn()).toDouble();
            double step = (max - min) / (sel.bottomRow() - sel.topRow());
            for (int indx = sel.topRow() + 1; indx < sel.bottomRow(); indx++) {
                if (indx < pArray->numRows()) {
                    min += step;
                    setValue(indx,min);
                    }
                }
            }
        }
    else {}

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}


void arnCompositeArrayViewer::Azzera_Hndl(void)
{
    if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
            for (int indx = 0; indx < pArray->numRows(); indx++) {
            setValue(indx,0);
            }
        }
    else if (pArray->isColumnSelected(pArray->currentColumn())) {
        for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
            Q3TableSelection sel = pArray->selection(indxSel);
            for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                if (indx < pArray->numRows()) {
                    setValue(indx,0);
                    }
                }
            }
        }
    else {}

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}

void arnCompositeArrayViewer::Aggiungi_Hndl(void)
{
    bool ok = false;
    double res = QInputDialog::getDouble(
        tr( "Aggiungi" ),
        tr( "Inserisci Numero." ),
        0, -2147483647, 2147483647, prec + 3, &ok, this, "InizializeValueBox" );
    if ( ok ) { // user entered something and pressed OK
        if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
            for (int indx = 0; indx < pArray->numRows(); indx++) {
                double val = pArray->text(indx,pArray->currentColumn()).toDouble();
                val += res;
                setValue(indx,val);
                }
            }
        else if (pArray->isColumnSelected(pArray->currentColumn())) {
            for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
                Q3TableSelection sel = pArray->selection(indxSel);
                for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                    if (indx < pArray->numRows()) {
                        double val = pArray->text(indx,pArray->currentColumn()).toDouble();
                        val += res;
                        setValue(indx,val);
                        }
                    }
                }
            }
        else {}
        }
	else {;}// user pressed Cancel

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}

void arnCompositeArrayViewer::Moltiplica_Hndl(void)
{
    bool ok = false;
    double res = QInputDialog::getDouble(
        tr( "Aggiungi" ),
        tr( "Inserisci Numero." ),
        0, -2147483647, 2147483647, prec + 3, &ok, this, "InizializeValueBox" );
    if ( ok ) { // user entered something and pressed OK
        if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
            for (int indx = 0; indx < pArray->numRows(); indx++) {
                double val = pArray->text(indx,pArray->currentColumn()).toDouble();
                val *= res;
                setValue(indx,val);
                }
            }
        else if (pArray->isColumnSelected(pArray->currentColumn())) {
            for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
                Q3TableSelection sel = pArray->selection(indxSel);
                for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                    if (indx < pArray->numRows()) {
                        double val = pArray->text(indx,pArray->currentColumn()).toDouble();
                        val *= res;
                        setValue(indx,val);
                        }
                    }
                }
            }
        else {}
        }
	else {;}// user pressed Cancel

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}

void arnCompositeArrayViewer::Nascondi_Hndl(void)
{
    if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
        for (int indx = 0; indx < pArray->numRows(); indx++) {
            pArray->hideRow(indx);
            }
        }
    else if (pArray->isColumnSelected(pArray->currentColumn())) {
        for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
            Q3TableSelection sel = pArray->selection(indxSel);
            for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                if (indx < pArray->numRows()) {
                    pArray->hideRow(indx);
                    }
                }
            }
        }
    else {}

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}

void arnCompositeArrayViewer::Mostratutti_Hndl(void)
{
    for (int indx = 0; indx < pArray->numRows(); indx++) {
        pArray->showRow(indx);
        }

    pArray->clearSelection();
	if (pGLArray) pGLArray->invalidate();
}

void arnCompositeArrayViewer::Copia_Hndl(void)
{
	QString aTxt("VECTOR\n");
	int minR, minC;
	minR = pArray->numRows();
	minC = pArray->numCols();
	for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
		Q3TableSelection sel = pArray->selection(indxSel);
		for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
			for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
				if ((indR < pArray->numRows()) && (indC < pArray->numCols())) {
					if (indR < minR) minR = indR;
					if (indC < minC) minC = indC;
					}
				}
			}
		}
	for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
		Q3TableSelection sel = pArray->selection(indxSel);
		for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
			for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
				if ((indR < pArray->numRows()) && (indC < pArray->numCols())) {
					QString r,c;
					r.setNum(indR - minR);
					c.setNum(indC - minC);
					aTxt += r; aTxt += ",";
					aTxt += c; aTxt += ",";
					aTxt += pArray->text(indR,indC);
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
			pArray->clearSelection();
			Incolla->setEnabled(true);
			}
		else {
			//pClip->clear(QClipboard::Clipboard);
			//pClip->clear(QClipboard::Selection);
			pClip->setText( aTxt, QClipboard::Clipboard);
			pArray->clearSelection();
			Incolla->setEnabled(true);
			}
		}
}

void arnCompositeArrayViewer::Incolla_Hndl(void)
{
	int rOff,cOff;
	int pos;
	if (pClip) {
		if (pClip->supportsSelection()) {
			QString tmpS(pClip->text(QClipboard::Selection));
			arnDebug("%s",tmpS.latin1());
			pos = tmpS.find("VECTOR");
			if ((pos == -1) || (pos > 0)) {
				tmpS = pClip->text(QClipboard::Clipboard);
				rOff = pArray->currentRow();
				cOff = pArray->currentColumn();
				QStringList strList = QStringList::split("\n", tmpS );
				for (int indx = 0; indx < int(strList.count()); indx++) {
					bool ok;
					float __val;
					__val = strList[indx].toFloat(&ok);
					if (!ok) {
						arnDebug("Clipboard not usable. Erased Globally.");
						pClip->clear(QClipboard::Clipboard);
						return;
						}
					//arnDebug("%d",__val);
					int indR = rOff + indx;
					setValue(indR,/*indC,*/strList[indx].toDouble());
					}
				return;
				}
			int rOff,cOff;
			rOff = pArray->currentRow();
			cOff = pArray->currentColumn();
			QStringList strList = QStringList::split("\n", tmpS );
			for (int indx = 1; indx < int(strList.count()); indx++)  {
				QStringList line = QStringList::split(",", strList[indx] );
				int indR,indC;
				indR = rOff + line[0].toInt();
				indC = cOff + line[1].toInt();
				QString st(line[2]);
				setValue(indR,/*indC,*/st.toDouble());
				}
			}
		else {
			QString tmpS(pClip->text(QClipboard::Clipboard));
			arnDebug("%s",tmpS.latin1());
			pos = tmpS.find("VECTOR");
			if ((pos == -1) || (pos > 0)) {
				tmpS = pClip->text(QClipboard::Clipboard);
				rOff = pArray->currentRow();
				cOff = pArray->currentColumn();
				QStringList strList = QStringList::split("\n", tmpS );
				for (int indx = 0; indx < int(strList.count()); indx++) {
					bool ok;
					float __val;
					__val = strList[indx].toFloat(&ok);
					if (!ok) {
						arnDebug("Clipboard not usable. Erased Globally.");
						pClip->clear(QClipboard::Clipboard);
						return;
						}
					//arnDebug("%d",__val);
					int indR = rOff + indx;
					setValue(indR,/*indC,*/strList[indx].toDouble());
					}
				return;
				}
			int rOff,cOff;
			rOff = pArray->currentRow();
			cOff = pArray->currentColumn();
			QStringList strList = QStringList::split("\n", tmpS );
			for (int indx = 1; indx < int(strList.count()); indx++)  {
				QStringList line = QStringList::split(",", strList[indx] );
				int indR,indC;
				indR = rOff + line[0].toInt();
				indC = cOff + line[1].toInt();
				QString st(line[2]);
				setValue(indR,/*indC,*/st.toDouble());
				}
			}		
		}
		
	if (pGLArray) pGLArray->invalidate();
}

void arnCompositeArrayViewer::selectCells(int sRow, int eRow)
{
//	Q3TableSelection sel;
//	sel.init(sRow,1);
//	sel.expandTo(eRow,1);
//	pArray->addSelection(sel);
	int scrValstep, tmp;
	pArray->clearSelection();
	if (sRow > eRow) {tmp = sRow; sRow = eRow; eRow = tmp;}
	pArray->selectCells(sRow,0,eRow,1);
	scrValstep = (pArray->verticalScrollBar()->maxValue() - pArray->verticalScrollBar()->minValue()) / pArray->numRows();
	pArray->verticalScrollBar()->setValue(sRow * scrValstep);
}


void arnCompositeArrayViewer::doValueChange(int row, int col)
{
	if (pGLArray) {
		pGLArray->setValue(row,pArray->text(row,col).toDouble());
		}
    emit valueChanged(row,col);
}

void arnCompositeArrayViewer::languageChange()
{
    LXValLabel->setText( tr( "X" ) );
    XValLabel->setText( tr( "" ) );
    LYValLabel->setText( tr( "Y" ) );
    ViewArrayButton->setText( tr( "Vector" ) );
    View2DGraphButton->setText( tr( "2DGraph" ) );
}

void arnCompositeArrayViewer::ArrayViewerButton_hndl(void)
{
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
	if (pGLArray) {
		if (mainsplitter->widget(mainsplitter->indexOf(pGLArray)) != 0) pGLArray->hide();
		}
	if (pArray) {
		if (mainsplitter->widget(mainsplitter->indexOf(pArray)) != 0) {
			LXValLabel->hide();
			LYValLabel->hide();
			XValLabel->hide();
			YVallineEdit->hide();
			pArray->hide();
			}
		}
	if (pArray) {
		pArray->show();
		}
}

void arnCompositeArrayViewer::Graph2DViewerButton_hndl(void)
{
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
	if (pGLArray) {
		if (mainsplitter->widget(mainsplitter->indexOf(pGLArray)) != 0) pGLArray->hide();
		}
	if (pArray) {
		if (mainsplitter->widget(mainsplitter->indexOf(pArray)) != 0) {
			pArray->hide();
			}
		}
	if (pGLArray) {
		disconnect(YVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(YLineEditTextChange_hndl(const QString&)));
		XValLabel->setText("");
		YVallineEdit->setText("");
		connect(YVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(YLineEditTextChange_hndl(const QString&)));
		LXValLabel->show();
		LYValLabel->show();
		XValLabel->show();
		YVallineEdit->show();
		pGLArray->invalidate();
		pGLArray->show();
		}
}

void arnCompositeArrayViewer::Graph2DSelection_hndl(int start_row, int end_row)
{
	disconnect(YVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(YLineEditTextChange_hndl(const QString&)));
	if ((start_row == end_row)) {
		if (pArray) {
			YVallineEdit->setReadOnly(false);
			singlepointRow = start_row;
			XValLabel->setText(pArray->verticalHeader()->label(start_row));
			YVallineEdit->setText(pArray->text(start_row,0));
			}
		}
	else {
		if (pArray) {
			YVallineEdit->setReadOnly(true);
			singlepointRow = -1;
			XValLabel->setText("");
			YVallineEdit->setText("");
			pArray->clearSelection(true);
			pArray->selectCells(start_row,0, end_row,0);
			}
		}
	connect(YVallineEdit, SIGNAL(textChanged(const QString&)),this , SLOT(YLineEditTextChange_hndl(const QString&)));
}

void arnCompositeArrayViewer::YLineEditTextChange_hndl(const QString& text)
{
	if ((singlepointRow != -1)) {
		setValue(singlepointRow,text.toDouble());
		if (pGLArray) pGLArray->invalidate();
		}
}



void arnCompositeArrayViewer::enterEvent(QEvent * /*e*/)
{
	if (pClip) {
		if (pClip->supportsSelection()) {
			if (!(pClip->text(QClipboard::Selection).isNull())) {
				QString tmpS(pClip->text(QClipboard::Selection));
				int pos = tmpS.find("VECTOR");
				if ((pos == -1) || (pos > 0)) Incolla->setEnabled(false);
				else Incolla->setEnabled(true);
				}
			else Incolla->setEnabled(false);
			}
		else {
			if (!(pClip->text(QClipboard::Clipboard).isNull())) {
				QString tmpS(pClip->text(QClipboard::Clipboard));
				int pos = tmpS.find("VECTOR");
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

// void arnCompositeArrayViewer::resizeEvent ( QResizeEvent * e )
// {
// 
// }

// void arnCompositeArrayViewer::paintEvent ( QPaintEvent * event )
// {
// 	if (pArray && pArray->isEnabled() && pArray->isShown()) {
// 		pArray->repaintContents(true);
// 		}
// 	return arnObjectViewer::paintEvent(event);
// }
