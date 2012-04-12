/***************************************************************************
                          arnSODevice.h  -  description
                             -------------------
    begin                : mar giu 1 2004
    copyright            : (C) 2004 by fgiovagnini
    email                : fgiovagnini@obione
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/
#ifndef ArnSODeviceH
#define ArnSODeviceH

#include <Q3ListView>
#include "arnParametric.h"

#define DEVICE_VERSION	"1.1"

class arnSOKCDevice;
class arnSOKPDevice;
class arnSOKLDevice;
class arnSOCfg;
class arnEFMFileDescr;
typedef struct WidgetStatusList {
	int Length;
	arnVisibleWidgetStatus_t* WidgetStatus;
	bool* alarmEnabled;
	float* alarmThUP;
	float* alarmThDOWN;
	__colorName_t* colorTrack;
	} WidgetStatusList_t;

class arnSOCfg : public QObject
{
    Q_OBJECT

	private:
	protected:
		arnCarrier *pCarrier;
		void* Cfg;
		int CfgSize;
		void* Cds;
		WidgetStatusList_t rtPackWidgetList;
		WidgetStatusList_t rtParamWidgetList;
	signals:
		void deviceRequest(arnDeviceToKtoolRequestType_t, void*);
	public slots:
		virtual inline void deviceRequest_generator(arnDeviceToKtoolRequestType_t /*req*/, void* /*pParam*/) {emit deviceRequest(arn_dtkr_NONE,0);}
	public:
		arnSOCfg(QObject *parent = 0, const char* name = 0)
			: QObject (parent, name) {pCarrier = 0; Cfg = 0; CfgSize = 0;}
		virtual ~arnSOCfg(void) {;}
		virtual bool getConfiguration(int *err) = 0;
		virtual bool getCodes(int *err) = 0;
		virtual void showCodes(const char* caption) = 0;
		virtual bool hasParametersEnv(void) = 0;		// tell if the device has Parameters features
		virtual bool hasParametersVisible(void) = 0;	// tell if the device has Parameters features are visible
		virtual bool hasMultiParamEnabled(void) = 0;	// tell if the device has Multi Parameters (more than one block) features active
		virtual int DefaultMultiParamIndex(void) {return 0;} // if Multi Parameters (more than one block) features present but inactive, set the default block.
		virtual bool hasRtEnv(void) = 0;
		virtual bool hasDlEnv(void) = 0;
		virtual void debugConfiguration(void) {;}
		inline virtual void setCarrier(arnCarrier *pC) {pCarrier = pC;}
		inline virtual void* cfg(void) {return Cfg;}
		inline virtual void* codes(void) {return Cds;}
		inline virtual arnCarrier *carrier(void) {return pCarrier;}
		inline virtual void setRTPackWidgetStatusList(arnVisibleWidgetStatus_t* pList,
			bool* pAEList,
			float* pATHUPList,
			float* pATHDOWNList,
			__colorName_t* pCLRTACKList,
			int Len) {
			rtPackWidgetList.WidgetStatus = pList;
			rtPackWidgetList.alarmEnabled = pAEList;
			rtPackWidgetList.alarmThUP = pATHUPList;
			rtPackWidgetList.alarmThDOWN = pATHDOWNList;
			rtPackWidgetList.colorTrack = pCLRTACKList;
			rtPackWidgetList.Length = Len;
			}
		inline virtual void setRTParamWidgetStatusList(arnVisibleWidgetStatus_t* pList,
		   float* pATHDOWNList,
		   int Len) {
			rtParamWidgetList.WidgetStatus = pList;
			rtParamWidgetList.alarmEnabled = 0;
			rtParamWidgetList.alarmThUP = 0;
			rtParamWidgetList.alarmThDOWN = pATHDOWNList;
			rtParamWidgetList.colorTrack = 0;
			rtParamWidgetList.Length = Len;
			}
		inline virtual WidgetStatusList_t* RTPackWidgetStatusList(void) {return &rtPackWidgetList;}
		inline virtual WidgetStatusList_t* RTParamWidgetStatusList(void) {return &rtParamWidgetList;}
};

class arnSOKPDevice : public Q3ListView
{
    Q_OBJECT

    protected:
		arnSOKCDevice *pKCDevice;
		arnSOCfg *pCfg;
    public:
        arnSOKPDevice(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0)
        	: Q3ListView (parent, name, f) {pKCDevice = 0;}
        virtual ~arnSOKPDevice(void) {;}
		inline void setKCDevice(arnSOKCDevice *pKC) {pKCDevice = pKC;}
		inline void setCfg(arnSOCfg *pC) {pCfg = pC;}
        const char* getDeviceVersion(void) {return DEVICE_VERSION;}
        inline virtual bool initLayout(arnParametric *pLowDevice) {if (!pLowDevice) return false; return false;}
        inline virtual bool evalRelations(arnParametric *pLowDevice) {if (!pLowDevice) return false; return false;}
        inline virtual bool evalDiff(arnParametric *pLDBase,arnParametric *pLDCurrent) {if (!pLDBase || !pLDCurrent) return false; return false;}
		inline virtual void RestoreItemColor(void) {;}
		inline virtual unsigned int getParContainerDim(void) {return 0;}
        inline virtual bool SADevice(void) {return false;}
        inline virtual const char* getParContainerID(void) {return 0;}
		inline virtual bool checkCode(void)  {return false;}
        inline virtual CpuTarget_t getCPUTarget(void) {return Ctt_None;}
        inline virtual unsigned char getBlocksNumber(void) {return 0;}
        inline virtual unsigned long getBlockStartAddress(unsigned char Indx) {if (Indx) return 0; return 0;}
        inline virtual const char* getLanguage(void) {return 0;}
        inline virtual CommProtocol_t getProtocol(void) {return cp_none;}
        // embedded firmware
		inline virtual bool HasEmbeddedFirmware(void) {return false;}
};

class arnSOKCDevice : public QFrame // penso che il migliore sia QPanel
{
	Q_OBJECT

	protected:
		arnSOKPDevice *pKPDevice;
		arnSOCfg *pCfg;
		bool enableRtGraphic;
	public:
		arnSOKCDevice(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0)
			: QFrame (parent, name, f) {pKPDevice = 0; pCfg = 0; enableRtGraphic = false;}
		virtual ~arnSOKCDevice(void) {;}
		inline void setKPDevice(arnSOKPDevice *pKP) {pKPDevice = pKP;}
		inline void setCfg(arnSOCfg *pC) {pCfg = pC;}
		inline const char* getDeviceVersion(void) {return DEVICE_VERSION;}
		inline virtual const char* getRtpID(void) {return 0;}
		inline virtual bool hasRtPacket(void) {return false;}
		inline virtual bool hasRtParams(void) {return false;}
		inline virtual bool initRtPacketLayout(void* parms) {if (!parms) return false; return false;}
		inline virtual bool initRtParamsLayout(void* parms) {if (!parms) return false; return false;}
		inline virtual bool evalRelations(void* parms) {if (!parms) return false; return false;}
		inline virtual const char* getLanguage(void) {return 0;}
		inline virtual bool checkCode(void)  {return false;}
		inline virtual CommProtocol_t getProtocol(void) {return cp_none;}
		inline virtual bool receiveRt(unsigned char* bff, unsigned int *len) {*bff = 0; *len = 0; return false;} // len in / out;check su sizeof(bff)
		inline virtual bool updateRtPacket(unsigned char* bff, unsigned int len) {*bff = 0; len = 0; return false;}
		inline virtual bool updateRtParams(unsigned char* bff, unsigned int len) {*bff = 0; len = 0; return false;}
		inline virtual bool sendRt(unsigned char* bff, unsigned int len) {*bff = 0; len = 0; return false;}
		virtual bool Action(arnKCDeviceActionType_t actType,void* addParms = 0) {addParms = 0; if (actType == arn_kcd_NONE) return false; return false;}
		inline void EnableRtGraphic(bool en) {enableRtGraphic = en;}

		// host PC logger logger
		inline virtual bool hasHostedLogger(void) {return false;}
		inline virtual bool HostedLoggerEnableTriggerd(void) {return false;}
		inline virtual bool HostedLoggerEnableTimed(void) {return false;}
		inline virtual int HostedLoggerSamplingTime(void) {return 1000;}
		inline virtual char* HostedLoggerTimedFilename(void) {return 0;}
		inline virtual char* HostedLoggerTriggeredFilename(void) {return 0;}
};

class arnSOKLDevice : public QFrame
{
	Q_OBJECT
	private:
	
	private slots:
		virtual void doCurrentfileChange( const arnEFMFileDescr*) = 0;
	
	protected:
		arnSOCfg *pCfg;
		QStatusBar* outDisplay;
		QApplication* appl;
		char* CurrentWDir;
		bool CfgMode;
		// funzione per definire il metodo evetuale di filtraggio del canale da device a device
		virtual inline float channelFilter(unsigned int indx, float rowdata) {if (indx == 0) return rowdata; return rowdata;}
		// funzione che ci dice per ciscun canale quante cifre decimali sono significative nel costruire il file dei dati
		virtual inline unsigned char channelPrecision(unsigned int indx) {if (indx == 0) return 0; return 0;}
	protected slots:
	
	signals:
		void currentfileChanged(const arnEFMFileDescr*);
	public:
		arnSOKLDevice(QWidget *parent = 0, const char* name = 0, Qt::WFlags f = 0)
			: QFrame (parent, name, f) {
				pCfg = 0;
				CurrentWDir = 0;
				CfgMode = false;
				outDisplay = 0;
				appl = 0;
				}
		virtual ~arnSOKLDevice(void) {;}
		// general
		inline const char* getDeviceVersion(void) {return DEVICE_VERSION;}
		inline virtual bool hasEmbeddedLogger(void) {return false;}
		inline virtual bool evalRelations(void* parms) {parms = 0; return false;}
		inline virtual const char* getLanguage(void) {return 0;}
		inline virtual const char* getEnbLogID(void) {return 0;}
		inline virtual CommProtocol_t getProtocol(void) {return cp_none;}
		inline virtual bool checkCode(void)  {return false;}
		inline virtual void setCfg(arnSOCfg *pAC) {pCfg = pAC;}
		inline virtual void setOutDisplay(QStatusBar* outD) {outDisplay = outD;}
		inline virtual void setApplication(QApplication* app) {appl = app;}
		inline virtual void configMode(bool cfg) {CfgMode = cfg;}
		inline virtual void setCurrentWDir(char* CurrWDir) {CurrentWDir = CurrWDir;}
		// embedded logger
		inline virtual bool initEmbeddedLogger(void* parms) {parms = 0; return false;}
		virtual bool download(unsigned char *pBff,unsigned long Len) = 0;
		virtual bool getConfiguration(void* pConfig) =  0;
		virtual bool setConfiguration(void* pConfig) =  0;
		virtual bool start(void) =  0;
		virtual bool stop(void) =  0;
		virtual bool erase(void) =  0;
		virtual bool checkStats(void) =  0;
		virtual bool diagnostic(void) =  0;
		// for off line datafile analysis
		virtual bool openfile(const char* fname) = 0;
		virtual bool closefile(const char* fname) = 0;
		virtual bool savefile(void) = 0;
		virtual bool savefileas(const char* fname) = 0;
		//virtual void updateDatafileDisplay(void) = 0;
		//virtual const char* currentfile(void) = 0;
	public slots:
	
};

extern "C"
{
arnSOKPDevice *CreateKPDevice(QWidget *parent, const char* name);
arnSOKCDevice *CreateKCDevice(QWidget *parent, const char* name);
arnSOKLDevice *CreateKLDevice(QWidget *parent, const char* name);
arnSOCfg *CreateCfg(QWidget *parent, const char* name);
}

#endif
