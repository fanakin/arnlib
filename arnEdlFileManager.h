/***************************************************************************
                          arnEdlFileManager.h  -  description
                             -------------------
    begin                : gio giu 16 2005
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

#ifndef ArnEdlFileManagerH
#define ArnEdlFileManagerH

#include <qaction.h>
#include <qframe.h>
#include <qlayout.h>
#include <Q3ListView>
#include <QList>
#include <QMenu>
#include "arnEdlFileInfo.h"
#include "arnEdlChannelList.h"
#include "CommonFunctions.h"


// ---------------------------------------------------
// ***************************************************
// --------- arnEFMFileDescr -------------------
// ***************************************************
// ---------------------------------------------------
class arnEFMFileDescr
{
	private:
	protected:
	public:
		arnEdlFileInfo *fileInfo;
		arnEdlChannelList *channelList;
		QAction *action;
		QString filename;
		arnEFMFileDescr(void);
		~arnEFMFileDescr(void);
		};

class arnViewport {
	private:
	protected:
		QList<arnEdlChannel*> channel;
		int viewport; // -1 non e' un valore valido; viewport logica; 0,1,2,etc.
		int idpsviewport; // -1 non e' un valore valido per le viewport idps
	public:
		arnViewport(int v = -1,int lv = -1) {/*channel.setAutoDelete(false);*/ viewport = v;idpsviewport = lv;}
		~arnViewport(void) {;}
		inline int Viewport(void) {return viewport;}
		inline int IdpsViewport(void) {return idpsviewport;}
		inline void addChannel (const arnEdlChannel* c) {channel.append((arnEdlChannel*)c);}
		inline bool removeChannel(const arnEdlChannel* c) {int i = channel.indexOf((arnEdlChannel*)c); if (i == -1) return false; channel.removeAt(i); return true;}
		inline int findChannel(const  arnEdlChannel* c) {
			QList<arnEdlChannel*>::iterator i;
			for (i = channel.begin(); i != channel.end(); ++i) {
				if (*i == c) return true;
				}
			return false;
			}
		inline bool isEmpty(void) {return channel.isEmpty();}
	};

typedef enum arnListViewItem {
    alvit_ListViewItem,
    alvit_CheckListItem,
    alvit__NoneItem
    } arnListViewItem_t;
	
class __containerQ3ListViewItem
{
	private:
	protected:
		arnListViewItem_t tpy;
	public:
		arnEdlChannel* pChannel;
		__containerQ3ListViewItem(void) {pChannel = 0;}
		~__containerQ3ListViewItem(void) {;}
		inline arnListViewItem_t type(void) {return tpy;}
};

class __myQ3ListViewItem : public Q3ListViewItem, public __containerQ3ListViewItem
{
	private: 
		void init(const QColor& c) {
			//arnDebug("Init\n");
			tpy = alvit_ListViewItem; color_ = c;
			}
	private slots:
	protected:
		QColor color_;
	protected slots:
	signals:
	public:
		__myQ3ListViewItem ( Q3ListView * parent,const QColor& c = QColor("black") )
			: Q3ListViewItem(parent), __containerQ3ListViewItem()
			{init(c);}
		__myQ3ListViewItem ( Q3ListViewItem * parent,const QColor& c = QColor("black") )
			: Q3ListViewItem(parent), __containerQ3ListViewItem()
			{init(c);}
		__myQ3ListViewItem ( Q3ListView * parent, Q3ListViewItem * after, const QColor& c = QColor("black"))
			: Q3ListViewItem(parent, after),__containerQ3ListViewItem()
			{init(c);}
		__myQ3ListViewItem ( Q3ListViewItem * parent, Q3ListViewItem * after,const QColor& c = QColor("black"))
			: Q3ListViewItem(parent, after),__containerQ3ListViewItem()
			{init(c);}
		__myQ3ListViewItem ( Q3ListView * parent, QString label1,const QColor& c = QColor("black"), QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null )
		: Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8), __containerQ3ListViewItem()
		 {init(c);}
		__myQ3ListViewItem ( Q3ListViewItem * parent, QString label1,const QColor& c = QColor("black"), QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null  )
		: Q3ListViewItem(parent, label1, label2, label3, label4, label5, label6, label7, label8),__containerQ3ListViewItem()
		{init(c);}
		__myQ3ListViewItem ( Q3ListView * parent, Q3ListViewItem * after, QString label1,const QColor& c = QColor("black"), QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null )
		: Q3ListViewItem(parent, after,label1, label2, label3, label4, label5, label6, label7, label8),__containerQ3ListViewItem() {init(c);}
		__myQ3ListViewItem ( Q3ListViewItem * parent, Q3ListViewItem * after,QString label1,const QColor& c = QColor("black"), QString label2 = QString::null, QString label3 = QString::null, QString label4 = QString::null, QString label5 = QString::null, QString label6 = QString::null, QString label7 = QString::null, QString label8 = QString::null  )
		: Q3ListViewItem(parent, after,label1, label2, label3, label4, label5, label6, label7, label8), __containerQ3ListViewItem() {init(c);}
		~__myQ3ListViewItem(void) {;}
		virtual void paintCell(QPainter *p, const QColorGroup &cg, int column, int width, int alignment) {
			QColorGroup colorGroup(cg);
			QColor color = colorGroup.text();
			colorGroup.setColor(QColorGroup::Text, color_);
			Q3ListViewItem::paintCell(p, colorGroup, column, width, alignment);
			colorGroup.setColor(QColorGroup::Text, color);
			}
		inline const QColor& color(void)  {return color_;}
		inline void setColor(QColor c)  {color_ = c;}
	public slots:
};

class __myQ3CheckListItem : public Q3CheckListItem, public __containerQ3ListViewItem
{
	private:
		void init(const QColor& c) {
			//arnDebug("Init\n");
			tpy = alvit_CheckListItem; color_ = c;
			}
	private slots:
	protected:
		QColor color_;
	protected slots:
	signals:
	public:
		__myQ3CheckListItem ( Q3CheckListItem * parent, const QString & text, const QColor& c = QColor("black"), Type tt = Controller )
			: Q3CheckListItem (parent,text,tt), __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem ( Q3CheckListItem * parent, Q3ListViewItem * after, const QString & text, const QColor& c = QColor("black") , Type tt = Controller )
			: Q3CheckListItem( parent,after,text,tt),  __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem( Q3ListViewItem * parent, const QString & text, const QColor& c = QColor("black"), Type tt = Controller )
			: Q3CheckListItem(parent,text,tt), __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem( Q3ListViewItem * parent, Q3ListViewItem * after, const QString & text,const QColor& c = QColor("black"), Type tt = Controller )
			: Q3CheckListItem(parent,after,text,tt), __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem( Q3ListView * parent, const QString & text,const QColor& c = QColor("black"), Type tt = Controller )
			: Q3CheckListItem (parent,text,tt ), __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem ( Q3ListView * parent, Q3ListViewItem * after, const QString & text,const QColor& c = QColor("black"),Type tt = Controller )
			: Q3CheckListItem(parent,after,text,tt), __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem( Q3ListViewItem * parent, const QString & text, const QPixmap & p,const QColor& c = QColor("black") )
			: Q3CheckListItem (parent,text,p), __containerQ3ListViewItem()
			{init(c);}
		__myQ3CheckListItem( Q3ListView * parent, const QString & text, const QPixmap & p,const QColor& c = QColor("black"))
			: Q3CheckListItem(parent,text,p), __containerQ3ListViewItem()
			{init(c);}
		~__myQ3CheckListItem(void) {;}
		virtual void paintCell(QPainter *p, const QColorGroup &cg, int column, int width, int alignment) {
			QColorGroup colorGroup(cg);
			QColor color = colorGroup.text();
			colorGroup.setColor(QColorGroup::Text, color_);
			Q3CheckListItem::paintCell(p, colorGroup, column, width, alignment);
			colorGroup.setColor(QColorGroup::Text, color);
			}
		//inline arnListViewItem_t type(void) {return tpy;}
		inline const QColor& color(void)  {return color_;}
		inline void setColor(QColor c)  {color_ = c;}
	public slots:
};

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlFileManager -------------------
// ***************************************************
// ---------------------------------------------------
class arnEdlFileManager : public Q3ListView
{
	Q_OBJECT
	
	private:
		/*! \brief it converts the status code into a text message
		*
		* @param code in the status code
		* @return the pointer to a string containg the text message
		* 
		* This  function instatiates a static text buffer vfor getting the message. \n
		* It returns the pointer to the string so the user does NOT free the pointer. \n
		* Ex:
		* ...
		* status = idpsConnect(hostname, 0);
		* if( status ) {
		*   fprintf(stderr, "%s\n", emessage(status));
		*   ...
		*   }
		* ...
		*/
		const char* emessage(int code);
		
		/*!
		* \brief Inizialization  function
		*
		* It will be called in every constructor; so it implement the common part of the construction process
		*/
		void init(void);
	private slots:
		void doCurrentChange( const arnEFMFileDescr*);
		void actfile_hndl(void);
	protected:
		QList<arnViewport*> Viewports;
		char* hostname; /*!< the name of the hos machine running the idps server. In this implementation always 0 */
		int status; /*!< getting the actual status of the client / server idps system */
		QList<arnEFMFileDescr *> *listOfOpenFiles;
		arnEFMFileDescr *currentOpenFile;
		QMenu *pPopUp;
		QMenu *pPopUpFiles;
		const QPixmap getColorPixmap(arnEdlChannel* ch);
		/*!
		* \brief It builds teh real comma separated value part of the data file during a downloading operation
		*
		* @param fd is the file descriptor
		* @param bff is the buffer containg the data for teh remote device
		* @param len is the length of the buffer
		* @return true, if no problem occurs during the building process and the file is properly made, false otherwise.
		* 
		* This function is called inside the buildFile funtion.
		*/
		//bool buildCSV(FILE *fd,unsigned char* bff,unsigned int len);
		void updateListView(arnEFMFileDescr *fdes);
		virtual void contextMenuEvent ( QContextMenuEvent * e );
	protected slots:
		virtual void doubleClicked_hndl ( Q3ListViewItem *, const QPoint &, int );
		virtual void clicked_hndl ( Q3ListViewItem * );
		virtual void itemRenamed_hndl ( Q3ListViewItem *, int, const QString &);
	signals:
		void currentChanged( const arnEFMFileDescr*);
	public:
		/*!
		* \brief Basic constructor
		*
		* @param nm is the name of the channel.
		* @param vport is the selected viewport for drawing the channel on idps server.
		* 
		* It build a datalogger channel data container
		*/
		arnEdlFileManager ( QWidget * parent = 0, const char * name = 0, Qt::WFlags f = 0 );
		
		/*!
		* \brief Basic destructor
		*
		* It destoryes a datalogger channel data container
		*/
		~arnEdlFileManager(void);
		
		inline arnEFMFileDescr* Current(void) {return currentOpenFile;}
		
		void setCurrent(int indx);
		
		void setCurrent(const char* fname);

		bool addOpenFile(const char* fname);
		
		bool deleteClosedFile(const char* fname);
		
		bool deleteCurrentOpenFile(void);
		
		arnEFMFileDescr* getOpenFile(int indx);
		
		arnEFMFileDescr* getOpenFile(const char* fname);
		

	public slots:
};

#endif
