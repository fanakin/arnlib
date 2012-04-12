/***************************************************************************
                          arnSAParametric.h  -  description
                             -------------------
    begin                : dom mar 9 2003
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

#ifndef ArnSAParametricH
#define ArnSAParametricH

#include <qstringlist.h>
#include "arnParametric.h"


typedef struct FirmwareDescr {
    QString filename; // nome del file .srec che si intende caricare con la mappa
    QStringList file; // stringlist del file .srec che si intende caricare con la mappa
    QStringList BootProgram; // stringlist del file .srec che contiene il boot program
    CpuTarget_t TargetCpu;
    FirmwareDescr(void) {filename = ""; /*BootProgram.setAutoDelete(true);*/ BootProgram.clear();
        /*file.setAutoDelete(true);*/
        file.clear();TargetCpu = Ctt_None;}
    FirmwareDescr& operator = (const FirmwareDescr& aPar) {
        filename = aPar.filename; file = aPar.file; TargetCpu = aPar.TargetCpu;
        BootProgram = aPar.BootProgram;
        return (*this);
        }
    } FirmwareDescr_t;

class arnSAParametric : public arnParametric
{
    private:
    protected:
        CommInterface_t serInterfType;
        char serInterfName[16];
        arnSerialInterface *pDev;
        FirmwareDescr_t *firmware;
        bool loadDataStream(void);
        unsigned char* ConvertTabToA20(unsigned char* destBuff,unsigned long Size);
        bool loadBootProgram(void);
        bool AutoBaudRate(void);
        bool DownloadBootProgram(void);
		bool DownloadTargetProgram(FirmwareDescr_t* pFirm);
        bool ListenAndAnswerToEcuForErasingSectors(unsigned char LstCmd,unsigned char AswCmd,unsigned char* Sect);
        bool ListenAndAnswerToEcu(unsigned char LstCmd,unsigned char AswCmd);
    public:
        arnSAParametric(unsigned int dim);
        arnSAParametric(unsigned int dim,unsigned int nSegs);
        arnSAParametric(const arnSAParametric& aPar);
        virtual ~arnSAParametric(void);
        virtual bool send(void);
        virtual bool receive(void);
        arnSAParametric& operator = (const arnSAParametric& aPar);
        bool setFirmwareFileName(const char* absdir, const char* filename);
        bool setFirmwareSRECFormat(QStringList *pfilelist);
        inline void setSerialInterface(arnSerialInterface *Dev) {if (pDev) {delete pDev; pDev = 0;} pDev = Dev;}
        inline void setSerialDeviceType(CommInterface_t comt) {serInterfType = comt;}
        inline void setSerialDeviceName(const char* comn) {
            if (strlen(comn) < sizeof(serInterfName)) strcpy(serInterfName,comn);
            else strncpy(serInterfName,comn,sizeof(serInterfName));
            }
        inline void setTargetCpu(CpuTarget_t tCpu) {firmware->TargetCpu = tCpu;}
		bool exportSRECTotalFile(const char* absdir, const char* filename);
		bool KLoaderEmu(const char* fname);
};

#endif
