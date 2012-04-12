/***************************************************************************
                          arnConfig.cpp  -  description
                             -------------------
    begin                : lun gen 27 2003
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
#define __DEBUG__

#include <errno.h>
#include <string.h>
#include <stdlib.h>

#include "CommonFunctions.h"
#include "arnConfig.h"

#include <QFile>

arnConfig::arnConfig(void)
{
    doc = 0;
    filename = 0;
}

arnConfig::~arnConfig(void)
{
    if (doc) delete doc;
    doc = 0;
    if (filename) free(filename);
    filename = 0;
}

//bool arnConfig::errorcheck(const char* str)
//{
//#ifdef __DEBUG__
//    switch (errno) {
//        // part for fopen
//        case EACCES: fprintf(stderr,"%s, EACCES\n",str); break;
//        case EINVAL: fprintf(stderr,"%s, EINVAL\n",str); break;
//        case EISDIR: fprintf(stderr,"%s, EISDIR\n",str); break;
//        case EMFILE: fprintf(stderr,"%s, EMFILE\n",str); break;
//        case ENOENT: fprintf(stderr,"%s, ENOENT\n",str); break;
//        case ENOMEM: fprintf(stderr,"%s, ENOMEM\n",str); break;
//        case ENOTDIR: fprintf(stderr,"%s, ENOTDIR\n",str); break;
//        case ETXTBSY: fprintf(stderr,"%s, ETXTBSY\n",str); break;
//        // end - part for fopen
//        default: break;
//        }
//#endif
//    return false;
//}

unsigned char *arnConfig::convert(unsigned char *in, char */*convert*/)
{
    unsigned char *out;
    int out_size;

    out_size = (int)strlen((const char*)in) + 1;
    out = (unsigned char*)malloc((size_t) out_size);
    if (out) {memcpy(out,in,(int)strlen((const char*)in)); out[out_size] = 0;}
    return (out);
}

bool arnConfig::savefile(void)
{
    QFile file (filename);
    if (!file.open (QIODevice::WriteOnly))
	return false;

    file.write (doc->toString().toAscii());
    file.close();

    return true;

    //    if (xmlSaveFormatFileEnc(this->filename, doc, 0/*encoding*/, 1) == -1) return false;
    //return true;
}

QString arnConfig::findkey(const char *key)
{
    QString nodeKey(key);
    QDomNode out;
    if (doc->nodeName() == nodeKey)
	return doc->firstChild().nodeValue(); //  ????????????????????????????

    if (!(out = _findkeyonchildren (*doc,key)).isNull()) 
	return out.firstChild().nodeValue();
    return 0;

/*
    xmlNodePtr rn = xmlDocGetRootElement(doc);
    xmlNodePtr out;
    if ((!xmlStrcmp(rn->name,(const xmlChar*)key))) return xmlNodeListGetString(doc,rn->xmlChildrenNode,1);
    if ((out = _findkeyonchildren(rn,key))) return xmlNodeListGetString(doc,out->xmlChildrenNode,1);
    return ((xmlChar *) 0);
*/
}

bool arnConfig::modifykey(const char *key, const char *newvalue)
{
    QString nodeKey (key);
    QDomNode out;
    
    if (doc->nodeName() == key) {
	doc->setNodeValue (QString(newvalue));
	return true;
    } 

    if (!(out = _findkeyonchildren (*doc, key)).isNull()) {
	out.removeChild (out.firstChild());
	out.appendChild (doc->createTextNode (newvalue));

	return true;
    }

    return false;

/*
    xmlNodePtr rn = xmlDocGetRootElement(doc);
    xmlNodePtr out;
    if ((!xmlStrcmp(rn->name,(const xmlChar*)key))) {
        xmlNodeSetContent(rn,(const xmlChar*)newvalue);
        return true;
        }
    if ((out = _findkeyonchildren(rn,key))) {
        xmlNodeSetContent(out,(const xmlChar*)newvalue);
        return true;
        }
    return false;
*/
}

//xmlNodePtr arnConfig::_findkey(xmlNodePtr cur,const char *key)
//{
//    xmlNodePtr out = (xmlNodePtr)0;
//    xmlNodePtr sn = cur;
//    if (!cur) return out;
//    while (cur) {
//            if ((!xmlStrcmp(cur->name,(const xmlChar*)key))) return cur;
//            cur = cur->next;
//            }
//    sn = sn->xmlChildrenNode;
//    return _findkey(sn,key);
//    return (xmlNodePtr)0;
//}

QDomNode arnConfig::_findkeyonchildren(const QDomNode &cur,const char *key)
{
    if (cur.isNull()) return QDomNode();

    QString keyName(key);
    QDomNode res;

    for (QDomNode chld = cur.firstChild();
	 !chld.isNull();
	 chld = chld.nextSibling()) {
	
	if (keyName == chld.nodeName())
	    return chld;

	if (!(res = _findkeyonchildren (chld, key)).isNull())
	    return res;
    }
    
    return QDomNode();  // not found
}

/*
    cur = cur->xmlChildrenNode;
    if (!cur) return (xmlNodePtr)0;
    while (cur) {
        xmlNodePtr res;
        if ((!xmlStrcmp(cur->name,(const xmlChar*)key))) return cur;
        res = _findkeyonchildren(cur,key);
        if (res) return res;
        cur = cur->next;
        }
    return cur;
}
*/

QDomNode arnConfig::addTextNode (QDomNode &node, const QString &tag, const QString &value)
{
    QDomElement element = doc->createElement (tag);
    QDomText text = doc->createTextNode (value);

//    element.setTagName (tag);
//    text.setData (value);

    element.appendChild (text);
    node.removeChild (node.firstChild());
    node.appendChild (element);

    return element;
}
