/***************************************************************************
                          arnGenericLogger.cpp  -  description
                             -------------------
    begin                : lun apr 7 2003
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

#include "CommonFunctions.h"
#include "arnGenericLogger.h"

arnGenericLogger::arnGenericLogger(void)
{
    strcpy(fname,"");
    fd = 0;
    ChannelList = new QList<struct ChannelItem *>;
    if (!ChannelList) arnCriticalExit();

}

arnGenericLogger::arnGenericLogger(char* filename)
{
    if (!filename) arnCriticalExit();
    strcpy(fname,filename);
    fd = 0;
    ChannelList = new QList<struct ChannelItem *>;
    if (!ChannelList) arnCriticalExit();

}

arnGenericLogger::~arnGenericLogger(void)
{
    if (ChannelList) {delete ChannelList; ChannelList = 0;}
    if (fd) {fflush(fd); fclose(fd); fd = 0;}
}

bool arnGenericLogger::addChannel(const char* Label)
{
    struct ChannelItem *tmp = new struct ChannelItem;
    if (!tmp) return false;

    tmp->Name = Label;
    tmp->Value = "0";
    ChannelList->append(tmp);

    return true;
}

bool arnGenericLogger::deleteChannel(const char* Label)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((struct ChannelItem *)ChannelList->at(i))->Name,Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return false;
    if (ChannelList->at(i) == 0) return false;
    ChannelList->removeAt(i);
//    if (!(ChannelList->remove(i))) return false;
    return true;
}

void arnGenericLogger::setChannelValue (const char* Label, char* val)
{
    bool found = false;
    int i;
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((struct ChannelItem *)ChannelList->at(i))->Name,Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((struct ChannelItem *)ChannelList->at(i))->Value = val;
}

void arnGenericLogger::setChannelValue (const char* Label, int val)
{
    bool found = false;
    int i;
    QString vvl;
    vvl.setNum(val);
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((struct ChannelItem *)ChannelList->at(i))->Name,Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((struct ChannelItem *)ChannelList->at(i))->Value = vvl;
}

void arnGenericLogger::setChannelValue (const char* Label, float val,int prec,char fmt)
{
    bool found = false;
    int i;
    QString vvl;
    vvl.setNum(val,fmt,prec);
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((struct ChannelItem *)ChannelList->at(i))->Name,Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((struct ChannelItem *)ChannelList->at(i))->Value = vvl;
}

void arnGenericLogger::setChannelValue (const char* Label, double val,int prec,char fmt)
{
    bool found = false;
    int i;
    QString vvl;
    vvl.setNum(val,fmt,prec);
    for ( i = 0; i < int(ChannelList->count()); ++i ) {
        if (!strcmp(((struct ChannelItem *)ChannelList->at(i))->Name,Label)) { // variabile gia' trovata
            found = true;
            break;
            }
        }
    if (!found) return;
    ((struct ChannelItem *)ChannelList->at(i))->Value = vvl;
}

bool arnGenericLogger::init (void)
{
    if (!strcmp(fname,"")) return false;
    if (!ChannelList->count()) return false;

    fd = fopen(fname,"wt");
    if (!fd) return false;

    for (int indx = 0; indx < int(ChannelList->count()); ++indx) {
        fprintf(fd,"%s\t",(const char*)((struct ChannelItem *)ChannelList->at(indx))->Name);
        }
    fprintf(fd,"\r\n");
    return true;
}

void arnGenericLogger::logg(void)
{
    if (!fd) return;

    for (int indx = 0; indx < int(ChannelList->count()); ++indx) {
        fprintf(fd,"%s\t",(const char*)((struct ChannelItem *)ChannelList->at(indx))->Value);
        }
    fprintf(fd,"\r\n");
	if (fflush(fd) == EOF) arnDebug("file flush error\n");
}

