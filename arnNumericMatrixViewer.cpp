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
#include "arnNumericMatrixViewer.h"
#include <QContextMenuEvent>

arnNumericMatrixViewer::arnNumericMatrixViewer(int rows, int cols, QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
    tpy = avt_NumericMatrixViewer;
    pMainLayout = new QVBoxLayout(this, 10, -1, "MainLayout");
    if (!pMainLayout) arnCriticalExit();
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
    pMatrix = new Q3Table(rows,cols,this,"Matrix");
    if (!pMatrix) arnCriticalExit();
    pName = new QLabel("Nome",this,"Name",0);
    if (!pName) arnCriticalExit();
    pMainLayout->addWidget(pMatrix,20);
    pMainLayout->addWidget(pName,5);
    pMainLayout->addWidget(pComment,5);

    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pMatrix, SIGNAL(valueChanged(int, int)), this, SLOT(doValueChange(int, int)));

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

    prec = precX = precY = 0;

    pClip = QApplication::clipboard();
    if (!pClip) arnCriticalExit();

}
    
arnNumericMatrixViewer::arnNumericMatrixViewer(QWidget *parent, const char *name, Qt::WFlags f)
    : arnObjectViewer(parent, name, f)
{
    tpy = avt_NumericMatrixViewer;
    pMainLayout = new QVBoxLayout(this, 10, -1, "MainLayout");
    if (!pMainLayout) arnCriticalExit();
    pComment = new QTextEdit(0);
    if (!pComment) arnCriticalExit();
    pComment->setTextFormat(Qt::RichText);
    pComment->setReadOnly(true);
    pMatrix = new Q3Table(this,"Matrix");
    if (!pMatrix) arnCriticalExit();
    pName = new QLabel("Nome",this,"Name",0);
    if (!pName) arnCriticalExit();
    pMainLayout->addWidget(pMatrix,20);
    pMainLayout->addWidget(pName,5);
    pMainLayout->addWidget(pComment,5);

    // per avere il reale segnale connesso in modo da usare anche la setText con  segnale agganciato.
    connect(pMatrix, SIGNAL(valueChanged(int, int)), this, SLOT(doValueChange(int, int)));

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

    prec = precX = precY = 0;

    pClip = QApplication::clipboard();
    if (!pClip) arnCriticalExit();
    
}

arnNumericMatrixViewer::~arnNumericMatrixViewer(void)
{

}

void arnNumericMatrixViewer::setXValue(int col, double val)
{
    QString ts;
    if (!precX) pMatrix->horizontalHeader()->setLabel(col,ts.setNum(val));
    else pMatrix->horizontalHeader()->setLabel(col,ts.setNum(val,'f',precX));
}

void arnNumericMatrixViewer::setYValue(int row, double val)
{
    QString ts;
    if (!precY) pMatrix->verticalHeader()->setLabel(row,ts.setNum(val));
    else pMatrix->verticalHeader()->setLabel(row,ts.setNum(val,'f',precY));
}

void arnNumericMatrixViewer::setValue(int row, int col, double val)
{
    QString ts;
    if (!prec) pMatrix->setText(row,col,ts.setNum(val));
    else  pMatrix->setText(row,col,ts.setNum(val,'f',prec));
}

QString arnNumericMatrixViewer::text(int row, int col)
{
    QString ts;
    ts = pMatrix->text(row,col);
    return ts;
}

void arnNumericMatrixViewer::contextMenuEvent ( QContextMenuEvent * e )
{
//arnDebug("Entrato\n");
	pPopUp->exec(QCursor::pos());
	e->accept();
}


// bool arnNumericMatrixViewer::eventFilter(QObject* watched, QEvent* e)
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

void arnNumericMatrixViewer::Inizializza_Hndl(void)
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
                        doValueChange(indR,indC);
                        }
                    }
                }
            }
        }
	else {;}// user pressed Cancel

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::Interpola_Hndl(void)
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
            doValueChange(sel.topRow(),indC);
            }

        step = (valP4 - valP2) / (sel.bottomRow() - sel.topRow());
        start = valP2;
        for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++)  {
            start += step;
            setValue(indR,sel.rightCol(),start);
            doValueChange(indR,sel.rightCol());
            }
        
        step = (valP4 - valP3) / (sel.rightCol() - sel.leftCol());
        start = valP3;
        for (int indC = sel.leftCol() + 1; indC < sel.rightCol(); indC++) {
            start += step;
            setValue(sel.bottomRow(),indC,start);
            doValueChange(sel.bottomRow(),indC);
            }

        step = (valP3 - valP1) / (sel.bottomRow() - sel.topRow());
        start = valP1;
        for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++)  {
            start += step;
            setValue(indR,sel.leftCol(),start);
            doValueChange(indR,sel.leftCol());
            }

        for (int indR = sel.topRow() + 1; indR < sel.bottomRow(); indR++) {
            double valP1= pMatrix->text(indR,sel.leftCol()).toDouble();
            double valP2 = pMatrix->text(indR,sel.rightCol()).toDouble();
            double step = (valP2 - valP1) / (sel.rightCol() - sel.leftCol());
            for (int indC = sel.leftCol() + 1; indC < sel.rightCol(); indC++) {
                valP1 += step;
                setValue(indR,indC,valP1);
                doValueChange(indR,indC);
                }
            }
        }

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::InterpolaX_Hndl(void)
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
                doValueChange(indR,indC);
                }
            }
        }

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::InterpolaY_Hndl(void)
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
                doValueChange(indR,indC);
                }
            }
        }

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::Azzera_Hndl(void)
{
    for (int indxSel = 0; indxSel < pMatrix->numSelections(); indxSel++) {
        Q3TableSelection sel = pMatrix->selection(indxSel);
        for (int indR = sel.topRow(); indR <= sel.bottomRow(); indR++) {
            for (int indC = sel.leftCol(); indC <= sel.rightCol(); indC++) {
                if ((indR < pMatrix->numRows()) && (indC < pMatrix->numCols())) {
                    setValue(indR,indC,0);
                    doValueChange(indR,indC);
                    }
                }
            }
        }

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::Aggiungi_Hndl(void)
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
                        doValueChange(indR,indC);
                        }
                    }
                }
            }
        }
	else {;}// user pressed Cancel

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::Moltiplica_Hndl(void)
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
                        doValueChange(indR,indC);
                        }
                    }
                }
            }
        }
	else {;}// user pressed Cancel

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::Nascondi_Hndl(void)
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

void arnNumericMatrixViewer::Mostratutti_Hndl(void)
{
    for (int indR = 0; indR < pMatrix->numRows(); indR++) pMatrix->showRow(indR);
    for (int indC = 0; indC < pMatrix->numCols(); indC++) pMatrix->showColumn(indC);

    pMatrix->clearSelection();
}

void arnNumericMatrixViewer::Copia_Hndl(void)
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

void arnNumericMatrixViewer::Incolla_Hndl(void)
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
				doValueChange(indR,indC);
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
				doValueChange(indR,indC);
				}
			}
		}
}

void arnNumericMatrixViewer::selectCells(int sRow, int sCol, int eRow, int eCol)
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

void arnNumericMatrixViewer::doValueChange(int row, int col)
{
    emit valueChanged(row,col);
}

void arnNumericMatrixViewer::enterEvent(QEvent *)
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
