/***************************************************************************
                          arnEdlFileManager.cpp  -  description
                             -------------------
    begin                : gio gnu 16 2005
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

#include <sys/param.h>
#include <qcursor.h>
#include <qaction.h>
#include <QObjectList>
#include <q3listview.h>
#include <qcolordialog.h>
#include "arnEdlFileManager.h"
#include <QContextMenuEvent>

// test test test
static const char* xpm_colorrect[] = {
	/* width    heigth   ncolors   char_per_pix */
	"  16       16       1         1",
	/* char     key      color */
	"  .        c        #ff0000",
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................", /* 1 */
	"................",
	"................",
	"................",
	"................",
	"................",
	"................",
	"................",
	};

// ---------------------------------------------------
// ***************************************************
// --------- arnEFMFileDescr -------------------
// ***************************************************
// ---------------------------------------------------

arnEFMFileDescr::arnEFMFileDescr(void)
{
	filename = "";
	fileInfo = 0;
	channelList = 0;
	action = 0;
}

arnEFMFileDescr::~arnEFMFileDescr(void)
{
	if(fileInfo) {delete fileInfo; fileInfo = 0;}
	if(channelList) {delete channelList; channelList = 0;}
	action = 0;
}

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlFileManager -------------------
// ***************************************************
// ---------------------------------------------------
arnEdlFileManager::arnEdlFileManager ( QWidget *parent, const char *name, Qt::WFlags f)
	: Q3ListView(parent, name, f)
{
	this->init();
}

arnEdlFileManager::~arnEdlFileManager(void)
{
//arnDebug("%s\n","~arnEdlFileManager");
#ifdef HAVE_IDPS
	status = idpsClose();
	if( status ) {
		arnDebug("%s\n", emessage(status));
		}
#else
	status = 0;
#endif
	currentOpenFile = 0;
	if (listOfOpenFiles) {delete listOfOpenFiles; listOfOpenFiles = 0;}
	
	if (pPopUpFiles) {delete pPopUpFiles; pPopUpFiles = 0;}
	if (pPopUp) {delete pPopUp; pPopUp = 0;}
}

void arnEdlFileManager::contextMenuEvent ( QContextMenuEvent * e )
{
//arnDebug("Entrato\n");
	pPopUp->exec(QCursor::pos());
	e->accept();
}

void arnEdlFileManager::init(void)
{
	hostname = 0;
	status = 0;
	Viewports.clear();
	//Viewports.setAutoDelete(true);
	
	listOfOpenFiles = new QList<arnEFMFileDescr *>;
	if (!listOfOpenFiles) arnCriticalExit();
	listOfOpenFiles->clear();
	//listOfOpenFiles->setAutoDelete(true);
	// nesun file aperto
	currentOpenFile = 0;
	// popup menus
	pPopUp = new QMenu(this);
	if (!pPopUp) arnCriticalExit();
	pPopUpFiles = new QMenu(this);
	if (!pPopUpFiles) arnCriticalExit();
	pPopUp->insertItem("Files",pPopUpFiles);
	pPopUpFiles->setCheckable (true);

	addColumn(trUtf8("Channels"));
	addColumn(trUtf8("Values"));

	connect(this, SIGNAL(doubleClicked ( Q3ListViewItem *, const QPoint &, int )), this, SLOT(doubleClicked_hndl ( Q3ListViewItem *, const QPoint &, int )));
	connect(this, SIGNAL(clicked ( Q3ListViewItem * )), this, SLOT(clicked_hndl ( Q3ListViewItem * )));
	connect(this, SIGNAL(itemRenamed ( Q3ListViewItem *, int, const QString & )), this, SLOT(itemRenamed_hndl ( Q3ListViewItem *, int, const QString & )));

}


const QPixmap arnEdlFileManager::getColorPixmap(arnEdlChannel* ch)
{
	char** xpm;
	xpm = new char*[19];
	if (!xpm) arnCriticalExit();
	xpm[18] = 0;
	for (unsigned int i = 0; i < 18; i++) {
		if (i == 1) continue;
		xpm[i] = (char*)xpm_colorrect[i];
		}
	xpm[1] = new char[16];
	strcpy(xpm[1],". c ");
	if (ch) {
		strcat(xpm[1],ch->Color().name());
		}
	else {
		QColor c("blue");
		strcat(xpm[1],c.name());
		}
	QPixmap res((const char**)xpm);
	delete [] xpm[1]; xpm[1] = 0;
	return res;
}

void arnEdlFileManager::updateListView(arnEFMFileDescr *fdes)
{
	Q3ListViewItem * itemRoot = 0;
	Q3ListViewItem * itemFather = 0;
	Q3ListViewItem * itemCurrent = 0;
	QString app;
	if (!fdes || !fdes->fileInfo || !fdes->channelList) return;

	clear ();
	
	itemRoot = new __myQ3ListViewItem( this);
	if (!itemRoot) arnCriticalExit();
	itemRoot->setText(0, trUtf8("DATA"));
    
	itemFather = itemRoot;
	itemCurrent = new __myQ3ListViewItem(itemFather,itemFather);
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("File Info"));

	itemFather = itemCurrent;

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Device Code"));
	itemCurrent->setText( 1, trUtf8(fdes->fileInfo->DeviceCode()));

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Creation Date"));
	itemCurrent->setText( 1, trUtf8(fdes->fileInfo->CreationDate()));

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Creation Time"));
	itemCurrent->setText( 1, trUtf8(fdes->fileInfo->CreationTime()));
	
	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Last Modify Date"));
	itemCurrent->setText( 1, trUtf8(fdes->fileInfo->LastmodifyDate()));

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Last Modify Time"));
	itemCurrent->setText( 1, trUtf8(fdes->fileInfo->LastmodifyTime()));

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Description"));
	itemCurrent->setText( 1, trUtf8(fdes->fileInfo->Description()));
	//itemCurrent->setMultiLinesEnabled (true);
	
	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("ChannelNumber"));
	itemCurrent->setText( 1, trUtf8(app.setNum(fdes->fileInfo->ChannelNumber())));
	
	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("SystemTimer"));
	itemCurrent->setText( 1, trUtf8(app.setNum(fdes->fileInfo->SystemTimer())));
	
	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("NumberOfFrames"));
	itemCurrent->setText( 1, trUtf8(app.setNum(fdes->fileInfo->NumberOfFrames())));

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("NumberOfPackets"));
	itemCurrent->setText( 1, trUtf8(app.setNum(fdes->fileInfo->NumberOfPackets())));

	itemCurrent = new __myQ3ListViewItem ( itemFather, itemFather );
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("NumberOfNotValidPackets"));
	itemCurrent->setText( 1, trUtf8(app.setNum(fdes->fileInfo->NumberOfNotValidPackets())));

	itemFather = itemRoot;
	itemCurrent = new __myQ3ListViewItem(itemFather,itemFather);
	if (!itemCurrent) arnCriticalExit();
	itemCurrent->setText( 0, trUtf8("Channel List"));

	itemFather = itemCurrent;
	for (unsigned int i = 0; i < fdes->fileInfo->ChannelNumber(); i++) {
		arnEdlChannel* chn = fdes->channelList->channel(i);
		if (chn) {
			itemCurrent = new __myQ3CheckListItem ( itemFather, itemFather,chn->Name(),chn->Color(),Q3CheckListItem::CheckBox);
			if (!itemCurrent) arnCriticalExit();
			((__myQ3CheckListItem*)itemCurrent)->pChannel = chn;
			if (((__myQ3CheckListItem*)itemCurrent)->pChannel->Shown()) ((__myQ3CheckListItem*)itemCurrent)->setOn(true);
			Q3ListViewItem * lf = (__myQ3ListViewItem *)itemCurrent;

			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("SamplingTime"));
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->SamplingTime())));

			itemCurrent = new __myQ3ListViewItem ( lf, lf);
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, "Color");
			//itemCurrent->setText( 1, trUtf8(chn->Color().name()));
			itemCurrent->setPixmap( 1,getColorPixmap(chn));
			
			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("Viewport"));
			((__myQ3ListViewItem*)itemCurrent)->pChannel = chn;
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->Viewport())));

			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("Floor"));
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->Floor())));

			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("Ceil"));
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->Ceil())));

			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("Min"));
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->Min())));

			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("Max"));
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->Max())));
			
			itemCurrent = new __myQ3ListViewItem ( lf, lf );
			if (!itemCurrent) arnCriticalExit();
			itemCurrent->setText( 0, trUtf8("LineType"));
			itemCurrent->setText( 1, trUtf8(app.setNum(chn->LineType())));
			}
		}

	// settaggi di apertura menu
	this->setRootIsDecorated(true);
	if (itemRoot) this->setOpen(itemRoot, true);
	if (itemRoot->firstChild()) this->setOpen(itemRoot->firstChild(), true);
	if (itemRoot->firstChild()) {
		__myQ3ListViewItem *r = ((__myQ3ListViewItem *)(itemRoot->firstChild()));
		__myQ3CheckListItem *it;
		for (it = ((__myQ3CheckListItem*)(r->firstChild())); it; it = ((__myQ3CheckListItem*)(it->nextSibling()))) {
			if (it->pChannel) {
				if (it->pChannel->Open()) {
					it->pChannel->setOpen(0);
					it->setOn(true);
					clicked_hndl(it);
					}
				}
			}
		}
}

void arnEdlFileManager::setCurrent(int indx)
{
	if (indx == -1)  {currentOpenFile = 0;}
	else if (indx < int(listOfOpenFiles->count())) {currentOpenFile = ((arnEFMFileDescr *)listOfOpenFiles->at(indx));}
	else {currentOpenFile = 0;}
	updateListView(currentOpenFile);
	doCurrentChange(currentOpenFile);
}

void arnEdlFileManager::setCurrent(const char* fname)
{
	bool found = false;
	int i;
	if (!fname)  {currentOpenFile = 0;}
	else {
		for ( i = 0; i < int(listOfOpenFiles->count()); ++i ) {
			if (!strcmp(((arnEFMFileDescr *)listOfOpenFiles->at(i))->filename.latin1(),fname)) { // variabile gia' trovata
				found = true;
				break;
				}
			}
		if (!found) currentOpenFile = 0;
		currentOpenFile = ((arnEFMFileDescr *)listOfOpenFiles->at(i));
		}
	updateListView(currentOpenFile);
	doCurrentChange(currentOpenFile);
	return;
}

arnEFMFileDescr* arnEdlFileManager::getOpenFile(int indx)
{
	if (indx < int(listOfOpenFiles->count())) {
		return ((arnEFMFileDescr *)listOfOpenFiles->at(indx));
		}
	return 0;
}

arnEFMFileDescr* arnEdlFileManager::getOpenFile(const char* fname)
{
	bool found = false;
	int i;
	for ( i = 0; i < int(listOfOpenFiles->count()); ++i ) {
		if (!strcmp(((arnEFMFileDescr *)listOfOpenFiles->at(i))->filename.latin1(),fname)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return 0;
	return ((arnEFMFileDescr *)listOfOpenFiles->at(i));
}

bool arnEdlFileManager::addOpenFile(const char* fname)
{
	arnEFMFileDescr *tmp;
	int i;
	for (i = 0; i < listOfOpenFiles->count(); i++) {
		if (!strcmp(((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->filename.latin1(),fname)) return false;
		}
	tmp = new arnEFMFileDescr();
	if (!tmp) arnCriticalExit();
	tmp->filename = fname;
	char outbff[MAXPATHLEN];
	QString name(arnExtactFileName(outbff,fname));
	QAction *file = new QAction(this,name);
	if (!file) arnCriticalExit();
	file->setText( trUtf8(name));
	file->setMenuText( trUtf8(name));
	file->setToolTip( trUtf8(name));
	file->setToggleAction(true);
	tmp->action = file;
	listOfOpenFiles->append(tmp);
	// connect
	connect( file, SIGNAL( activated() ), this, SLOT( actfile_hndl() ) );
	//....
	file->addTo(pPopUpFiles);
	for (i = 0; i < (listOfOpenFiles->count() - 1); i++) {
		QAction *act = ((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action;
		if (act) {act->setOn(false);}
		}
	//pPopUpFiles->setItemChecked(pPopUpFiles->idAt(pPopUpFiles->count() - 1),true);
	((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action->setOn(true);
// 	setCurrent(i);
	if (/*Current() && */(listOfOpenFiles->count() == 1)) {
#ifdef HAVE_IDPS
		status = idpsConnect(hostname, 0);
		if( status ) {
			arnDebug("%s\n", emessage(status));
			return false;
			}
		// Faccio una specie di ping alla stessa
		status = idpsCheck();
		if( status ) {
			arnDebug("%s\n", emessage(status));
			return false;
			}
		// proteggo il server da eventuali interrupt e signals
		status = idpsSigEnable(0);
		if( status ) {
			arnDebug("%s\n", emessage(status));
			return false;
			}
#else
		status = 0;
#endif
		}
	return true;
}

void arnEdlFileManager::actfile_hndl(void)
{
	QAction *action = (QAction *)(sender());
	int i;
	for (i = 0; i < (listOfOpenFiles->count()); i++) {
		QAction *act = ((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action;
		if (act) {act->setOn(false);}
		}
	bool found = false;
	for (i = 0; i < listOfOpenFiles->count(); i++) {
		QAction *act = ((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action;
		if (act && (act->name() == action->name())) {
			found = true;
			break;
			}
		}
	if (!found) return;
	setCurrent(i);
	action->setOn(true);
}

bool arnEdlFileManager::deleteClosedFile(const char* fname)
{
	bool found = false;
	int i;
	char outbff[MAXPATHLEN];
	QString name(arnExtactFileName(outbff,fname));
	for (i = 0; i < listOfOpenFiles->count(); i++) {
		QAction *act = ((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action;
		if (act->name() == name) {
			found = true ;
			break;
			}
		}
	if (found) pPopUpFiles->removeItemAt(i);
	//
	found = false;
	for (i = 0; i < (listOfOpenFiles->count()); i++) {
		if (!strcmp(((arnEFMFileDescr *)listOfOpenFiles->at(i))->filename.latin1(),fname)) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return false;
	arnEFMFileDescr *ptr = listOfOpenFiles->at(i);
	listOfOpenFiles->removeAt(i);
	if (ptr) delete ptr;
	for (i = 0; i < (listOfOpenFiles->count() - 1); i++) {
		QAction *act = ((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action;
		if (act) {act->setOn(false);}
		}
	((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action->setOn(true);
	setCurrent(i);
	if (!Current()) {
#ifdef HAVE_IDPS
		status = idpsClose();
		if( status ) {
			arnDebug("%s\n", emessage(status));
			return false;
			}
#else
		status = 0;
#endif
		}
	return true;
}

bool arnEdlFileManager::deleteCurrentOpenFile(void)
{
	bool found = false;
	int i;
	char outbff[MAXPATHLEN];
	//arnDebug("%d\n",listOfOpenFiles->count());
	if (!(listOfOpenFiles->count())) return true;
	QString name(arnExtactFileName(outbff,currentOpenFile->filename.latin1()));
	//arnDebug("%s\n",name.latin1());
	for ( i = 0; i < (listOfOpenFiles->count()); ++i ) {
		if (((arnEFMFileDescr *)listOfOpenFiles->at(i))->filename == currentOpenFile->filename) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (found) pPopUpFiles->removeItemAt(i);
	found = false;
	for ( i = 0; i < (listOfOpenFiles->count()); ++i ) {
		if (((arnEFMFileDescr *)listOfOpenFiles->at(i))->filename == currentOpenFile->filename) { // variabile gia' trovata
			found = true;
			break;
			}
		}
	if (!found) return false;
//BEGIN nuova implementazione eliminazione traccie grafiche
	for (unsigned int j = 0; j < ((arnEFMFileDescr *)listOfOpenFiles->at(i))->channelList->count(); j++) {
		arnEdlChannel *pChannel = ((arnEFMFileDescr *)listOfOpenFiles->at(i))->channelList->channel(j);
		if (pChannel && pChannel->Shown()) {
#ifdef HAVE_IDPS
			status = idpsDeleteObject(pChannel->DataID());
			if( status ) {
				arnDebug("%s\n", emessage(status));
				return false;
				}
#endif
			pChannel->setDataID(0);
			pChannel->setShown(false);
			for (unsigned int i = 0; i <pChannel->Frames(); i++) {
				arnEdlFrame_t *pb = pChannel->Frame(i);
#ifdef HAVE_IDPS
				status = idpsDeleteObject(pb->marker);
				if( status ) {
					arnDebug("%s\n", emessage(status));
					return false;
					}
#endif
				pb->marker = 0;
				}
			QList<arnViewport*>::iterator vp;
			for (vp = Viewports.begin(); vp != Viewports.end(); ++vp) {
				if ((pChannel->IdpsViewport()) == ((*vp)->IdpsViewport())) {
					if ((*vp)->removeChannel(pChannel) && ((*vp)->isEmpty())) {
#ifdef HAVE_IDPS
						status = idpsDeleteObject((*vp)->IdpsViewport());
						if( status ) {
							arnDebug("%s\n", emessage(status));
							return false;
							}
#endif
						Viewports.removeAt(Viewports.indexOf(*vp));
						}
					pChannel->setIdpsViewport(0);
					break;
					}
				}
#ifdef HAVE_IDPS
			idpsUpdate();
#endif
			}
		}
//END nuova implementazione eliminazione traccie grafiche
	arnEFMFileDescr *ptr = listOfOpenFiles->at(i);
	listOfOpenFiles->removeAt(i);
	if (ptr) delete ptr;
	if (!(listOfOpenFiles->count())) {setCurrent(-1);}
	else {
		for (i = 0; i < (listOfOpenFiles->count() - 1); i++) {
			QAction *act = ((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action;
			if (act) {act->setOn(false);}
			}
		((arnEFMFileDescr*)(listOfOpenFiles->at(i)))->action->setOn(true);
		setCurrent(i);
		}
	if (!Current()) {
#ifdef HAVE_IDPS
		status = idpsClose();
		if( status ) {
			arnDebug("%s\n", emessage(status));
			return false;
			}
#else
		status = 0;
#endif
		}
	return true;
}

void arnEdlFileManager::doCurrentChange( const arnEFMFileDescr* d)
{
	emit currentChanged(d);
}

const char* arnEdlFileManager::emessage(int code)
{
#ifdef HAVE_IDPS
	static char text[128];
	idpsMessage(code, text, sizeof(text));
#else
	code = 0;
	static char text[128] = "Unknown error code.";
#endif
	return text;
}

void arnEdlFileManager::doubleClicked_hndl ( Q3ListViewItem *item, const QPoint &p, int o)
{
/**/
	if (!item || p == QPoint() || o == 0) {;}
}

void arnEdlFileManager::itemRenamed_hndl ( Q3ListViewItem * item, int col, const QString & text )
{
	if (!col) {;}
	if (item && Current()) {
		if (item->text(0) == "Description") {
			Current()->fileInfo->setDescription(text);
			return;
			}
		__myQ3ListViewItem* it = (__myQ3ListViewItem*)item;
		if (it->type() == alvit_ListViewItem) {
			if (it->text(0) == "Viewport") {
				it->pChannel->setViewport(text.toInt());
				return;
				}
			}
		}
}

void arnEdlFileManager::clicked_hndl ( Q3ListViewItem * item )
{
	if (!item) return;
	__myQ3ListViewItem* it = (__myQ3ListViewItem*)item;
	if (it->type() == alvit_ListViewItem) {
		//arnDebug("alvit_ListViewItem; %s\n",item->text(0).latin1());
		if (item->text(0) == "Color") {
			QColor c = QColorDialog::getColor (QColor("white"), this,"dataColorDialog");
			if (c.isValid()) {
				if (((__myQ3CheckListItem *)(item->parent()))->pChannel) {
					((__myQ3CheckListItem *)(item->parent()))->pChannel->setColor(c);
					((__myQ3CheckListItem *)(item->parent()))->setColor(c);
					item->setPixmap( 1,getColorPixmap(((__myQ3CheckListItem *)(item->parent()))->pChannel));
					repaintItem((item));
					repaintItem((item->parent()));
					}
				}
			}
		else if (item->text(0) == "Description") {
			item->setRenameEnabled (1, true );
			item->startRename (1);
			}
		else if (item->text(0) == "Viewport") {
			item->setRenameEnabled (1, true );
			item->startRename (1);
			}
		}
	else if (it->type() == alvit_CheckListItem) {
		//arnDebug("alvit_CheckListItem; %s\n",item->text(0).latin1());
		__myQ3CheckListItem *pItem = (__myQ3CheckListItem*)item;
		if (pItem->isOn()) {
			if (pItem->pChannel->Shown()) {
				/*arnDebug("%s\n",pItem->pChannel->Name().latin1());*/
				return;
				}
			}
		else {
			if (!pItem->pChannel->Shown()) {
				/*arnDebug("%s\n",pItem->pChannel->Name().latin1());*/
				return;
				}
			}
		
		if (pItem->isOn()) {
			// parte di determinazione viewport
			bool found = false;
			QList<arnViewport*>::iterator vp;
			for (vp = Viewports.begin(); vp != Viewports.end(); ++vp) {
				if (pItem->pChannel->Viewport() == (*vp)->Viewport()) { // trovata la viewport cercata
					(*vp)->addChannel(pItem->pChannel);
					pItem->pChannel->setIdpsViewport((*vp)->IdpsViewport());
					found = true;
					break;
					}
				}
			if (!found) {
#ifdef HAVE_IDPS
				unsigned int lwp = 0;
				status = idpsNewViewPort("Channels","time (s)","data");
				if( status ) {
					arnDebug("%s\n", emessage(status));
					return;
					}
				status = idpsGetLastPort(&lwp);
				if( status ) {
					arnDebug("%s\n", emessage(status));
					return;
					}
				arnViewport* wp = new arnViewport(pItem->pChannel->Viewport(),lwp);
				if (!wp) arnCriticalExit();
				wp->addChannel(pItem->pChannel);
				pItem->pChannel->setIdpsViewport(lwp);
				Viewports.append(wp);
#endif
				}
			// parte di costruizone traccia
			unsigned int totdim = 0;
			for (unsigned int i = 0; i < pItem->pChannel->Frames(); i++) {
				totdim +=  pItem->pChannel->Frame(i)->data.count();
				}
			//arnDebug("totdim %d\n",totdim);
/*			arnDebug("Current()->fileInfo->SystemTimer() = %f\n",Current()->fileInfo->SystemTimer());
			arnDebug("pItem->pChannel->SamplingTime() = %f\n",pItem->pChannel->SamplingTime());*/
			float *xBff = new float[totdim + 4];
			float *yBff = new float[totdim + 4];
			if (!xBff || !yBff) arnCriticalExit();
			for (unsigned int i = 0; i < totdim; i++) {
				xBff[i] = (float(i) * ((Current()->fileInfo->SystemTimer() * pItem->pChannel->SamplingTime()) / 1000000.0));
				//arnDebug("xBff[%d] = %f\n",i,xBff[i]);
				}
			totdim = 0;
			for (unsigned int i = 0; i < pItem->pChannel->Frames(); i++) {
				arnEdlFrame_t *pb = pItem->pChannel->Frame(i);
				for (int j = 0; j < pItem->pChannel->Frame(i)->data.count(); j++) {
					yBff[totdim + j] = (*(pb)).data[j];
					//arnDebug("yBff[%d] = %f\n",j,yBff[j]);
					}
				totdim += pItem->pChannel->Frame(i)->data.count();
				}
			QColor c(pItem->pChannel->Color());
			//arnDebug("%d,%d,%d\n",c.red(),c.green(),c.blue());
#ifdef HAVE_IDPS
			status = idpsDefPlotColor(float(c.red()) / 255.0 ,float(c.green()) / 255.0,float(c.blue()) / 255.0);
			if( status ) {
				arnDebug("%s\n", emessage(status));
				delete [] xBff; xBff = 0;
				delete [] yBff; yBff = 0;
				return;
				}
			status = idpsDefMarkColor(float(c.red()) / 255.0 ,float(c.green()) / 255.0,float(c.blue()) / 255.0);
			if( status ) {
				arnDebug("%s\n", emessage(status));
				delete [] xBff; xBff = 0;
				delete [] yBff; yBff = 0;
				return;
				}
			status = idpsPolyLine(pItem->pChannel->IdpsViewport(), totdim, xBff,  yBff);
			if( status ) {
				arnDebug("%s\n", emessage(status));
				delete [] xBff; xBff = 0;
				delete [] yBff; yBff = 0;
				return;
				}
			unsigned int dataID;
			status = idpsGetLastData(&dataID);
			if( status ) {
				arnDebug("%s\n", emessage(status));
				delete [] xBff; xBff = 0;
				delete [] yBff; yBff = 0;
				return;
				}
			status = idpsPlotLabel(dataID, pItem->pChannel->Name().latin1(), "X %.2f Y %.2f");
			if( status ) {
				arnDebug("%s\n", emessage(status));
				delete [] xBff; xBff = 0;
				delete [] yBff; yBff = 0;
				return;
				}
			pItem->pChannel->setDataID(dataID);
			pItem->pChannel->setShown(true);
#else
		status = 0;
#endif
			// set dei frame markers
			totdim = 0;
			for (unsigned int i = 0; i < pItem->pChannel->Frames(); i++) {
#ifdef HAVE_IDPS
				char fb[32] = "Frm-";
				strcat(fb,QString::number(i + 1).latin1());
				arnEdlFrame_t *pb = pItem->pChannel->Frame(i);
				totdim += (pItem->pChannel->Frame(i)->data.count());
				status = idpsAxisMarker(pItem->pChannel->IdpsViewport(), AXISMARK_X, xBff[totdim - 1],  xBff[totdim - 1],fb);
				if( status ) {
					arnDebug("%s\n", emessage(status));
					delete [] xBff; xBff = 0;
					delete [] yBff; yBff = 0;
					return;
					}
				status = idpsGetLastMarker(&dataID);
				if( status ) {
					arnDebug("%s\n", emessage(status));
					delete [] xBff; xBff = 0;
					delete [] yBff; yBff = 0;
					return;
					}
				pb->marker = dataID;
#else
				status = 0;
#endif
				//arnDebug("%d\n",pb->marker);
				}
			delete [] xBff; xBff = 0;
			delete [] yBff; yBff = 0;
			}
		else {
#ifdef HAVE_IDPS
			status = idpsDeleteObject(pItem->pChannel->DataID());
			if( status ) {
				arnDebug("%s\n", emessage(status));
				return;
				}
			pItem->pChannel->setDataID(0);
			pItem->pChannel->setShown(false);
			for (unsigned int i = 0; i < pItem->pChannel->Frames(); i++) {
				arnEdlFrame_t *pb = pItem->pChannel->Frame(i);
				status = idpsDeleteObject(pb->marker);
				if( status ) {
					arnDebug("%s\n", emessage(status));
					return;
					}
				pb->marker = 0;
				}
			QList<arnViewport*>::iterator vp;
			for (vp = Viewports.begin(); vp != Viewports.end(); ++vp) {
				if ((pItem->pChannel->IdpsViewport()) == ((*vp)->IdpsViewport())) {
					if ((*vp)->removeChannel(pItem->pChannel) && ((*vp)->isEmpty())) {
						status = idpsDeleteObject((*vp)->IdpsViewport());
						if( status ) {
							arnDebug("%s\n", emessage(status));
							return;
							}
						Viewports.removeAt(Viewports.indexOf(*vp));
						}
					pItem->pChannel->setIdpsViewport(0);
					break;
					}
				}
			idpsUpdate();
#else
			status = 0;
#endif
			}
		}
	else {
		arnDebug("alvit__NoneItem; %s\n",item->text(0).latin1());
		}
	return;
}
