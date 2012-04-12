/***************************************************************************
                          arnStringArrayViewer.cpp  -  description
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
#include "arnStringArrayViewer.h"
#include <QContextMenuEvent>

arnStringArrayViewer::arnStringArrayViewer(int rows, QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
    tpy = avt_NumericArrayViewer;
    pMainLayout = new QVBoxLayout(this, 10, -1, "MainLayout");
    if (!pMainLayout) arnCriticalExit();
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
    pArray = new Q3Table(rows,1,this,"Matrix");
    if (!pArray) arnCriticalExit();
    pArray->horizontalHeader()->setStretchEnabled(true);
    pMainLayout->addWidget(pArray,20);
    pMainLayout->addWidget(pComment,5);

    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pArray, SIGNAL(valueChanged(int, int)), this, SLOT(doValueChange(int, int)));

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

}

arnStringArrayViewer::arnStringArrayViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
    tpy = avt_NumericArrayViewer;
    pMainLayout = new QVBoxLayout(this, 10, -1, "MainLayout");              
    if (!pMainLayout) arnCriticalExit();
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
    pArray = new Q3Table(5,1,this,"Matrix");
    if (!pArray) arnCriticalExit();
    pArray->horizontalHeader()->setStretchEnabled(true);
    pMainLayout->addWidget(pArray,20);
    pMainLayout->addWidget(pComment,5);

    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pArray, SIGNAL(valueChanged(int, int)), this, SLOT(doValueChange(int, int)));

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
    connect( Copia, SIGNAL( activated() ), this, SLOT( Copia_Hndl() ) );
    connect( Incolla, SIGNAL( activated() ), this, SLOT( Incolla_Hndl() ) );

    // aggiunta popup
//    SelezionaTutto->addTo(pPopUp);
    Inizializza->addTo(pPopUp);
    Interpola->addTo(pPopUp);
    Azzera->addTo(pPopUp);
    Aggiungi->addTo(pPopUp);
    Moltiplica->addTo(pPopUp);
    Copia->addTo(pPopUp);
    Incolla->addTo(pPopUp);

    prec = precX = 0;

    pClip = QApplication::clipboard();
    if (!pClip) arnCriticalExit();

}

arnStringArrayViewer::~arnStringArrayViewer(void)
{

}

void arnStringArrayViewer::setXValue(int row, double val)
{
    QString ts;
    if (!precX) pArray->verticalHeader()->setLabel(row,ts.setNum(val));
    else pArray->verticalHeader()->setLabel(row,ts.setNum(val,'f',precX));
}

void arnStringArrayViewer::setValue(int row, double val)
{
    QString ts;
    if (!prec) pArray->setText(row,0,ts.setNum(val));
    else pArray->setText(row,0,ts.setNum(val,'f',prec));
}

QString arnStringArrayViewer::text(int row)
{
    QString ts;
    ts = pArray->text(row,0);
    return ts;
}

QString arnStringArrayViewer::text(int row,int col)
{
    QString ts;
    ts = pArray->text(row,col);
    return ts;
}

void arnStringArrayViewer::contextMenuEvent ( QContextMenuEvent * e )
{
//arnDebug("Entrato\n");
	pPopUp->exec(QCursor::pos());
	e->accept();
}

// bool arnStringArrayViewer::eventFilter(QObject* watched, QEvent* e)
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

void arnStringArrayViewer::Inizializza_Hndl(void)
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
                doValueChange(indx,pArray->currentColumn());
                }
            }
        else if (pArray->isColumnSelected(pArray->currentColumn())) {
            for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
                Q3TableSelection sel = pArray->selection(indxSel);
                for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                    if (indx < pArray->numRows()) {
                        setValue(indx,res);
                        doValueChange(indx,pArray->currentColumn());
                        }
                    }
                }
            }
        else {}
        }
	else {;}// user pressed Cancel

    pArray->clearSelection();
}



void arnStringArrayViewer::Interpola_Hndl(void)
{
    if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
        double min = pArray->text(0,pArray->currentColumn()).toDouble();
        double max = pArray->text(pArray->numRows() - 1,pArray->currentColumn()).toDouble();
        double step = (max - min) / (pArray->numRows() - 1);
        for (int indx = 1; indx < pArray->numRows() - 1 ; indx++) {
            min += step;
            setValue(indx,min);
            doValueChange(indx,pArray->currentColumn());
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
                    doValueChange(indx,pArray->currentColumn());
                    }
                }
            }
        }
    else {}

    pArray->clearSelection();
}


void arnStringArrayViewer::Azzera_Hndl(void)
{
    if (pArray->isColumnSelected(pArray->currentColumn(),true)) {
            for (int indx = 0; indx < pArray->numRows(); indx++) {
            setValue(indx,0);
            doValueChange(indx,pArray->currentColumn());
            }
        }
    else if (pArray->isColumnSelected(pArray->currentColumn())) {
        for (int indxSel = 0; indxSel < pArray->numSelections(); indxSel++) {
            Q3TableSelection sel = pArray->selection(indxSel);
            for (int indx = sel.topRow(); indx <= sel.bottomRow(); indx++) {
                if (indx < pArray->numRows()) {
                    setValue(indx,0);
                    doValueChange(indx,pArray->currentColumn());
                    }
                }
            }
        }
    else {}

    pArray->clearSelection();
}

void arnStringArrayViewer::Aggiungi_Hndl(void)
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
                doValueChange(indx,pArray->currentColumn());
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
                        doValueChange(indx,pArray->currentColumn());
                        }
                    }
                }
            }
        else {}
        }
	else {;}// user pressed Cancel

    pArray->clearSelection();
}

void arnStringArrayViewer::Moltiplica_Hndl(void)
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
                doValueChange(indx,pArray->currentColumn());
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
                        doValueChange(indx,pArray->currentColumn());
                        }
                    }
                }
            }
        else {}
        }
	else {;}// user pressed Cancel

    pArray->clearSelection();
}

void arnStringArrayViewer::Nascondi_Hndl(void)
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
}

void arnStringArrayViewer::Mostratutti_Hndl(void)
{
    for (int indx = 0; indx < pArray->numRows(); indx++) {
        pArray->showRow(indx);
        }

    pArray->clearSelection();
}

void arnStringArrayViewer::Copia_Hndl(void)
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
			pClip->clear(QClipboard::Clipboard);
			pClip->clear(QClipboard::Selection);
			pClip->setText( aTxt, QClipboard::Selection);
			pArray->clearSelection();
			Incolla->setEnabled(true);
			}
		else {
			pClip->clear(QClipboard::Clipboard);
			pClip->clear(QClipboard::Selection);
			pClip->setText( aTxt, QClipboard::Clipboard);
			pArray->clearSelection();
			Incolla->setEnabled(true);
			}
		}
}

void arnStringArrayViewer::Incolla_Hndl(void)
{
if (pClip) {
	if (pClip->supportsSelection()) {
		QString tmpS(pClip->text(QClipboard::Selection));
		int pos = tmpS.find("VECTOR");
		if ((pos == -1) || (pos > 0)) return;
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
			doValueChange(indR,indC);
			}
		}
	else {
		QString tmpS(pClip->text(QClipboard::Clipboard));
		int pos = tmpS.find("VECTOR");
		if ((pos == -1) || (pos > 0)) return;
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
			doValueChange(indR,indC);
			}
		}
	}
}

void arnStringArrayViewer::selectCells(int sRow, int eRow)
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


void arnStringArrayViewer::doValueChange(int row, int col)
{
    emit valueChanged(row,col);
}

void arnStringArrayViewer::enterEvent(QEvent */*e*/)
{
    if (pClip->supportsSelection()) {
        QString tmpS(pClip->text(QClipboard::Selection));
        int pos = tmpS.find("VECTOR");
        if ((pos == -1) || (pos > 0)) Incolla->setEnabled(false);
        else Incolla->setEnabled(true);
        }
}
