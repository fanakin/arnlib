/***************************************************************************
                          arnParametric.h  -  description
                             -------------------
    begin                : ven mar 7 2003
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
#ifndef ArnParametricH
#define ArnParametricH

#include <qstring.h>
#include <qlabel.h>
#include <qstatusbar.h>
#include <qapplication.h>

#include "arnlibtypes.h"
#include "arnConfig.h"
#include "arnCarrier.h"

typedef union memImage {
            unsigned char *arr/*[sizeof(arnParameter_t)]*/;
            } memImage_t;
typedef struct memWrapper {
            memImage_t memoryImg;
            unsigned int memImageDim;
            unsigned int memImageDisp;
            memWrapper(void) {memoryImg.arr = 0;}
            } memWrapper_t;

class arnParContainer {
private:
protected:
    QList<memWrapper_t *> memWrapperList;
    //QPtrList<memWrapper_t> memWrapperList;
		unsigned int currentMemListElemIndex;
        QString codeID;
        QString comments;
    public:
        arnParContainer(unsigned int dim);
        arnParContainer(unsigned int dim,unsigned int nSegs);
        arnParContainer(const arnParContainer& aPar);
        ~arnParContainer(void);
        arnParContainer& operator = (const arnParContainer& aPar);
        bool operator == (const arnParContainer& aPar);
        unsigned int memImageSizeOf(void);
        inline QString& CodeID(void) {return codeID;}
        inline QString& Comments(void) {return comments;}
        inline void setCodeID(QString& cd) {codeID = cd;}
        inline void setComments(QString& cd) {comments = cd;}
        inline void setCodeID(const char* cd) {codeID = cd;}
        inline void setComments(const char* cd) {comments = cd;}
        inline memWrapper_t* getmemWrapper(void) {if (!memWrapperList.count()) return 0; return memWrapperList[currentMemListElemIndex];}
        memWrapper_t* getmemWrapper(unsigned int indx);
        inline unsigned int count(void) {return memWrapperList.count();}
		inline void setCurrentParameters(unsigned int indx) {
			if (indx < ((unsigned int)memWrapperList.count()))  currentMemListElemIndex = indx;
			else currentMemListElemIndex = 0;
			}
		inline unsigned int CurrentParameters(void) {return currentMemListElemIndex;}
};

class arnParametric : arnConfig {
    private:
    protected:
		bool isAValidMappa;
        arnParContainer *pMappa;
        QStatusBar* outDisplay;
        QApplication* appl;
        arnCarrier *pMon;

        bool LoadHeader(const QDomDocument &doc, const QDomNode &cur);
        void LoadComment(const QDomDocument &doc, const QDomNode &cur);
        bool LoadCodeID(const QDomDocument &doc, const QDomNode &cur);
        bool LoadnSegments(const QDomDocument &doc, const QDomNode &cur);
        void LoadData(const QDomDocument &doc, const QDomNode &cur);
        bool createDoc(bool zerod = true);
        bool ldfile(const char* fname);

	QDomNode addTextNode (QDomNode &node, const QString &tag, const QString &value);
	QString getTextNode (const QDomNode &node);
    
    public:
    /*! \brief default constructor
    *
    * Ex:\n
    * ...\n
    */
    arnParametric(unsigned int dim);

    /*! \brief default constructor
    *
    * Ex:\n
    * ...\n
    */
    arnParametric(unsigned int dim,unsigned int nSegs);

    /*! \brief copy contructor
    *
    * Ex:\n
    * ...\n
    */
    arnParametric(const arnParametric& aPar);

    /*! \brief assignment operator
    *
    * Ex:\n
    * ...\n
    */
    arnParametric& operator = (const arnParametric& aPar);

    bool operator == (const arnParametric& aPar);

    /*! \brief destructor
    *
    * Ex:\n
    * ...\n
    */
    ~arnParametric(void);

    virtual bool loadfile(const char* fname);
    virtual bool loadfile(const char* absdir, const char* filename);
    virtual bool loadfile(char *buffer, int size); // usa la xmlDocPtr xmlParseMemory(char *buffer, int size);
    virtual bool createfile(const char* absdir, const char* filename);
    virtual bool createfile(const char* fname);
    virtual bool saveasfile(const char* absdir, const char* filename);
    virtual bool saveasfile(const char* fname);
    virtual bool savefile(void);
    inline virtual bool send(void) {return false;}
    inline virtual bool receive(void) {return false;}
    virtual void reset(void);
    inline arnParContainer& getParContainer(void) {return (*pMappa);}
    inline void setOutDisplay(QStatusBar* outD) {outDisplay = outD;}
    inline void setApplication(QApplication* app) {appl = app;}

	/*! \brief
	*
	* Ex:\n
	* ...\n
	*/
	inline void setCarrier(arnCarrier *Cr) {pMon = Cr;}

	/*! \brief
	*
	* Ex:\n
	* ...\n
	*/
	inline bool IsAValidSetOfParameters(void) {return isAValidMappa;}
};

#endif
