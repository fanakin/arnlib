/***************************************************************************
                          arnEdlChannel.h  -  description
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

#ifndef ArnEdlChannelH
#define ArnEdlChannelH

#ifdef HAVE_IDPS
#include "libidps.h"
#endif
#include <qcolor.h>
#include <QList>
#include <QVector>

// ---------------------------------------------------
// ***************************************************
// --------- arnEdlChannel -------------------
// ***************************************************
// ---------------------------------------------------
typedef QVector<float> arnEdlDataFrame_t;
typedef struct arnEdlFrame {
	unsigned int marker;
	arnEdlDataFrame_t data;
	} arnEdlFrame_t;

class arnEdlChannel
{
	private:
		/*!
		* \brief Inizialization  function
		*
		* It will be called in every constructor; so it implement the common part of the construction process
		*/
		void init(void);
	protected:
		bool shown; /*!< flag telling if the channel as a drawing on the viewort */
		bool open; /*!< flag telling is the channel is open at the moment when file is closed so it has to be restored */
		unsigned int viewport; /*!< viewport as in logical description; 0,1,2,3,etc. */
		unsigned int idpsviewport; /*!< viewport as in idps */
		unsigned int dataID;  /*!< data identifier for idps */
		QColor color; /*!< color of track */
		QString name; /*!< name of the channel */
		unsigned int samplingtime; /*!< sampling rate of the channel */
		unsigned char size; /*!< size in bytes of the channel */
		unsigned char isSigned; /*!< flag telling if the row channel is signed or unsigned */
		float floor; /*!< minimum visibale value */
		float ceil; /*!< maximum visible value */
		float min; /*!< minimum channel value */
		float max; /*!< maximum channel value */
		int linetype; /*!< type of line of track as in idps */
		QList<arnEdlFrame_t *> *frames; /*!< all the frames of the channel */
		/*!
		* \brief It builds the real comma separated value part of the data file during a downloading operation
		*
		* @param fd is the file descriptor
		* @param bff is the buffer containg the data for teh remote device
		* @param len is the length of the buffer
		* @return true, if no problem occurs during the building process and the file is properly made, false otherwise.
		* 
		* This function is called inside the buildFile funtion.
		*/
		//bool buildCSV(FILE *fd,unsigned char* bff,unsigned int len);
	public:
		/*!
		* \brief Basic constructor
		*
		* @param nm is the name of the channel.
		* @param vport is the selected viewport for drawing the channel on idps server.
		* 
		* It build a datalogger channel data container
		*/
		arnEdlChannel (QString nm, int vport = 0);
		
		/*!
		* \brief Basic destructor
		*
		* It destoryes a datalogger channel data container
		*/
		~arnEdlChannel(void);

/*		inline float& operator[](int indx) {return data[indx];}
		
		inline const float& operator[](int indx) const {return data[indx];}*/
		
		inline void setViewport (int vp) {viewport = vp;}
		
		inline void setIdpsViewport (int vp) {idpsviewport = vp;}
		
		inline int Viewport (void) {return viewport;}
		
		inline int IdpsViewport (void) {return idpsviewport;}
		
		inline void setColor (QColor c) {color = c;}
		
		inline QColor Color (void) {return color;}
		
		inline void setName (QString n) {name = n;}
		
		inline QString Name (void) {return name;}
		
		inline void setSamplingTime (unsigned int n) {samplingtime = n;}
		
		inline unsigned int SamplingTime (void) {return samplingtime;}
		
		inline unsigned char Size(void) {return size;}
		
		inline void setSize(unsigned char v) {size = v;}
		
		inline unsigned char Signed(void) {return isSigned;}
		
		inline void setSigned(unsigned char v) {isSigned = v;}
		
		inline void setFloor (float n) {floor = n;}
		
		inline float Floor (void) {return floor;}
		
		inline void setCeil (float n) {ceil = n;}
		
		inline float Ceil (void) {return ceil;}
		
		//inline void setMin (float n) {min = n;} dovrebbe esserci una eval min privata / protetta
		
		inline float Min (void) {return min;}
		
		//inline void setMax (float n) {ceil = n;} dovrebbe esserci una eval max privata / protetta
		
		inline float Max (void) {return max;}
		
		inline void setLineType (int n) {linetype = n;}
		
		inline int LineType (void) {return linetype;}
		
		bool addFrame(void);
		
		inline bool deleteFrame(int indx) {
			if (indx < int(frames->count())) {
			    arnEdlFrame_t *ptr = frames->at(indx);  // autodelete
			    frames->removeAt(indx);
			    if (ptr) delete ptr;			    
				}
			return true;
			}
		
		inline arnEdlFrame_t* Frame(int indx) {
			if (indx < int(frames->count())) {
				return ((arnEdlFrame_t *)frames->at(indx));
				}
			return 0;
			}
		
		inline unsigned int Frames(void) {return frames->count();}
		
		inline unsigned int DataID(void) {return dataID;}
		
		inline void setDataID(unsigned int d) {dataID = d;}
		
		inline bool Shown(void) {return shown;}
		
		inline void setShown(bool b) {shown = b;}
		
		inline bool Open(void) {return open;}
		
		inline void setOpen(bool b) {open = b;}
};

#endif
