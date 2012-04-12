/***************************************************************************
                          arnGraphDataStream.cpp  -  description
                             -------------------
    begin                : mar giu 14 2005
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

/*!
* \file arnGraphDataStream.h.
* \brief Gaphical data stream. This class is the container for teh data to graph with idps
*
* In this class we implement the component having all the faetures for drawing with \n
* with IDPS (www.idps.org) the set data stream. \n
* The constructors are QDataStream related.
*
*/

#ifndef ArnGraphDataStreamH
#define ArnGraphDataStreamH

#include <libidps.h>
#include <qcolor.h>
#include <qobject.h>
#include <QQueue>
#include "CommonFunctions.h"

// typedef enum {
// 	gss_
// 	} arnGraphStreamStatus_t;

class arnGraphDataStream : public QObject
{
	Q_OBJECT
	
	private:
		/*! \brief it makes the common initialization part. It is called by all the constructors
		*
		* This  function encapsulates all the actions needed by the construction process \n
		* and it is called by all the constructors so that all the eventual modifications of the \n
		* construction mechanism is properly propagated.
		*/
		void init(void);
	protected:
		QQueue<float> coda; /*!< this is the queue of the value forming the data stream of the channel */
		QColor color; /*!< color of the stream on the graphic */
		//QString name; /*!< name of the stream */
		int timebase; /*!< value of the sampling rate in uS */
		int visibleWinSize; /*!< number of visible samples */
		int visibleStartPoint; /*!< index of the first visible samples of the datastream */
		double min; /*!< minimum value of the stream */
		double max; /*!< maximum value of the stream */
		bool visible; /*!< flag telling if the stream is visible */
		int lineformat; /*!< line format of the stream on the graphic */
	public :
		/*! \brief Generic empty contructor
		*
		* This constructor is for compatibility with QObject \n
		* See QObject.
		*/
		arnGraphDataStream(QObject * parent = 0, const char * name = 0);
		
		
		/*! \brief Destructor
		*
		* It is in charge to distroy everything internal related stuff \n
		*/
		~arnGraphDataStream(void);
		
		/*! \brief it returs the color property
		*
		* @return color value
		* It gets the color value \n
		*/
		inline QColor Color(void) {return color;}
		
		/*! \brief it sets the color property
		*
		* @param clr is the color value as QColor
		* It sets the color value \n
		*/
		inline void setColor(QColor clr) {color = clr;}
		
		/*! \brief it returs the timebase property
		*
		* @return timebase value
		* It gets the timebase value. It is measured in uS (microseconds) \n
		*/
		inline int Timebase(void) {return timebase;}
		
		/*! \brief it sets the timebase property
		*
		* @param tb is the timebase value
		* It sets the timebase value and it is measured in uS (microseconds)\n
		*/
		inline void setTimebase(int tb) {timebase = tb;}
		
		/*! \brief it returs the visibleWinSize property
		*
		* @return visibleWinSize value
		* It gets the visibleWinSize value. It is measured in number of samples \n
		*/
		inline int VisibleWinSize(void) {return visibleWinSize;}
		
		/*! \brief it sets the visibleWinSize property
		*
		* @param vWS is the visibleWinSize value
		* It sets the visibleWinSize value and it is measured in number of samples\n
		*/
		inline void setVisibleWinSize(int vWS) {visibleWinSize = vWS;}

		/*! \brief it returs the visibleStartPoint property
		*
		* @return visibleStartPoint value
		* It gets the visibleWinSize value. It is measured in number of samples where begins the visible window\n
		*/
		inline int VisibleStartPoint(void) {return visibleStartPoint;}
		
		/*! \brief it sets the visibleStartPoint property
		*
		* @param vSP is the visibleStartPoint value
		* It sets the visibleStartPoint value and it is measured in number of samples where begins the visible window\n
		*/
		inline void setVisibleStartPoint(int vSP) {visibleStartPoint = vSP;}
		
		/*! \brief it returs the min property
		*
		* @return min value
		* It gets the min value. It is measured in the same unit if the physical greatness of the channel\n
		*/
		inline double Min(void) {return min;}
		
		/*! \brief it sets the min property
		*
		* @param mn is the min value
		* It sets the min value and it is measured in the same unit if the physical greatness of the channel\n
		*/
		inline void setMin(double mn) {min = mn;}
		
		/*! \brief it returs the max property
		*
		* @return max value
		* It gets the max value. It is measured in the same unit if the physical greatness of the channel\n
		*/
		inline double Max(void) {return max;}
		
		/*! \brief it sets the max property
		*
		* @param mx is the max value
		* It sets the max value and it is measured in the same unit if the physical greatness of the channel\n
		*/
		inline void setMax(double mx) {min = mx;}
		
		/*! \brief it returs the visible property
		*
		* @return visible value
		* It gets the visible value. True if visible, false otherwise\n
		*/
		inline bool Visible(void) {return max;}
		
		/*! \brief it sets the visible property
		*
		* @param V is the visible value
		* It sets the visible value; true if visible and false otherwise\n
		*/
		inline void setVisible(bool V) {visible = V;}
		
		/*! \brief it returs the lineformat property
		*
		* @return lineformat value
		* It gets the lineformat value. It is expessed as a numeric consatnt defined in libidps.h (See www.idps.org)\n
		*/
		inline int Lineformat(void) {return lineformat;}
		
		/*! \brief it sets the lineformat property
		*
		* @param Lf is the lineformat value
		* It sets the lineformat value and it is expessed as a numeric consatnt defined in libidps.h (See www.idps.org)\n
		*/
		inline void setLineformat(int lF) {lineformat = lF;}

//		/*! \brief it returs the name property
//		*
//		* @return name value
//		* It gets the name value.\n
//		*/
//		inline QString Name(void) {return name;}
		
//		/*! \brief it sets the name property
//		*
//		* @param nm is the name value
//		* It sets the name value. \n
//		*/
//		inline void setName(QString nm) {name = nm;}
		
		/*! \brief it gest coda's elements number property
		*
		* @return the number of elements into the queue
		* It gets teh numers of elemnts into the queue. \n
		*/
		inline unsigned int count(void) {return coda.count();}
		
		/*! \brief it clear coda's elements and delete them
		*
		* It clear the elementinto the queue. \n
		*/
		inline void clear(void) {return coda.clear();}
		
		/*! \brief it add an element to the queue of the stream
		*
		* @param val is the value added to the tail of the queue
		* It adds to the tail of the queue the value. \n
		*/
		inline void enQueue(float val) {
			coda.enqueue(val);
			}
		 
		/*! \brief it extracts the head form the queue of the stream
		*
		* @param val is the pointer to the value extracted
		* @return true if the queue is not empty, false otherwise
		* It extracts the head form the queue; if the queue is empty it returns false and *val is meaningless; otherwise it returns true and val has the extracted value.
		*/
		inline bool deQueue(float* val) {
			if (coda.isEmpty()) return false;
			float res = coda.dequeue();
			if (val) *val = res;
			return true;
			}
};

#endif
