/***************************************************************************
                          arnSObjectContainer.h  -  description
                             -------------------
    begin                : mar apr 26 2005
    copyright            : (C) 2005 by fabio giovagnini
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

#ifndef ArnSObjectContainerH
#define ArnSObjectContainerH

#include "arnlibtypes.h"
#include "arnObjectViewer.h"

typedef enum arnSingleObjectType {
	sot_ObjectContainer,
	sot_Variable,
	sot_Array,
	sot_Matrix,
	sot_NumericVariable,
	sot_StringVariable,
	sot_NumericArray,
	sot_StringArray,
	sot_MiscArray,
	sot_MiscNumericArray,
	sot_MiscMarkNumericArray,
	sot_NumericMatrix,
	sot_MiscMatrix,
	sot_MiscNumericMatrix,
	sot_MiscMarkNumericMatrix,
	sot_MiscMarkTraceNumericMatrix,
	sot_None
	} arnSingleObjectType_t;

// ---------------------------------------------------
// ***************************************************
// --------- arnSObjectContainer -------------------
// ***************************************************
// ---------------------------------------------------
class arnSObjectContainer : public QObject
{
	Q_OBJECT

	private:
		void init(void);
	protected:
		arnSingleObjectType_t tpe;
		NumericFixedFormat_t elemformat;
		NumericProcess_t filterT;
		unsigned char prc;
		unsigned long offst;
		unsigned long sze;
		double mn;
		double mx;
		double flr;
		double cil;
		unsigned char *pDataFrame;
		arnObjectViewer *pViewer;
		QString Comment;

		virtual void evalPrec(void);
		virtual double checkValue(double val);
	public:
		arnSObjectContainer ( QObject * parent = 0, const char * name = 0 );
		virtual ~arnSObjectContainer(void);
		inline arnSingleObjectType_t type(void) {return tpe;}
		virtual inline void setViewer(arnObjectViewer *pV) {pViewer = pV;}
		virtual inline void setFilterType(NumericProcess_t f) {filterT = f;}
		virtual inline void setComment(const QString& cm) {Comment = cm;}
		virtual inline void setFormat(NumericFixedFormat_t ft) {elemformat = ft;}
		inline void setOffset(unsigned long offs) {offst = offs;}
		inline unsigned long offset(void) {return offst;}
		inline void setSize(unsigned long sz) {sze = sz;}
		inline unsigned long size(void) {return sze;}
		inline double min(void) {return mn;}
		inline double max(void) {return mx;}
		inline double floor(void) {return flr;}
		inline double ceil(void) {return cil;}
		inline NumericProcess_t filterType(void) {return filterT;}
		inline void setDataFrame(unsigned char *pDF) {pDataFrame = pDF;}
		inline const unsigned char* DataFrame(void) {return pDataFrame;}
		inline const QString& comment(void) {return Comment;}
		inline NumericFixedFormat_t format(void) {return elemformat;}
		inline unsigned char prec(void) {return prc;}
		inline void setPrec(unsigned char pc) {prc = pc;}
		void setMin(double m);
		void setMax(double m);
		void setFloor(double f);
		void setCeil(double c);
};

#endif
