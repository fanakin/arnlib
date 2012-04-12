/***************************************************************************
                          arnParametric.cpp  -  description
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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <QFile>

#include "arnParametric.h"


arnParContainer::arnParContainer(unsigned int dim)
{
    //memWrapperList.setAutoDelete(true);
    memWrapperList.clear();
	currentMemListElemIndex = 0;
    codeID = "";
    comments = "";
    memWrapper_t *pTmp = new memWrapper_t;
    pTmp->memImageDim = dim;
    pTmp->memImageDisp = 0;
    pTmp->memoryImg.arr = new unsigned char[pTmp->memImageDim];
    if (!(pTmp->memoryImg.arr)) arnCriticalExit();
    memset(pTmp->memoryImg.arr,0,pTmp->memImageDim);
    memWrapperList.append(pTmp);
}

arnParContainer::arnParContainer(unsigned int dim,unsigned int nSegs)
{
    //memWrapperList.setAutoDelete(true);
    memWrapperList.clear();
	currentMemListElemIndex = 0;
    codeID = "";
    comments = "";
    for (unsigned int i = 0; i < nSegs; i++) {
        memWrapper_t *pTmp = new memWrapper_t;
        pTmp->memImageDim = dim;
        pTmp->memImageDisp = 0;
        pTmp->memoryImg.arr = new unsigned char[pTmp->memImageDim];
        if (!(pTmp->memoryImg.arr)) arnCriticalExit();
        memset(pTmp->memoryImg.arr,0,pTmp->memImageDim);
        memWrapperList.append(pTmp);
        }
}

arnParContainer::arnParContainer(const arnParContainer& aPar)
{
    //memWrapperList.setAutoDelete(true);
    memWrapperList.clear();
	currentMemListElemIndex = 0;
    codeID = aPar.codeID;
    comments = aPar.comments;

    for (int i = 0; i < aPar.memWrapperList.count(); i++) {
        memWrapper_t *pTmp = new memWrapper_t;
        memWrapper_t *pTmpScr = aPar.memWrapperList[i];
//        memWrapper_t *pTmpScr = ((QPtrList<struct memWrapper>)(aPar.memWrapperList)).at(i);

        pTmp->memImageDim = pTmpScr->memImageDim;
        pTmp->memImageDisp = pTmpScr->memImageDisp;
        pTmp->memoryImg.arr = new unsigned char[pTmp->memImageDim];
        if (!(pTmp->memoryImg.arr)) arnCriticalExit();
        memcpy(pTmp->memoryImg.arr,pTmpScr->memoryImg.arr,pTmpScr->memImageDim);
        memWrapperList.append(pTmp);
        }
}

arnParContainer& arnParContainer::operator = (const arnParContainer& aPar)
{
    memWrapperList.clear();
	currentMemListElemIndex = 0;
    codeID = aPar.codeID;
    comments = aPar.comments;

    for (int i = 0; i < aPar.memWrapperList.count(); i++) {
        memWrapper_t *pTmp = new memWrapper_t;
        memWrapper_t *pTmpScr = aPar.memWrapperList[i];
//        memWrapper_t *pTmpScr = ((QPtrList<struct memWrapper>)(aPar.memWrapperList)).at(i);
        
        pTmp->memImageDim = pTmpScr->memImageDim;
        pTmp->memImageDisp = pTmpScr->memImageDisp;
        pTmp->memoryImg.arr = new unsigned char[pTmp->memImageDim];
        if (!(pTmp->memoryImg.arr)) arnCriticalExit();
        memcpy(pTmp->memoryImg.arr,pTmpScr->memoryImg.arr,pTmpScr->memImageDim);
        memWrapperList.append(pTmp);
        }
    return (*this);
}

bool arnParContainer::operator == (const arnParContainer& aPar)
{
	bool res = false;
	int memres = 0;
	int i;
	for (i = 0; i < aPar.memWrapperList.count(); i++) {
		if (this->memWrapperList[i]->memImageDim != aPar.memWrapperList[i]->memImageDim) {break;}
		if (this->memWrapperList[i]->memImageDisp != aPar.memWrapperList[i]->memImageDisp) {break;}
		if ((memres = memcmp(this->memWrapperList[i]->memoryImg.arr,aPar.memWrapperList[i]->memoryImg.arr,this->memWrapperList[i]->memImageDim))) {break;}
		}
	if (i == aPar.memWrapperList.count()) res = true;
    return res;
}

arnParContainer::~arnParContainer(void)
{
	for (int i = 0; i < memWrapperList.count(); i++) {
		memWrapper_t *pTmpScr = memWrapperList[i];
		if (pTmpScr &&  pTmpScr->memoryImg.arr) {
			delete [] pTmpScr->memoryImg.arr;
			pTmpScr->memoryImg.arr = 0;
			}
		delete memWrapperList[i];
		memWrapperList[i] = 0;
		}
}

memWrapper_t* arnParContainer::getmemWrapper(unsigned int indx)
{
    if (!memWrapperList.count() || (indx >= (unsigned int)memWrapperList.count())) return 0;
    return memWrapperList.at(indx);
}

unsigned int arnParContainer::memImageSizeOf(void)
{
	memWrapper_t *pTmpScr = memWrapperList[0];
	if (!pTmpScr) arnCriticalExit();
	return pTmpScr->memImageDim;
}


#define FILEFORMAT_VERSION  "0.1.0.0"
struct stgas {
    char* tag;
    char* value;
    };
#define IDX_HEADER              0
#define IDX_H_TOOLNAME          1
#define IDX_H_TOOLVERSION       2
#define IDX_H_TOOLLICENSE       3
#define IDX_H_TOOLPRODUCER      4
#define IDX_CODEID              5
#define IDX_COMMENT             6
#define IDX_NSEGMENTS           7
#define IDX_DATA                8
static struct stgas _tags[] = {
	{(char*)"header",(char*)""},
	{(char*)"h_toolname",(char*)"kpar"},
	{(char*)"h_toolversion",(char*)FILEFORMAT_VERSION},
	{(char*)"h_toollicense",(char*)"G.P.L"},
	{(char*)"h_toolproducer",(char*)"aurion s.r.l"},
	{(char*)"codeID",(char*)""},
	{(char*)"comment",(char*)""},
	{(char*)"nSegmets",(char*)""},
	{(char*)"data",(char*)""},
    };

arnParametric::arnParametric(unsigned int dim)
    : arnConfig()
{
    pMon = 0;
    appl = 0;
    appl = 0;
    pMappa = new arnParContainer(dim);
    if (!pMappa) exit(EXIT_FAILURE);
    reset();
}

arnParametric::arnParametric(unsigned int dim,unsigned int nSegs)
{
    pMon = 0;
    outDisplay = 0;
    appl = 0;
    pMappa = new arnParContainer(dim,nSegs);
    if (!pMappa) exit(EXIT_FAILURE);
    reset();
}

    
arnParametric::arnParametric(const arnParametric& aPar)
    : arnConfig()
{
    pMon = aPar.pMon;
    outDisplay = aPar.outDisplay;
    appl = aPar.appl;
    pMappa = new arnParContainer(*(aPar.pMappa));
    if (!pMappa) exit(EXIT_FAILURE);
}

arnParametric& arnParametric::operator = (const arnParametric& aPar)
{
    pMon = aPar.pMon;
    outDisplay = aPar.outDisplay;
    appl = aPar.appl;
    (*pMappa) = (*(aPar.pMappa));
    return (*this);
}

bool arnParametric::operator == (const arnParametric& aPar)
{
/*    pMon = aPar.pMon;
    outDisplay = aPar.outDisplay;
    appl = aPar.appl;*/
    return ((*pMappa) == (*(aPar.pMappa)));
}

arnParametric::~arnParametric(void)
{
    if (pMappa) {delete pMappa; pMappa = 0;}
}

bool arnParametric::loadfile(const char* absdir, const char* filename)
{
    char *t;
    int l;
    //char *encoding = "ISO-8859-1";

    if (!arnFindFile(absdir,filename)) return false;
    l = strlen(absdir) + strlen(filename) + 2;
    t = (char*)malloc(l * sizeof(char));
    if (!t) return false;

	memset (t, 0, l*sizeof(char));
    strcpy(t,absdir);
    strcat(t,"/");
    strcat(t,filename);

    if (this->filename) free(this->filename);
    this->filename = (char*)malloc(l * sizeof(char));
    if (!this->filename)  {free(t); t = 0; return false;}
    strcpy(this->filename,t);
    free(t); t = 0;

    return arnParametric::ldfile(this->filename);
}

bool arnParametric::loadfile(const char* fname)
{
    int l;
    //char *encoding = "ISO-8859-1";
    l = strlen(fname) + 2;

    if (this->filename) free(this->filename);
    this->filename = (char*)malloc(l * sizeof(char));
    if (!this->filename) return false;
    strcpy(this->filename,fname);

    return arnParametric::ldfile(this->filename);
}

bool arnParametric::createDoc(bool zerod)
{
    if (doc) delete doc;
    doc = new QDomDocument ("settings_and_parameters");

    QDomNode conf = doc->createElement ("settings_and_parameters");
    doc->appendChild (conf);
    
/*
    xmlNodePtr rootnode;
    xmlNodePtr newnode,father;

    // see the conversion example
    if (doc) xmlFreeDoc(doc);
    doc = 0;
    doc = xmlNewDoc ((const xmlChar*)"1.0");
    rootnode = xmlNewDocNode(doc, NULL, (const xmlChar*)"settings_and_parameters",(const xmlChar*) 0);
    xmlDocSetRootElement(doc, rootnode);
*/
    QDomNode father = addTextNode (conf, _tags[IDX_HEADER].tag, _tags[IDX_HEADER].value);

    addTextNode (father, _tags[IDX_H_TOOLNAME].tag,_tags[IDX_H_TOOLNAME].value );    
    addTextNode (father, _tags[IDX_H_TOOLVERSION].tag,_tags[IDX_H_TOOLVERSION].value );
    addTextNode (father, _tags[IDX_H_TOOLLICENSE].tag,_tags[IDX_H_TOOLLICENSE].value);
    addTextNode (father, _tags[IDX_H_TOOLPRODUCER].tag,_tags[IDX_H_TOOLPRODUCER].value);

    addTextNode (conf, _tags[IDX_COMMENT].tag,_tags[IDX_COMMENT].value);

/*
    newnode = xmlNewTextChild(rootnode,NULL, (const xmlChar*)_tags[IDX_HEADER].tag,(const xmlChar*)_tags[IDX_HEADER].value);
    father = newnode;
    newnode = xmlNewTextChild(father,NULL, (const xmlChar*)_tags[IDX_H_TOOLNAME].tag,(const xmlChar*)_tags[IDX_H_TOOLNAME].value);
    newnode = xmlNewTextChild(father,NULL, (const xmlChar*)_tags[IDX_H_TOOLVERSION].tag,(const xmlChar*)_tags[IDX_H_TOOLVERSION].value);
    newnode = xmlNewTextChild(father,NULL, (const xmlChar*)_tags[IDX_H_TOOLLICENSE].tag,(const xmlChar*)_tags[IDX_H_TOOLLICENSE].value);
    newnode = xmlNewTextChild(father,NULL, (const xmlChar*)_tags[IDX_H_TOOLPRODUCER].tag,(const xmlChar*)_tags[IDX_H_TOOLPRODUCER].value);

    newnode = xmlNewTextChild(rootnode,NULL, (const xmlChar*)_tags[IDX_COMMENT].tag,(const xmlChar*)_tags[IDX_COMMENT].value);

*/

    addTextNode (conf, _tags[IDX_CODEID].tag, pMappa->CodeID()) ;

/* NOTE: latin1 or better local8bit/utf8 ? */
/*
    newnode = xmlNewTextChild(rootnode,NULL, (const xmlChar*)_tags[IDX_CODEID].tag,(const xmlChar*)pMappa->CodeID().toLatin1().constData());
*/

    addTextNode (conf, _tags[IDX_NSEGMENTS].tag,QString("%1").arg(pMappa->count()));

/*
    {
	
    char pb[32];
    sprintf(pb,"%d",pMappa->count());
    newnode = xmlNewTextChild(rootnode,NULL, (const xmlChar*)_tags[IDX_NSEGMENTS].tag,(const xmlChar*)pb);
    }
*/

    father = addTextNode (conf, _tags[IDX_DATA].tag,_tags[IDX_DATA].value);

//    newnode = xmlNewTextChild(rootnode,NULL, (const xmlChar*)_tags[IDX_DATA].tag,(const xmlChar*)_tags[IDX_DATA].value);

/*** Tutto da migliorare qui sotto.... ****/

//    father = newnode;
    for (unsigned int i = 0; i < pMappa->count(); i++) {
        char* labelbf = new char[strlen(_tags[IDX_DATA].tag) + 10];
        if (!labelbf) return false;
        sprintf(labelbf,"%s-%d",_tags[IDX_DATA].tag,i);

        if (!pMappa || !(pMappa->getmemWrapper())) arnCriticalExit();
        char *bff = new char[ (2 * pMappa->getmemWrapper()->memImageDim) + 10];
        unsigned int dl;
        if (!bff) return false;
        if (zerod) memset(pMappa->getmemWrapper(i)->memoryImg.arr,0,pMappa->getmemWrapper(i)->memImageDim);
        arnBinToHexDigit(bff,(int*)(&dl),(const unsigned char*) pMappa->getmemWrapper(i)->memoryImg.arr,pMappa->getmemWrapper(i)->memImageDim);
        if (dl != (2 * pMappa->getmemWrapper()->memImageDim)) {delete [] bff; bff = 0; return false;}

	addTextNode (father, labelbf, bff);
//        newnode = xmlNewTextChild(father,NULL, (const xmlChar*)labelbf,(const xmlChar*)bff);

        delete [] bff; bff = 0;
        delete [] labelbf; labelbf = 0;
        }
    return true;
}

bool arnParametric::createfile(const char* fname)
{
    int l;

    l = strlen(fname) + 2;
    if (this->filename) free(this->filename);
    this->filename = (char*)malloc(l * sizeof(char));
    if (!this->filename) return false;
    strcpy(this->filename,fname);

    if (!createDoc(true)) return false;

    QFile fl(filename);
    
    if (!fl.open (QIODevice::WriteOnly) )
	return false;
    fl.write (doc->toString().toAscii());  // to ascii
    fl.close();

//    xmlSaveFormatFileEnc(this->filename, doc, 0/*encoding*/, 1);

    if (!this->loadfile(fname)) return false;

    return true;

}

bool arnParametric::createfile(const char* absdir, const char* filename)
{
    char *t;
    int l;
    //char *encoding = "ISO-8859-1";

    l = strlen(absdir) + strlen(filename) + 2;
    t = (char*)malloc(l * sizeof(char));
    if (!t) return false;

    memset(t, 0, l * sizeof(char));
    strcpy(t,absdir);
    strcat(t,"/");
    strcat(t,filename);

    if (this->filename) free(this->filename);
    this->filename = (char*)malloc(l * sizeof(char));
    if (!this->filename) {free(t); t = 0; return false;}
    strcpy(this->filename,t);
    free(t); t= 0;

    if (!createDoc(true)) return false;
    
    if (!arnConfig::savefile()) return false;

    if (!this->loadfile(absdir, filename)) return false;

    return true;
}

bool arnParametric::savefile(void)
{
    if (!(this->filename) || !strcmp(this->filename,"")) return false;

//    if (!doc) {
    if (!createDoc(false)) return false;
//        }

    if (!modifykey(_tags[IDX_COMMENT].tag,pMappa->Comments().toLatin1().constData())) {return false;}
    
    for (unsigned int i = 0; i < pMappa->count(); i++) {
        char* labelbf = new char[strlen(_tags[IDX_DATA].tag) + 10];
        if (!labelbf) return false;
        sprintf(labelbf,"%s-%d",_tags[IDX_DATA].tag,i);

        char *bff;
        unsigned int dl;
        bff = new char[ (2 * pMappa->getmemWrapper(i)->memImageDim) + 10];
        if (!bff) return false;
        arnBinToHexDigit(bff,(int*)(&dl),(const unsigned char*) pMappa->getmemWrapper(i)->memoryImg.arr,pMappa->getmemWrapper(i)->memImageDim);
        if (dl != (2 * pMappa->getmemWrapper(i)->memImageDim)) {delete [] bff; bff = 0; return false;}
        bff[dl] = 0;
        if (!modifykey(labelbf,bff)) {delete [] bff; bff = 0; return false;}
        delete [] bff; bff = 0;
        delete [] labelbf; labelbf = 0;
        }

    return arnConfig::savefile();
}

bool arnParametric::saveasfile(const char* absdir, const char* filename)
{
    char *t;
    int l;

    l = strlen(absdir) + strlen(filename) + 2;
    t = (char*)malloc(l * sizeof(char));
    if (!t) return false;

    memset(t, 0, l * sizeof(char));
    strcpy(t,absdir);
    strcat(t,"/");
    strcat(t,filename);

    if (this->filename) free(this->filename);
    this->filename = (char*)malloc(l * sizeof(char));
    if (!this->filename) {free(t); t = 0; return false;}
    strcpy(this->filename,t);
    free(t); t= 0;

    if (!this->savefile()) return false;
    if (!this->loadfile(absdir, filename)) return false;
    return true;
}

bool arnParametric::saveasfile(const char* fname)
{
    int l;

    l = strlen(fname) + 2;
    if (this->filename) free(this->filename);
    this->filename = (char*)malloc(l * sizeof(char));
    if (!this->filename) return false;
    strcpy(this->filename,fname);

    if (!this->savefile()) return false;
    if (!this->loadfile(fname)) return false;
    return true;
}

void arnParametric::reset(void)
{
	for (unsigned int indx = 0; indx < pMappa->count(); indx++)
		memset(pMappa->getmemWrapper(indx)->memoryImg.arr,0,pMappa->getmemWrapper(indx)->memImageDim);
	isAValidMappa = false;
}

bool arnParametric::loadfile(char *buffer, int size)
{
    QDomNode cur;

    if (doc) delete doc;
    doc = new QDomDocument;
    doc->setContent (QByteArray(buffer, size));

    QDomNode conf = doc->firstChild();

/*
    xmlNodePtr rootnode;
    xmlNodePtr cur;

    if (doc) xmlFreeDoc(doc);
    doc = 0;
    doc = xmlParseMemory(buffer,size);
    if (!doc) {return false;}

    rootnode = xmlDocGetRootElement(doc);
    if (!rootnode) {return false;}
*/
    if (conf.nodeName() != QString("settings_and_parameters")) return false;


/*
    if ((xmlStrcmp(rootnode->name,(const xmlChar*) "settings_and_parameters"))) {return false;}

*/

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_HEADER].tag)) {
	    if (!LoadHeader (*doc, cur)) 
		return false;
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_HEADER].tag))) {
            if (!LoadHeader(doc,cur)) {return false;}
            break;
            }
        cur = cur->next;
        }
*/

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_COMMENT].tag)) {
	    LoadComment (*doc, cur);
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_COMMENT].tag))) {
            LoadComment(doc,cur);
            break;
            }
        cur = cur->next;
        }
*/

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_CODEID].tag)) {
	    if (!LoadCodeID (*doc, cur)) 
		return false;
	    break;
	}
    }

/*

    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_CODEID].tag))) {
            if (!LoadCodeID(doc,cur)) return false;
            break;
            }
        cur = cur->next;
        }
*/

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_NSEGMENTS].tag)) {
	    if (!LoadnSegments (*doc, cur)) 
		return false;
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_NSEGMENTS].tag))) {
            if (!LoadnSegments(doc,cur)) return false;
            break;
            }
        cur = cur->next;
        }
*/
    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_DATA].tag)) {
	    LoadData (*doc, cur) ;	       
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_DATA].tag))) {
            LoadData(doc,cur);
            break;
            }
        cur = cur->next;
        }
*/
    isAValidMappa = true;
    return true;
}


bool arnParametric::ldfile(const char* fname)
{
    QDomNode cur;

    if (doc) delete doc;
    doc = new QDomDocument;
    QFile fl (fname);
    
    if (!fl.open (QIODevice::ReadOnly))
        return false;
    
    if (!doc->setContent(&fl)) {
        fl.close();
        return false;
    }

    fl.close();

/*

    xmlNodePtr rootnode;
    xmlNodePtr cur;

    if (doc) xmlFreeDoc(doc);
    doc = 0;
    doc = xmlParseFile(fname);
    if (!doc) {return false;}
*/

    QDomNode conf = doc->firstChild();
    if (conf.nodeName() == "xml")
	conf = conf.nextSibling();

    if (conf.nodeName() != QString("settings_and_parameters")) return false;

/*
    if ((xmlStrcmp(rootnode->name,(const xmlChar*) "settings_and_parameters"))) {return false;}

*/

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_HEADER].tag)) {
	    if (!LoadHeader (*doc, cur)) 
		return false;
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_HEADER].tag))) {

            if (!LoadHeader(doc,cur)) {return false;}
            break;
            }
        cur = cur->next;
        }
*/

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_COMMENT].tag)) {
	    LoadComment (*doc, cur);
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_COMMENT].tag))) {
            LoadComment(doc,cur);
            break;
            }
        cur = cur->next;
        }
*/


    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_CODEID].tag)) {
	    if (!LoadCodeID (*doc, cur)) 
		return false;
	    break;
	}
    }

/*

    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_CODEID].tag))) {
            if (!LoadCodeID(doc,cur)) return false;
            break;
            }
        cur = cur->next;
        }
*/


    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_NSEGMENTS].tag)) {
	    if (!LoadnSegments (*doc, cur)) 
		return false;
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_NSEGMENTS].tag))) {
            if (!LoadnSegments(doc,cur)) return false;
            break;
            }
        cur = cur->next;
        }
*/
    

    for (cur = conf.firstChild(); !cur.isNull(); cur = cur.nextSibling()) {
	if (cur.nodeName() == QString (_tags[IDX_DATA].tag)) {
	    LoadData (*doc, cur) ;	       
	    break;
	}
    }

/*
    cur = rootnode->xmlChildrenNode;
    while (cur) {
        if (!(xmlStrcmp(cur->name,(const xmlChar*)_tags[IDX_DATA].tag))) {
            LoadData(doc,cur);
            break;
            }
        cur = cur->next;
        }
*/
	isAValidMappa = true;
    return true;
}

bool arnParametric::LoadHeader(const QDomDocument &/*doc*/, const QDomNode &cur)
{
    QString key;

    for (QDomNode nd = cur.firstChild(); !nd.isNull(); nd = nd.nextSibling()) {
	key = getTextNode (nd);
	if (key.isNull()) 
	    continue;
	if (nd.nodeName() == QString (_tags[IDX_H_TOOLNAME].tag) ) {
	    if (key != QString (_tags[IDX_H_TOOLNAME].value))
		return false;
	} else if (nd.nodeName() == QString (_tags[IDX_H_TOOLVERSION].tag) ) {
	    if (key != QString (_tags[IDX_H_TOOLVERSION].value))
		return false;
	} else if (nd.nodeName() == QString (_tags[IDX_H_TOOLLICENSE].tag) ) {
	    if (key != QString (_tags[IDX_H_TOOLLICENSE].value))
		return false;
	} else	if (nd.nodeName() == QString (_tags[IDX_H_TOOLPRODUCER].tag) ) {
	    if (key != QString (_tags[IDX_H_TOOLPRODUCER].value))
		return false;
	}

    }

/*
    xmlChar *key;
    int res;
    cur = cur->xmlChildrenNode;
    while (cur)  {
        if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_H_TOOLNAME].tag))) {
            key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            if (!key) continue;
            res  = strcmp(_tags[IDX_H_TOOLNAME].value,(const char*)key);
            xmlFree(key);
            key = 0;
            if (res) return false;
            }
        else if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_H_TOOLVERSION].tag))) {
            key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            if (!key) continue;
            res  = strcmp(_tags[IDX_H_TOOLVERSION].value,(const char*)key);
            xmlFree(key);
            key = 0;
            if (res) return false;
            }
        else if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_H_TOOLLICENSE].tag))) {
            key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            if (!key) continue;
            res  = strcmp(_tags[IDX_H_TOOLLICENSE].value,(const char*)key);
            xmlFree(key);
            key = 0;
            if (res) return false;
            }
        else if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_H_TOOLPRODUCER].tag))) {
            key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            if (!key) continue;
            res  = strcmp(_tags[IDX_H_TOOLPRODUCER].value,(const char*)key);
            xmlFree(key);
            key = 0;
            if (res) return false;
            }
        cur = cur->next;
        }
*/
    return true;
}

void arnParametric::LoadComment(const QDomDocument &/*doc*/, const QDomNode & cur)
{

    if (cur.nodeName() == QString (_tags[IDX_COMMENT].tag)) {
	pMappa->setComments (getTextNode(cur).toAscii().constData());   // cur.nodeValue()
    }

/*
    xmlChar *key;
    if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_COMMENT].tag))) {
            key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            if (!key) return;
            pMappa->setComments((char*)key);
            xmlFree(key);
            key = 0;
            }
*/
    return ;
}

bool arnParametric::LoadCodeID(const QDomDocument &/*doc*/, const QDomNode & cur)
{
    if (cur.nodeName() == QString (_tags[IDX_CODEID].tag)) {
	QString key = getTextNode(cur); //.nodeValue();
	if (key.isNull()) 
	    return false;
	if (pMappa->CodeID() == key) 
	    return true;
    }
    
    return false;

/*
    xmlChar *key;
    bool res = false;
    if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_CODEID].tag))) {
        key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        if (!key) return res;
        if (!strcmp(pMappa->CodeID().toLatin1().constData(),(char*)key)) res = true;
        xmlFree(key);
        key = 0;
        }

    return res;
*/
}

bool arnParametric::LoadnSegments(const QDomDocument &/*doc*/, const QDomNode &cur)
{
    if (cur.nodeName() == QString (_tags[IDX_NSEGMENTS].tag)) {
	QString key = getTextNode(cur); //.nodeValue();
	if (key.isNull()) 
	    return false;
	if (pMappa->count() == key.toUInt()) 
	    return true;
    }

    return false;

/*
    xmlChar *key;
    bool res = false;
    if (!(xmlStrcmp(cur->name,(const xmlChar*) _tags[IDX_NSEGMENTS].tag))) {
        key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
        if (!key) return res;
        QString tp((char*)key);
        if (pMappa->count() == tp.toUInt()) res = true;
        xmlFree(key);
        key = 0;
        }
    return res;
*/
}

void arnParametric::LoadData(const QDomDocument &/*doc*/, const QDomNode &cur)
{
    QDomNode n = cur.firstChild();
    unsigned int idx;
    QString nodeKey;

    for (idx = 0 ; !n.isNull() && idx < pMappa->count(); idx++, n = n.nextSibling()) {
	QString labelbf = QString ("%1-%2").arg(_tags[IDX_DATA].tag).arg(idx);
	if (n.nodeName() == labelbf) {
	    nodeKey = getTextNode(n); //.nodeValue();
	    arnHexDigitToBin((pMappa->getmemWrapper(idx)->memoryImg.arr),
			     (int*)&(pMappa->getmemWrapper(idx)->memImageDim),
			     nodeKey.toAscii().constData(),
			     nodeKey.toAscii().count());
	}
    }
    

/*
    xmlChar *key;
    cur = cur->xmlChildrenNode;
    for (unsigned int indx = 0; (indx < pMappa->count() && cur); indx++) {
        char* labelbf = new char[strlen(_tags[IDX_DATA].tag) + 10];
        if (!labelbf) return;
        sprintf(labelbf,"%s-%d",_tags[IDX_DATA].tag,indx);
        if (!(xmlStrcmp(cur->name,(const xmlChar*)labelbf))) {
            key = xmlNodeListGetString(doc,cur->xmlChildrenNode,1);
            if (!key) {delete [] labelbf; labelbf = 0; return;}
            arnHexDigitToBin((pMappa->getmemWrapper(indx)->memoryImg.arr),(int*)&(pMappa->getmemWrapper(indx)->memImageDim),(const char*)key,strlen((const char*)key));
            xmlFree(key);
            key = 0;
            }
        if (pMappa->getmemWrapper(indx)->memImageDim != pMappa->memImageSizeOf()) {pMappa->getmemWrapper(indx)->memImageDim = pMappa->memImageSizeOf();}
        delete [] labelbf; labelbf = 0;
        cur = cur->next;
        }
    return ;
*/
}

QDomNode arnParametric::addTextNode (QDomNode &node, const QString &tag, const QString &value)
{
    QDomElement element = doc->createElement (tag);
    QDomText text = doc->createTextNode (value);

//    element.setTagName (tag);
//    text.setData (value);
    
    element.appendChild (text);
    node.appendChild (element);

    return element;
}

QString arnParametric::getTextNode (const QDomNode &node) {
    return node.firstChild().nodeValue();
}
