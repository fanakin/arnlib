/***************************************************************************
                          arnGraphVisualizer.cpp  -  description
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
* \file arnGraphVisualizer.h.
* \brief Gaphical Windows for arnGraphDataStream. It is the wrapper for handling idps server
*
* In this class we implement the component for wrapping the client / server mechanis of idps (www.idps.org). \n
* When it is called it build a local drawing server and predisposes all the stuff for drawing some datastream. \n
*
*/

#ifndef ArnGraphVisualizerH
#define ArnGraphVisualizerH

#include <qobject.h>
#include <QList>
#include "arnGraphDataStream.h"

class arnGraphVisualizer : public QObject
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
	
		int samplingTime; /*!< Tempo di campionamento per la costruzione dell'asse x; e' espresso in uS */
		int visibleWinSize; /*!< numero di campioni visibili */
	private slots:

	protected:
		char* hostname; /*!< the name of the hos machine running the idps server. In this implementation always 0 */
		int status; /*!< getting the actual status of the client / server idps system */
		QList<arnGraphDataStream *> *ChannelList; /*!< lista dei canali visualizzabili */
		//float samplingTime; /*!< Tempo di campionamento per la costruzione dell'asse x; e' espresso in uS */
		unsigned int viewPortID; /*!< ID della viweport dove visualizzare i dati */
	protected slots: 

	signals:

	public :
		/*! \brief Generic QObject inherited constructor
		*
		* See QObject.
		*/
		arnGraphVisualizer(QObject * parent = 0, const char * name = 0);
		
		/*! \brief Distructor
		*
		* It is in charge to distroy everything internal related stuff \n
		*/
		~arnGraphVisualizer(void);

//		/*! \brief it returs the samplingTime property
//		*
//		* @return samplingTime value
//		* It gets the samplingTime value. It is expressed in uS (microseconds)\n
//		*/
//		inline double SamplingTime(void) {return samplingTime;}
		
//		/*! \brief it sets the samplingTime property
//		*
//		* @param ST is the samplingTime value as uS (microseconds)
//		* It sets the samplingTime value and it is expessed ad uS (microseconds) \n
//		*/
//		inline void setSamplingTime(double ST) {samplingTime = ST;}

		/*! \brief It gets a channel of the list
		*
		* @param Label is name of the channel\n
		* @return the pointer to the channel of label if any, 0 otherwise\n
		*
		* This function allowes to access a channel of the channel list.\n
		* Using such a function allows to set all the parameter of a channel.\n
		* See arnGraphDataStream.
		* Ex:\n
		* ...\n
		*/
		arnGraphDataStream* Channel(const char* Label);
		
		/*! \brief It gets a channel of the list
		*
		* @param indx is the index of the channel into the channel list\n
		* @return the pointer to the channel of inmdex if any, 0 otherwise\n
		*
		* Overloaded function like the above. It as been implemented for speed needs.
		* Ex:\n
		* ...\n
		*/
		inline arnGraphDataStream* Channel(int indx) {
			if (indx < int(ChannelList->count())) {return ((arnGraphDataStream*)ChannelList->at(indx));}
			return 0;
			}
		
		/*! \brief It shows all the set datastream
		*
		* This function shows all the set datastream. \n
		*/
		void Show(void);

		/*! \brief  It hides all the set datastream
		*
		* This function hides all the set datastream. \n
		*/
		void Hide(void);

		/*! \brief  It updates the content of the graphical window
		*
		* This function updates the content of the window; it is very usefull to show changing on some. \n
		* or all set datastream. \n
		*/
		void Update(void);

		/*! \brief add a channel to the visualizer\n
		*
		* @param Label is name of the channel\n
		* @return true if adding has been successfull, false otherwise\n
		*
		* Adding a label means to add 2 QLabel objects: the former is\n
		* the real label, the latter is a QLabel where to display\n
		* the channel value really. This class at laest for now\n
		* doesn't matter about scaling the value. Elsewhere some other\n
		* agents have to do the right scaling before seeting the Channel\n
		* value.
		* Ex:\n
		* ...\n
		*/
		bool addChannel(const char* Label);

		/*! \brief delete a channel from the visualizer\n
		*
		* @param Label is name of the channel\n
		* @return true if deleting has been successfull, false otherwise\n
		*
		* Ex:\n
		* ...\n
		*/
		bool deleteChannel(const char* Label);

		/*! \brief loads a value into the stream \n
		*
		* @param Label is name of the channel\n
		* @param val value inserted\n
		* @return true if insertion has been successfull, false otherwise\n
		*
		* Ex:\n
		* ...\n
		*/
		bool PushValue(const char* Label, float val);

		/*! \brief loads a segment of data into the stream \n
		*
		* @param Label is name of the channel\n
		* @param bff is the segment to load\n
		* @param len is the length of the segment\n
		* @return true if insertion has been successfull, false otherwise\n
		*
		* Ex:\n
		* ...\n
		*/
		bool PushSegment(const char* Label, float *bff, unsigned int len);

		/*! \brief delete a channel from the visualizer\n
		*
		* @param indx is the index into the list of the channels\n
		* @param val value inserted\n
		* @return true if insertion has been successfull, false otherwise\n
		*
		* Ex:\n
		* ...\n
		*/
		bool PushValue(int indx, float val);

		/*! \brief  loads a value into the stream \n
		*
		* @param indx is the index into the list of the channels\n
		* @param bff is the segment to load\n
		* @param len is the length of the segment\n
		* @return true if insertion has been successfull, false otherwise\n
		*
		* Ex:\n
		* ...\n
		*/
		bool PushSegment(int indx, float *bff, unsigned int len);
		
		/*! \brief it checks the integrity and coherence of all the channel for one viewport visualization \n
		*
		* @return true if all the channels has the same Timebase, VisibleWinSize; false otherwise\n
		*
		* Ex:\n
		* ...\n
		*/
		bool CheckChannelList(void);
};

#endif
